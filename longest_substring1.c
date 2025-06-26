#include<stdio.h>
#include<string.h>
void main()
{
  char str[30],subs[10],longest[20];
  int i,j,count[256],len,larlen=0,lastindex[256];

  printf("Enter a string: ");
  scanf(" %[^\n]",str);

  i=0;
  while(str[i])
  {
    for(j=0 ; str[j] ; j++)
      count[str[j]]=0;
    j=0;
    if(i!=0)
      i=lastindex[str[i]]+1;
    while(str[i])
    {
      count[str[i]]++;
      if(count[str[i]]==1)
      { 
          lastindex[str[i]]=i;
          subs[j++]=str[i++];
      }
      else
        break;
    }
    subs[j]='\0';
    len=j;
    if(len>larlen)
    {
      larlen=len;
      strcpy(longest,subs);
    }
  }
  printf("The longest substring is %s\nlength=%d\n",longest,larlen);
}