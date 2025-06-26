#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student
{
  int no;
  char name[30];
  int tmark;
  struct student* link;
};
struct student *head;

void InsertBeg(int num,char name[],int tmarks)
{
  struct student* new=(struct student*)malloc(sizeof(struct student));
  if(new==NULL)
    printf("no space in heap\n");
  else
  {
    new->no=num;
    strcpy(new->name,name);
    new->tmark=tmarks;
    new->link=head->link;
    head->link=new;
  }
}
char* delete(int num)
{
  char* s=(char*)malloc(sizeof(char)*30);
  struct student* ptr=head->link,*prev=head;//prev should be initialized
  if(ptr==NULL)
  {
    printf("List empty");
    return NULL;
  }
  else
  {
    while(ptr!=NULL && ptr->no!=num)
    {
      prev=ptr;
      ptr=ptr->link;
    }
    if(ptr==NULL)
    {
      printf("student with no %d not found\n",num);
      return NULL;
    }
    else
    {
      strcpy(s,ptr->name);
      //s=ptr->name; you cant do this
      prev->link=ptr->link;
      free(ptr);
      return s;//address of a local variable having memory allocated in stack 
    }//cannot be returned .but pointer types an variables whose memory is allocated
  }//during runtime can be returned
}

struct student* Search(int num)
{
  struct student* ptr=head->link;
  if(ptr==NULL)
  {
    printf("List empty\n");
    return NULL;
  }
  while(ptr!=NULL && ptr->no!=num)
    ptr=ptr->link;

   return ptr;
}

void swap(struct student* i,struct student* j)
{
  struct student temp;
  temp=*i;
  *i=*j;
  *j=temp;
}
void Sort()
{
  struct student *i,*j;
  i=head->link;
  while(i!=NULL && i->link!=NULL)
  {
    j=i->link;
    while(j!=NULL)
    {
      if(i->no>j->no)
      {
        struct student *ilink,*jlink;
        ilink=i->link;
        jlink=j->link;
        /*temp=*i;
        *i=*j;
        *j=temp;*/
        swap(i,j);
        i->link=ilink;//or i->link <-> j->link
        j->link=jlink;
      }
      j=j->link;
    }
    i=i->link;
  }
}

void display()
{
  struct student* ptr=head->link;
  int i=1;
  if(ptr==NULL)
    printf("List empty\n");
  else
  {
    while(ptr!=NULL)
    {
      printf("\nSTUDENT %d:\n",i++);
      printf("NAME: %s\n",ptr->name);
      printf("ROLL NO: %d\n",ptr->no);
      printf("TOTAL MARKS: %d\n",ptr->tmark);
      ptr=ptr->link;
    }
  }
}

void returnNode()
{
  struct student* ptr=head;
  while(ptr!=NULL)
  {
    struct student* temp=ptr->link;
    free(ptr);
    ptr=temp;
  }
}
void main()
{
  int choice,num,key,tmarks;
  struct student* stud;
  char *name;
  head=(struct student*)malloc(sizeof(struct student));
  head->link=NULL;
  do
  {
    printf("\nEnter your choice:\n1)INSERT(at beg)\n2)DELETE\n3)SEARCH\n4)SORT\n5)DISPLAY\n6)EXIT\n");
    scanf("%d",&choice);

    switch(choice)
    {
      case 1:printf("Enter the student details:\n");
            printf("NUMBER: ");
            scanf("%d",&num);
            printf("NAME: ");
            scanf(" %[^\n]",name);
            printf("TOTAL MARKS: ");
            scanf("%d",&tmarks);
            InsertBeg(num,name,tmarks);
            break;
      case 2:printf("Enter the number of the student to be deleted: ");
            scanf("%d",&num);
            name=delete(num);
            printf("Deleted student is %s\n",name);
            break;
      case 3:printf("Enter the number of student to be searched: ");
            scanf("%d",&key);
            stud=Search(key);
            if(stud!=NULL)
            {
              printf("Student with num %d is present\n",key);
              printf("Details are:\n");
              printf("NAME:%s\n",stud->name);
              printf("Total marks: %d\n",stud->tmark);
            }
            else
              printf("Student with num %d is absent in the list\n",key);
            break;
      case 4:Sort();
            printf("sorted list: \n");
            display();
            break;
      case 5:display();
            break;
      case 6:returnNode();
            return;
      default:returnNode();
              return;
    }
  }
  while(1);
}