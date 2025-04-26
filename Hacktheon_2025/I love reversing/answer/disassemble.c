__int64 sub_140002A70()
{
  DWORD LastError; // eax
  int v2; // eax
  WCHAR *v3; // rcx
  int v4; // eax
  __int64 v5; // rcx
  WCHAR Filename[4096]; // [rsp+20h] [rbp-4018h] BYREF
  wchar_t String2[4096]; // [rsp+2020h] [rbp-2018h] BYREF

  if ( !GetModuleFileNameW(0LL, Filename, 0x1000u) )
  {
    LastError = GetLastError();
    sub_140002310(L"GetModuleFileNameW", LastError, L"Failed to obtain executable path.\n");
    return 0xFFFFFFFFLL;
  }
  v2 = sub_140008840(Filename);
  v3 = Filename;
  if ( v2 )
  {
    if ( (int)sub_1400088C0(Filename, String2) < 0 )
    {
      sub_140001F30(L"Failed to resolve full path to executable %ls.\n", Filename);
      return 0xFFFFFFFFLL;
    }
    v4 = wcsncmp(L"\\\\?\\", String2, 4uLL);
    v5 = 4LL;
    if ( v4 )
      v5 = 0LL;
    v3 = &String2[v5];
  }
  if ( sub_140008A00(v3) )
    return 0LL;
  sub_140001F30(L"Failed to convert executable path to UTF-8.\n");
  return 0xFFFFFFFFLL;
}

__int64 __fastcall sub_140002B80(__int64 a1)
{
  FILE *v2; // rax
  __int64 v4; // rax
  unsigned int v5; // r14d
  const char *v6; // rbx
  bool v7; // di
  unsigned __int8 *v8; // rbp
  int v9; // edi
  void *v10; // rax
  FILE *v11; // rax
  FILE *v12; // rbx
  __int64 v13; // rax
  __int64 v15; // rax
  __int64 v16; // rax
  char *v17; // r15
  const char *v18; // rdx
  __int64 v19; // rbp
  unsigned __int64 i; // rbx
  int v21; // eax
  char v22; // cl
  char v23; // al
  unsigned __int8 *v24; // rax
  int v25; // edx
  __int64 v26; // rax
  const CHAR *v27; // rbx
  const char *v28; // rax
  char *v29; // rdi
  char *v30; // rcx
  bool v31; // bl
  unsigned __int8 *v32; // rax
  int v33; // edx
  char v34; // al
  __int64 v35; // rax
  _QWORD *v36; // rbx
  const char *v37; // rcx
  char v38; // al
  unsigned int v39; // edi
  const char *v40; // rdx
  char v41; // al
  unsigned int v42; // edi
  __int64 Buf2; // [rsp+20h] [rbp-2048h] BYREF
  WCHAR PathName[4096]; // [rsp+30h] [rbp-2038h] BYREF

  v2 = _acrt_iob_func(2u);
  setbuf(v2, 0LL);
  if ( (int)sub_140002A70(a1 + 16) < 0 )
    return -1LL;
  v4 = sub_140001930(a1 + 16);
  *(_QWORD *)(a1 + 8208) = v4;
  v5 = -1;
  if ( v4 )
  {
    v6 = (const char *)(a1 + 4112);
    swprintf((wchar_t *const)(a1 + 4112), 0x1000uLL, "%s", (const char *)(a1 + 16));
    goto LABEL_5;
  }
  v11 = (FILE *)sub_1400039D0(a1 + 16, "rb");
  v12 = v11;
  if ( !v11 )
  {
LABEL_16:
    sub_140001E50(
      "Could not load PyInstaller's embedded PKG archive from the executable (%s)\n",
      (const char *)(a1 + 16));
    return 0xFFFFFFFFLL;
  }
  Buf2 = 0xE0B0A0B0D49454DLL;
  if ( !sub_1400073D0(v11, &Buf2, 8uLL) )
  {
    fclose(v12);
    goto LABEL_16;
  }
  v6 = (const char *)(a1 + 4112);
  swprintf((wchar_t *const)(a1 + 4112), 0x1000uLL, "%s", (const char *)(a1 + 16));
  v13 = -1LL;
  while ( v6[++v13] != 0 )
    ;
  *(_DWORD *)(v13 + a1 + 4109) = 6777712;
  v15 = sub_140001930(a1 + 4112);
  *(_QWORD *)(a1 + 8208) = v15;
  if ( !v15 )
  {
    sub_140001E50("Could not side-load PyInstaller's PKG archive from external file (%s)\n", (const char *)(a1 + 4112));
    return 0xFFFFFFFFLL;
  }
LABEL_5:
  v7 = 0;
  *(_BYTE *)(a1 + 8224) = *(_BYTE *)(*(_QWORD *)(a1 + 8208) + 4120LL);
  v8 = (unsigned __int8 *)sub_140007E70("PYINSTALLER_RESET_ENVIRONMENT");
  if ( v8 )
  {
    v9 = *v8 - 49;
    if ( *v8 == 49 )
      v9 = v8[1];
    sub_140007FE0("PYINSTALLER_RESET_ENVIRONMENT");
    v7 = v9 == 0;
  }
  j__free_base(v8);
  if ( v7 )
    goto LABEL_22;
  v10 = (void *)sub_140007E70("_PYI_ARCHIVE_FILE");
  if ( !v10 || strcmp(v6, (const char *)v10) )
  {
    j__free_base(v10);
LABEL_22:
    sub_140007F80("_PYI_ARCHIVE_FILE", v6);
    sub_140007FE0("_PYI_APPLICATION_HOME_DIR");
    sub_140007FE0("_PYI_PARENT_PROCESS_LEVEL");
    sub_140007FE0("_PYI_SPLASH_IPC");
    goto LABEL_23;
  }
  j__free_base(v10);
LABEL_23:
  v16 = sub_140007E70("_PYI_PARENT_PROCESS_LEVEL");
  if ( v16 && *(_BYTE *)v16 )
  {
    if ( *(_BYTE *)v16 == 48 && !*(_BYTE *)(v16 + 1) )
    {
      v17 = (char *)(a1 + 8225);
LABEL_28:
      *v17 = 1;
      goto LABEL_29;
    }
    if ( *(_BYTE *)v16 != 49 || *(_BYTE *)(v16 + 1) )
    {
      sub_140001E50("Invalid value in _PYI_PARENT_PROCESS_LEVEL: %s\n", (const char *)v16);
      return 0xFFFFFFFFLL;
    }
    v17 = (char *)(a1 + 8225);
    *(_BYTE *)(a1 + 8225) = 2;
  }
  else
  {
    v17 = (char *)(a1 + 8225);
    if ( !*(_BYTE *)(a1 + 8224) )
      goto LABEL_28;
    *v17 = 0;
  }
LABEL_29:
  j__free_base((void *)v16);
  if ( (unsigned __int8)*v17 < 2u )
  {
    v18 = "1";
    if ( !*v17 )
      v18 = "0";
    sub_140007F80("_PYI_PARENT_PROCESS_LEVEL", v18);
  }
  v19 = *(_QWORD *)(a1 + 8208);
  for ( i = *(_QWORD *)(v19 + 4104); i < *(_QWORD *)(v19 + 4112); i = sub_140001920(v19, i) )
  {
    if ( *(_BYTE *)(i + 17) == 111 )
    {
      if ( !strncmp((const char *)(i + 18), "pyi-python-flag", 0xFuLL) )
      {
        if ( !strncmp((const char *)(i + 34), "Py_GIL_DISABLED", 0xFuLL) )
          *(_BYTE *)(a1 + 12409) = 1;
      }
      else
      {
        if ( !strncmp((const char *)(i + 18), "pyi-runtime-tmpdir", 0x12uLL) )
          *(_QWORD *)(a1 + 12392) = i + 37;
        if ( !strncmp((const char *)(i + 18), "pyi-contents-directory", 0x16uLL) )
          *(_QWORD *)(a1 + 12400) = i + 41;
        if ( !strncmp((const char *)(i + 18), "pyi-hide-console", 0x10uLL) )
        {
          if ( !strcmp((const char *)(i + 35), "hide-early") )
          {
            *(_BYTE *)(a1 + 12408) = 1;
          }
          else if ( !strcmp((const char *)(i + 35), "minimize-early") )
          {
            *(_BYTE *)(a1 + 12408) = 3;
          }
          else if ( !strcmp((const char *)(i + 35), "hide-late") )
          {
            *(_BYTE *)(a1 + 12408) = 2;
          }
          else
          {
            v21 = strcmp((const char *)(i + 35), "minimize-late");
            v22 = 0;
            if ( !v21 )
              v22 = 4;
            *(_BYTE *)(a1 + 12408) = v22;
          }
        }
      }
    }
  }
  v23 = *(_BYTE *)(a1 + 12408);
  if ( v23 == 1 )
  {
    sub_1400085B0();
  }
  else if ( v23 == 3 )
  {
    sub_1400086E0();
  }
  v24 = (unsigned __int8 *)sub_140007E70("PYINSTALLER_STRICT_UNPACK_MODE");
  if ( v24 )
  {
    v25 = *v24 - 48;
    if ( *v24 == 48 )
      v25 = v24[1];
    *(_BYTE *)(a1 + 12337) = v25 != 0;
  }
  j__free_base(v24);
  if ( *(_BYTE *)(a1 + 8224) )
  {
    if ( *v17 )
    {
      v28 = (const char *)sub_140007E70("_PYI_APPLICATION_HOME_DIR");
      v29 = (char *)v28;
      if ( !v28 || !*v28 )
      {
        sub_140001E50("_PYI_APPLICATION_HOME_DIR not set for onefile child process!\n");
        return v5;
      }
      v27 = (const CHAR *)(a1 + 8226);
      if ( swprintf((wchar_t *const)(a1 + 8226), 0x1000uLL, "%s", v28) >= 4096 )
      {
        sub_140001E50("Path exceeds PYI_PATH_MAX limit.\n");
        j__free_base(v29);
        return v5;
      }
      j__free_base(v29);
    }
    else
    {
      v26 = sub_1400085C0();
      *(_QWORD *)(a1 + 12344) = v26;
      if ( !v26 )
      {
        sub_140001E50("Failed to initialize security descriptor for temporary directory!\n");
        return v5;
      }
      if ( (int)sub_140007CA0(a1) < 0 )
      {
        sub_140001E50("Could not create temporary directory!\n");
        return v5;
      }
      v27 = (const CHAR *)(a1 + 8226);
    }
  }
  else
  {
    sub_1400038F0(PathName, a1 + 16);
    v27 = (const CHAR *)(a1 + 8226);
    v30 = (char *)(a1 + 8226);
    if ( *(_QWORD *)(a1 + 12400) )
      sub_140003A40(v30);
    else
      swprintf((wchar_t *const)v30, 0x1000uLL, "%s", (const char *)PathName);
  }
  if ( *(_QWORD *)(*(_QWORD *)(a1 + 8208) + 4128LL) && *(_BYTE *)(a1 + 8224) && !*v17 )
  {
    SetDllDirectoryW(0LL);
    LoadLibraryExW(L"VCRUNTIME140.dll", 0LL, 0x1000u);
  }
  if ( !sub_140008950(v27, (int)PathName) )
  {
    sub_140001E50("Failed to convert DLL search path!\n");
    return v5;
  }
  SetDllDirectoryW(PathName);
  v31 = 0;
  if ( *(_QWORD *)(*(_QWORD *)(a1 + 8208) + 4128LL) )
  {
    v32 = (unsigned __int8 *)sub_140007E70("PYINSTALLER_SUPPRESS_SPLASH_SCREEN");
    if ( v32 )
    {
      v33 = *v32 - 49;
      if ( *v32 == 49 )
        v33 = v32[1];
      v31 = v33 == 0;
    }
    j__free_base(v32);
    if ( v31 || (v34 = *v17, (unsigned __int8)*v17 >= 2u) )
    {
      sub_140007F80("_PYI_SPLASH_IPC", "0");
      goto LABEL_112;
    }
    if ( *(_BYTE *)(a1 + 8224) )
    {
      if ( v34 )
        goto LABEL_112;
    }
    else if ( v34 != 1 )
    {
      goto LABEL_112;
    }
    v35 = sub_140006200();
    v36 = (_QWORD *)(a1 + 8216);
    *(_QWORD *)(a1 + 8216) = v35;
    if ( (unsigned int)sub_140006780(v35, a1) )
    {
      v37 = "Failed to load splash screen resources!\n";
LABEL_110:
      sub_140002140(v37);
      sub_140006400(*v36);
      sub_1400061B0(a1 + 8216);
      goto LABEL_112;
    }
    if ( *(_BYTE *)(a1 + 8224) && (unsigned int)sub_140006240(*v36, a1) )
    {
      v37 = "Failed to unpack splash screen dependencies from PKG archive!\n";
      goto LABEL_110;
    }
    if ( (unsigned int)sub_1400065F0(*v36) )
    {
      v37 = "Failed to load Tcl/Tk shared libraries for splash screen!\n";
      goto LABEL_110;
    }
    if ( (unsigned int)sub_140006930(*v36, a1 + 16) )
    {
      v37 = "Failed to start splash screen!\n";
      goto LABEL_110;
    }
  }
LABEL_112:
  if ( *(_BYTE *)(a1 + 8224) && !*(_BYTE *)(a1 + 8225) )
  {
    if ( (int)sub_140002780(a1) >= 0 )
    {
      sub_140008590(a1 + 12344);
      v38 = *(_BYTE *)(a1 + 12408);
      if ( v38 == 2 )
      {
        sub_1400085B0();
      }
      else if ( v38 == 4 )
      {
        sub_1400086E0();
      }
      sub_140007F80("_PYI_APPLICATION_HOME_DIR", a1 + 8226);
      v39 = sub_140008020(a1);
      sub_140006400(*(_QWORD *)(a1 + 8216));
      sub_1400061B0(a1 + 8216);
      if ( (int)sub_140007F20(a1 + 8226) < 0 && (int)sub_1400086F0(a1) < 0 )
      {
        v40 = (const char *)(a1 + 8226);
        if ( *(_BYTE *)(a1 + 12337) )
        {
          sub_140001E50("Failed to remove temporary directory: %s\n", v40);
          sub_1400018E0(a1 + 8208);
          return v5;
        }
        sub_140002140("Failed to remove temporary directory: %s\n", v40);
      }
      sub_1400018E0(a1 + 8208);
      return v39;
    }
    return v5;
  }
  v41 = *(_BYTE *)(a1 + 12408);
  if ( v41 == 2 )
  {
    sub_1400085B0();
  }
  else if ( v41 == 4 )
  {
    sub_1400086E0();
  }
  v42 = sub_140002720(a1);
  sub_140002A30(a1);
  sub_140006400(*(_QWORD *)(a1 + 8216));
  sub_1400061B0(a1 + 8216);
  return v42;
}

int main(int argc, const char **argv, const char **envp)
{
  unk_140040D10 = argc;
  *((_QWORD *)&unk_140040D10 + 1) = argv;
  return sub_140002B80(&unk_140040D10, argv, envp);
}