#include<stdio.h>
#include<stdlib.h>
#define SIZE 10
void display();
struct process{
    int pid;
    int arr_time;
    int burst_time;
    int priority;
    int res_time;
    int comp_time;
    int completed;
    int turnaround_time;
    int waiting_time;
    int rem_time;
    int isfirst;
}*p[SIZE];
int n,ts;
void sort(){
    int i,j;

    for(i=0 ; i<n ; i++)
        for(j=0 ; j<n-i-1 ; j++){
            if(p[j]->arr_time > p[j+1]->arr_time){
                struct process temp=*p[j];
                *p[j]=*p[j+1];
                *p[j+1]=temp;
            }
        }
}

void fcfs(){
    int sys_time=0,i,avgtt=0,avgwt=0;

    for(i=0 ; i<n ; i++){
        if(sys_time >= p[i]->arr_time){
            p[i]->res_time=sys_time-p[i]->arr_time;
            p[i]->comp_time=sys_time+p[i]->burst_time;
            p[i]->turnaround_time=p[i]->comp_time-p[i]->arr_time;
            p[i]->waiting_time=p[i]->turnaround_time-p[i]->burst_time;

            avgtt+=p[i]->turnaround_time;
            avgwt+=p[i]->waiting_time;

            sys_time+=p[i]->burst_time;
            p[i]->rem_time=0;
        }else{
            sys_time++;
            i--;//imp
        }
    }
    avgtt/=n;
    avgwt/=n;
    display();
    printf("\navg waiting time=%d\n",avgwt);
    printf("avg turn around time=%d\n\n\n",avgtt);
}

int remain(){
    int i;
    for(i=0 ; i<n ; i++)
        if(!p[i]->completed)
            return 1;
    return 0;
}

void sjf(){
    int sys_time=0,i,j,min_time,min_index,k,avgtt=0,avgwt=0;
    struct process* temp[SIZE];
    while(remain()){
        j=0;
        for(i=0 ; i<n ; i++){
            if(!p[i]->completed && sys_time >= p[i]->arr_time)  
                temp[j++]=p[i];
        }
        if(j==0){
            sys_time++;
            continue;
        }
        min_time=temp[0]->burst_time;
        min_index=0;
        for(k=1 ; k<j ; k++){
            if(temp[k]->burst_time < min_time){
                min_index=k;
                min_time=temp[k]->burst_time;
            }
        }

        temp[min_index]->res_time = sys_time - temp[i]->arr_time;
        temp[min_index]->comp_time = sys_time + temp[min_index]->burst_time;
        temp[min_index]->turnaround_time = temp[min_index]->comp_time-temp[min_index]->arr_time;
        temp[min_index]->waiting_time=temp[min_index]->turnaround_time-temp[min_index]->burst_time;
        sys_time+=temp[min_index]->burst_time;

        avgtt += temp[min_index]->turnaround_time;
        avgwt += temp[min_index]->waiting_time;

        temp[min_index]->completed=1;
        temp[min_index]->rem_time=0;
    }
    avgtt /= n;
    avgwt /= n;
    display();
    printf("\navg waiting time=%d\n",avgwt);
    printf("avg turn around time=%d\n\n\n",avgtt);
}

void priority_sched(){
    int sys_time=0,i,j,max_priority,max_index,k,avgtt=0,avgwt=0;
    struct process *temp[SIZE];
    for(i=0 ; i<n ; i++)
        p[i]->completed=0;
    while(remain()){
        j=0;
        for(i=0 ; i<n ; i++){
            if(!p[i]->completed && sys_time >= p[i]->arr_time)  
                temp[j++]=p[i];
        }
        if(j==0){
            sys_time++;
            continue;
        }
        max_priority=temp[0]->priority;
        max_index=0;
        for(k=1 ; k<j ; k++){
            if(temp[k]->priority < max_priority){
                max_index=k;
                max_priority=temp[k]->priority;
            }
        }

        temp[max_index]->res_time = sys_time-temp[i]->arr_time;
        temp[max_index]->comp_time = sys_time+temp[max_index]->burst_time;
        temp[max_index]->turnaround_time = temp[max_index]->comp_time - temp[max_index]->arr_time;
        temp[max_index]->waiting_time = temp[max_index]->turnaround_time - temp[max_index]->burst_time;
        sys_time+=temp[max_index]->burst_time;

        avgtt+=temp[max_index]->turnaround_time;
        avgwt+=temp[max_index]->waiting_time;

        temp[max_index]->completed=1;
        temp[max_index]->rem_time=0;
    }
    avgtt /= n;
    avgwt /= n;
    display();
    printf("\navg waiting time=%d\n",avgwt);
    printf("avg turn around time=%d\n\n\n",avgtt);
}
int Q[SIZE],f=-1,r=-1;

void enqueue(int item){
    if(f==(r+1)%SIZE){
        printf("queue full\n");
        return;
    }else if(f==-1)
            f=r=0;
        else    
            r=(r+1)%SIZE;
    Q[r]=item;
}

int dequeue(){
    if(f==-1){
        printf("Queue empty\n");
    }else{
        int item=Q[f];
        if(f==SIZE-1)
            f=0;
        else
            f++;
        if(f==(r+1)%SIZE)   
            f=r=-1;
        return item;
    }
}

void round_robin(){
    int sys_time=0,i,j,avgtt=0,avgwt=0;

    for(j=0 ; j<n ; j++){
        p[j]->completed=0;
        p[j]->rem_time=p[j]->burst_time;
        p[j]->isfirst=1;
        enqueue(j);
    }

    while(remain()){
        i=dequeue();
        if(sys_time >= p[i]->arr_time && !p[i]->completed){
            if(p[i]->rem_time < ts){
                if(p[i]->isfirst){
                    p[i]->res_time=sys_time - p[i]->arr_time;
                    p[i]->isfirst=0;
                }

                p[i]->completed=1;
                sys_time += p[i]->rem_time;
                p[i]->rem_time=0;

                p[i]->comp_time=sys_time;
                p[i]->turnaround_time=p[i]->comp_time - p[i]->arr_time;
                p[i]->waiting_time=p[i]->turnaround_time-p[i]->burst_time;
                avgtt+=p[i]->turnaround_time;
                avgwt+=p[i]->waiting_time;
            }else{
                if(p[i]->isfirst==1){
                    p[i]->res_time=sys_time-p[i]->arr_time;
                    p[i]->isfirst=0;
                }

                p[i]->rem_time-=ts;
                sys_time+=ts;
                if(p[i]->rem_time==0){
                    p[i]->completed=1;
                    p[i]->comp_time=sys_time;
                    p[i]->turnaround_time=p[i]->comp_time-p[i]->arr_time;
                    p[i]->waiting_time=p[i]->turnaround_time-p[i]->burst_time;
                    avgtt+=p[i]->turnaround_time;
                    avgwt+=p[i]->waiting_time;
                }else
                    enqueue(i);//imp
            }
        }else{
            if(!p[i]->completed)
                sys_time++;//sorted in order of arr time
        }
    }
    avgtt /= n;
    avgwt /= n;
    display();
    printf("\navg waiting time=%d\n",avgwt);
    printf("avg turn around time=%d\n\n\n",avgtt);
}

void display(){
    int i;
    printf("PID  Arr_Time  Burst_Time  Response_Time  Completion_Time  TurnAround_tIme  Waiting_Time\n");
    for(i=0 ; i<n ; i++){
        printf("%-5d%-10d%-12d%-15d%-17d%-17d%-d\n",p[i]->pid,p[i]->arr_time,p[i]->burst_time,p[i]->res_time,p[i]->comp_time,p[i]->turnaround_time,p[i]->waiting_time);
    }
}

void main(){
    int i;
    printf("How many processes?");
    scanf("%d",&n);

    printf("ENter the arrival time of %d processes: \n",n);
    for(i=0 ; i<n ; i++){
        p[i]=(struct process*)malloc(sizeof(struct process));
        scanf("%d",&(p[i]->arr_time));
        p[i]->pid=i+1;
    }

    printf("ENter the burst time of %d processes: \n",n);
    for(i=0 ; i<n ; i++){
        scanf("%d",&(p[i]->burst_time));
        p[i]->rem_time=p[i]->burst_time;
        p[i]->completed=0;
    }

    printf("ENter the  priorities of %d processes: \n",n);
    for(i=0 ; i<n ; i++)
        scanf("%d",&(p[i]->priority));

    printf("Enter the time quantum for round robin scheduling: ");
    scanf("%d",&ts);

    sort();

    printf("The given table is: \n");
    printf("PID  Arr_Time  Burst_Time  Priority\n");
    for(i=0 ; i<n ; i++){
        printf("%-5d%-10d%-12d%-d\n",p[i]->pid,p[i]->arr_time,p[i]->burst_time,p[i]->priority);
    }

    printf("\n\nFCFS\n");
    fcfs();

    printf("SJF:\n");
    sjf();

    printf("PRIORITY SCHEDULING:\n");
    printf("[NOTE: we assumed that lower no denotes higher priority]\n");
    priority_sched();

    printf("ROUND ROBIN:\n");
    round_robin();
}