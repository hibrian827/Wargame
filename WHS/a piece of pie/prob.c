#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>



void proc_init ()
{
  setvbuf (stdin, 0, 2, 0);
  setvbuf (stdout, 0, 2, 0);
  setvbuf (stderr, 0, 2, 0);
}

__attribute__ ((naked))
void gadget()
{
 asm(".intel_syntax noprefix\n"
    "pop rdi\n"
    "ret\n"   
    ".att_syntax \n"
    :
    :
    : "rdi"
 ); 
}

int read_input (char *buf, int len)
{
  int ret;

  ret = read (0, buf, len);

  if (ret < 0)
  {
    fprintf (stderr, "read error!\n");
    exit (1);
  }

  if (buf[ret-1] == '\n')
    buf[ret-1] = '\0';

  return ret;
}

void vuln()
{
  char buf[0xa0];
  proc_init ();

  printf ("1: ");
  read_input(buf, 0x100);
  puts(buf);

  printf ("2: ");
  read_input(buf, 0x100);
  puts(buf);

  printf ("3: ");
  read_input(buf, 0x100);
}

int main ()
{
  char buf[0xb0];
  int menu;
  proc_init ();

  printf("name: ");
  read_input(buf, 0xa0);

  printf("Hello! ");
  puts(buf);

  vuln();
  return 0;
}
