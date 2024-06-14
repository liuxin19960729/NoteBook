#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    int fd;
    struct iovec iov[1];
    struct stat myStruct;
    int x;
#define STR_SIZE 1024
    char str[STR_SIZE];
    ssize_t numRead, totRequired;
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
    {
        printf("print:--help\n");
        return 1;
    }

    fd = open(argv[1], O_RDONLY);

    if (fd == -1)
    {
        perror("open error\n");
        return 2;
    }

    totRequired = 0;

    iov[0].iov_base = &str;
    iov[0].iov_len = STR_SIZE;
    totRequired += iov[0].iov_len;

    numRead = readv(fd, iov, 1);

    if (numRead == -1)
    {
        perror("readv\n");
        return 3;
    }

    if (numRead < totRequired)
        printf("Read fewer bytes than requested\n");

    printf("total bytes requested:%ld;bytes read :%ld\n", (long)totRequired, (long)numRead);
    printf("%s\n",(char *)iov[0].iov_base);
    return 0;
}