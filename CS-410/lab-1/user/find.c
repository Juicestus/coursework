#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"


void find(char *directory, char *filename)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(directory, 0)) < 0){
        fprintf(2, "find: cannot open %s\n", directory);
        exit(1);
    }

    if(fstat(fd, &st) < 0){
        fprintf(2, "find: cannot stat %s\n", directory);
        close(fd);
        exit(1);
    }

    if(st.type == T_DIR){
        strcpy(buf, directory);
        p = buf + strlen(buf);
        *p++ = '/';

        while(read(fd, &de, sizeof(de)) == sizeof(de)){
            if(de.inum == 0)
                continue;
            
            if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
                continue;
            
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            
            if(stat(buf, &st) < 0){
                fprintf(2, "find: cannot stat %s\n", buf);
                continue;
            }

            if(strcmp(de.name, filename) == 0){
                printf("%s\n", buf);
            }
            
            if(st.type == T_DIR){
                find(buf, filename);
            }
        }
        
    }
    
    close(fd);
}

int
main(int argc, char *argv[])
{
    if(argc != 3)
    {
        fprintf(2, "usage: find <directory> <filename>\n");
        exit(1); 
    }

    char *directory = argv[1];

    char *filename = argv[2];

    find(directory, filename);
    exit(0);
}