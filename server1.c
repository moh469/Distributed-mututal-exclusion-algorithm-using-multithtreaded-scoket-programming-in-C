#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<string.h>
#include<pthread.h>



void *service(void *ptr)
{


int m;
int i ;
ssize_t rc;
m=*((int*)ptr);
char client_msg[20];
/* reading client request for file */
rc =read(m,client_msg,20);
  for(i=0;i<20;i++)
   {
    printf("%c",client_msg[i]);
    fflush(stdin);
    fflush(stdout); 
    
   }
   
int lsize;
FILE *fp;
int*s;
char*mtr;
char *str;
printf("going to read file");
fflush(stdin);
fflush(stdout); 

/* opening file for sending to client */

fp=fopen("thread15.c","r");
fseek (fp , 0 , SEEK_END);
lsize = ftell (fp);
rewind (fp);
s=&lsize;
printf("%d",sizeof(s));
fflush(stdin);
    fflush(stdout); 

 /* sending  size of file  to client */
 
write(m,s,sizeof(s));

/* creating buffer for holding file */
str = (char*) malloc (sizeof(char)*lsize);
  if (str == NULL) {fputs ("Memory error",stderr); exit (2);}

/* writing file into buffer */
fread(str,1,lsize,fp);
    printf("%d",lsize);
    printf("file read");
    fflush(stdin);
    fflush(stdout); 
    printf("%s",str);
    fflush(stdin);
    fflush(stdout); 
 
 /* sending file to client  */
write(m,str,lsize);
    printf("file write");
    fflush(stdin);
    fflush(stdout); 
  

close(m);


}



int  main ()

{


pthread_t tid[40];
void *k;
struct sockaddr_in client ,server ;
int n,l,i,m,child,size1,size2 ,j ;

n=socket(AF_INET, SOCK_STREAM, 0); 
  if (n == -1)
   {
    printf("error in socket creation  ");
   }
  
bzero(&server,sizeof(server));
server.sin_family =AF_INET;
server.sin_addr.s_addr = htonl(INADDR_ANY);
server.sin_port=htons(9877);
 
j= bind(n,(const struct sockaddr *)&server,sizeof(server));
  if(j==-1)
    printf("error in bind");
    fflush(stdin);
    fflush(stdout); 
 
  if(j==0)
    printf("binding connection is ok");
    fflush(stdin);
    fflush(stdout); 
 
l= listen(n,5);
if(l==0)
  printf(" listen connection is ok ");
  fflush(stdin);
  fflush(stdout);
if(l==-1)
  printf("error in listening connection  ");
  fflush(stdin);
  fflush(stdout);

for(; ;)
{
   m=accept(n,0,0);
   k=&m;
   if(m==-1)
     {
      printf("error in accepting connection");
      fflush(stdin);
      fflush(stdout);
      }
   else
    { 
     printf(" accept connection is ok ");
     fflush(stdin);
     fflush(stdout);
     }
   pthread_create(tid,NULL ,service,k);
}
close(n);
  
}


