int __fastcall sub_140001020(FILE *a1, const char *a2, __crt_locale_pointers *a3, va_list a4)
{
  unsigned __int64 *v4; // rax

  v4 = (unsigned __int64 *)sub_140001000();
  return _stdio_common_vfprintf(*v4, a1, a2, a3, a4);
}

__int64 print_func(__int64 a1, ...)
{
  FILE *v1; // rax
  va_list va; // [rsp+58h] [rbp+10h] BYREF

  va_start(va, a1);
  v1 = _acrt_iob_func(1u);
  return (unsigned int)sub_140001020(v1, a1, 0LL, (__int64 *)va);
}

int __fastcall sub_1400010F0(FILE *a1, const char *a2, __crt_locale_pointers *a3, va_list a4)
{
  unsigned __int64 *v4; // rax

  v4 = (unsigned __int64 *)sub_140001010();
  return _stdio_common_vfscanf(*v4, a1, a2, a3, a4);
}

__int64 sub_140001140(const char *a1, ...)
{
  FILE *v1; // rax
  va_list va; // [rsp+58h] [rbp+10h] BYREF

  va_start(va, a1);
  v1 = _acrt_iob_func(0);
  return (unsigned int)sub_1400010F0(v1, a1, 0LL, (__int64 *)va);
}

__int64 __fastcall sub_140001270(__int64 a1)
{
  unsigned int v2; // [rsp+0h] [rbp-18h]
  int v3; // [rsp+4h] [rbp-14h]

  v3 = 0;
  v2 = 0;
  while ( *(_BYTE *)(a1 + v3) )
  {
    ++v2;
    ++v3;
  }
  return v2;
}

__int64 print_func(__int64 a1, ...)
{
  FILE *v1; // rax
  va_list va; // [rsp+58h] [rbp+10h] BYREF

  va_start(va, a1);
  v1 = _acrt_iob_func(1u);
  return (unsigned int)sub_140001020(v1, a1, 0LL, (__int64 *)va);
}

_BOOL8 __fastcall sub_1400012D0(__int64 a1)
{
  unsigned int v2; // [rsp+24h] [rbp-14h]
  int i; // [rsp+28h] [rbp-10h]

  v2 = 0;
  for ( i = 0; i < (int)sub_140001270(a1); ++i )
    ++v2;
  print_func((__int64)&unk_1400032C0, v2);
  system("pause");
  return v2 != 14;
}

__int64 __fastcall sub_140001390(int a1)
{
  system("cls");
  if ( a1 != -2 )
  {
    if ( a1 != -1 )
    {
      if ( a1 != 2 )
        print_func((__int64)"You Wrong Length!\n");
      print_func((__int64)"YOU THINK SERIAL! by Calc!! :P\n");
    }
    system("calc");
  }
  return print_func((__int64)"Cheer Up!!\n");
}

__int64 __fastcall sub_140001430(__int64 a1)
{
  __int64 v2; // [rsp+30h] [rbp-28h]

  v2 = -1LL;
  do
    ++v2;
  while ( *(_BYTE *)(a1 + v2) );
  system("cls");
  print_func((__int64)"welcome first routine\n");
  print_func((__int64)"Do you know it is detour?\n");
  Sleep(0x1F4u);
  return sub_140001390(-1);
}

__int64 sub_1400011C0()
{
  char v1[16]; // [rsp+28h] [rbp-20h] BYREF

  print_func((__int64)"\n\n\tInput >> ");
  sub_140001140("%s", v1);
  if ( (unsigned int)sub_1400012D0(v1) )
    return print_func((__int64)"nono\n");
  else
    return sub_140001430(v1);
}

int __fastcall main(int argc, const char **argv, const char **envp)
{
  __int64 v3; // rdx
  __int64 v4; // r8

  print_func("W3lC0me WHS2 CTF :D\n", argv, envp);
  print_func("developer... constant\n", v3, v4);
  sub_1400011C0();
  return 0;
}


__int64 __fastcall sub_140001610(__int64 a1)
{
  int i; // [rsp+20h] [rbp-68h]
  int v3; // [rsp+24h] [rbp-64h]
  int v4; // [rsp+28h] [rbp-60h]
  unsigned __int64 v5; // [rsp+30h] [rbp-58h]
  int v6[14]; // [rsp+40h] [rbp-48h] BYREF

  v3 = 0;
  v4 = 0;
  v6[0] = 204;
  v6[1] = 204;
  v6[2] = 204;
  v6[3] = 204;
  v6[4] = 204;
  v6[5] = 204;
  v6[6] = 204;
  v6[7] = 204;
  v6[8] = 204;
  v6[9] = 204;
  v6[10] = 204;
  v6[11] = 204;
  v6[12] = 204;
  memset(&v6[13], 0, sizeof(int));
  for ( i = 0; ; ++i )
  {
    v5 = -1LL;
    do
      ++v5;
    while ( *(_BYTE *)(a1 + v5) );
    if ( i >= v5 )
      break;
    if ( *(_BYTE *)(a1 + i) != 45 || *(_BYTE *)(a1 + i) != 115 || *(_BYTE *)(a1 + i) != 77 )
    {
      if ( *(_BYTE *)(a1 + i) == 74 )
      {
        *(_BYTE *)(a1 + i) ^= 2u;
        v6[i] ^= 2u;
        ++v3;
      }
      if ( *(_BYTE *)(a1 + i) == 102 )
      {
        *(_BYTE *)(a1 + i) ^= 3u;
        v6[i] &= 2u;
        *(_BYTE *)(a1 + i) |= 5u;
        *(_BYTE *)(a1 + i) ^= 0xAu;
        *(_BYTE *)(a1 + i) ^= 0xAu;
        v6[i] |= 2u;
        ++v3;
      }
      if ( *(_BYTE *)(a1 + i) == 105 )
      {
        v6[i] ^= 4u;
        *(_BYTE *)(a1 + i) ^= 5u;
        v6[i] += 5;
        ++v3;
      }
      if ( *(_BYTE *)(a1 + i) == 122 )
      {
        v6[i] += 2;
        *(_BYTE *)(a1 + i) -= 10;
        *(_BYTE *)(a1 + i) ^= 0x1Fu;
        ++v3;
      }
      if ( *(_BYTE *)(a1 + i) == 69 )
      {
        v6[i] -= 3;
        *(_BYTE *)(a1 + i) += 12;
        *(_BYTE *)(a1 + i) ^= 0x18u;
        ++v3;
      }
      if ( *(_BYTE *)(a1 + i) == 120 )
      {
        v6[i] -= 3;
        *(_BYTE *)(a1 + i) += 11;
        *(_BYTE *)(a1 + i) ^= 0xF7u;
        ++v3;
      }
      if ( *(_BYTE *)(a1 + i) == 81 )
      {
        v6[i] -= 4;
        *(_BYTE *)(a1 + i) += 12;
        *(_BYTE *)(a1 + i) ^= 0x14u;
        ++v3;
      }
      v4 = v3;
    }
  }
  if ( v4 == 9 )
    return sub_140001B40(a1);
  else
    return sub_140001390(-2);
}

__int64 __fastcall sub_140001B40(__int64 a1)
{
  int i; // [rsp+20h] [rbp-48h]
  char v3[24]; // [rsp+28h] [rbp-40h] BYREF

  strcpy(v3, "submit it");
  memset(&v3[10], 0, 0xBuLL);
  print_func((__int64)"flag{");
  for ( i = 0; i < 14; ++i )
    print_func((__int64)"%c", (unsigned int)*(char *)(a1 + i));
  print_func((__int64)"}\n");
  print_func((__int64)"%s\n", v3);
  return print_func((__int64)"THANKS\n");
}