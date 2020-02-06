#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define DV_FILE "/dev/vchar_dev"

int main()
{
    int fd; // file descriptor
    char buf[20];

    fd = open(DV_FILE, O_RDWR);
    if(fd < 0)
    {
        printf("Fail to open driver\n");
        return -1;
    }

    while(1)
    {
        write(fd, "s", 1);
        usleep(500000);
        write(fd, "c", 1);
        usleep(500000);
    }

    close(fd);

    return 0;

}
