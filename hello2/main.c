#include <stdio.h>
#include "../common/unp.h"


int 
main(int argc, char **args)
{
       
        char buffer[20];
        int fd = atoi(args[1]);
        printf("hello2 exec fd is %d \n",fd);
        memset(buffer,0,sizeof(buffer) );
        ssize_t bytes = read(fd,buffer,sizeof(buffer)-1);
        if(bytes < 0)
        {
                perror("exe1: read fail:");
                return -1;
        }
        else
        {
                printf("exe1: read %ld,%s\n",bytes,buffer);
        }
        return 0;
}