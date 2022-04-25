#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

// https://blog.csdn.net/u012349696/article/details/51439459
// 借鉴上文

void crate_at(char *dir_path, char *relative_path)
{
    int dir_fd;
    int fd;
    int flags;
    mode_t mode;

    dir_fd = open(dir_path, O_RDONLY);
    if (dir_fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    flags = O_CREAT | O_TRUNC | O_RDWR;
    mode = 0640; 
    fd = openat(dir_fd, relative_path, flags, mode);
    if (fd < 0) 
    {
        perror("openat");
        exit(EXIT_FAILURE);
    }

    write(fd, "HELLO", 5);

    close(fd);
    close(dir_fd);
}

int create_at_dir(char *dir_path, char *relative_path) 
{
    DIR *dir;
	int dirfd2;
	int fd;
	int n;
 
	dir = opendir(dir_path);
	if(NULL == dir)
	{
		perror("open dir error");
		return -1;
	}
	dirfd2 = dirfd(dir);
	if(-1 == dirfd2)
	{
		perror("dirfd error");
		return -1;
	}
 
	fd = openat(dirfd2,relative_path,O_CREAT|O_RDWR|O_TRUNC,0640);
	if(-1 == fd)
	{
		perror("opeat error");
		return -1;
	}
	n = write(fd,"Hello world!\n",15);
	
	close(fd);
	closedir(dir);
    return 0;
}

int main()
{
    crate_at("./open", "log.txt");
    create_at_dir("./open", "log2.txt");
    return 0;
}