#include <stdio.h>
#include <sys/types.h>

ssize_t writeln(long a1)
{
  int i; // [rsp+1Ch] [rbp-4h]

  for ( i = 0; ; ++i )
  {
    write(1, (const void *)(i + a1), 1uLL);
    if ( *(char *)(i + a1) == 46 )
      break;
  }
  return write(1, "\n", 1uLL);
}

int readint()
{
  char nptr[24]; // [rsp+0h] [rbp-20h] BYREF
  unsigned long v2; // [rsp+18h] [rbp-8h]

  v2 = __readfsqword(0x28u);
  readln(nptr);
  return atoi(nptr);
}

long readln(long a1)
{
  long result; // rax
  int i; // [rsp+1Ch] [rbp-4h]

  for ( i = 0; i <= 255; ++i )
  {
    read(0, (void *)(i + a1), 1uLL);
    result = *(unsigned int *)(i + a1);
    if ( (char)result == 46 )
      break;
  }
  return result;
}

void *cleara(void *a1, int a2)
{
  return memset(a1, 46, a2);
}

unsigned long run()
{
  int v1; // [rsp+Ch] [rbp-114h]
  char v2[264]; // [rsp+10h] [rbp-110h] BYREF
  // canary [rsp+118h] [rbp-8h]

  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(stdout, 0LL, 2, 0LL);
  setvbuf(stderr, 0LL, 2, 0LL);
  writeln("Mirin, It's the End of Period with Period.");
  v2[0] = 46;
  while ( 1 )
  {
    while ( 1 )
    {
      writeln("1: read.");
      writeln("2: write.");
      writeln("3: clear.");
      write(1, "> ", 2uLL);
      v1 = readint();
      if ( v1 != 3 )
        break;
      cleara(v2, 256LL);
    }
    if ( v1 > 3 )
      break;
    if ( v1 == 1 )
    {
      writeln("Read: .");
      writeln(v2);
    }
    else
    {
      if ( v1 != 2 )
        break;
      writeln("Write: .");
      readln(v2);
    }
  }
  writeln("Invalid Command.");
  writeln("Finally, Just Watch the Curtain Fall.");
  return 0;
}

int main(int argc, const char **argv, const char **envp)
{
  run(argc, argv, envp);
  return 0;
}