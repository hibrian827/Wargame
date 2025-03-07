void * start_routine(void *a1)
{
  if ( qword_4038 != 3735928559 )
  {
    sleep(0xA);
    qword_4030 = qword_4038;
  }
  return 0;
}

void * sub_13D7(const char *a1)
{
  FILE *stream; // [rsp+10h] [rbp-20h]
  long n; // [rsp+18h] [rbp-18h]
  void *ptr; // [rsp+20h] [rbp-10h]

  stream = fopen(a1, "r");
  if ( !stream )
  {
    perror("Failed to open flag file\n");
    exit(1);
  }
  fseek(stream, 0, 2);
  n = ftell(stream);
  rewind(stream);
  ptr = malloc(n + 1);
  if ( !ptr )
  {
    perror("Memory allocation failed\n");
    exit(1);
  }
  fread(ptr, 1, n, stream);
  *((_BYTE *)ptr + n) = 0;
  fclose(stream);
  return ptr;
}

unsigned long sub_1369()
{
  unsigned long v1; // [rsp+8h] [rbp-8h]

  v1 = __readfsqword(0x28);
  setvbuf(stdin, 0, 2, 0);
  setvbuf(stdout, 0, 2, 0);
  return v1 - __readfsqword(0x28);
}

void main(long a1, char **a2, char **a3)
{
  int v3; // [rsp+4h] [rbp-1Ch] BYREF
  pthread_t newthread; // [rsp+8h] [rbp-18h] BYREF
  void *ptr; // [rsp+10h] [rbp-10h]
  unsigned long v6; // [rsp+18h] [rbp-8h]

  v6 = __readfsqword(0x28);
  sub_1369(a1, a2, a3);
  ptr = (void *)sub_13D7("./flag");
  qword_4030 = 0;
  while ( 1 )
  {
    sub_154B();
    printf("Input: ");
    __isoc99_scanf("%u", &v3);
    if ( v3 == 4 )
    {
      free(ptr);
      exit(0);
    }
    if ( v3 > 4 )
    {
LABEL_16:
      puts("Invalid Menu! Please try again.");
    }
    else
    {
      switch ( v3 )
      {
        case 3:
          if ( qword_4030 == 3735928559 )
            printf("Flag : %s\n", (const char *)ptr);
          else
            puts("Don't have permission!");
          break;
        case 1:
          printf("Input: ");
          __isoc99_scanf("%lu", &qword_4038);
          break;
        case 2:
          if ( pthread_create(&newthread, 0LL, start_routine, 0LL) )
          {
            perror("Thread creation failed\n");
            exit(1);
          }
          pthread_detach(newthread);
          break;
        default:
          goto LABEL_16;
      }
    }
  }
}