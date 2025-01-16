int flag()
{
  char *argv[4]; // [rsp+0h] [rbp-20h] BYREF

  argv[3] = "/bin/sh";
  argv[0] = "/bin/sh";
  argv[1] = 0;
  return execve("/bin/sh", argv, 0LL);
}

int calendar(char *a1, unsigned int *a2)
{
  int v3[12]; // [rsp+10h] [rbp-50h] BYREF
  int v4[8]; // [rsp+40h] [rbp-20h] BYREF

  v4[0] = 7238995;
  v4[1] = 7237453;
  v4[2] = 6649172;
  v4[3] = 6579543;
  v4[4] = 7694420;
  v4[5] = 6910534;
  v4[6] = 7627091;
  v3[0] = 7233866;
  v3[1] = 6448454;
  v3[2] = 7496013;
  v3[3] = 7499841;
  v3[4] = 7954765;
  v3[5] = 7238986;
  v3[6] = 7107914;
  v3[7] = 6780225;
  v3[8] = 7365971;
  v3[9] = 7627599;
  v3[10] = 7761742;
  v3[11] = 6513988;
  return sprintf(
           a1,
           "%.3s %3s%3d %.2d:%.2d:%.2d %d\n",
           (const char *)&v4[a2[6]],
           (const char *)&v3[a2[4]],
           a2[3],
           a2[2],
           a2[1],
           *a2,
           a2[5] + 1900);
}

int main(int argc, const char **argv, const char **envp)
{
  int v3; // eax
  int sec; // [rsp+18h] [rbp-78h] BYREF
  int min; // [rsp+1Ch] [rbp-74h] BYREF
  int hour; // [rsp+20h] [rbp-70h] BYREF
  int year; // [rsp+24h] [rbp-6Ch] BYREF
  int month; // [rsp+28h] [rbp-68h] BYREF
  int day; // [rsp+2Ch] [rbp-64h] BYREF
  int v11[3]; // [rsp+30h] [rbp-60h] BYREF
  int v12; // [rsp+3Ch] [rbp-54h]
  int v13; // [rsp+40h] [rbp-50h]
  int v14; // [rsp+44h] [rbp-4Ch]
  int v15; // [rsp+48h] [rbp-48h]
  char v16[28]; // [rsp+70h] [rbp-20h] BYREF
  int v17; // [rsp+8Ch] [rbp-4h]

  v17 = 0;
  setup(argc, argv, envp);
  puts("Calendar v0.1");
  
  printf("Year: ");
  __isoc99_scanf("%d", &year);
  v14 = year - 1900;
  
  printf("Month: ");
  __isoc99_scanf("%d", &month);
  month = (month - 1) % 12;
  v13 = month++;
  
  printf("Day: ");
  __isoc99_scanf("%d", &day);
  day = (day - 1) % 31 + 1;
  v12 = day;
  
  printf("Hour: ");
  __isoc99_scanf("%d", &hour);
  hour %= 24;
  v11[2] = hour;
  
  printf("Minute: ");
  __isoc99_scanf("%d", &min);
  min %= 60;
  v11[1] = min;
  
  printf("Second: ");
  __isoc99_scanf("%d", &sec);
  sec %= 60;
  v11[0] = sec;
  
  if ( month > 2 )
    v3 = year - 2;
  else
    v3 = year--;
  
  day += v3;
  v15 = (year / -100 + year / 4 + 23 * month / 9 + day + 4 + year / 400) % 7;
  
  calendar(v16, v11);
  
  printf("Formatted date: %s", v16);
  if ( v13 == 11 && v12 == 25 && !v15 && v17 )
  {
    puts("A Present for Admin!");
    flag();
  }
  return 0;
}