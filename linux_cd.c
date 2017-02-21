#include <linux/cdrom.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdio.h>

int quit = 0;

void handler(int s){
   quit = 1;
}

int main(int argc, char* argv[])
{
    signal (SIGINT,handler);
    
    int f = open("/dev/cdrom", O_RDONLY | O_NONBLOCK);
    if (f < 0)
    {
        perror("");
        return -1;
    }
    
    while (!quit)
    {
        ioctl(f, CDROMEJECT);
        sleep(1);
        ioctl(f, CDROMCLOSETRAY);
        sleep(1);
    }
    
    close(f);
    
    return 0;
}
