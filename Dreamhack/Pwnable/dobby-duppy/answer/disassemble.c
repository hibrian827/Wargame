#include <stdio.h>

long sandbox()
{
  long v1; // [rsp+8h] [rbp-8h]

  v1 = seccomp_init(0);
  if ( !v1 )
    exit(0);
  seccomp_rule_add(v1, 2147418112, 2, 0);
  seccomp_rule_add(v1, 2147418112, 0, 0);
  seccomp_rule_add(v1, 2147418112, 1, 0);
  return seccomp_rule_add(v1, 2147418112, 33, 0);
}

int main(int argc, const char **argv, const char **envp)
{
  long buf[32]; // [rsp+0h] [rbp-110h] BYREF
  int fd; // [rsp+104h] [rbp-Ch]
  void (*v6)(void); // [rsp+108h] [rbp-8h]

  memset(buf, 0, sizeof(buf));
  v6 = (void (*)(void))buf;
  init(argc, argv, envp);
  sandbox();
  printf("Say hello to Dobby...if he is Dobby :) ");
  read(0, buf, 0x100);
  puts("\nWhat? I'm Duppy! NOT Dobby!");
  puts("\nNow you are bliiiiiiiiind");
  fd = open("/dev/null", 2);
  dup2(fd, 0);
  dup2(fd, 1);
  dup2(fd, 2);
  v6();
  return 0;
}