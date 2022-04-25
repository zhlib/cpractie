#include <stdio.h>
#include "../common/unp.h"

int
main(int argc, char **argv)
{
    // 来源  https://www.cnblogs.com/my_life/articles/5228295.html
    // 子进程 共享文件偏移量
    // 直接close 写不到磁盘,等30秒试试
    int fd,pid;
    char buffer[20];
    char rBuffer[100];
    fd = open("1.txt",O_RDWR|O_CREAT|O_TRUNC|O_SYNC,0666);
    printf("descriptor is %d\n",fd);

    sprintf(rBuffer, "This is test %d bbbbbbbbbbbbbbbbbbbbbbbbbbb", fd);
    ssize_t n =  write(fd,rBuffer,20);
    printf("wirte %ld bytes \n",n);
    //fsync(fd);
   // sleep(30);
    close(fd);
    // return 0;

    fd = open("1.txt",O_RDONLY);
    printf("new descriptor is %d\n",fd);


    return
    // int val = fcntl(fd,F_GETFD);
    // val |= FD_CLOEXEC;
    // fcntl(fd,F_SETFD,val);

    pid = fork();
    if(pid == 0)
    {
        char chlid_buf[2];
        memset(chlid_buf, 0, sizeof(chlid_buf) - 1);
        ssize_t bytes = read(fd,chlid_buf, sizeof(chlid_buf) - 1);
        printf("child fd is %d, bytes:%ld,%s\n",fd, bytes,chlid_buf);

        char fd_str[5];
        memset(fd_str, 0, sizeof(fd_str));
        sprintf(fd_str, "%d", fd);
        int ret = execl("./hello2", "hello2", fd_str,NULL);
        if(-1 == ret)
            perror("ececl fail:");
        return 0;
    }

    waitpid(pid, NULL, 0);
    memset(buffer, 0, sizeof(buffer) - 1);
    ssize_t bytes = read(fd,buffer,sizeof(buffer)-1 );
    printf("parent, bytes:%ld,%s\n",bytes,buffer);
}