#include <stdio.h>

char *buf;

int main(int argc, const char **argv, const char **envp)
{
  long v3; // rbx
  long v4; // rbx
  long v5; // rbx
  long v6; // rbx
  long v7; // rbx
  long v8; // rbx
  long v9; // rbx
  long v10; // rbx
  long v11; // rbx
  long v12; // rbx
  long v13; // rbx
  long v14; // rbx
  long v15; // rbx
  long v16; // rbx
  long v17; // rbx
  long v18; // rbx
  int fd; // [rsp+24h] [rbp-1Ch]
  void (*v21)(void); // [rsp+28h] [rbp-18h]

  setup();
  printf("Input shellcode: ");
  read(0, &buf, 0x100);
  v21 = (void (*)(void))mmap(0, 0x1000, 7, 34, -1, 0);
  *(long *)v21 = buf;
  *((long *)v21 + 1) = buf+0x8;
  *((long *)v21 + 2) = buf+0x10;
  *((long *)v21 + 3) = buf+0x18;
  *((long *)v21 + 4) = buf+0x20;
  *((long *)v21 + 5) = buf+0x28;
  *((long *)v21 + 6) = buf+0x30;
  *((long *)v21 + 7) = buf+0x38;
  *((long *)v21 + 8) = buf+0x40;
  *((long *)v21 + 9) = buf+0x48;
  *((long *)v21 + 10) = buf+0x50;
  *((long *)v21 + 11) = buf+0x58;
  *((long *)v21 + 12) = buf+0x60;
  *((long *)v21 + 13) = buf+0x68;
  *((long *)v21 + 14) = buf+0x70;
  *((long *)v21 + 15) = buf+0x78;
  *((long *)v21 + 16) = buf+0x80;
  *((long *)v21 + 17) = buf+0x88;
  *((long *)v21 + 18) = buf+0x90;
  *((long *)v21 + 19) = buf+0x98;
  *((long *)v21 + 20) = buf+0xa0;
  *((long *)v21 + 21) = buf+0xa8;
  *((long *)v21 + 22) = buf+0xb0;
  *((long *)v21 + 23) = buf+0xb8;
  *((long *)v21 + 24) = buf+0xc0;
  *((long *)v21 + 25) = buf+0xc8;
  *((long *)v21 + 26) = buf+0xd0;
  *((long *)v21 + 27) = buf+0xd8;
  *((long *)v21 + 28) = buf+0xe0;
  *((long *)v21 + 29) = buf+0xe8;
  *((long *)v21 + 30) = buf+0xf0;
  *((long *)v21 + 31) = buf+0xf8;
  puts("\nNot gonna show you the result!");
  fd = open("/dev/n", 2);
  dup2(fd, 0);
  dup2(fd, 1);
  dup2(fd, 2);
  v21();
  return 0;
}