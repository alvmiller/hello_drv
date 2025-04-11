#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

// https://embetronicx.com/tutorials/linux/device-drivers/linux-device-driver-tutorial-programming/
// https://olegkutkov.me/2018/03/14/simple-linux-character-device-driver/
// https://embetronicx.com/tutorials/linux/device-drivers/ioctl-tutorial-in-linux/

// gcc -o client client.c
// make
// sudo insmod hello_drv.ko
// sudo dmesg
// lsmod | grep hello_drv
// sudo ./client
// sudo rmmod hello_drv

int8_t write_buf[1024] = { 'H', 'e', 'l', 'l', 'o' };
int8_t read_buf[1024];

int main()
{     
        int fd = open("/dev/hello_drv", O_RDWR);
        if(fd < 0) {
        	perror("Can't open Drv");
                printf("Cannot open device file...\n");
                return 0;
        }
        
	printf("String to write into driver:%s\n", write_buf);
	printf("Data Writing ...");
	write(fd, write_buf, strlen(write_buf)+1);
	printf("Done!\n");

	printf("Data Reading ...");
	read(fd, read_buf, 1024);
	printf("Done!\n\n");
	printf("Data = %s\n\n", read_buf);
        
        close(fd);

        return 0;
}