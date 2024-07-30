#include <stdio.h>

int main()
{
  char *sh = "/bin/sh";
  execve(sh, NULL, NULL);
}