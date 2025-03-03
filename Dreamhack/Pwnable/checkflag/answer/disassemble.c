int main(int argc, const char **argv, const char **envp)
{
  long v3; // rcx
  char *v4; // rdi
  FILE *v5; // rax
  FILE *v6; // r12
  ssize_t v7; // rdx
  FILE *v8; // r12
  char v10[64]; // [rsp+0h] [rbp-E8h] BYREF
  char v11[136]; // [rsp+40h] [rbp-A8h] BYREF
  unsigned long v12; // [rsp+C8h] [rbp-20h]

  v3 = 50;
  v12 = __readfsqword(0x28u);
  v4 = v10;
  while ( v3 )
  {
    *(_DWORD *)v4 = 0;
    v4 += 4;
    --v3;
  }
  v5 = fopen("flag", "r");
  if ( !v5 )
LABEL_8:
    exit(1);
  v6 = v5;
  fgets(v11, 64, v5);
  fclose(v6);
  fputs("What's the flag? ", _bss_start);
  fflush(_bss_start);
  v7 = read(0, v10, 0xC8);
  v8 = _bss_start;
  if ( (long)strlen(v11) > v7 || strcmp(v10, v11) )
  {
    fputs("Failed!\n", v8);
    goto LABEL_8;
  }
  fputs("Correct!\n", v8);
  return 0;
}