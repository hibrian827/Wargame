int added;
int pagenum;
int size;
int edit_size;

int init()
{
  int i; // [rsp+Ch] [rbp-4h]

  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(_bss_start, 0LL, 2, 0LL);
  setvbuf(stderr, 0LL, 2, 0LL);
  puts(&s);
  puts(&byte_20A8);
  puts(&byte_20E8);
  for ( i = 0; i <= 1; ++i )
    puts(&byte_2188);
  return puts(&byte_21C8);
}

int menu()
{
  puts("\n===== 4-page article =====");
  puts("1. new article");
  puts("2. view article");
  puts("3. edit article");
  puts("4. Exit");
  return printf("> ");
}

int main(int argc, const char **argv, const char **envp)
{
  int v4; // [rsp+24h] [rbp-11Ch] BYREF
  void *buf; // [rsp+28h] [rbp-118h]
  char s[264]; // [rsp+30h] [rbp-110h] BYREF
  unsigned __int64 v7; // [rsp+138h] [rbp-8h]

  v7 = __readfsqword(0x28u);
  v4 = -1;
  init();
  memset(s, 0, 0x100uLL);
  while ( 1 )
  {
    menu();
    __isoc99_scanf("%d", &v4);
    if ( v4 == 4 )
      return 0;
    if ( v4 == 3 )
    {
      if ( added )
      {
        printf("Page number: ");
        __isoc99_scanf("%u", &pagenum);
        if ( (unsigned int)pagenum > 4 )
        {
          puts("[ERROR] Only [0~3] page is available");
          exit(-1);
        }
        printf("Edit size: ");
        __isoc99_scanf("%u", &edit_size);
        if ( (unsigned int)edit_size > 0x40 )
        {
          puts("[ERROR] Too large");
          exit(-1);
        }
        printf("Write content : ");
        buf = &s[pagenum << 6];
        read(0, buf, 0x40);
      }
      else
      {
LABEL_14:
        puts("Write a article first");
      }
    }
    else
    {
      if ( v4 > 3 )
        goto LABEL_22;
      if ( v4 == 1 )
      {
        if ( added )
        {
          puts("article already written");
        }
        else
        {
          printf("Enter article size : ");
          __isoc99_scanf("%u", &size);
          if ( (unsigned int)size > 0x100 )
          {
            puts("[ERROR] Too large");
            exit(-1);
          }
          printf("Write content : ");
          read(0, s, (unsigned int)size);
          ++added;
        }
      }
      else if ( v4 == 2 )
      {
        if ( !added )
          goto LABEL_14;
        printf("Content: %s\n", s);
      }
      else
      {
LABEL_22:
        puts("Invalid choice");
      }
    }
  }
}