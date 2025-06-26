#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TABLE_SIZE 10

//node
struct person{
  char name[30];
  int age;
  struct person* link;//self referential => hash table is array of linked list
}*hashTable[TABLE_SIZE];

/*hash table
initialization
hash fn
insertion
deletion
search
printTable
destroy
*/

unsigned int hash(char* name){
  int i,hashAddress=0;
  for(i=0 ; name[i]!='\0' ; i++){
    hashAddress+=name[i];
    hashAddress=(hashAddress*name[i])%TABLE_SIZE;
  }
  return hashAddress;
}

struct person* newPerson(char* name,int age){
  struct person* new=(struct person*)malloc(sizeof(struct person));
  strcpy(new->name,name);
  new->age=age;
  new->link=NULL;
}


void initializeTable(){
  int i;
  for(i=0 ; i<TABLE_SIZE ; i++){
    hashTable[i]=newPerson("",0);//head of linked lists
  }
}

void printTable(){
  int i;
  printf("START\n");
  for(i=0 ; i<TABLE_SIZE ; i++){
    if(hashTable[i]->link==NULL)
      printf("\t%d  ------\n",i);
    else{
      struct person* ptr=hashTable[i]->link;
      printf("\t%d  ",i);
      while(ptr!=NULL){
        printf("%s -> ",ptr->name);
        ptr=ptr->link;
      }
      printf("\n");
    }
  }
  printf("END\n");
}

//insert at beginning
void insert(char* name,int age){
  int i;
  struct person* new=newPerson(name,age);
  unsigned int index=hash(name);
  
  new->link=hashTable[index]->link;
  hashTable[index]->link=new;
}

struct person* delete(char* name){
  int i;
  unsigned int index=hash(name);

  struct person* ptr=hashTable[index]->link,*prev=hashTable[index];//prev initialize imp
  while(ptr!=NULL && strcasecmp(ptr->name,name)!=0){
    prev=ptr;
    ptr=ptr->link;
  }
  if(ptr==NULL)
    return NULL;
  else
  {
    struct person* temp=ptr;
    prev->link=ptr->link;
    free(ptr);
    return temp;
  }
}

struct person* search(char* name){
  int i;
  unsigned int index=hash(name);
  
  struct person* ptr=hashTable[index]->link;
  while(ptr!=NULL && strcasecmp(ptr->name,name)!=0)
    ptr=ptr->link;
  if(ptr==NULL)
    return NULL;
  else
    return ptr;
}

void destroy(){
  int i;
  for(i=0 ; i<TABLE_SIZE ; i++){
    struct person* ptr=hashTable[i];
    while(ptr!=NULL){
      struct person* temp=ptr->link;
      free(ptr);
      ptr=temp;
    }
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
              insert(name,age);
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
      case 5: destroy();
              return;
    }
  }while(1);

}