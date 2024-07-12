#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>



int main(void)
{
    int status;
    pid_t pid;
    if (!fork())
    {
        return 1; // 子进程
    }

    pid = wait(&status);

    if (pid == -1)
        perror("wait");
    printf("pid=%d\n", pid);
    if (WIFEXITED(status))
    {
        printf("Nomal temination with exit status=%d\n", WEXITSTATUS(status));
    }



    if (WIFSIGNALED(status))
    {
         printf("killed by  %d\n", WIFSIGNALED(status));
         
    }




    return 0;
}
