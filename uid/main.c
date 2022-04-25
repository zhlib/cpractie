#include <stdio.h>
#include "../common/unp.h"


int main(int argc,char *argv[])
{
   if(argc!=2)
   {
      printf("error\n");
   }
   printf("uid = %d,gid=%d,euid=%d,egid=%d\n",getuid(),getgid(),geteuid(),getegid());
   if(access(argv[1],R_OK)<0)
   {
      printf("access error for %s\n",argv[1]);
   }
   else
   {
      printf("read access OK\n");
   }

   if(faccessat(0,argv[1],R_OK,AT_EACCESS))
   {
      printf("faccessat error for %s\n",argv[1]);
   }
   else
   {
      printf("faccessat read access OK\n");
   }
 

   if(open(argv[1],O_RDONLY)<0)
   {
      printf("open error for %s\n",argv[1]);
   }
   else
   {
      printf("open for reading OK\n");
   }
   return 0;
    
}

