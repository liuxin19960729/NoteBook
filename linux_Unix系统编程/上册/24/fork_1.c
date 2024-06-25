
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

void main()
{
    pid_t child_pid;

    switch (child_pid = fork())
    {
    case -1:
        // 错误处理

        perror("fork return -1");

        break;

    case 0:
        printf("child sleep before \n");
        sleep(2);
        printf("child exec \n");
        // 子进程
        break;
    default:
        // 父进程
        printf("parent exec \n");
        int status = 0;
        wait(&status);
        printf("child return status:%d\n", status);
        break;
    }
}
