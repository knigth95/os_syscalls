#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>

#define SYS_getcwd 17

int sys_getcwd()
{
    char *buf = NULL;
    size_t size = 0;
    long ret;

    /* 获取所需的缓冲区大小 */
    size = syscall(SYS_getcwd, buf, size);
    if (size <= 0) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    /* 分配缓冲区 */
    buf = malloc(size * sizeof(char));
    if (buf == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    /* 获取当前工作目录 */
    ret = syscall(SYS_getcwd, buf, size);
    if (ret == -1) {
        perror("getcwd");
        exit(EXIT_FAILURE);
        return *buf;
    }

    //printf("当前工作目录：%s\n", buf);

    
    free(buf);
    buf = NULL;
    return *buf;
}
