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


int main(){
   int fd;//handle 
     // socket initialize
   fd=socket(AF_INET,SOCK_STREAM,0);

     struct sockaddr_in saddr;
     saddr.sin_family = AF_INET;
     saddr.sin_port = htons(9053);
     saddr.sin_addr.s_addr = INADDR_ANY;
     int cs=connect(fd,(struct sockaddr *)& saddr,sizeof( saddr));
     char respond[256];
     recv(fd,&respond,sizeof(respond),0);


     //4th key-pair
  int phi4= 120;
  int p4=11;
  int q4=13;
  int n4=p4*q4;//143 
  int e4=7;//public
  int d4=103;//private
  int l=strlen(respond);
  char m1[256];
  strcpy(m1,respond);
  printf(" Got A message");
  printf("it is %s\n",respond);
  for(int i=0;i<l;i+=3){
    int t=((int)m1[i]-48)*100+((int)m1[i+1]-48)*10+((int)m1[i+2]-48);
    //  printf("original t is %d \n ",t);
    int tmp3=powMod(t,d4, n4);
    char c=tmp3;
   
    printf("%c",c);

  }
  printf("\n");

  close(fd);

  return 0;
}
