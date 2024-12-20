#include <stdio.h>

// .bss:0000000000404080 buf             dq 100h dup(?)          ; DATA XREF: main+BC↑o
// .bss:0000000000404080                                         ; main+D3↑o
// .bss:0000000000404080 _bss            ends

unsigned long win()
{
  char *argv[3]; // [rsp+0h] [rbp-20h] BYREF
  unsigned long v2; // [rsp+18h] [rbp-8h]

  v2 = __readfsqword(0x28u);
  argv[0] = "/bin/sh";
  argv[1] = 0LL;
  execve("/bin/sh", argv, 0LL);
  return v2 - __readfsqword(0x28u);
}

int main(int argc, const char **argv, const char **envp)
{
  long v3; // [rsp+8h] [rbp-18h] BYREF
  long i; // [rsp+10h] [rbp-10h]
  unsigned long v5; // [rsp+18h] [rbp-8h]

  v5 = __readfsqword(0x28u);
  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(_bss_start, 0LL, 2, 0LL);
  setvbuf(stderr, 0LL, 2, 0LL);
  for ( i = 0LL; ; i = buf[i] )
  {
    printf("val: ");
    __isoc99_scanf("%lu", &v3);
    buf[i] = v3;
  }
}