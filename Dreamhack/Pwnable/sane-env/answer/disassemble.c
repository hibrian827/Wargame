#include <stdio.h>

int main(int argc, const char **argv, const char **envp)
{
  int v4; // [rsp+24h] [rbp-22Ch] BYREF
  int v5; // [rsp+28h] [rbp-228h]
  int v6; // [rsp+2Ch] [rbp-224h]
  size_t size; // [rsp+30h] [rbp-220h]
  char *buf; // [rsp+38h] [rbp-218h]
  char s[256]; // [rsp+40h] [rbp-210h] BYREF
  char value[264]; // [rsp+140h] [rbp-110h] BYREF
  unsigned long v11; // [rsp+248h] [rbp-8h]

  v11 = __readfsqword(0x28u);
  setup();
  puts("[Sane Env System]");
  do
  {
    menu();
    v5 = 0;
    __isoc99_scanf("%d", &v4);
    if ( v4 == 4 )
    {
      v5 = 1;
    }
    else
    {
      if ( v4 > 4 )
        goto LABEL_36;
      switch ( v4 )
      {
        case 1:
          do
            v6 = getchar();
          while ( v6 != 10 && v6 != -1 );
          printf("Environment variable name: ");
          fgets(s, 256, stdin);
          if ( s[strlen(s) - 1] == 10 )
            s[strlen(s) - 1] = 0;
          printf("Environment variable value: ");
          fgets(value, 256, stdin);
          if ( value[strlen(value) - 1] == 10 )
            value[strlen(value) - 1] = 0;
          if ( setenv(s, value, 1) == -1 )
          {
            puts("setenv() failed!");
            exit(-1);
          }
          puts("Environment variable set!");
          break;
        case 2:
          do
            v6 = getchar();
          while ( v6 != 10 && v6 != -1 );
          printf("Environment variable name: ");
          fgets(s, 256, stdin);
          if ( s[strlen(s) - 1] == 10 )
            s[strlen(s) - 1] = 0;
          if ( unsetenv(s) == -1 )
          {
            puts("unsetenv() failed!");
            exit(-1);
          }
          puts("Environment variable cleared!");
          break;
        case 3:
          size = confstr(0, 0LL, 0LL);
          if ( !size )
          {
            puts("_CS_PATH invalid!");
            exit(-1);
          }

          buf = (char *)malloc(size);
          if ( !buf )
          {
            puts("malloc() failed!");
            exit(-1);
          }
          
          if ( !confstr(0, buf, size) )
          {
            puts("confstr() failed!");
            exit(-1);
          }
          
          if ( setenv("PATH", buf, 1) == -1 )
          {
            puts("PATH setup failed!");
            exit(-1);
          }
          
          free(buf);
          
          if ( system("cat ~/flag") == -1 )
          {
            puts("system() failed!");
            exit(-1);
          }
          
          puts("system() worked!");
          break;
        default:
LABEL_36:
          puts("no hack!");
          exit(-1);
      }
    }
  }
  while ( !v5 );
  return 0;
}