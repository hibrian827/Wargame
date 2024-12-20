#include <stdio.h>
#include <unistd.h>

// 0000000000401561 <gadgets>:
//   401561:       f3 0f 1e fa             endbr64 
//   401565:       5f                      pop    %rdi
//   401566:       c3                      ret    

int stage1_clear;
int stage2_clear;
int stage_key;

int get_flag(long a1)
{
  long v2; // [rsp+0h] [rbp-20h] BYREF
  long v3; // [rsp+8h] [rbp-18h]
  long *v4; // [rsp+18h] [rbp-8h]

  v3 = a1;
  if ( !stage1_clear || !stage2_clear )
  {
    puts("[-] Previous stages are not cleared!");
    exit(0);
  }
  v4 = &v2;
  check_alignment(&v2);
  if ( (stage_key ^ 0x12345678) != v3 )
  {
    puts("[-] Invalid final key!");
    exit(0);
  }
  return system("/bin/sh");
}

long check_alignment(const void *a1)
{
  long result; // rax

  result = (unsigned int)a1 & 0xF;
  if ( ((unsigned int)a1 & 0xF) != 0 )
  {
    puts("[-] Stack is not properly aligned!");
    printf("RSP: %p\n", a1);
    exit(0);
  }
  return result;
}

long execute_stage1(long a1)
{
  long result; // rax
  long v2; // [rsp+0h] [rbp-20h] BYREF
  long v3; // [rsp+8h] [rbp-18h]
  long *v4; // [rsp+18h] [rbp-8h]

  v3 = a1;
  v4 = &v2;
  check_alignment(&v2);
  if ( (stage_key ^ 0xCAFEBABELL) != v3 )
  {
    puts("[-] Invalid stage 1 key!");
    exit(0);
  }
  stage1_clear = 1LL;
  result = stage_key ^ v3;
  stage_key ^= v3;
  return result;
}

long execute_stage2(long a1)
{
  long result; // rax
  long v2; // [rsp+0h] [rbp-20h] BYREF
  long v3; // [rsp+8h] [rbp-18h]
  long *v4; // [rsp+18h] [rbp-8h]

  v3 = a1;
  if ( !stage1_clear )
  {
    puts("[-] Stage 1 is not cleared!");
    exit(0);
  }
  v4 = &v2;
  check_alignment(&v2);
  if ( (stage_key ^ 0xF00DBABELL) != v3 )
  {
    puts("[-] Invalid stage 2 key!");
    exit(0);
  }
  stage2_clear = 1LL;
  result = stage_key ^ v3;
  stage_key ^= v3;
  return result;
}

int print_stage_info()
{
  const char *v0; // rax
  const char *v1; // rax

  if ( stage1_clear )
    v0 = "Cleared";
  else
    v0 = "Not cleared";
  printf("Stage 1: %s\n", v0);
  if ( stage2_clear )
    v1 = "Cleared";
  else
    v1 = "Not cleared";
  printf("Stage 2: %s\n", v1);
  return printf("Current stage key: 0x%llx\n", stage_key);
}

ssize_t vulnerable()
{
  char buf[16]; // [rsp+0h] [rbp-10h] BYREF

  print_stage_info();
  printf("Input: ");
  return read(0, buf, 0x100uLL);
}

long init()
{
  long result; // rax

  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(_bss_start, 0LL, 2, 0LL);
  result = rand() ^ 0xDEADBEEF;
  stage_key = (unsigned int)result;
  return result;
}

int main(int argc, const char **argv, const char **envp)
{
  init(argc, argv, envp);
  puts("이제 각 단계를 반드시 순서대로 통과해야 합니다!\n");
  puts("각 단계의 키는 이전 단계의 값에 따라 변경됩니다.\n");
  vulnerable();
  return 0;
}