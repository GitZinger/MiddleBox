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


int LetterAsc(int e, int n,char *m1,int l,char *ms1,int u){
  //    char ms1[256];
   
    for (int j=0;j<l;j++){
    int tmp1=(int) m1[j]; // convert to ascii
    printf("the %c is %d ",m1[j],tmp1);   
    int tmp3=powMod(tmp1, e, n); // encyption with rsa
    // convert the int to char and concatenate again
    printf(" enc is %d\n",tmp3);
    char tmp2[10];
    sprintf(tmp2,"%d",tmp3); // int to char 
    if(tmp3<u)
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


int main(){
  //rsa keys pre-computed for simplification so in the following case,
 
  // for A and B communication Private Key d2 would be 3447, same p,q,n as the last pair. and public key k1:e1  would be 7
  int p = 59;
  int q = 53;
  int n = p*q; 
  
  int phi = (p-1)*(q-1);

  //4th key-pair for A and B communication
  int phi4= 120;
  int p4=11;
  int q4=13;
  int n4=p4*q4;
  int e4=7;//public
  int d4=103;//private
  //1st B own secret key
     int e1=7;
     int ks0=8;// a constant value
     int d2= (1 + (ks0*phi))/e1; //
     // printf("%d the 2nd pri k is\n",ks2);


     /*
  while (e1 < phi) 
    { 
        // e must be co-prime to phi and 
        // smaller than phi. 
      if (gcd(e1, phi)==1) 
            break; 
      else
            e1++; 
	
	 } */
   
    
      
    
  // int msg=9;
  //  int c = powMod(msg, e, n); // encrypted equation
  //  int mm = powMod(c, d, n); // decrypted 
     // printf("the enc is %d\n",c);
     //     printf("the dnc is %d\n",mm);


     


    
    //handshake between MB and B----------------------
     






     
  // keys 
     int k0=11;
     char m1[256]="attack";
     char m2[]="benign";
     int kr=9;
     char ms1[256];

  // communicate for test
  //message into ascii for encryption
     /*
  for (int j=0;j<strlen(m1);j++){
    int tmp1=(int) m1[j]; // convert to ascii
    printf("the %c is %d ",m1[j],tmp1);   
    int tmp3=powMod(tmp1, e4, n4); // encyption with rsa
    // convert the int to char and concatenate again
    printf(" enc is %d\n",tmp3);
    char tmp2[10];
    sprintf(tmp2,"%d",tmp3); // int to char 
    if(tmp3<100)
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
  }*/
  //  printf(" d is %d",d);

     LetterAsc(e4,n4,m1,strlen(m1),ms1,100);
     printf("%s is the message to be sent to A\n ",ms1);
     char ms3[256];
      LetterAsc(e4,n4,m2,strlen(m2),ms3,100);
      printf("%s is the message to be sent to A its original is %s\n ",ms3,m2);
      
     char ms2[256];
      LetterAsc(e1,n,m1,strlen(m1),ms2,1000);
      char ms4[256];
      LetterAsc(e1,n,m2,strlen(m2),ms4,1000);
  //send to MB and A

  int fo;
  fo=socket(AF_INET,SOCK_STREAM,0);
  
  struct sockaddr_in oaddr;
  oaddr.sin_family = AF_INET;
  oaddr.sin_port = htons(9052);
  oaddr.sin_addr.s_addr = INADDR_ANY;

  bind(fo,(struct sockaddr *)&oaddr,sizeof(oaddr));
  listen(fo,50);
  
  int clientSocket;
  clientSocket=accept(fo,NULL,NULL);
  // sleep(3);
   char hs1[256];
   char hello[256]="hello";
  // printf("get the %s\n",hs1);
  // sleep(4);
  send(clientSocket,hello,sizeof(hello),0);
  //  close(fo);
  // clientSocket=accept(fo,NULL,NULL);
  int r =recv(clientSocket,&hs1,sizeof(hs1),0);
  printf("get the %s\n",hs1);
  char cm[256];
  CRSA(e1,n,hs1,strlen(hs1),cm);
  printf("the cm is %s\n",cm);
  send(clientSocket,cm,sizeof(cm),0);//send the double twice RSA communitative
  send(clientSocket,ms1,sizeof(ms1),0);// Message for A
  send(clientSocket,ms2,sizeof(ms2),0);//token to MB
  send(clientSocket,ms3,sizeof(ms3),0);//another one for A
  send(clientSocket,ms4,sizeof(ms4),0);//token to MB
  
  // printf("%d \n",r);
    close(fo);
  return 0;

  
}
