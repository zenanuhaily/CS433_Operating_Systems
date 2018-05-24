/*CS433 Programming Assignment 1
Zena Nuhaily
CS433 filecpy.c
This program uses standard system calls to copy the contents of one file to ano\
ther file.
*/
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
 int fd1;
    if (argc !=3)
    {
      fprintf(stderr, "usage: %s <source> <dest> \n", argv[0]);
      return -1;
    }
  fd1 = open(argv[1],O_RDONLY);
    if (fd1 < 0)
      {
        fprintf(stderr, "error opening file\n");
       return -1;
      }
 char buf[256];
 size_t nbytes = sizeof(buf);
 ssize_t temp = read(fd1, buf, nbytes);

    if(temp == -1)
      {
        fprintf(stderr, "error while reading \n");
        return -1;
      }
int fd2 = open(argv[2], O_CREAT | O_WRONLY, ALLPERMS);
    if(fd2 == -1)
      {
        fprintf(stderr, "error while opening \n");
        return -1;
      }
    temp = write(fd2, buf, temp);
    if(temp == -1)
      {
        fprintf(stderr, "error while writing \n",argv[2]);
        return -1;
      }
int close1 = close(fd1);
    if(close1 == -1)
      {
        fprintf(stderr, "error while closing \n",argv[1]);
        return -1;

      }
int close2 = close(fd2);
    if(close2 == -1)
      {
        fprintf(stderr, "error while closing \n",argv[2]);
        return -1;
      }

    return 0;//end
}
/*

[nuhai003@empress cs433]$ strace ./filecpy
execve("./filecpy", ["./filecpy"], [/ 29 vars /]) = 0
  brk(NULL)                               = 0x2366000
  mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fc5ebd55000
  access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
  open("/opt/rh/rh-ruby24/root/usr/local/lib64/tls/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
  stat("/opt/rh/rh-ruby24/root/usr/local/lib64/tls/x86_64", 0x7ffc48651da0) = -1 ENOENT (No such file or directory)
  open("/opt/rh/rh-ruby24/root/usr/local/lib64/tls/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
  stat("/opt/rh/rh-ruby24/root/usr/local/lib64/tls", 0x7ffc48651da0) = -1 ENOENT (No such file or directory)
  open("/opt/rh/rh-ruby24/root/usr/local/lib64/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
  stat("/opt/rh/rh-ruby24/root/usr/local/lib64/x86_64", 0x7ffc48651da0) = -1 ENOENT (No such file or directory)
  open("/opt/rh/rh-ruby24/root/usr/local/lib64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
  stat("/opt/rh/rh-ruby24/root/usr/local/lib64", {st_mode=S_IFDIR|0755, st_size=6, ...}) = 0
  open("/opt/rh/rh-ruby24/root/usr/lib64/tls/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
  stat("/opt/rh/rh-ruby24/root/usr/lib64/tls/x86_64", 0x7ffc48651da0) = -1 ENOENT (No such file or directory)
  open("/opt/rh/rh-ruby24/root/usr/lib64/tls/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
  stat("/opt/rh/rh-ruby24/root/usr/lib64/tls", {st_mode=S_IFDIR|0555, st_size=6, ...}) = 0






 /*
