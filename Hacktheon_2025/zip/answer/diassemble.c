#include <stdio.h>
#include <malloc.h>
#include <sys/mman.h>
#include <string.h>

long* list1;
long* list2;

long sub_2390(int a1)
{
  int v1; // ebx
  long* v2; // r14
  void *v3; // rax
  unsigned int v4; // ebx
  long v5; // r15
  long v6; // rax
  long result; // rax
  long v8; // r12
  int v9; // ebp
  bool v10; // cf
  unsigned int v11; // ebp
  int *v12; // rax
  long v13; // r12

  if ( !a1 )
    return 0;
  v1 = a1 + 7;
  v2 = list1;
  if ( !list1 )
  {
    list1 = malloc(0x20);
    v3 = mmap(0, 0x1000, 3, 34, -1, 0);
    if ( v3 == (void *)-1 )
    {
      fwrite("fail to mmap\n", 0xD, 1, stderr);
      v2 = 0;
      v4 = v1 & 0xFFFFFFF8;
      v5 = 0x1003E0003;
      goto LABEL_6;
    }
    v2 = list1;
    *(long *)list1 = v3;
    *(int *)(v2 + 8) = 0;
    *(_OWORD *)(v2 + 16) = 0;
  }
  v4 = v1 & 0xFFFFFFF8;
  v5 = *(long *)(v2 + 16);
  if ( !v5 )
  {
LABEL_13:
    v8 = *(unsigned int *)(v2 + 8);
    result = 0;
    v9 = *(int *)(v2 + 8);
    v10 = __CFADD__(v4, v9);
    v11 = v4 + v9;
    if ( !v10 && v11 <= 0x1000 )
    {
      v12 = malloc(0x18);
      *(char *)v12 = 1;
      v12[1] = v4;
      v13 = *(long *)v2 + v8;
      *((long *)v12 + 1) = v13;
      *((long *)v12 + 2) = 0;
      if ( v5 )
        *(long *)(*(long *)(v2 + 24) + 16) = v12;
      else
        *(long *)(v2 + 16) = v12;
      *(long *)(v2 + 24) = v12;
      *(int *)(v2 + 8) = v11;
      return v13;
    }
    return result;
  }
LABEL_6:
  v6 = v5;
  while ( *(char *)v6 != 2 || *(int *)(v6 + 4) != v4 )
  {
    v6 = *(long *)(v6 + 16);
    if ( !v6 )
      goto LABEL_13;
  }
  *(char *)v6 = 1;
  return *(long *)(v6 + 8);
}

long *make_functable()
{
  long *result; // rax

  result = (long *)list2;
  if ( !list2 )
  {
    result = (long *)sub_2390(128);
    *result = sub_1580;
    result[1] = sub_15A0;
    result[2] = sub_15A0;
    result[3] = sub_15A0;
    result[4] = sub_15A0;
    result[5] = sub_15A0;
    result[6] = sub_15A0;
    result[7] = sub_15A0;
    result[8] = sub_15A0;
    result[9] = sub_15A0;
    result[10] = sub_15A0;
    result[11] = sub_15A0;
    result[12] = sub_15A0;
    result[13] = sub_15A0;
    result[14] = sub_15A0;
    list2 = (long)result;
  }
  return result;
}

long decode_zip(long a1, int a2, long a3)
{
  long result; // rax
  long v5; // rsi
  long v6; // r10
  long v7; // rax
  long v8; // r11
  unsigned char v9; // r11
  char v10; // r11

  result = 0;
  if ( (a2 & 3) == 0 && a2 )
  {
    v5 = 0;
    LODWORD(v6) = 0;
    while ( 1 )
    {
      v8 = *(unsigned char *)(a1 + v5);
      if ( v8 == 61 )
        return (unsigned int)v6;
      result = 0;
      if ( (unsigned char)(v8 - 123) >= 0xB0u )
      {
        v9 = byte_3210[v8];
        if ( v9 != 0xFF )
        {
          switch ( v5 & 3 )
          {
            case 0:
              *(char *)(a3 + (unsigned int)v6) = 4 * v9;
              break;
            case 1:
              *(char *)(a3 + (unsigned int)v6) |= (v9 >> 4) & 3;
              v6 = (unsigned int)(v6 + 1);
              v10 = 16 * v9;
              goto LABEL_13;
            case 2:
              *(char *)(a3 + (unsigned int)v6) |= (v9 >> 2) & 0xF;
              v6 = (unsigned int)(v6 + 1);
              v10 = v9 << 6;
LABEL_13:
              *(char *)(a3 + v6) = v10;
              break;
            case 3:
              v7 = (unsigned int)v6;
              LODWORD(v6) = v6 + 1;
              *(char *)(a3 + v7) |= v9;
              break;
          }
          ++v5;
          result = (unsigned int)v6;
          if ( a2 != (int)v5 )
            continue;
        }
      }
      return result;
    }
  }
  return result;
}

_OWORD *sub_2060()
{
  _OWORD *v0; // rbx
  long v1; // rax

  v0 = (_OWORD *)sub_2390(32);
  *v0 = 0;
  v0[1] = 0;
  v1 = sub_2390(22);
  *(_OWORD *)v1 = 0;
  *(long *)(v1 + 14) = 0;
  *((long *)v0 + 2) = v1;
  return v0;
}

bool sub_1C20(_BYTE *a1, FILE *a2)
{
  int v3; // edi
  void *v4; // rax
  size_t v5; // r15
  void *v6; // rax
  size_t v7; // r15
  int v8; // edi
  void *v9; // rax
  size_t v10; // r15
  void *v11; // rax
  _DWORD *v12; // rax

  fread(a1, 1, 0x1E, a2);
  if ( *a1 != 80 || a1[1] != 75 || a1[2] != 3 || a1[3] != 4 )
    return 0;
  v3 = *((unsigned __int16 *)a1 + 13);
  if ( *((_WORD *)a1 + 13) )
  {
    v4 = (void *)sub_2390(v3 + 1);
    *((_QWORD *)a1 + 6) = v4;
    v5 = *((unsigned __int16 *)a1 + 13);
    if ( fread(v4, 1, v5, a2) != v5 )
      return 0;
    *(_BYTE *)(*((_QWORD *)a1 + 6) + *((unsigned __int16 *)a1 + 13)) = 0;
  }
  if ( *((_WORD *)a1 + 14) )
  {
    v6 = (void *)sub_2390(*((unsigned __int16 *)a1 + 14));
    *((_QWORD *)a1 + 4) = v6;
    v7 = *((unsigned __int16 *)a1 + 14);
    if ( fread(v6, 1, v7, a2) != v7 )
      return 0;
  }
  v8 = *(_DWORD *)(a1 + 18);
  if ( v8 )
  {
    v9 = (void *)sub_2390(v8);
    *((_QWORD *)a1 + 7) = v9;
    v10 = *(unsigned int *)(a1 + 18);
    if ( fread(v9, 1, v10, a2) != v10 )
      return 0;
    v11 = (void *)sub_2390(*(_DWORD *)(a1 + 22));
    *((_QWORD *)a1 + 8) = v11;
    memset(v11, 0, *(unsigned int *)(a1 + 22));
    a1[30] = 0;
  }
  if ( (a1[6] & 8) == 0 )
    return 1;
  v12 = (_DWORD *)sub_2390(12);
  *(_QWORD *)v12 = 0;
  v12[2] = 0;
  *((_QWORD *)a1 + 5) = v12;
  return fread(v12, 1, 0xC, a2) == 12;
}

long read_file(long *a1, FILE *a2)
{
  unsigned int v2; // ebp
  unsigned long v3; // r12
  unsigned long v4; // rax
  long v5; // r15
  long v6; // r12
  long v7; // r15

  if ( !(unsigned char)sub_1F20(a1[2], a2, a1 + 3) )
    return 0;
  a1[1] = sub_2390(8 * (unsigned int)*(unsigned __int16 *)(a1[2] + 10));
  *a1 = sub_2390(8 * (unsigned int)*(unsigned __int16 *)(a1[2] + 10));
  fseek(a2, *(unsigned int *)(a1[2] + 16), 0);
  LOBYTE(v2) = 1;
  if ( *(_WORD *)(a1[2] + 10) )
  {
    v3 = 0;
    do
    {
      v5 = sub_2390(72);
      *(_OWORD *)v5 = 0;
      *(_OWORD *)(v5 + 16) = 0;
      *(_OWORD *)(v5 + 32) = 0;
      *(_OWORD *)(v5 + 48) = 0;
      *(long *)(v5 + 64) = 0;
      *(long *)(a1[1] + 8 * v3) = v5;
      if ( !(unsigned char)sub_1DF0(v5, a2) )
      {
        if ( *(long *)(v5 + 64) )
          ((void (*)(void))sub_24D0)();
        if ( *(long *)(v5 + 48) )
          ((void (*)(void))sub_24D0)();
        if ( *(long *)(v5 + 56) )
          ((void (*)(void))sub_24D0)();
        sub_24D0(v5);
      }
      ++v3;
      v4 = *(unsigned __int16 *)(a1[2] + 10);
    }
    while ( v3 < v4 );
    if ( (_WORD)v4 )
    {
      v6 = 0;
      while ( 1 )
      {
        fseek(a2, *(unsigned int *)(*(long *)(a1[1] + 8 * v6) + 42), 0);
        v7 = sub_2390(72);
        *(_OWORD *)v7 = 0;
        *(_OWORD *)(v7 + 16) = 0;
        *(_OWORD *)(v7 + 32) = 0;
        *(_OWORD *)(v7 + 48) = 0;
        *(long *)(v7 + 64) = 0;
        *(long *)(*a1 + 8 * v6) = v7;
        if ( !(unsigned char)sub_1C20(v7, a2) )
          break;
        if ( ++v6 >= (unsigned long)*(unsigned __int16 *)(a1[2] + 10) )
          return v2;
      }
      sub_1BC0(v7);
      return 0;
    }
  }
  return v2;
}

char show_entries(long *a1)
{
  long v1; // rax
  unsigned long i; // r15
  long v3; // rcx
  long v4; // rdx
  const void *v5; // r12
  unsigned __int16 v6; // bp

  v1 = a1[2];
  if ( *(_WORD *)(v1 + 10) )
  {
    for ( i = 0; i < *(unsigned __int16 *)(v1 + 10); ++i )
    {
      v3 = *(long *)(a1[1] + 8 * i);
      v4 = *(long *)(*a1 + 8 * i);
      v5 = *(const void **)(v4 + 48);
      if ( v5 )
      {
        v6 = *(_WORD *)(v4 + 26);
        if ( v6 )
          goto LABEL_6;
      }
      else
      {
        v5 = *(const void **)(v3 + 64);
        v6 = *(_WORD *)(v4 + 26);
        if ( v6 )
        {
LABEL_6:
          if ( v5 )
            goto LABEL_10;
          continue;
        }
      }
      v6 = *(_WORD *)(v3 + 28);
      if ( v5 )
      {
LABEL_10:
        if ( v6 )
        {
          printf("Entry %d: ", (unsigned int)i);
          fwrite(v5, 1, v6, stdout);
          putchar(10);
          v1 = a1[2];
        }
      }
    }
  }
  return 1;
}

char sub_1A30(_QWORD *a1)
{
  char result; // al
  __int64 v2; // r12
  __int64 v3; // rbp
  __int64 v4; // rbx
  unsigned int v5; // r13d
  __int64 v6; // rbp
  unsigned __int16 v7; // ax
  const char *v8; // rbx

  result = 1;
  if ( *(_WORD *)(a1[2] + 10) )
  {
    v2 = 0;
    while ( 1 )
    {
      v3 = *(_QWORD *)(a1[1] + 8 * v2);
      v4 = *(_QWORD *)(*a1 + 8 * v2);
      if ( *(_BYTE *)(v4 + 30) )
      {
        v5 = *(_DWORD *)(v4 + 22);
        if ( v5 )
          goto LABEL_6;
        goto LABEL_16;
      }
      v7 = *(_WORD *)(v4 + 8);
      if ( v7 )
      {
        if ( !*(_DWORD *)(v4 + 18) )
          goto LABEL_12;
      }
      else
      {
        v7 = *(_WORD *)(v3 + 10);
        if ( !*(_DWORD *)(v4 + 18) )
        {
LABEL_12:
          if ( !*(_DWORD *)(v3 + 20) )
            goto LABEL_15;
        }
      }
      if ( *(_QWORD *)(v4 + 64) && !(unsigned __int8)sub_1630(v7, *(_QWORD *)(v4 + 56)) )
        return 0;
LABEL_15:
      *(_BYTE *)(v4 + 30) = 1;
      v5 = *(_DWORD *)(v4 + 22);
      if ( v5 )
      {
LABEL_6:
        v6 = *(_QWORD *)(v4 + 64);
        if ( v6 )
          goto LABEL_17;
        goto LABEL_3;
      }
LABEL_16:
      v5 = *(_DWORD *)(v3 + 24);
      v6 = *(_QWORD *)(v4 + 64);
      if ( v6 )
      {
LABEL_17:
        if ( v5 )
        {
          v8 = (const char *)malloc(2 * (((2863311531u * (unsigned __int64)(v5 + 2)) >> 32) & 0xFFFFFFFE) + 1);
          sub_1740(v6, v5, v8);
          printf("Entry %d: %s\n", (unsigned int)v2, v8);
        }
      }
LABEL_3:
      if ( ++v2 >= (unsigned __int64)*(unsigned __int16 *)(a1[2] + 10) )
        return 1;
    }
  }
  return result;
}

char sub_1BC0(long *a1)
{
  long v2; // rdi
  long v3; // rdi
  long v4; // rdi
  long v5; // rdi
  long v6; // rdi

  v2 = a1[6];
  if ( v2 )
    sub_24D0(v2);
  v3 = a1[4];
  if ( v3 )
    sub_24D0(v3);
  v4 = a1[7];
  if ( v4 )
    sub_24D0(v4);
  v5 = a1[8];
  if ( v5 )
    sub_24D0(v5);
  v6 = a1[5];
  if ( v6 )
    sub_24D0(v6);
  sub_24D0((long)a1);
  return 1;
}

char sub_24D0(long a1)
{
  long v1; // rax

  v1 = list1;
  while ( 1 )
  {
    v1 = *(long *)(v1 + 16);
    if ( !v1 )
      break;
    if ( *(long *)(v1 + 8) == a1 )
    {
      *(char *)v1 = 2;
      return 1;
    }
  }
  return 0;
}

char sub_20A0(long *a1)
{
  unsigned long v2; // r14
  long v3; // rdi
  unsigned long v4; // r15
  long *v5; // r14
  long v6; // rdi
  long v7; // rdi
  long v8; // rdi

  if ( *a1 && *(_WORD *)(a1[2] + 10) )
  {
    v2 = 0;
    do
      sub_1BC0(*(long *)(*a1 + 8 * v2++));
    while ( v2 < *(unsigned __int16 *)(a1[2] + 10) );
  }
  v3 = a1[2];
  if ( a1[1] )
  {
    if ( *(_WORD *)(v3 + 10) )
    {
      v4 = 0;
      do
      {
        v5 = *(long **)(a1[1] + 8 * v4);
        v6 = v5[8];
        if ( v6 )
          sub_24D0(v6);
        v7 = v5[6];
        if ( v7 )
          sub_24D0(v7);
        v8 = v5[7];
        if ( v8 )
          sub_24D0(v8);
        sub_24D0(v5);
        ++v4;
        v3 = a1[2];
      }
      while ( v4 < *(unsigned __int16 *)(v3 + 10) );
    }
    goto LABEL_16;
  }
  if ( v3 )
LABEL_16:
    sub_24D0(v3);
  sub_24D0(a1);
  return 1;
}

long main(int a1, char **a2, char **a3)
{
  size_t v3; // rax
  unsigned int v4; // ebx
  void *v5; // r14
  size_t v6; // rsi
  FILE *v7; // rbx
  long v8; // r14
  long result; // rax
  int v10[1028]; // [rsp+0h] [rbp-1048h] BYREF
  unsigned long v11; // [rsp+1010h] [rbp-38h]

  setvbuf(stdin, 0, 2, 0);
  setvbuf(stdout, 0, 2, 0);
  setvbuf(stderr, 0, 2, 0);
  make_functable();
  while ( 1 )
  {
    printf("Base64 encoded ZIP>> ");
    scanf("%4096s", v10);
    v3 = strlen((const char *)v10);
    v4 = v3;
    v5 = malloc(3 * (unsigned int)(v3 >> 2));
    v6 = (unsigned int)decode_zip(v10, v4, v5);
    v7 = fmemopen(v5, v6, "r");
    v8 = sub_2060();
    if ( !(unsigned char)read_file(v8, v7) )
      break;
    do
    {
      while ( 1 )
      {
        while ( 1 )
        {
          printf("Menu>> ");
          scanf("%u", v10);
          if ( v10[0] != 1 )
            break;
          show_entries(v8);
        }
        if ( v10[0] != 2 )
          break;
        sub_1A30(v8);
      }
    }
    while ( v10[0] );
    fclose(v7);
    sub_20A0(v8);
  }
}