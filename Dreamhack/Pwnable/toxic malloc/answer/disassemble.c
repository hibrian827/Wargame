#include <stdio.h>

FILE **sub_11B0()
{
  return &stdout;
}

FILE **sub_1220()
{
  FILE **result; // rax

  if ( !byte_4028 )
  {
    if ( &__cxa_finalize )
      _cxa_finalize(off_4008);
    result = sub_11B0();
    byte_4028 = 1;
  }
  return result;
}

int sub_1269()
{
  setvbuf(stdin, 0, 2, 0);
  return setvbuf(stdout, 0, 2, 0);
}

unsigned sub_12B0(long a1)
{
  void **v1; // rbx
  unsigned int v3; // [rsp+14h] [rbp-1Ch] BYREF
  unsigned long v4; // [rsp+18h] [rbp-18h]

  v4 = __readfsqword(0x28u);
  v3 = 0;
  printf("enter index for new data (0-4): ");
  __isoc99_scanf("%d", &v3);
  if ( v3 < 5 )
  {
    if ( *(long *)(8 * (int)v3 + a1) )
      free(*(void **)(8 * (int)v3 + a1));
    v1 = (void **)(8 * (int)v3 + a1);
    *v1 = malloc(0xB0);
    if ( !*(long *)(8 * (int)v3 + a1) )
    {
      puts("memory allocation failed.");
      exit(1);
    }
    printf("enter data for creation: ");
    read(0, *(void **)(8 * (int)v3 + a1), 0xAF);
  }
  else
  {
    puts("invalid index. please try again.");
  }
  return v4 - __readfsqword(0x28u);
}

unsigned sub_1412(long a1)
{
  unsigned int v2; // [rsp+14h] [rbp-Ch] BYREF
  unsigned long v3; // [rsp+18h] [rbp-8h]

  v3 = __readfsqword(0x28u);
  v2 = 0;
  printf("enter index of data to update (0-4): ");
  __isoc99_scanf("%d", &v2);
  if ( v2 < 5 )
  {
    if ( *(long *)(8 * (int)v2 + a1) )
    {
      printf("enter data for update: ");
      read(0, *(void **)(8 * (int)v2 + a1), 0xAF);
    }
    else
    {
      puts("no data to update. please create data first.");
    }
  }
  else
  {
    puts("invalid index. please try again.");
  }
  return v3 - __readfsqword(0x28u);
}

unsigned sub_1507(long a1)
{
  unsigned int v2; // [rsp+14h] [rbp-Ch] BYREF
  unsigned long v3; // [rsp+18h] [rbp-8h]

  v3 = __readfsqword(0x28u);
  v2 = 0;
  printf("enter index of data to read (0-4): ");
  __isoc99_scanf("%d", &v2);
  if ( v2 < 5 )
  {
    if ( *(long *)(8 * (int)v2 + a1) )
      printf("data: %s\n", *(const char **)(8 * (int)v2 + a1));
    else
      puts("no data to read. please create data first.");
  }
  else
  {
    puts("invalid index. please try again.");
  }
  return v3 - __readfsqword(0x28u);
}

unsigned sub_15ED(long a1)
{
  unsigned int v2; // [rsp+14h] [rbp-Ch] BYREF
  unsigned long v3; // [rsp+18h] [rbp-8h]

  v3 = __readfsqword(0x28u);
  v2 = 0;
  printf("enter index of data to delete (0-4): ");
  __isoc99_scanf("%d", &v2);
  if ( v2 < 5 )
  {
    if ( *(long *)(8 * (int)v2 + a1) )
    {
      free(*(void **)(8 * (int)v2 + a1));
      puts("data deleted successfy.");
    }
    else
    {
      puts("no data to delete.");
    }
  }
  else
  {
    puts("invalid index. please try again.");
  }
  return v3 - __readfsqword(0x28u);
}

void sub_16D3()
{
  long v0; // [rsp+8h] [rbp-38h] BYREF
  long v1[6]; // [rsp+10h] [rbp-30h] BYREF

  v1[5] = __readfsqword(0x28u);
  memset(v1, 0, 40);
  while ( 1 )
  {
    puts("\n=== menu ===");
    puts("1. create");
    puts("2. update");
    puts("3. read");
    puts("4. delete");
    puts("5. exit");
    printf("enter your choice: ");
    __isoc99_scanf("%ld", &v0);
    while ( getchar() != 10 )
      ;
    switch ( v0 )
    {
      case 1:
        sub_12B0(v1);
        break;
      case 2:
        sub_1412(v1);
        break;
      case 3:
        sub_1507(v1);
        break;
      case 4:
        sub_15ED(v1);
        break;
      case 5:
        puts("exiting program.");
        exit(0);
      default:
        printf("%ld is invalid choice, please try again.\n", v0);
        break;
    }
  }
}

int main(long a1, char **a2, char **a3)
{
  sub_1269(a1, a2, a3);
  sub_16D3();
  return 0;
}