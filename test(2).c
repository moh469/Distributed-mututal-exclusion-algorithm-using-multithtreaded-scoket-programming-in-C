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
#include <pthread.h>



/* global variable*/
         int k;
         int pid=0;
         int flag;
         int cs;
         pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
         pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
         pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;
         pthread_mutex_t mutex4 = PTHREAD_MUTEX_INITIALIZER;
         int dq[9];
         char ipdq[9][17];
         int port[10];
         int m;

/* message structure which is to be sent */
struct  msg
{
         int a;
         int qid;
         int d[10];
         char iparr1[17];
         int port1;
}; 




/* message structure where message is to be stored */
struct c_msg
{
        int b;
        int mid;
        int c[10];
        char iparr2[17];
        int port2;
};
struct msg ms ;
struct c_msg c_ms;

f()
{
fflush(stdin);
fflush(stdout);
}

/* comparison operation */
comparison()
{
       int i,j,y;
       int mark=1;
       int glass =0;
        
       for(i=1;i<10;i++)
       {
       
       if(c_ms.c[i]<=ms.d[i])
       {
       i++;
       }
       else
       {
       mark=0;
       i++;
       }
       
       }
       
       for(y=1;y<10;y++)
       {
       printf("data mean ");
       f();
       if((c_ms.c[y])!=(ms.d[y]))
       {
       glass=1;
       
       }
       
       }
      
       if(glass==1 && mark==1)
       return 1;
       else
       return 0;
 }

/* recieve thread */



void * receive()
{      int i=pid;
       int x ;
       int n;
       int count=1;
     /*  int m;
       m=*((int*)ptr); */
       k=0;
       int t ;
       struct sockaddr *mo ;
       socklen_t z;
       for(n=1;n<2;n++)
       {
       c_ms.b=4;
       
/* receiving message */
      
/* incrementing vector clock before receiving data */       
       pthread_mutex_lock(&mutex3);
       ms.d[i]=ms.d[i]+1;
       pthread_mutex_unlock(&mutex3);
      	 printf("data mean is ");
       f();
       x=recvfrom(m,&c_ms,100,0,mo,&z);
       printf("%d",c_ms.b);
       f();				
       if(x==-1) 
       {
       printf("error in receiving data");
       f();
       }
       else
       {
       printf("data is received ");
       f();
       } 
/* comparing maximum value of vector clock */       
       pthread_mutex_lock(&mutex3);
       for(i=0;i<10;i++)
       {
       
       if(ms.d[i] < c_ms.c[i])
        ms.d[i]=c_ms.c[i];
       }
	pthread_mutex_unlock(&mutex3);   
/* sending reply */
       i =pid;
       if(c_ms.b==1)
       {
      
       t=comparison();
       printf("socket ");
   	f();
        
       if( (flag==1 && t==1) || (flag==0 && cs==0))
       {
/* setting flag for reply message */
       pthread_mutex_lock(&mutex1);
       ms.a=0;
       pthread_mutex_unlock(&mutex1);
/* incementing vector clock */      
       pthread_mutex_lock(&mutex3);
       ms.d[i]=ms.d[i]+1;
       pthread_mutex_unlock(&mutex3);
       strcpy(  ms.iparr1,"192.168.2.142 \0");
       ms.port1=9877;
       
       
       sendto(m,&ms,100,0,mo,z);
       }
      
 /* deffered queue value assignment */
       else 
       {
       pthread_mutex_lock(&mutex4);
       dq[k]=c_ms.mid;
 /* storing ip address in ip address queue */
      strcpy(ipdq[dq[k]],c_ms.iparr2);
/* storing  port no in port queue */       
       port[dq[k]]=c_ms.port2;
       k=k+1;
       pthread_mutex_unlock(&mutex4);
       }
       }
/* end of outer if loop */
       else
       {
       count =count+1 ;
       if(count==9)
       {
/* got all the reply messages from all the processes for entering critical section */
       pthread_mutex_lock(&mutex2);
       cs=1;
       pthread_mutex_unlock(&mutex2);
       }
       }
       }
/* end of while loop */ 
} 
/* end of receive thread */ 


/* main  function */ 

int  main ()
{       
        int cs =0;
        pthread_t id;
        int j;
        int i ;
        int x ;
	int on=1;
	struct sockaddr_in client ,server,merver ;
	// int m;
	char server_msg[20]="give me file";
	char c_msg[40];
	socklen_t t;
	ssize_t p,q;
	struct sockaddr *so ;
/* saving process id in message */
	ms.qid=pid;
/* intilizing vector clock value */

	 

	for(i=1;i<11;i++)
	{ 
	
	ms.d[i]=0;
	}
	
	  
/* socket creation */
	
	m=  socket(AF_INET, SOCK_DGRAM, 0);
	 
	if (m == -1)
   	{
      	printf("error in socket creation %d", errno );
      	f();
   	}
   	
   	else 
   	{
   	
   	printf("socket is created");
   	f();
 	}
/* clients own addresss */ 	
 	client.sin_family =AF_INET;
	client.sin_port = htons(9878);
	client.sin_addr.s_addr = htonl(INADDR_ANY);
	
/* binding connection */  	
	
	j= bind(m,(const struct sockaddr *)&client,sizeof(client));
  	if(j==-1)
    	printf("error in bind");
    	f();
 	if(j==0)
    	printf("binding connection is ok");
    	f();
 	
 /* server's address where request message is to be broad casted */	
 	
 	server.sin_family =AF_INET;
	server.sin_port = htons(9880);
	inet_pton(AF_INET, "127.0.0.1", &(server.sin_addr));
	so=&server;
	t=sizeof(server);
/* thread creation for receiving data */
        pthread_create(&id,NULL,receive,NULL);
        pthread_mutex_lock(&mutex1);
/*set this variable as 1 to show that it is request message from the procees */
 	ms.a=1;
 	pthread_mutex_unlock(&mutex1);
 	 i =pid;
/* incrementing vector clock before sending */
 	pthread_mutex_lock(&mutex3);
 	ms.d[i]=ms.d[i]+1;
 	pthread_mutex_unlock(&mutex3);
 /* assigning ip address to message */
 	strcpy(  ms.iparr1,"192.168.2.142 \0");
	setsockopt(m,SOL_SOCKET,SO_BROADCAST,&on,sizeof(on));

/* sending request message */ 
        sleep(5);    
        p= sendto(m,&ms,100,0,so,t);
        if(p==-1) 
        {
        printf("error in sending  data");
        f();
        }
        else
        {
        
        printf("data is sent ");
        f();
        } 
        

/* flag for showing that a request has been sent by this process */
        flag=1;
        i =0;
/* critical section execution */
        while(i==0)
        {
      /*  printf("waiting for critical section execution  ");*/
        f();
        pthread_mutex_lock(&mutex2);
        if(cs==1)
        {
        printf("critical section executed ");
        i=1;
        }
        pthread_mutex_unlock(&mutex2);
        }
        merver.sin_family =AF_INET;
	
	
	
        
        pthread_mutex_lock(&mutex1);
        ms.a=0;
        pthread_mutex_unlock(&mutex1);
 /* send reply to defered queue requests */       
        for(i=0;i++;i<k)
        {
        merver.sin_port = htons(port[i]);
        inet_pton(AF_INET, ipdq[i], &(merver.sin_addr));
        so=&merver;
	t=sizeof(merver);
        
        sendto(m,&ms,100,0,so,t); 
        }
        
	close(m);
  
}


