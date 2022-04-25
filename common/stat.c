#include "unp.h"
#include <dirent.h>
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>

int fileType(int argc, char *argv[])
{
    int i;
    struct stat buf;
    struct stat *p = &buf;
    char *ptr;

    for (i = 1; i <argc; i ++){
        // printf("%s: ", argv[i]);
        get_dir(argv[i]);
        // if (lstat(argv[i],&buf) < 0) {
        //     err_ret("lstat error");
        //     continue;
        // }

        // //scanf("%d%d%d",p->st_uid,&p->st_dev,&p->st_gid) ;

        // printf("%d%d%d",p->st_uid,&p->st_dev,&p->st_gid) ;

        // if (S_ISREG(buf.st_mode))
        //     ptr = "regular";
        // else if (S_ISDIR(buf.st_mode))
        //     ptr = "directory";
        // else if (S_ISCHR(buf.st_mode))
        //     ptr = "character special";
        // else if (S_ISFIFO(buf.st_mode))
        //     ptr = "fifo";
        // else if (S_ISLNK(buf.st_mode))
        //     ptr = "symbolic link";
        // else if (S_ISSOCK(buf.st_mode))
        //     ptr = "socket";
        // else
        //     ptr = "** unknown mode **";
        // printf("%s\n", ptr);
    }

    return 0;
}


//获取文件权限
void get_perm(mode_t mod,char *buf)
{
    bzero(buf,100);
    int i = 9;
    while(i--)
    {
        if(mod & 1<<i)
        {
            switch((8-i)%3)
            {
            case 0: buf[8-i] = 'r'; break;
            case 1: buf[8-i] = 'w'; break;
            case 2: buf[8-i] = 'x'; break;
            }
        }
        else
            buf[8-i] = '-';
    }
}


char  get_type(mode_t mod)
{
	/*
	if( S_ISREG(mod) ) return '-';
       if( S_ISDIR(mod) ) return 'd';
       if( S_ISCHR(mod) ) return 'c';
       if( S_ISBLK(mod) ) return 'b';
       if( S_ISLNK(mod) ) return 'l';
       if( S_ISSOCK(mod) ) return 's';
       if( S_ISFIFO(mod) ) return 'p';
	*/
	switch(mod & S_IFMT)
    {
    case S_IFSOCK: return 's';//socket 套接字
    case S_IFREG: return '-';//普通文件
    case S_IFCHR: return 'c';//字符设备
    case S_IFBLK: return 'b';//块设备
    case S_IFLNK: return 'l';//符号链接
    case S_IFIFO: return 'p';//管道文件
    case S_IFDIR: return 'd';//目录文件
    }

    return '0';
}


//获取文件最后一次修改时间
void get_ltime(time_t *t,char *buf)
{
	struct tm *tmp;
	tmp=localtime(t);
	sprintf(buf,"%d-%d-%d %d:%d:%d", (1900 + tmp->tm_year), ( 1 + tmp->tm_mon), tmp->tm_mday,
		tmp->tm_hour, tmp->tm_min, tmp->tm_sec); 
	return ;
}


void put_stat(char *dir,char *name)
{
    struct stat s;
	if(-1 == stat(dir, &s) )
    {
        perror("stat");
        exit(0);
    }

    char buf_perm[100];
	get_perm(s.st_mode,buf_perm);//获取文件权限
	char buf_time[100];
    get_ltime(&s.st_ctime,buf_time);//获取文件最后一次修改时间
	printf( "%c%s %5d %15s %15s %15ld %15s  %15s  \033[0m\n", 
                get_type(s.st_mode),
                buf_perm,
                s.st_nlink,
                getpwuid(s.st_uid)->pw_name,
                getgrgid(s.st_gid)->gr_name,
                s.st_size, 
                buf_time,
                name );
}


void get_dir(char *dir) 
{
    DIR *dp = opendir(dir);
    struct dirent *p;
    printf("%s:\n", dir);
    puts("{");
    while ((p =readdir(dp)))
    {
        char ttp[1024];
        bzero(ttp, sizeof(ttp));
        strcat(ttp, dir);
        if( strcmp(ttp, "/") !=0) strcat(ttp,"/");
        strcat(ttp, p->d_name);
        put_stat(ttp, p->d_name);
    }
    
    puts("}");
    return;
}