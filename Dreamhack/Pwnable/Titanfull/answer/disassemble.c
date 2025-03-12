int Init()
{
  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(stdout, 0LL, 2, 0LL);
  return setvbuf(stderr, 0LL, 2, 0LL);
}

unsigned long vanguard()
{
  char v1[24]; // [rsp+0h] [rbp-20h] BYREF
  unsigned long v2; // [rsp+18h] [rbp-8h]

  v2 = __readfsqword(0x28);
  puts("You selected RSR vanguard class titan!");
  printf("Please enter the name of titan : ");
  __isoc99_scanf("%s", v1);
  check = 1;
  return __readfsqword(0x28) ^ v2;
}

int select_titan()
{
  int result; // eax
  int i; // [rsp+Ch] [rbp-44h]
  long v2[8]; // [rsp+10h] [rbp-40h]

  v2[7] = 0LL;
  v2[0] = (long)"Ion";
  v2[1] = (long)"Scorch";
  v2[2] = (long)"Northstar";
  v2[3] = (long)"Ronin";
  v2[4] = (long)"Tone";
  v2[5] = (long)"Legion";
  v2[6] = (long)"Monarch";
  for ( i = 1; i <= 7; ++i ) printf("%d. %s\n", (unsigned int)i, (const char *)v2[i - 1]);
  printf("select titan: ");
  __isoc99_scanf("%d", &titan);
  if ( titan > 0 && titan <= 7 )
  {
    result = printf("You select %s.\n", (const char *)v2[titan - 1]);
  }
  else
  {
    puts("Invalid input.");
    result = select_titan();
  }
  check = 1;
  return result;
}

void menu()
{
  int v0; // [rsp+Ch] [rbp-54h] BYREF
  char buf[72]; // [rsp+10h] [rbp-50h] BYREF
  unsigned long v2; // [rsp+58h] [rbp-8h]

  v2 = __readfsqword(0x28);
  puts("-----------------------------------------------------------------------");
  puts(&byte_2108);
  puts(&byte_21E0);
  puts(&byte_22B8);
  puts(&byte_2390);
  puts(&byte_2468);
  puts(&byte_2540);
  puts("-----------------------------------------------------------------------");
  write(1, "What your name pilot? > ", 0x18);
  read(0, buf, 0x30);
  printf("hello, ");
  printf(buf);
  while ( 1 )
  {
    while ( 1 )
    {
      puts("1. Titan select");
      puts("2. Lunch Titan");
      puts("3. exit");
      printf("> ");
      __isoc99_scanf("%d", &v0);
      if ( v0 != 7274 ) break;
      if ( check == 1 ) goto LABEL_18;
      vanguard();
    }
    if ( v0 <= 7274 )
    {
      if ( v0 == 3 )
        exit(0);
      if ( v0 <= 3 )
      {
        if ( v0 == 1 )
        {
          if ( check != 1 ) select_titan();
          else
LABEL_18:
            puts("You already select titan!");
        }
        else if ( v0 == 2 )
        {
          if ( check )
          {
            printf("Standby for titanfall!");
            exit(0);
          }
          puts("Plese select titan!");
        }
      }
    }
  }
}

int main(int argc, const char **argv, const char **envp)
{
  Init(argc, argv, envp);
  menu();
}