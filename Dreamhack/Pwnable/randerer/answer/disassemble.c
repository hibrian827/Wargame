#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

long canary;

int win()
{
  return system("/bin/sh");
}

void init_canary()
{
  unsigned int v0; // eax
  long v1; // rbx
  int i; // [rsp+Ch] [rbp-14h]

  v0 = time(0);
  srand(v0);
  for ( i = 0; i <= 7; ++i )
  {
    v1 = canary << 8;
    canary = v1 | (unsigned int)rand();
  }
}

int main(int argc, const char **argv, const char **envp)
{
  time_t v3; // rax
  char buf[16]; // [rsp+0h] [rbp-20h] BYREF
  long v6; // [rsp+10h] [rbp-10h]

  setvbuf(stdin, 0, 2, 0);
  setvbuf(stdout, 0, 2, 0);
  setvbuf(stderr, 0, 2, 0);
  v6 = canary;
  v3 = time(0);
  printf("time: %ld\n", v3);
  printf("input your data: ");
  read(0, buf, 0x100);
  if ( v6 != canary )
  {
    puts("*** stack smashing detected ***: terminated Aborted");
    exit(1);
  }
  return 0;
}