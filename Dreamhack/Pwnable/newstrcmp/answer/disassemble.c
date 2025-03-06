unsigned long flag()
{
  char *argv[3]; // [rsp+10h] [rbp-20h] BYREF
  unsigned long v2; // [rsp+28h] [rbp-8h]

  v2 = __readfsqword(0x28u);
  argv[0] = "/bin/sh";
  argv[1] = 0LL;
  execve("/bin/sh", argv, 0LL);
  return v2 - __readfsqword(0x28u);
}

int * newstrcmp(const char *a1, long a2, int *a3)
{
  int v3; // edx
  int *result; // rax
  int i; // [rsp+28h] [rbp-8h]
  int v7; // [rsp+2Ch] [rbp-4h]

  v7 = strlen(a1);
  for ( i = 0; ; ++i )
  {
    if ( i >= v7 )
    {
      a3[1] = 0;
      result = a3;
      *a3 = -1;
      return result;
    }
    if ( a1[i] != *(char *)(i + a2) ) break;
  }
  if ( a1[i] >= *(char *)(i + a2) ) v3 = 1;
  else v3 = -1;
  a3[1] = v3;
  result = a3;
  *a3 = i;
  return result;
}

int main(int argc, const char **argv, const char **envp)
{
  int v4; // [rsp+10h] [rbp-50h]
  unsigned int v5; // [rsp+14h] [rbp-4Ch] BYREF
  int v6; // [rsp+18h] [rbp-48h]
  char buf[2]; // [rsp+1Eh] [rbp-42h] BYREF
  char v8[16]; // [rsp+20h] [rbp-40h] BYREF
  long v9; // [rsp+30h] [rbp-30h]
  long v10; // [rsp+38h] [rbp-28h]
  char v11[24]; // [rsp+40h] [rbp-20h] BYREF
  unsigned long v12; // [rsp+58h] [rbp-8h]

  v12 = __readfsqword(0x28);
  v9 = 0;
  v10 = 0;
  v4 = 0;
  setup(argc, argv, envp);
  puts("Tester for newstrcmp");
  while ( 1 )
  {
    printf("Trial: %d\n", (unsigned int)++v4);
    printf("Exit? (y/n): ");
    read(0, buf, 2);
    if ( buf[0] == 121 )
      break;
    printf("Input string s1: ");
    read(0, v8, 0x40);
    printf("Input string s2: ");
    read(0, v11, 0x40);
    newstrcmp(v8, v11, &v5);
    printf("Result of newstrcmp: ");
    if ( v6 )
    {
      if ( v6 >= 0 )
        printf("s1 is larger than s2, first differs at %d\n", v5);
      else
        printf("s1 is smaller than s2, first differs at %d\n", v5);
    }
    else
    {
      puts("Two strings are the same!");
    }
  }
  return 0;
}