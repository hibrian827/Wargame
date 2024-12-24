#include <stdio.h>

void sub_403520(char *s, __int64 a2, ...)
{
  gcc_va_list va; // [rsp+8h] [rbp-D0h] BYREF

  va_start(va, a2);
  __vfprintf_chk(stderr, 1LL, a2, va);
  perror(s);
}

void *sub_403070()
{
  void *v0; // r12
  char v2; // [rsp+0h] [rbp-8h]

  v0 = calloc(1uLL, 0x5088uLL);
  if ( !v0 )
    sub_403520("calloc", v2);
  return v0;
}

__int64 sub_4045E0(char *s, char *path)
{
  ssize_t v2; // rax
  char *v3; // rax
  unsigned int v4; // r13d
  char *v6; // rax
  int v7; // [rsp+Ch] [rbp-106Ch] BYREF
  __int128 v8; // [rsp+10h] [rbp-1068h] BYREF
  __int128 v9; // [rsp+20h] [rbp-1058h]
  __int128 v10; // [rsp+30h] [rbp-1048h]
  __int128 v11; // [rsp+40h] [rbp-1038h]
  char v12; // [rsp+50h] [rbp-1028h]
  struct stat stat_buf; // [rsp+60h] [rbp-1018h] BYREF

  v2 = readlink("/proc/self/exe", s, 0xFFFuLL);
  if ( v2 == -1 )
  {
    v12 = 0;
    v8 = 0LL;
    v9 = 0LL;
    v10 = 0LL;
    v11 = 0LL;
    v7 = 0;
    v6 = __xpg_basename(s);
    __strcpy_chk(&stat_buf, v6, 4096LL);
    __isoc99_sscanf(&stat_buf, "ld-%64[^.].so.%d", &v8, &v7);
  }
  else
  {
    s[v2] = 0;
    v8 = 0LL;
    v9 = 0LL;
    v10 = 0LL;
    v11 = 0LL;
    v12 = 0;
    v7 = 0;
    v3 = __xpg_basename(s);
    __strcpy_chk(&stat_buf, v3, 4096LL);
    if ( (unsigned int)__isoc99_sscanf(&stat_buf, "ld-%64[^.].so.%d", &v8, &v7) != 2 )
      goto LABEL_5;
  }
  if ( strchr(path, 47) )
  {
    v4 = sub_404470(s, path);
    if ( !v4 )
      return v4;
  }
  else if ( !(unsigned int)sub_404550((char *)&stat_buf) && snprintf((char *)&stat_buf, 0x1000uLL, "%s", path) > 4095
         || !(unsigned int)sub_404470(s, (char *)&stat_buf) )
  {
    return 0;
  }
LABEL_5:
  v4 = 1;
  if ( __lxstat(1, s, &stat_buf) >= 0 )
  {
    v4 = 1;
    if ( (stat_buf.st_mode & 0xF000) == 40960
      && (snprintf((char *)&stat_buf, 0x1000uLL, "%s", s) > 4095 || !realpath((const char *)&stat_buf, s)) )
    {
      return 0;
    }
  }
  return v4;
}

__int64 sub_403E50(unsigned int a1, char **a2)
{
  __int64 v4; // rax
  __int64 v5; // rbp
  _BOOL4 v6; // ebx
  const char *v7; // r12
  _BYTE *v8; // rax
  char *v9; // rsi
  __int64 v10; // rax
  void *v11; // r14
  int v12; // edx
  int v13; // ecx
  int v14; // r8d
  int v15; // r9d
  const char *v16; // rdi
  unsigned int v17; // r12d
  int v19; // ecx
  int v20; // r8d
  int v21; // r9d
  FILE *v22; // rax
  int v23; // ecx
  int v24; // r8d
  int v25; // r9d
  int v26; // edx
  FILE *v27; // r14
  __int64 v28; // rdi
  __int64 v29; // [rsp+8h] [rbp-2050h] BYREF
  __int64 s2[2]; // [rsp+10h] [rbp-2048h] BYREF
  char filename[4096]; // [rsp+20h] [rbp-2038h] BYREF
  char v32[4152]; // [rsp+1020h] [rbp-1038h] BYREF

  v29 = 0LL;
  v4 = sub_403070();
  if ( !v4 )
    return (unsigned int)-1;
  v5 = v4;
  if ( !(unsigned int)sub_4045E0(filename, *a2) || !(unsigned int)sub_4047D0(v32, filename) )
    return (unsigned int)-1;
  v6 = 0;
  v7 = (const char *)sub_4079E0("_MEIPASS2");
  if ( v7 )
  {
    v6 = 1;
    v8 = (_BYTE *)sub_4079E0("_PYI_ONEDIR_MODE");
    if ( v8 )
    {
      if ( *v8 == 49 )
        v6 = v8[1] != 0;
      free(v8);
      j__unsetenv("_PYI_ONEDIR_MODE");
    }
  }
  j__unsetenv("_MEIPASS2");
  v9 = filename;
  if ( !(unsigned int)sub_403160(v5, filename) )
  {
    v9 = v32;
    if ( !(unsigned int)sub_403160(v5, v32) )
    {
      sub_403450(
        (unsigned int)"Cannot open PyInstaller archive from executable (%s) or external archive (%s)\n",
        (unsigned int)filename,
        (unsigned int)v32,
        v19,
        v20,
        v21);
      return (unsigned int)-1;
    }
    if ( !v7 )
    {
      v22 = fopen(filename, "rb");
      v26 = -1;
      v27 = v22;
      if ( !v22 )
      {
LABEL_28:
        v17 = -1;
        sub_403450(
          (unsigned int)"Cannot side-load external archive %s (code %d)!\n",
          (unsigned int)v32,
          v26,
          v23,
          v24,
          v25);
        return v17;
      }
      v9 = (char *)s2;
      s2[0] = 0xE0B0A0B0D49454DLL;
      if ( !sub_408590(v22, s2, 8uLL) )
      {
        fclose(v27);
        v26 = 1;
        goto LABEL_28;
      }
    }
  }
  v10 = sub_4079E0("_PYI_PROCNAME");
  v11 = (void *)v10;
  if ( v10 )
  {
    v9 = (char *)v10;
    if ( prctl(15, v10, 0LL, 0LL) )
    {
      v17 = -1;
      sub_403450((unsigned int)"LOADER: failed to set linux process name!\n", (_DWORD)v9, v12, v13, v14, v15);
      return v17;
    }
    free(v11);
  }
  v16 = "_PYI_PROCNAME";
  j__unsetenv("_PYI_PROCNAME");
  *(_DWORD *)(v5 + 20604) = a1;
  *(_QWORD *)(v5 + 20608) = a2;
  if ( v6 )
  {
    if ( v7 || *(_DWORD *)(v5 + 20592) )
    {
      v29 = sub_406D70("_PYI_PROCNAME", v9);
LABEL_16:
      sub_406DB0(&v29);
      goto LABEL_17;
    }
    goto LABEL_44;
  }
  if ( *(_DWORD *)(v5 + 20592) )
  {
    v16 = (const char *)v5;
    if ( (unsigned int)sub_403320(v5) == -1 )
      return (unsigned int)-1;
    if ( v7 || *(_DWORD *)(v5 + 20592) )
      goto LABEL_31;
  }
  else if ( v7 )
  {
LABEL_31:
    v29 = sub_406D70(v16, v9);
    v28 = v29;
    goto LABEL_32;
  }
LABEL_44:
  sub_407A10("_MEIPASS2", v5 + 8304);
  sub_407A10("_PYI_ONEDIR_MODE", 4231188LL);
  if ( (unsigned int)sub_408030((char *)(v5 + 8304)) == -1 || (unsigned int)sub_4081C0(filename) == -1 )
    return (unsigned int)-1;
  v29 = sub_406D70(filename, a1);
  v28 = v29;
  if ( v6 )
    goto LABEL_16;
LABEL_32:
  if ( (unsigned int)sub_4068B0(v28, v5) )
    goto LABEL_16;
  if ( (unsigned int)sub_406AB0(v5, v29) || (unsigned int)sub_406CF0(v29) )
  {
    sub_406EF0(v29);
    sub_406DB0(&v29);
    if ( v7 )
      goto LABEL_18;
    goto LABEL_36;
  }
  sub_406FE0(v29, filename);
LABEL_17:
  if ( v7 )
  {
LABEL_18:
    if ( !strcmp((const char *)(v5 + 8304), v7) )
    {
LABEL_21:
      nullsub_1(v5);
      v17 = sub_403DE0(v5);
      sub_403E30(v5);
      sub_406EF0(v29);
      sub_406DB0(&v29);
      return v17;
    }
    if ( snprintf((char *)(v5 + 12400), 0x1000uLL, "%s", v7) <= 4095 )
    {
      *(_DWORD *)(v5 + 20596) = 1;
      __strcpy_chk(v5 + 16496, v5 + 12400, 4096LL);
      goto LABEL_21;
    }
    return (unsigned int)-1;
  }
LABEL_36:
  if ( (unsigned int)sub_403AF0(v5, v29) )
    return (unsigned int)-1;
  sub_407A10("_MEIPASS2", v5 + 12400);
  if ( !prctl(16, s2, 0LL, 0LL) )
    sub_407A10("_PYI_PROCNAME", s2);
  if ( (unsigned int)sub_408030((char *)(v5 + 12400)) == -1 )
    return (unsigned int)-1;
  nullsub_2();
  v17 = sub_4081F0(filename);
  sub_406EF0(v29);
  sub_406DB0(&v29);
  if ( *(_DWORD *)(v5 + 20596) == 1 )
    sub_407B40(v5 + 12400, v5);
  sub_4030B0((void *)v5);
  sub_4080D0(v5, v5);
  return v17;
}

int main(int a1, char **a2, char **a3)
{
  return sub_403E50(a1, a2, a3);
}