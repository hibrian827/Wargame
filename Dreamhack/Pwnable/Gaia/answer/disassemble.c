unsigned int init()
{
  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(_bss_start, 0LL, 2, 0LL);
  signal(14, sig_handle);
  return alarm(5u);
}

long control(long a1)
{
  return a1;
}

int print_str(const char *a1)
{
  int result; // eax

  result = printf(a1);
  if ( result < 0 )
    exit(0);
  return result;
}

void vuln(long a1, long a2)
{
  long v2; // rdx
  char s[136]; // [rsp+0h] [rbp-90h] BYREF
  unsigned long v4; // [rsp+88h] [rbp-8h]

  v4 = __readfsqword(0x28u);
  control(1LL);
  init(1LL, a2, v2);
  print_str("Good Job!!\n");
  print_str("Who are you?? : ");
  fgets(s, 130, stdin);
  print_str("Congratulations ");
  print_str(s);
  control(1LL);
  exit(1);
}

void vuln(long a1, long a2)
{
  long v2; // rdx
  char s[136]; // [rsp+0h] [rbp-90h] BYREF
  unsigned long v4; // [rsp+88h] [rbp-8h]

  v4 = __readfsqword(0x28);
  control(1LL);
  init(1LL, a2, v2);
  print_str("Good Job!!\n");
  print_str("Who are you?? : ");
  fgets(s, 130, stdin);
  print_str("Congratulations ");
  print_str(s);
  control(1LL);
  exit(1);
}

int main(int argc, const char **argv, const char **envp)
{
  int v4; // [rsp+Ch] [rbp-54h]
  int v5; // [rsp+10h] [rbp-50h]
  int i; // [rsp+14h] [rbp-4Ch]
  int j; // [rsp+18h] [rbp-48h]
  char s[32]; // [rsp+20h] [rbp-40h] BYREF
  char v9[24]; // [rsp+40h] [rbp-20h] BYREF
  unsigned long v10; // [rsp+58h] [rbp-8h]

  v10 = __readfsqword(0x28);
  v4 = 0;
  v5 = 0;
  init(argc, argv, envp);
  control(1LL);
  print_str("=====================================\n");
  print_str("How can you move on to the next step?\n");
  print_str("=====================================\n");
  print_str("num1 : ");
  fgets(s, 20, stdin);
  for ( i = 0; s[i] > 47 && s[i] <= 57; ++i )
    v4 = 10 * v4 + s[i] - 48;
  print_str("num2 : ");
  fgets(v9, 20, stdin);
  for ( j = 0; v9[j] > 47 && v9[j] <= 57; ++j )
    v5 = 10 * v5 + v9[j] - 48;
  if ( v4 >= 0 && v5 >= 0 && v4 + v5 < 0 )
    vuln();
  print_str("Nope!!\n");
  return 0;
}