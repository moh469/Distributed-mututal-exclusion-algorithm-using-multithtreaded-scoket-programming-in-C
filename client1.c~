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




int  main ()
{

ssize_t wc;
ssize_t rc=1;
struct sockaddr_in client ,server ;
int m,i,size1,size2 ,l ;
char server_msg[20]="give me file";
int lsize;
int *s;
s=&lsize;

FILE*fp;
 char *str;
/* opening file for writing */
fp= fopen("mos","w");
if(fp==NULL)
{ 
 printf("error in opening file");
 fflush(stdin);
 fflush(stdout);
 }
m=  socket(AF_INET, SOCK_STREAM, 0); 
if (m == -1)
   {
      printf("error in socket creation %d", errno );
   }
client.sin_family =AF_INET;
client.sin_port = htons(9877);
inet_pton(AF_INET, "127.0.0.1", &(client.sin_addr));
/* connecting to server */
l= connect(m, (const struct sockaddr *)&client,sizeof(client));
if(l==0)
{
   printf("conection established ");
   fflush(stdin);
   fflush(stdout);
}

if(l==-1)
 {
   printf("trying to connect ");
   fflush(stdin);
   fflush(stdout);
  }
/* requesting for file */
 
write(m,server_msg,20);
 
 /*reading size of file*/
 
read(m,s,sizeof(s));
printf("%d",lsize);
fflush(stdin);
fflush(stdout);
 /*allocating memory for file */

str = (char*) malloc (sizeof(char)*lsize);


   if (str == NULL)
     {
      fputs ("Memory error",stderr); 
      exit (2);
     }
/* reading  file from server */     
rc =read(m,str,lsize);
printf("%d",rc);
fflush(stdin);
fflush(stdout);
printf("%s",str);
fflush(stdin);
fflush(stdout);
 /* writing   file from server to a  file on client side */  
fwrite(str,1,strlen(str),fp);
fseek (fp , 0 , SEEK_END);
close(m);
  
}


