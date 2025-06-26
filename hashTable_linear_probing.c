#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TABLE_SIZE 10
#define DELETED_NODE (struct person*)0xffffffff

struct person{
  char name[30];
  int age;
}*hashTable[TABLE_SIZE];

unsigned int hash(char* name){
  int i,hashAddress=0;
  for(i=0 ; name[i]!='\0' ; i++){
    hashAddress+=name[i];
    hashAddress=(hashAddress*name[i])%TABLE_SIZE;
  }
  return hashAddress;
}

void initializeTable(){
  int i;
  for(i=0 ; i<TABLE_SIZE ; i++){
    hashTable[i]=NULL;
  }
}

//3 states 1)NULL 2)DELETED 3)PRESENT
void printTable(){
  int i;
  printf("START\n");
  for(i=0 ; i<TABLE_SIZE ; i++){
    if(hashTable[i]==NULL)
      printf("\t%d  ------\n",i);
    else if(hashTable[i]==DELETED_NODE)
            printf("\t%d  <deleted>\n",i);
          else
            printf("\t%d  %s\n",i,hashTable[i]->name);
  }
  printf("END\n");
}

struct person* newPerson(char* name,int age){
  struct person* new=(struct person*)malloc(sizeof(struct person));
  strcpy(new->name,name);
  new->age=age;
}

int insert(char* name,int age){
  int i;
  struct person* new=newPerson(name,age);
  unsigned int u=hash(name);
  printf("\nPROBE SEQUENCE: <");//do last
  for(i=0 ; i<TABLE_SIZE ; i++){
    int index=(u+i)%TABLE_SIZE;
    printf("%d,",index);//
    if(hashTable[index]==NULL || hashTable[index]==DELETED_NODE){
      hashTable[index]=new;
      printf("\b>\n\n");//
      return 1;
    }
  }
  printf("Table Overflow\n");
  return 0;
}

struct person* delete(char* name){
  int i;
  unsigned int u=hash(name);

  for(i=0 ; i<TABLE_SIZE ; i++){
    int index=(u+i)%TABLE_SIZE;
    if(hashTable[index]==NULL)
      return NULL;
    else if(hashTable[index]==DELETED_NODE)
            continue;
          else  if(strcasecmp(hashTable[index]->name,name)==0){
              struct person* p=hashTable[index];
              hashTable[index]=DELETED_NODE;
              return p;
    }
  }
  return NULL;
}

struct person* search(char* name){
  int i;
  unsigned int u=hash(name);
  for(i=0 ; i<TABLE_SIZE ; i++){
    int index=(u+i)%TABLE_SIZE;
    if(hashTable[index]==NULL)
      return NULL;
    else if(hashTable[index]==DELETED_NODE)
            continue;
          else if(strcasecmp(hashTable[index]->name,name)==0){
            return hashTable[index];
    }
  }
  return NULL;
}

void destroy(){
  int i;
  for(i=0 ; i<TABLE_SIZE ; i++){
    free(hashTable[i]);
  }
}

void main(){
  int choice,age;
  char name[30];
  struct person* p;
  initializeTable();
//  printTable();
  do{
    printf("Enter your choice: \n1)INSERT\n2)DELETE\n3)SEARCH\n4)DISPLAY\n5)EXIT\n");
    scanf("%d",&choice);

    switch(choice){
      case 1: printf("Enter the name: ");
              scanf("%s",name);
              printf("Enter age: ");
              scanf("%d",&age);
              if(insert(name,age))
                printf("insertion success\n");
              else
                printf("insertion failed\n");
              printTable();
              break;
      case 2: printf("Enter name of person to be deleted: ");
              scanf(" %s",name);
              p=delete(name);
              if(p!=NULL){
                printf("deletion success\nDETAILS: \n");
                printf("age: %d\n",p->age);
              }else
                printf("not deleted\n");
              printf("After deletion:\n");
              printTable();
              break;
      case 3: printf("Enter name of person to be searched: ");
              scanf(" %s",name);
              p=search(name);
              if(p!=NULL){
                printf("%s FOUND\n",name);
                printf("age: %d\n",p->age);
              }else
                printf("%s not FOUND\n",name);
              break;
      case 4: printTable();
              break;
      case 5:  destroy();
              return;
    }
  }while(1);

}