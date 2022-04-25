#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../common/unp.h"

// 进程间传递文件描述符,用于不同进程间共享文件
// 文件表项 进程表项 v-node 共享偏移量 文件状态
int main(int argc, char *argv[])
{
	int oldfd,newfd;
	char *oldstr = "Write by oldfd.\n";
	char *newstr = "Write by newfd.\n";

	oldfd = open("test.txt", O_RDWR|O_CREAT, 0644);
	printf("oldfd = %d\n", oldfd);

	if(oldfd == -1) {
		printf("File open error\n");
		exit(-1); 
	}

	/* 开始复制 */
	newfd = dup(oldfd);
	printf("newfd = %d\n", newfd);

	/* 使用oldfd写 */
	write(oldfd, oldstr, strlen(oldstr));
	if(close(oldfd) == -1) {
		printf("Close oldfd error.\n");
		exit(-1);
	}

	/* 使用newfd写 */
	write(newfd, newstr, strlen(newstr));
	if(close(newfd) == -1) {
		printf("Close newfd error.\n");
		exit(-1);
	}


    fileType(argc,argv);

	exit(0);
}

