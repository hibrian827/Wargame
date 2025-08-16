unsigned long sub_4F8C(long a1)
{
  int *v1; // rbp
  struct _Unwind_Exception *v3; // rbx
  char v4; // dl
  void *v5; // rdi
  unsigned long result; // rax
  long v7; // rbx
  void *v8; // r14
  long *v9; // rdi
  long *v10; // rax
  long v11; // rax
  int v12; // r14d
  char *v13; // rbx
  char v14; // al
  char v15; // dl
  char *v16; // rbx
  char v17; // al
  char v18; // dl
  int v19; // eax
  int v20; // esi
  int v21; // edi
  char *v22; // rbx
  char v23; // si
  std::ostream *v24; // rax
  void *v25; // rdi
  char *v26; // rbx
  int v27; // [rsp+Ch] [rbp-24Ch]
  int v28[4]; // [rsp+10h] [rbp-248h] BYREF
  char v29; // [rsp+20h] [rbp-238h]
  void *s1; // [rsp+30h] [rbp-228h] BYREF
  size_t n; // [rsp+38h] [rbp-220h]
  long v32[2]; // [rsp+40h] [rbp-218h] BYREF
  void *v33; // [rsp+50h] [rbp-208h] BYREF
  long v34; // [rsp+58h] [rbp-200h]
  long v35[2]; // [rsp+60h] [rbp-1F8h] BYREF
  void *v36; // [rsp+70h] [rbp-1E8h] BYREF
  long v37; // [rsp+78h] [rbp-1E0h]
  long v38[2]; // [rsp+80h] [rbp-1D8h] BYREF
  int *v39; // [rsp+90h] [rbp-1C8h] BYREF
  long v40; // [rsp+98h] [rbp-1C0h]
  long v41[7]; // [rsp+A0h] [rbp-1B8h] BYREF
  char v42[8]; // [rsp+D8h] [rbp-180h] BYREF
  int v43; // [rsp+E0h] [rbp-178h]
  void *v44; // [rsp+E8h] [rbp-170h]
  long v45; // [rsp+F0h] [rbp-168h]
  long v46[2]; // [rsp+F8h] [rbp-160h] BYREF
  long v47[28]; // [rsp+108h] [rbp-150h] BYREF
  char v48; // [rsp+1E8h] [rbp-70h]
  char v49; // [rsp+1E9h] [rbp-6Fh]
  long v50; // [rsp+1F0h] [rbp-68h]
  long v51; // [rsp+1F8h] [rbp-60h]
  long v52; // [rsp+200h] [rbp-58h]
  long v53; // [rsp+208h] [rbp-50h]
  unsigned long v54; // [rsp+218h] [rbp-40h]

  v54 = __readfsqword(0x28u);
  ((void (*)(void))sub_3EFC)();
  if ( *(char *)(a1 + 800) )
    goto LABEL_11;
LABEL_69:
  std::__ostream_insert<char,std::char_traits<char>>(std::cout, "Enter move: ", 12LL);
  s1 = v32;
  n = 0LL;
  LOBYTE(v32[0]) = 0;
  v26 = *(char **)((char *)&std::cin[30] + *(_QWORD *)(std::cin[0] - 24));
  if ( !v26 )
  {
    if ( v54 == __readfsqword(0x28u) )
    {
      v3 = (struct _Unwind_Exception *)std::__throw_bad_cast();
      goto LABEL_32;
    }
    goto LABEL_5;
  }
  if ( !v26[56] )
  {
LABEL_5:
    std::ctype<char>::_M_widen_init(v26);
    v4 = (*(long (__fastcall **)(char *, long))(*(_QWORD *)v26 + 48LL))(v26, 10LL);
    goto LABEL_72;
  }
  v4 = v26[67];
LABEL_72:
  std::getline<char,std::char_traits<char>,std::allocator<char>>(std::cin, &s1, (unsigned int)v4);
  if ( n == 4 && !memcmp(s1, "quit", 4uLL) )
  {
    v5 = s1;
    if ( s1 == v32 )
      goto LABEL_11;
    goto LABEL_10;
  }
  std::ios_base::ios_base((std::ios_base *)v47);
  v47[0] = (long)&unk_7A08;
  v47[27] = 0LL;
  v48 = 0;
  v49 = 0;
  v50 = 0LL;
  v51 = 0LL;
  v52 = 0LL;
  v53 = 0LL;
  v1 = &dword_0;
  v39 = &dword_0;
  *(int **)((char *)&v39 + MEMORY[0xFFFFFFFFFFFFFFE8]) = &dword_0;
  v40 = 0LL;
  std::basic_ios<char,std::char_traits<char>>::init((char *)&v39 + *((_QWORD *)v39 - 3), 0LL);
  v39 = (int *)&unk_7A30;
  v47[0] = (long)&unk_7A30 + 40;
  v41[0] = (long)&unk_7A78;
  memset(&v41[1], 0, 48);
  std::locale::locale((std::locale *)v42);
  v41[0] = (long)&unk_7C08;
  v43 = 0;
  v7 = n;
  v8 = s1;
  v44 = v46;
  if ( !s1 && n )
  {
    if ( v54 == __readfsqword(0x28u) )
      std::__throw_logic_error("basic_string: construction from null is not valid");
  }
  else if ( n <= 0xF )
  {
    if ( n == 1 )
    {
      LOBYTE(v46[0]) = *(char *)s1;
      goto LABEL_31;
    }
    if ( !n )
    {
LABEL_31:
      v45 = v7;
      *((char *)v44 + v7) = 0;
      v43 = 8;
      std::__cxx11::basic_stringbuf<char,std::char_traits<char>,std::allocator<char>>::_M_sync(v41, v44, 0LL, 0LL);
      goto LABEL_33;
    }
    v9 = v46;
LABEL_29:
    memcpy(v9, v8, v7);
    goto LABEL_31;
  }
  if ( v7 < 0 )
  {
    if ( v54 == __readfsqword(0x28u) )
      std::__throw_length_error("basic_string::_M_create");
  }
  else if ( v7 + 1 >= 0 )
  {
    v10 = (long *)operator new(v7 + 1);
LABEL_28:
    v9 = v10;
    v44 = v10;
    v46[0] = v7;
    goto LABEL_29;
  }
  v10 = (long *)(v54 - __readfsqword(0x28u));
  if ( v10 )
    goto LABEL_28;
  v3 = (struct _Unwind_Exception *)std::__throw_bad_alloc();
  v41[0] = (long)&unk_7A78;
  std::locale::~locale((std::locale *)v42);
  v39 = &dword_0;
  *(int **)((char *)&v39 + MEMORY[0xFFFFFFFFFFFFFFE8]) = &dword_0;
  v40 = 0LL;
  v47[0] = (long)&unk_7A08;
  std::ios_base::~ios_base((std::ios_base *)v47);
  while ( 1 )
  {
LABEL_32:
    std::__cxx11::basic_string<char,std::char_traits<char>,std::allocator<char>>::_M_dispose(&s1);
    if ( v54 == __readfsqword(0x28u) )
    {
      _Unwind_Resume(v3);
      goto LABEL_93;
    }
LABEL_33:
    std::basic_ios<char,std::char_traits<char>>::init(v47, v41);
    v33 = v35;
    v34 = 0LL;
    LOBYTE(v35[0]) = 0;
    v36 = v38;
    v37 = 0LL;
    LOBYTE(v38[0]) = 0;
    v11 = std::operator>><char,std::char_traits<char>,std::allocator<char>>(&v39, &v33);
    std::operator>><char,std::char_traits<char>,std::allocator<char>>(v11, &v36);
    v12 = -1;
    v27 = -1;
    if ( v34 == 2 )
    {
      v13 = v33;
      v14 = tolower(*(char *)v33);
      if ( (unsigned __int8)(v14 - 97) > 7u )
      {
        v12 = -1;
        v27 = -1;
      }
      else
      {
        v15 = v13[1];
        if ( (unsigned __int8)(v15 - 49) > 7u )
        {
          v12 = -1;
          v27 = -1;
        }
        else
        {
          v12 = (char)(v14 - 97);
          v27 = 56 - v15;
        }
      }
    }
    if ( v37 == 2 )
    {
      v16 = v36;
      v17 = tolower(*(char *)v36);
      if ( (unsigned __int8)(v17 - 97) <= 7u )
      {
        v18 = v16[1];
        if ( (unsigned __int8)(v18 - 49) <= 7u && v12 >= 0 && (unsigned int)v27 <= 7 )
          break;
      }
    }
    std::__ostream_insert<char,std::char_traits<char>>(std::cout, "Invalid position format!", 24LL);
    v22 = *(char **)((char *)&std::cout[30] + *(_QWORD *)(std::cout[0] - 24LL));
    if ( v22 )
    {
      if ( v22[56] )
      {
        v23 = v22[67];
      }
      else
      {
LABEL_59:
        std::ctype<char>::_M_widen_init(v22);
        v23 = (*(long (__fastcall **)(char *, long))(*(_QWORD *)v22 + 48LL))(v22, 10LL);
      }
      v24 = (std::ostream *)std::ostream::put((std::ostream *)std::cout, v23);
      std::ostream::flush(v24);
      if ( v36 != v38 )
        operator delete(v36, v38[0] + 1);
      if ( v33 != v35 )
        operator delete(v33, v35[0] + 1);
      v39 = (int *)&unk_7A30;
      v47[0] = (long)&unk_7A30 + 40;
      v41[0] = (long)&unk_7C08;
      if ( v44 != v46 )
        operator delete(v44, v46[0] + 1);
      v41[0] = (long)&unk_7A78;
      std::locale::~locale((std::locale *)v42);
      v39 = v1;
      *(int **)((char *)&v39 + *((_QWORD *)v1 - 3)) = &dword_0;
      v40 = 0LL;
      v47[0] = (long)&unk_7A08;
      std::ios_base::~ios_base((std::ios_base *)v47);
      v25 = s1;
      if ( s1 != v32 )
LABEL_67:
        operator delete(v25, v32[0] + 1);
LABEL_68:
      if ( *(char *)(a1 + 800) )
        goto LABEL_11;
      goto LABEL_69;
    }
    if ( v54 != __readfsqword(0x28u) )
      goto LABEL_59;
    v3 = (struct _Unwind_Exception *)std::__throw_bad_cast();
    std::__cxx11::basic_string<char,std::char_traits<char>,std::allocator<char>>::_M_dispose(&v36);
    std::__cxx11::basic_string<char,std::char_traits<char>,std::allocator<char>>::_M_dispose(&v33);
    std::__cxx11::basic_istringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_istringstream(&v39);
  }
  v19 = (char)(v17 - 97);
  v20 = 56 - v18;
  v28[0] = v27;
  v28[1] = v12;
  v28[2] = v20;
  v28[3] = v19;
  v29 = 0;
  if ( !*(_DWORD *)(a1 + 96LL * v27 + 12LL * v12)
    || (v21 = *(_DWORD *)(a1 + 768), *(_DWORD *)(a1 + 96LL * v27 + 12LL * v12 + 4) != v21)
    || v19 == v12 && v20 == v27
    || *(_DWORD *)(a1 + 96LL * v20 + 12LL * v19) && v21 == *(_DWORD *)(a1 + 96LL * v20 + 12LL * v19 + 4)
    || !(unsigned __int8)sub_2B36(a1, v28) )
  {
    std::__ostream_insert<char,std::char_traits<char>>(std::cout, "Invalid move!\n", 14LL);
    goto LABEL_74;
  }
  sub_3512(a1, v28);
  sub_3EFC(a1);
  if ( !*(char *)(a1 + 800) )
  {
LABEL_74:
    if ( v36 != v38 )
      operator delete(v36, v38[0] + 1);
    if ( v33 != v35 )
      operator delete(v33, v35[0] + 1);
    v39 = (int *)&unk_7A30;
    v47[0] = (long)&unk_7A30 + 40;
    v41[0] = (long)&unk_7C08;
    if ( v44 != v46 )
      operator delete(v44, v46[0] + 1);
    v41[0] = (long)&unk_7A78;
    std::locale::~locale((std::locale *)v42);
    v39 = v1;
    *(int **)((char *)&v39 + *((_QWORD *)v1 - 3)) = &dword_0;
    v40 = 0LL;
    v47[0] = (long)&unk_7A08;
    std::ios_base::~ios_base((std::ios_base *)v47);
    v25 = s1;
    if ( s1 != v32 )
      goto LABEL_67;
    goto LABEL_68;
  }
  sub_45CE(a1);
  if ( v36 != v38 )
    operator delete(v36, v38[0] + 1);
  if ( v33 != v35 )
    operator delete(v33, v35[0] + 1);
  v39 = (int *)&unk_7A30;
  v47[0] = (long)&unk_7A30 + 40;
  v41[0] = (long)&unk_7C08;
  if ( v44 != v46 )
    operator delete(v44, v46[0] + 1);
  v41[0] = (long)&unk_7A78;
  std::locale::~locale((std::locale *)v42);
  v39 = v1;
  *(int **)((char *)&v39 + *((_QWORD *)v1 - 3)) = &dword_0;
  v40 = 0LL;
  v47[0] = (long)&unk_7A08;
  std::ios_base::~ios_base((std::ios_base *)v47);
  v5 = s1;
  if ( s1 != v32 )
LABEL_10:
    operator delete(v5, v32[0] + 1);
LABEL_11:
  result = v54 - __readfsqword(0x28u);
  if ( result )
LABEL_93:
    JUMPOUT(0x5AC1LL);
  return result;
}

long sub_45CE(long a1)
{
  _DWORD *v1; // rax
  _DWORD *v2; // r9
  char v3; // r10
  int v4; // ecx
  int v5; // esi
  int v6; // r11d
  int v7; // ebx
  int v8; // edx
  _BYTE *v9; // r12
  char v10; // si
  std::ostream *v11; // rax
  _BYTE *v12; // r12
  char v13; // si
  std::ostream *v14; // rax
  long v15; // rax
  char *v16; // r12
  const char *v17; // rsi
  _BYTE *v18; // rbp
  char v19; // si
  std::ostream *v20; // rax
  long v21; // rax
  char *v22; // rdx
  std::ostream *v23; // rbp
  _BYTE *v24; // r12
  char v25; // si
  std::ostream *v26; // rax
  _BYTE *v27; // rbp
  char v28; // si
  std::ostream *v29; // rdi
  long result; // rax
  struct _Unwind_Exception *v31; // rbx
  _BYTE *v32; // rbp
  char v33; // dl
  long v34; // rax
  char *v35; // rdx
  std::ostream *v36; // rbp
  _BYTE *v37; // r13
  char v38; // si
  std::ostream *v39; // rax
  char v40; // si
  std::ostream *v41; // rax
  void *v42; // [rsp+0h] [rbp-258h] BYREF
  long v43; // [rsp+8h] [rbp-250h]
  long v44[2]; // [rsp+10h] [rbp-248h] BYREF
  int *v45; // [rsp+20h] [rbp-238h] BYREF
  long v46; // [rsp+28h] [rbp-230h]
  long v47[7]; // [rsp+30h] [rbp-228h] BYREF
  char v48[48]; // [rsp+68h] [rbp-1F0h] BYREF
  char v49[136]; // [rsp+98h] [rbp-1C0h] BYREF
  long v50[28]; // [rsp+120h] [rbp-138h] BYREF
  char v51; // [rsp+200h] [rbp-58h]
  char v52; // [rsp+201h] [rbp-57h]
  long v53; // [rsp+208h] [rbp-50h]
  long v54; // [rsp+210h] [rbp-48h]
  long v55; // [rsp+218h] [rbp-40h]
  long v56; // [rsp+220h] [rbp-38h]
  unsigned long v57; // [rsp+228h] [rbp-30h]

  v57 = __readfsqword(0x28u);
  v1 = *(_DWORD **)(a1 + 776);
  v2 = *(_DWORD **)(a1 + 784);
  if ( v1 == v2 )
  {
    v4 = 0;
    v5 = 0;
    v7 = 0;
  }
  else
  {
    v3 = 0;
    v4 = 0;
    v5 = 0;
    v6 = 0;
    v7 = 0;
    do
    {
      switch ( v1[1] )
      {
        case 1:
          ++v7;
          ++v6;
          break;
        case 2:
          v7 += 10;
          break;
        case 3:
        case 4:
          v7 += 5;
          break;
        case 5:
          v7 += 20;
          break;
        case 6:
          v7 += 50;
          if ( v1[2] == 6 )
            v3 = 1;
          break;
        default:
          break;
      }
      v8 = v1[4];
      v5 += v8 == 3;
      v4 += v8 == 4;
      v1 += 5;
    }
    while ( v2 != v1 );
    if ( v6 > 9 )
      v7 += 300;
    if ( v3 )
      v7 += 3000;
  }
  if ( v5 > 4 )
    v7 += 500;
  if ( v4 > 9 )
    v7 += 2000;
  std::__ostream_insert<char,std::char_traits<char>>(std::cout, &unk_6420, 130LL);
  v9 = *(_BYTE **)((char *)&std::cout[30] + *(_QWORD *)(std::cout[0] - 24LL));
  if ( v9 )
  {
    if ( v9[56] )
    {
      v10 = v9[67];
      goto LABEL_23;
    }
  }
  else if ( v57 == __readfsqword(0x28u) )
  {
    std::__throw_bad_cast();
  }
  std::ctype<char>::_M_widen_init(v9);
  v10 = (*(long (__fastcall **)(_BYTE *, long))(*(_QWORD *)v9 + 48LL))(v9, 10LL);
LABEL_23:
  v11 = (std::ostream *)std::ostream::put((std::ostream *)std::cout, v10);
  std::ostream::flush(v11);
  std::__ostream_insert<char,std::char_traits<char>>(std::cout, &unk_64A8, 47LL);
  v12 = *(_BYTE **)((char *)&std::cout[30] + *(_QWORD *)(std::cout[0] - 24LL));
  if ( v12 )
  {
    if ( v12[56] )
    {
      v13 = v12[67];
      goto LABEL_26;
    }
  }
  else if ( v57 == __readfsqword(0x28u) )
  {
    std::__throw_bad_cast();
  }
  std::ctype<char>::_M_widen_init(v12);
  v13 = (*(long (__fastcall **)(_BYTE *, long))(*(_QWORD *)v12 + 48LL))(v12, 10LL);
LABEL_26:
  v14 = (std::ostream *)std::ostream::put((std::ostream *)std::cout, v13);
  std::ostream::flush(v14);
  std::__ostream_insert<char,std::char_traits<char>>(std::cout, &unk_60C7, 12LL);
  v15 = std::cout[0];
  *(_QWORD *)((char *)&std::cout[2] + *(_QWORD *)(std::cout[0] - 24LL)) = 31LL;
  v16 = (char *)std::cout + *(_QWORD *)(v15 - 24);
  LODWORD(v15) = *((_DWORD *)v16 + 6);
  LOBYTE(v15) = v15 & 0x4F;
  *((_DWORD *)v16 + 6) = v15 | 0x20;
  v17 = "Black";
  if ( !*(_DWORD *)(a1 + 804) )
    v17 = "White";
  std::__ostream_insert<char,std::char_traits<char>>(std::cout, v17, 5LL);
  std::__ostream_insert<char,std::char_traits<char>>(std::cout, &unk_60A7, 4LL);
  v18 = *(_BYTE **)((char *)&std::cout[30] + *(_QWORD *)(std::cout[0] - 24LL));
  if ( v18 )
  {
    if ( v18[56] )
    {
      v19 = v18[67];
      goto LABEL_31;
    }
  }
  else if ( v57 == __readfsqword(0x28u) )
  {
    std::__throw_bad_cast();
  }
  std::ctype<char>::_M_widen_init(v18);
  v19 = (*(long (__fastcall **)(_BYTE *, long))(*(_QWORD *)v18 + 48LL))(v18, 10LL);
LABEL_31:
  v20 = (std::ostream *)std::ostream::put((std::ostream *)std::cout, v19);
  std::ostream::flush(v20);
  std::__ostream_insert<char,std::char_traits<char>>(std::cout, &unk_60D4, 17LL);
  v21 = std::cout[0];
  *(_QWORD *)((char *)&std::cout[2] + *(_QWORD *)(std::cout[0] - 24LL)) = 25LL;
  v22 = (char *)std::cout + *(_QWORD *)(v21 - 24);
  LODWORD(v21) = *((_DWORD *)v22 + 6);
  LOBYTE(v21) = v21 & 0x4F;
  *((_DWORD *)v22 + 6) = v21 | 0x20;
  v23 = (std::ostream *)std::ostream::operator<<(std::cout, (unsigned int)v7);
  std::__ostream_insert<char,std::char_traits<char>>(v23, &unk_60A7, 4LL);
  v24 = *(_BYTE **)((char *)v23 + *(_QWORD *)(*(_QWORD *)v23 - 24LL) + 240);
  if ( v24 )
  {
    if ( v24[56] )
    {
      v25 = v24[67];
      goto LABEL_34;
    }
  }
  else if ( v57 == __readfsqword(0x28u) )
  {
    std::__throw_bad_cast();
  }
  std::ctype<char>::_M_widen_init(v24);
  v25 = (*(long (__fastcall **)(_BYTE *, long))(*(_QWORD *)v24 + 48LL))(v24, 10LL);
LABEL_34:
  v26 = (std::ostream *)std::ostream::put(v23, v25);
  std::ostream::flush(v26);
  std::__ostream_insert<char,std::char_traits<char>>(std::cout, &unk_64D8, 130LL);
  v27 = *(_BYTE **)((char *)&std::cout[30] + *(_QWORD *)(std::cout[0] - 24LL));
  if ( v27 )
  {
    if ( v27[56] )
    {
      v28 = v27[67];
      goto LABEL_37;
    }
  }
  else if ( v57 == __readfsqword(0x28u) )
  {
    std::__throw_bad_cast();
  }
  std::ctype<char>::_M_widen_init(v27);
  v28 = (*(long (__fastcall **)(_BYTE *, long))(*(_QWORD *)v27 + 48LL))(v27, 10LL);
LABEL_37:
  v29 = (std::ostream *)std::ostream::put((std::ostream *)std::cout, v28);
  std::ostream::flush(v29);
  if ( v7 <= 4999 )
    goto LABEL_38;
  std::ios_base::ios_base((std::ios_base *)v50);
  v50[0] = (long)&unk_7A08;
  v50[27] = 0LL;
  v51 = 0;
  v52 = 0;
  v53 = 0LL;
  v54 = 0LL;
  v55 = 0LL;
  v56 = 0LL;
  v31 = (struct _Unwind_Exception *)&dword_0;
  v45 = &dword_0;
  *(int **)((char *)&v45 + MEMORY[0xFFFFFFFFFFFFFFE8]) = &dword_0;
  v46 = 0LL;
  std::basic_ios<char,std::char_traits<char>>::init((char *)&v45 + *((_QWORD *)v45 - 3), 0LL);
  v45 = (int *)&unk_7B20;
  v50[0] = (long)&unk_7B20 + 40;
  std::basic_filebuf<char,std::char_traits<char>>::basic_filebuf(v47);
  std::basic_ios<char,std::char_traits<char>>::init(v50, v47);
  if ( std::basic_filebuf<char,std::char_traits<char>>::open(v47, "/home/ctf/flag.txt", 8LL) )
    std::basic_ios<char,std::char_traits<char>>::clear((char *)&v45 + *((_QWORD *)v45 - 3), 0LL);
  else
    std::basic_ios<char,std::char_traits<char>>::clear(
      (char *)&v45 + *((_QWORD *)v45 - 3),
      *(_DWORD *)((char *)&v47[2] + *((_QWORD *)v45 - 3)) | 4u);
  if ( (unsigned __int8)std::__basic_file<char>::is_open(v49) )
  {
    v42 = v44;
    v43 = 0LL;
    LOBYTE(v44[0]) = 0;
    v32 = *(_BYTE **)&v49[*((_QWORD *)v45 - 3) + 120];
    if ( v32 )
    {
      if ( v32[56] )
      {
        v33 = v32[67];
LABEL_64:
        std::getline<char,std::char_traits<char>,std::allocator<char>>(&v45, &v42, (unsigned int)v33);
        if ( !std::basic_filebuf<char,std::char_traits<char>>::close(v47) )
          std::basic_ios<char,std::char_traits<char>>::clear(
            (char *)&v45 + *((_QWORD *)v45 - 3),
            *(_DWORD *)((char *)&v47[2] + *((_QWORD *)v45 - 3)) | 4u);
        std::__ostream_insert<char,std::char_traits<char>>(std::cout, &unk_60F9, 10LL);
        v34 = std::cout[0];
        *(_QWORD *)((char *)&std::cout[2] + *(_QWORD *)(std::cout[0] - 24LL)) = 33LL;
        v35 = (char *)std::cout + *(_QWORD *)(v34 - 24);
        LODWORD(v34) = *((_DWORD *)v35 + 6);
        LOBYTE(v34) = v34 & 0x4F;
        *((_DWORD *)v35 + 6) = v34 | 0x20;
        v36 = (std::ostream *)std::__ostream_insert<char,std::char_traits<char>>(std::cout, v42, v43);
        std::__ostream_insert<char,std::char_traits<char>>(v36, &unk_60A7, 4LL);
        v37 = *(_BYTE **)((char *)v36 + *(_QWORD *)(*(_QWORD *)v36 - 24LL) + 240);
        if ( v37 )
        {
          if ( v37[56] )
          {
            v38 = v37[67];
            goto LABEL_74;
          }
        }
        else if ( v57 == __readfsqword(0x28u) )
        {
          std::__throw_bad_cast();
        }
        std::ctype<char>::_M_widen_init(v37);
        v38 = (*(long (__fastcall **)(_BYTE *, long))(*(_QWORD *)v37 + 48LL))(v37, 10LL);
LABEL_74:
        v39 = (std::ostream *)std::ostream::put(v36, v38);
        std::ostream::flush(v39);
        if ( v42 != v44 )
          operator delete(v42, v44[0] + 1);
        goto LABEL_80;
      }
    }
    else if ( v57 == __readfsqword(0x28u) )
    {
      v31 = (struct _Unwind_Exception *)std::__throw_bad_cast();
      std::__cxx11::basic_string<char,std::char_traits<char>,std::allocator<char>>::_M_dispose(&v42);
LABEL_67:
      std::basic_ifstream<char,std::char_traits<char>>::~basic_ifstream(&v45);
      if ( v57 == __readfsqword(0x28u) )
      {
        _Unwind_Resume(v31);
        return sub_4F8C();
      }
    }
    std::ctype<char>::_M_widen_init(v32);
    v33 = (*(long (__fastcall **)(_BYTE *, long))(*(_QWORD *)v32 + 48LL))(v32, 10LL);
    goto LABEL_64;
  }
  std::__ostream_insert<char,std::char_traits<char>>(std::cout, "Error on opening flag.txt. contact to @admin", 44LL);
  v32 = *(_BYTE **)((char *)&std::cout[30] + *(_QWORD *)(std::cout[0] - 24LL));
  if ( !v32 )
  {
    if ( v57 != __readfsqword(0x28u) )
      goto LABEL_87;
    v31 = (struct _Unwind_Exception *)std::__throw_bad_cast();
    goto LABEL_67;
  }
  if ( !v32[56] )
  {
LABEL_87:
    std::ctype<char>::_M_widen_init(v32);
    v40 = (*(long (__fastcall **)(_BYTE *, long))(*(_QWORD *)v32 + 48LL))(v32, 10LL);
    goto LABEL_84;
  }
  v40 = v32[67];
LABEL_84:
  v41 = (std::ostream *)std::ostream::put((std::ostream *)std::cout, v40);
  std::ostream::flush(v41);
LABEL_80:
  v45 = (int *)&unk_7B20;
  v50[0] = (long)&unk_7B20 + 40;
  v47[0] = (long)&unk_7B68;
  std::basic_filebuf<char,std::char_traits<char>>::close(v47);
  std::__basic_file<char>::~__basic_file(v49);
  v47[0] = (long)&unk_7A78;
  std::locale::~locale((std::locale *)v48);
  v45 = (int *)v31;
  *(int **)((char *)&v45 + (unsigned long)v31[-1].exception_cleanup) = &dword_0;
  v46 = 0LL;
  v50[0] = (long)&unk_7A08;
  std::ios_base::~ios_base((std::ios_base *)v50);
LABEL_38:
  result = v57 - __readfsqword(0x28u);
  if ( result )
    return sub_4F8C();
  return result;
}

long sub_2972(_DWORD *a1, int *a2)
{
  int v4; // r10d
  int v5; // eax
  int v6; // ecx
  int v7; // edx
  int v9; // edx
  _DWORD *v10; // rax
  unsigned int v11; // ebx
  int v12; // edi
  int v13; // ecx
  int v14; // eax
  int v15; // edx
  int v16; // esi
  unsigned int v17; // r11d
  unsigned int v18; // ecx
  _DWORD *v19; // rsi
  int v20; // eax
  signed int v21; // edx
  int v22; // ecx
  int *v23; // rdx
  int v24; // ecx
  int v25; // edi

  v4 = *a2;
  v5 = a1[192];
  if ( v5 )
  {
    if ( v4 != 5 )
      goto LABEL_45;
    v6 = a2[2];
    v7 = 6;
  }
  else
  {
    if ( v4 != 2 )
      goto LABEL_45;
    v6 = a2[2];
    v7 = 1;
  }
  if ( v7 == v6 )
    return 0LL;
LABEL_45:
  v25 = v5 == 0;
  v19 = a1;
  v18 = 0;
LABEL_22:
  v10 = v19;
  v9 = 0;
  while ( *v10 != 6 || v25 != v10[1] )
  {
    ++v9;
    v10 += 3;
    if ( v9 == 8 )
    {
      ++v18;
      v19 += 24;
      if ( v18 != 8 )
        goto LABEL_22;
      goto LABEL_11;
    }
  }
  if ( v18 <= 7 && v9 >= 0 )
  {
    v20 = v9 - a2[3];
    if ( v20 < 0 )
      v20 = a2[3] - v9;
    v21 = a2[2] - v18;
    v22 = v18 - a2[2];
    if ( v22 >= 0 )
      v21 = v22;
    if ( v20 < v21 )
      v20 = v21;
    if ( v20 == 1 )
      return 0LL;
  }
LABEL_11:
  v11 = a2[1];
  v12 = a2[3] - v11;
  v13 = v11 - a2[3];
  if ( v13 < 0 )
    v13 = a2[3] - v11;
  v14 = a2[2] - v4;
  v15 = v4 - a2[2];
  if ( v15 < 0 )
    v15 = a2[2] - v4;
  v16 = v15;
  if ( v13 >= v15 )
    v16 = v13;
  v17 = 1;
  if ( v16 > 1 )
  {
    v17 = 0;
    if ( v16 <= 2 && (v15 & v13) == 0 )
    {
      v17 = LOBYTE(a1[24 * v4 + 2 + 3 * v11]);
      if ( (char)v17 )
      {
        return 0;
      }
      else
      {
        if ( v14 )
          v14 = (v14 >> 31) | 1;
        if ( v12 )
          v12 = (v12 >> 31) | 1;
        v23 = &a1[24 * v4 + 24 * (long)v14 + 3 * v12 + 3 * (long)(int)v11];
        do
        {
          v11 += v12;
          v4 += v14;
          if ( (v4 | v11) > 7 )
            break;
          v24 = *v23;
          if ( *v23 == 2 )
            return *((unsigned __int8 *)v23 + 8) ^ 1u;
          v23 += 24 * v14 + 3 * v12;
        }
        while ( !v24 );
      }
    }
  }
  return v17;
}

int main(int a1, char **a2, char **a3, long a4, long a5, long a6, char a7)
{
  char *v7; // rcx
  char *v8; // rdx
  char *v9; // rax
  char *v10; // rdx
  char *v11; // rax
  char *v12; // rax
  int v14[2]; // [rsp+0h] [rbp-358h] BYREF
  char v15; // [rsp+8h] [rbp-350h]
  int v16; // [rsp+Ch] [rbp-34Ch]
  int v17; // [rsp+10h] [rbp-348h]
  char v18; // [rsp+14h] [rbp-344h]
  int v19; // [rsp+18h] [rbp-340h]
  int v20; // [rsp+1Ch] [rbp-33Ch]
  char v21; // [rsp+20h] [rbp-338h]
  int v22; // [rsp+24h] [rbp-334h]
  int v23; // [rsp+28h] [rbp-330h]
  char v24; // [rsp+2Ch] [rbp-32Ch]
  long v25; // [rsp+30h] [rbp-328h]
  char v26; // [rsp+38h] [rbp-320h]
  int v27; // [rsp+3Ch] [rbp-31Ch]
  int v28; // [rsp+40h] [rbp-318h]
  char v29; // [rsp+44h] [rbp-314h]
  int v30; // [rsp+48h] [rbp-310h]
  int v31; // [rsp+4Ch] [rbp-30Ch]
  char v32; // [rsp+50h] [rbp-308h]
  int v33; // [rsp+54h] [rbp-304h]
  int v34; // [rsp+58h] [rbp-300h]
  char v35; // [rsp+5Ch] [rbp-2FCh]
  char v36[96]; // [rsp+60h] [rbp-2F8h] BYREF
  long v37; // [rsp+C0h] [rbp-298h] BYREF
  char v38; // [rsp+240h] [rbp-118h] BYREF
  int v39[2]; // [rsp+2A0h] [rbp-B8h] BYREF
  char v40; // [rsp+2A8h] [rbp-B0h]
  int v41; // [rsp+2ACh] [rbp-ACh]
  int v42; // [rsp+2B0h] [rbp-A8h]
  char v43; // [rsp+2B4h] [rbp-A4h]
  int v44; // [rsp+2B8h] [rbp-A0h]
  int v45; // [rsp+2BCh] [rbp-9Ch]
  char v46; // [rsp+2C0h] [rbp-98h]
  int v47; // [rsp+2C4h] [rbp-94h]
  int v48; // [rsp+2C8h] [rbp-90h]
  char v49; // [rsp+2CCh] [rbp-8Ch]
  long v50; // [rsp+2D0h] [rbp-88h]
  char v51; // [rsp+2D8h] [rbp-80h]
  int v52; // [rsp+2DCh] [rbp-7Ch]
  int v53; // [rsp+2E0h] [rbp-78h]
  char v54; // [rsp+2E4h] [rbp-74h]
  int v55; // [rsp+2E8h] [rbp-70h]
  int v56; // [rsp+2ECh] [rbp-6Ch]
  char v57; // [rsp+2F0h] [rbp-68h]
  int v58; // [rsp+2F4h] [rbp-64h]
  int v59; // [rsp+2F8h] [rbp-60h]
  char v60; // [rsp+2FCh] [rbp-5Ch]
  int v61; // [rsp+300h] [rbp-58h]
  void *v62; // [rsp+308h] [rbp-50h]
  long v63; // [rsp+310h] [rbp-48h]
  long v64; // [rsp+318h] [rbp-40h]
  char v65; // [rsp+320h] [rbp-38h]
  int v66; // [rsp+324h] [rbp-34h]
  long v67; // [rsp+328h] [rbp-30h]
  char v68; // [rsp+330h] [rbp-28h]
  long v69; // [rsp+334h] [rbp-24h]
  char v70; // [rsp+33Ch] [rbp-1Ch]
  unsigned long v71; // [rsp+348h] [rbp-10h]

  v71 = __readfsqword(0x28u);
  v7 = v36;
  v8 = v36;
  do
  {
    v9 = v8 - 96;
    do
    {
      *(_DWORD *)v9 = 0;
      *((_DWORD *)v9 + 1) = 0;
      v9[8] = 0;
      v9 += 12;
    }
    while ( v9 != v8 );
    v8 += 96;
  }
  while ( v8 != &a7 );
  v61 = 0;
  v62 = 0LL;
  v63 = 0LL;
  v64 = 0LL;
  v65 = 0;
  v66 = 0;
  v10 = v36;
  do
  {
    v11 = v10 - 96;
    do
    {
      *(_DWORD *)v11 = 0;
      *((_DWORD *)v11 + 1) = 0;
      v11[8] = 0;
      v11 += 12;
    }
    while ( v11 != v10 );
    v10 += 96;
  }
  while ( v10 != &a7 );
  v14[0] = 2;
  v14[1] = 1;
  v15 = 0;
  v16 = 3;
  v17 = 1;
  v18 = 0;
  v19 = 4;
  v20 = 1;
  v21 = 0;
  v22 = 5;
  v23 = 1;
  v24 = 0;
  v69 = 0x100000006LL;
  v70 = 0;
  v25 = 0x100000006LL;
  v26 = 0;
  v27 = 4;
  v28 = 1;
  v29 = 0;
  v30 = 3;
  v31 = 1;
  v32 = 0;
  v33 = 2;
  v34 = 1;
  v35 = 0;
  do
  {
    *(_DWORD *)v7 = 1;
    *((_DWORD *)v7 + 1) = 1;
    v7[8] = 0;
    v7 += 12;
  }
  while ( v7 != (char *)&v37 );
  v12 = &v38;
  do
  {
    *(_DWORD *)v12 = 1;
    *((_DWORD *)v12 + 1) = 0;
    v12[8] = 0;
    v12 += 12;
  }
  while ( v12 != (char *)v39 );
  v39[0] = 2;
  v39[1] = 0;
  v40 = 0;
  v41 = 3;
  v42 = 0;
  v43 = 0;
  v44 = 4;
  v45 = 0;
  v46 = 0;
  v47 = 5;
  v48 = 0;
  v49 = 0;
  v67 = 6LL;
  v68 = 0;
  v50 = 6LL;
  v51 = 0;
  v52 = 4;
  v53 = 0;
  v54 = 0;
  v55 = 3;
  v56 = 0;
  v57 = 0;
  v58 = 2;
  v59 = 0;
  v60 = 0;
  sub_4F8C(v14, &a7);
  if ( v62 )
    operator delete(v62, v64 - (_QWORD)v62);
  if ( v71 == __readfsqword(0x28u) )
    return 0LL;
  else
    return sub_2972();
}