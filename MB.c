#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <time.h>
#include <math.h>

int gcd(int a, int h) 
{ 
    int temp; 
    while (1) 
    { 
        temp = a%h; 
        if (temp == 0) 
          return h; 
        a = h; 
        h = temp; 
    } 
}

int powMod(int a, int b, int n) {
	long long x = 1, y = a;

	while (b > 0) {
		if (b % 2 == 1)
			x = (x * y) % n;
		y = (y * y) % n; // Squaring the base
		b /= 2;
	}

	return x % n;
}



int LetterAsc(int e, int n,char  *m1,int l,char *ms1){
  // char ms1[256];
   
    for (int j=0;j<l;j++){
    int tmp1=(int) m1[j]; // convert to ascii
    printf("the %c is %d ",m1[j],tmp1);   
    int tmp3=powMod(tmp1, e, n); // encyption with rsa
    // convert the int to char and concatenate again
    printf(" enc is %d\n",tmp3);
    char tmp2[10];
    sprintf(tmp2,"%d",tmp3); // int to char 
    if(tmp3<1000)
      {
	if(j==0){
	  strcpy(ms1,"0");
		 
	}else{
	  strcat(ms1,"0");}
	strcat(ms1,tmp2); 	
      }
    else{
      if(j==0){
	strcpy(ms1,tmp2);
      }else{
	strcat(ms1,tmp2);}} // concat}
  }


}
int CRSA(int e,int n,char  *m1,int l,char *ms1){

  for(int i=0;i<l;i+=4){
    int t=((int)m1[i]-48)*1000+((int)m1[i+1]-48)*100+((int)m1[i+2]-48)*10+((int)m1[i+3]-48);
    printf("original is %d ",t);
    int tmp3=powMod(t, e, n);
     printf(" enc is %d\n",tmp3);
    char tmp2[10];
    sprintf(tmp2,"%d",tmp3); // int to char 
    if(tmp3<1000)
      {
	if(i==0){
	  strcpy(ms1,"0");
		 
	}else{
	  strcat(ms1,"0");}
	strcat(ms1,tmp2); 	
      }
    else{
      if(i==0){//first time
	strcpy(ms1,tmp2);
      }else{
	strcat(ms1,tmp2);}} // concat}
  
  }//for

  return 0;
}


int IntiB(){
  int fd;//handle for Bob and MidB
     // socket initialize
  fd=socket(AF_INET,SOCK_STREAM,0);

     struct sockaddr_in saddr;
     saddr.sin_family = AF_INET;
     saddr.sin_port = htons(9052);
     saddr.sin_addr.s_addr = INADDR_ANY;
     int cs=connect(fd,(struct sockaddr *)& saddr,sizeof( saddr));

     
  return fd;
}


int YMHandShake(int fd,char *respond, int s )
{
   //for handshake d would be 2011; e would 3 n would be 3127;
  
  int p = 59;
  int q = 53;
  int n = p*q;
  int phi = (p-1)*(q-1);
  int e2 = 3; // Pub Key K2 for handshake with MB
  int k = 2;  // A constant value 
  int d2 = (1 + (k*phi))/e2; // Private Key for handshake with MB Keep Secrete

  //handshake keyword  rules 
  char result[256]="attack";
  
  char rule2[]="luckily";
  char rule1[256];
  
  LetterAsc(e2,n,result,strlen(result),rule1);

     
    
     //     printf("the message is %s\n",rule1);
     // sleep(5);
     
     // recv(fd, respond,sizeof( respond),0);
  char first[256];
  recv(fd,first,sizeof(first),0);
  printf("the shake hand %s\n",first);
  printf("sending the 1st enc %s\n",rule1);
  int r=send(fd,rule1,sizeof(rule1),0);
  
  recv(fd,respond,s,0);
  
  
  return 0;
}


int MidBoxForward(char *m,int l){
  int hs;//as server ID
  //another connect between MidB and destination Alice
  hs=socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in hsa;
  hsa.sin_family = AF_INET;
  hsa.sin_port = htons(9053);
  hsa.sin_addr.s_addr = INADDR_ANY;
  //

  bind(hs,(struct sockaddr *)&hsa,sizeof(hsa));

  listen(hs,3);

  int alice;
  alice=accept(hs,NULL,NULL);
  send(alice,m,l,0);

  close(hs);
  


  return 0;
}



int main(){

  // socket b 
   int fd=IntiB();
    //preset encrypted rule for simple test
   // char r1[]="271652352327169292386";
  
  //
   
   int p = 59;
  int q = 53;
  int n = p*q;
  int phi = (p-1)*(q-1);
  int e2 = 3; // Pub Key K2 for handshake with MB
  

  char respond[256];
  int s=sizeof(respond);
  YMHandShake(fd,respond,s);
  
  printf("%s got \n", respond);//got the rule
  char m1a[256];
  char m1t[256];
  char m2a[256];
  char m2t[256];
  recv(fd,&m1a,sizeof(m1a),0);//original
  recv(fd,&m1t,sizeof(m1t),0);//token
  recv(fd,&m2a,sizeof(m2a),0);
  recv(fd,&m2t,sizeof(m2t),0);//token
  char c1t[256];
  char c2t[256];
  CRSA(e2,n,m1t,strlen(m1t),c1t);
  CRSA(e2,n,m2t,strlen(m2t),c2t);
  printf(" 1st cmr is %s\n",m1t);
  printf(" the token is %s\n",c1t);
  if(strcmp(c1t, respond)==0)
       printf(" catch a malicious the message is blocked \n");
  else
       printf(" pass to A\n");
  // MidBoxForward(m2a,sizeof(m2a));
  if(strcmp(c2t, respond)==0)
       printf(" catch a malicious \n");
  else{
    
    printf(" pass to A the enc mes is %s\n",m2a);
    MidBoxForward(m2a,sizeof(m2a));

  }



     
     //     int r=send(fd,rule1,sizeof(rule1),0);
     // printf("%d \n",r);
     close(fd);
     return 0;
     



}
