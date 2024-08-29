int __fastcall main(int argc, const char **argv, const char **envp)
{
  unsigned __int64 v4; // [rsp+8h] [rbp-28h] BYREF
  __int64 v5; // [rsp+10h] [rbp-20h] BYREF
  __int64 v6; // [rsp+18h] [rbp-18h] BYREF
  __int64 v7[2]; // [rsp+20h] [rbp-10h] BYREF

  v7[1] = __readfsqword(0x28u);
  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(stdout, 0LL, 2, 0LL);
  setvbuf(stderr, 0LL, 2, 0LL);
  jump_table[0] = (__int64)&read;
  qword_4058 = (__int64)&write;
  while ( 1 )
  {
    printf("Enter command: ");
    __isoc99_scanf("%lld", &v4);
    if ( v4 >= 2 )
      break;
    printf("Enter arguments: ");
    __isoc99_scanf("%lld", &v5);
    __isoc99_scanf("%lld", &v6);
    __isoc99_scanf("%lld", v7);
    ((void (__fastcall *)(_QWORD, __int64, _QWORD))jump_table[v4])((unsigned int)v5, v6, LODWORD(v7[0]));
  }
  puts("Invalid command");
  return 0;
}