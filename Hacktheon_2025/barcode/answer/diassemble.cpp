__int64 __fastcall sub_2650(_BYTE *a1, _BYTE *a2)
{
  __int64 result; // rax

  *a1 = *a2;
  a1[8] = a2[8];
  a1[16] = a2[16];
  a1[24] = a2[24];
  a1[32] = a2[32];
  a1[40] = a2[40];
  a1[48] = a2[48];
  a1[56] = a2[56];
  a1[1] = a2[1];
  a1[9] = a2[9];
  a1[17] = a2[17];
  a1[25] = a2[25];
  a1[33] = a2[33];
  a1[41] = a2[41];
  a1[49] = a2[49];
  a1[57] = a2[57];
  a1[2] = a2[2];
  a1[10] = a2[10];
  a1[18] = a2[18];
  a1[26] = a2[26];
  a1[34] = a2[34];
  a1[42] = a2[42];
  a1[50] = a2[50];
  a1[58] = a2[58];
  a1[3] = a2[3];
  a1[11] = a2[11];
  a1[19] = a2[19];
  a1[27] = a2[27];
  a1[35] = a2[35];
  a1[43] = a2[43];
  a1[51] = a2[51];
  a1[59] = a2[59];
  a1[4] = a2[4];
  a1[12] = a2[12];
  a1[20] = a2[20];
  a1[28] = a2[28];
  a1[36] = a2[36];
  a1[44] = a2[44];
  a1[52] = a2[52];
  a1[60] = a2[60];
  a1[5] = a2[5];
  a1[13] = a2[13];
  a1[21] = a2[21];
  a1[29] = a2[29];
  a1[37] = a2[37];
  a1[45] = a2[45];
  a1[53] = a2[53];
  a1[61] = a2[61];
  a1[6] = a2[6];
  a1[14] = a2[14];
  a1[22] = a2[22];
  a1[30] = a2[30];
  a1[38] = a2[38];
  a1[46] = a2[46];
  a1[54] = a2[54];
  a1[62] = a2[62];
  a1[7] = a2[7];
  a1[15] = a2[15];
  a1[23] = a2[23];
  a1[31] = a2[31];
  a1[39] = a2[39];
  a1[47] = a2[47];
  a1[55] = a2[55];
  result = (unsigned __int8)a2[63];
  a1[63] = result;
  return result;
}

int __fastcall sub_2850(__int64 a1)
{
  __int64 v2; // r14
  __int64 v3; // r15
  int v4; // edi
  int v5; // edi
  int v6; // edi
  int v7; // edi
  int v8; // edi
  int v9; // edi
  int v10; // edi
  int v11; // edi
  int result; // eax

  v2 = 0LL;
  do
  {
    v3 = v2 + 8;
    v4 = 42;
    if ( !*(_BYTE *)(a1 + v2) )
      v4 = 32;
    putchar(v4);
    v5 = 42;
    if ( !*(_BYTE *)(a1 + v2 + 1) )
      v5 = 32;
    putchar(v5);
    v6 = 42;
    if ( !*(_BYTE *)(a1 + v2 + 2) )
      v6 = 32;
    putchar(v6);
    v7 = 42;
    if ( !*(_BYTE *)(a1 + v2 + 3) )
      v7 = 32;
    putchar(v7);
    v8 = 42;
    if ( !*(_BYTE *)(a1 + v2 + 4) )
      v8 = 32;
    putchar(v8);
    v9 = 42;
    if ( !*(_BYTE *)(a1 + v2 + 5) )
      v9 = 32;
    putchar(v9);
    v10 = 42;
    if ( !*(_BYTE *)(a1 + v2 + 6) )
      v10 = 32;
    putchar(v10);
    v11 = 42;
    if ( !*(_BYTE *)(a1 + v2 + 7) )
      v11 = 32;
    putchar(v11);
    result = putchar(10);
    v2 += 8LL;
  }
  while ( v3 != 64 );
  return result;
}

_BYTE *__fastcall std::__cxx11::basic_string<char,std::char_traits<char>,std::allocator<char>>::_M_mutate(
  _QWORD *a1,
  size_t a2,
  __int64 a3,
  _BYTE *a4,
  size_t a5)
{
__int64 v8; // r15
_QWORD *v9; // r12
unsigned __int64 v10; // rax
__int64 v11; // r13
unsigned __int64 v12; // rax
_BYTE *result; // rax
_BYTE *v14; // rsi
size_t v15; // rbp
__int64 v16; // rcx
__int64 v17; // rdx
_BYTE *v18; // rdi
_QWORD *v19; // r15
_QWORD *v20; // r12
size_t v21; // rcx
_BYTE *v22; // rdi
_BYTE *v23; // r14
_BYTE *v24; // [rsp+8h] [rbp-50h]
__int64 v26; // [rsp+18h] [rbp-40h]

v8 = a1[1];
v9 = a1 + 2;
v10 = 15LL;
if ( (_QWORD *)*a1 != a1 + 2 )
v10 = a1[2];
v11 = v8 + a5 - a3;
if ( v11 >= 0 )
{
if ( v11 > v10 )
{
v12 = 2 * v10;
  if ( v11 < v12 )
  {
    v11 = 0x7FFFFFFFFFFFFFFFLL;
    if ( v12 < 0x7FFFFFFFFFFFFFFFLL )
      v11 = v12;
  }
}
if ( v11 + 1 >= 0 )
{
result = (_BYTE *)operator new(v11 + 1);
v24 = result;
if ( a2 )
{
  v14 = (_BYTE *)*a1;
  if ( a2 == 1 )
  {
    *result = *v14;
  }
  else
  {
    memcpy(result, v14, a2);
    result = v24;
  }
}
v26 = a3;
v15 = a2 + a3;
v16 = v8;
v17 = a5;
if ( a4 && a5 )
{
  v18 = &result[a2];
  if ( a5 != 1 )
  {
    memcpy(v18, a4, a5);
    result = v24;
    v17 = a5;
    v16 = v8;
    v19 = v9;
    v20 = (_QWORD *)*a1;
    if ( v16 == v15 )
      goto LABEL_23;
    goto LABEL_18;
  }
  *v18 = *a4;
  v17 = 1LL;
}
v19 = v9;
v20 = (_QWORD *)*a1;
if ( v16 == v15 )
  goto LABEL_23;
LABEL_18:
v21 = v16 - v15;
if ( v21 )
{
  v22 = &result[a2 + v17];
  v23 = (char *)v20 + a2 + v26;
  if ( v21 == 1 )
  {
    *v22 = *v23;
    if ( v20 == v19 )
      goto LABEL_25;
  }
  else
  {
    memcpy(v22, v23, v21);
    result = v24;
    if ( v20 == v19 )
      goto LABEL_25;
  }
  goto LABEL_24;
}
LABEL_23:
if ( v20 == v19 )
{
LABEL_25:
  *a1 = result;
  a1[2] = v11;
  return result;
}
LABEL_24:
operator delete(v20);
result = v24;
goto LABEL_25;
}
std::__throw_bad_alloc();
}
std::__throw_length_error("basic_string::_M_create");
return (_BYTE *)sub_2650("basic_string::_M_create", &unk_30B0);
}

__int64 __fastcall main(int a1, const char **a2, char **a3)
{
  char *v3; // rbx
  signed __int64 v4; // rax
  size_t v5; // r14
  __int64 *v6; // r15
  const char *v7; // r15
  size_t v8; // rax
  _BYTE *v9; // r14
  char v10; // al
  std::ostream *v11; // rax
  const char *v12; // rbx
  size_t v13; // rax
  __int64 v14; // rax
  char v15; // al
  std::ostream *v16; // rdi
  unsigned int v17; // ebx
  __int64 v18; // rax
  char v19; // al
  _BYTE *v20; // r14
  __int64 *v21; // r15
  _QWORD *v22; // rbp
  unsigned __int64 v23; // rsi
  unsigned int v24; // r8d
  __int64 v25; // rdx
  __int64 v26; // rax
  __int64 v27; // rdi
  __int64 v28; // rax
  __int64 v29; // rdi
  bool v30; // cf
  __m128i *v31; // r14
  __m128i *v32; // r13
  __m128i v33; // xmm0
  __m128i v34; // xmm1
  __m128i v35; // xmm2
  __m128i *v36; // r15
  __int64 v37; // r15
  __int64 v38; // rax
  __int64 v39; // r13
  char *v40; // r12
  __int64 v41; // r15
  __m128i v42; // xmm0
  __m128i v43; // xmm1
  __m128i v44; // xmm2
  const __m128i *v45; // rax
  __m128i v46; // xmm0
  __m128i v47; // xmm1
  __m128i v48; // xmm2
  char *v49; // r14
  bool v50; // zf
  std::ostream *v51; // rax
  __int64 v53; // r8
  __int64 v54; // r9
  __int64 v55; // r10
  __int64 v56; // r8
  __int64 v57; // r8
  int v58; // esi
  char *v59; // r10
  __int64 v60; // r11
  __int64 v61; // rbx
  __m128i v62; // xmm3
  struct _Unwind_Exception *v63; // r14
  void *v64; // rdi
  void *v65; // rdi
  __int64 v66; // [rsp+0h] [rbp-118h]
  void *v67; // [rsp+8h] [rbp-110h] BYREF
  __int64 v68; // [rsp+10h] [rbp-108h]
  __m128i v69; // [rsp+20h] [rbp-F8h] BYREF
  __m128i v70; // [rsp+30h] [rbp-E8h] BYREF
  __m128i v71; // [rsp+40h] [rbp-D8h] BYREF
  __m128i v72; // [rsp+50h] [rbp-C8h] BYREF
  char v73[64]; // [rsp+60h] [rbp-B8h] BYREF
  void *v74[2]; // [rsp+A0h] [rbp-78h] BYREF
  __int64 v75[2]; // [rsp+B0h] [rbp-68h] BYREF
  void *v76; // [rsp+C0h] [rbp-58h]
  unsigned __int64 v77; // [rsp+C8h] [rbp-50h]
  __int64 dest[2]; // [rsp+D0h] [rbp-48h] BYREF
  unsigned __int64 v79; // [rsp+E0h] [rbp-38h]

  v3 = (char *)a2;
  // v79 = __readfsqword(0x28u);
  if ( a1 == 2 )
  {
    v3 = (char *)a2[1];
    v76 = dest;
    v4 = strlen(v3);
    v5 = v4;
    v6 = dest;
    if ( (unsigned __int64)v4 >= 0x10 )
    {
      v6 = (__int64 *)operator new(v4 + 1);
      v76 = v6;
      dest[0] = v5;
    }
    if ( v5 )
    {
      if ( v5 == 1 )
        *(_BYTE *)v6 = *v3;
      else
        memcpy(v6, v3, v5);
    }
    v77 = v5;
    *((_BYTE *)v6 + v5) = 0;
    v3 = (char *)(v77 - 2);
    v74[0] = v75;
    v20 = (char *)v76 + 2;
    if ( v77 - 2 < 0x10 )
    {
      v21 = v75;
      if ( v77 == 3 )
      {
        LOBYTE(v75[0]) = *v20;
        v21 = v75;
        goto LABEL_37;
      }
LABEL_36:
      memcpy(v21, v20, (size_t)v3);
LABEL_37:
      v74[1] = v3;
      v3[(_QWORD)v21] = 0;
      sub_12E0(&v67, v74);
      v22 = v67;
      v66 = v68;
      v23 = (unsigned __int64)(v68 - (_QWORD)v67) >> 3;
      v24 = v23 - 1;
      if ( (int)v23 - 1 > 0 )
      {
        v25 = v24;
        v26 = (unsigned int)v23;
        if ( v24 < 0x22
          || (v53 = (unsigned int)(v23 - 2), v54 = 8 * v25 - 8, (char *)v67 + 8 * v53 - v54 > (char *)v67 + 8 * v53)
          || (char *)v67 + 8 * v25 - v54 > (char *)v67 + 8 * v25
          || (unsigned int)v53 < (int)v25 - 1
          || (unsigned __int64)(v25 - 1) >> 32
          || (v55 = 8 * v25, v56 = (v68 - (_QWORD)v67 + 0x7FFFFFFF0LL) & 0x7FFFFFFF8LL, v67 < (char *)v67 + v56)
          && (char *)v67 + v56 - v55 + 8 < (char *)v67 + 8 * v25 + 8 )
        {
          v27 = v25;
        }
        else
        {
          v57 = v25 & 0x7FFFFFFC;
          v26 = (unsigned int)v23 - v57;
          v27 = v25 & 3;
          v58 = v23 - 2;
          v59 = (char *)v67 + v55 - 8;
          v60 = 0LL;
          do
          {
            v61 = (unsigned int)(v58 + v60);
            v62 = _mm_xor_si128(
                    _mm_xor_si128(_mm_loadu_si128((const __m128i *)&v59[8 * v60 - 16]), (__m128i)-1LL),
                    _mm_loadu_si128((const __m128i *)&v22[v61 - 3]));
            *(__m128i *)&v59[8 * v60] = _mm_xor_si128(
                                          _mm_xor_si128(_mm_loadu_si128((const __m128i *)&v59[8 * v60]), (__m128i)-1LL),
                                          _mm_loadu_si128((const __m128i *)&v22[v61 - 1]));
            *(__m128i *)&v59[8 * v60 - 16] = v62;
            v60 -= 4LL;
          }
          while ( -(v25 & 0x7FFFFFFC) != v60 );
          if ( v57 == v25 )
            goto LABEL_42;
        }
        v28 = v26 + 4294967294LL;
        v29 = v27 + 1;
        do
        {
          v22[v29 - 1] = ~(v22[v29 - 1] ^ v22[(unsigned int)v28--]);
          v30 = v29-- == 1;
        }
        while ( !v30 && v29 != 1 );
      }
LABEL_42:
      if ( v22 != (_QWORD *)v66 )
      {
        v3 = 0LL;
        v31 = 0LL;
        v32 = 0LL;
        do
        {
          while ( 1 )
          {
            sub_18F0(*v22, v73);
            sub_2650(&v69, v73);
            if ( v31 == v32 )
              break;
            v33 = _mm_loadu_si128(&v69);
            v34 = _mm_loadu_si128(&v70);
            v35 = _mm_loadu_si128(&v71);
            v31[3] = _mm_loadu_si128(&v72);
            v31[2] = v35;
            v31[1] = v34;
            *v31 = v33;
            v36 = v31;
            v31 += 4;
            if ( ++v22 == (_QWORD *)v66 )
              goto LABEL_60;
          }
          if ( (char *)v31 - v3 == 0x7FFFFFFFFFFFFFC0LL )
            goto LABEL_90;
          v37 = ((char *)v31 - v3) >> 6;
          v38 = (v37 == 0) + v37;
          v39 = v38 + v37;
          if ( (unsigned __int64)(v38 + v37) >= 0x1FFFFFFFFFFFFFFLL )
            v39 = 0x1FFFFFFFFFFFFFFLL;
          if ( __CFADD__(v37, v38) )
            v39 = 0x1FFFFFFFFFFFFFFLL;
          if ( v39 )
            v40 = (char *)operator new(v39 << 6);
          else
            v40 = 0LL;
          v41 = v37 << 6;
          v42 = _mm_loadu_si128(&v69);
          v43 = _mm_loadu_si128(&v70);
          v44 = _mm_loadu_si128(&v71);
          *(__m128i *)&v40[v41 + 48] = _mm_loadu_si128(&v72);
          *(__m128i *)&v40[v41 + 32] = v44;
          *(__m128i *)&v40[v41 + 16] = v43;
          *(__m128i *)&v40[v41] = v42;
          v36 = (__m128i *)v40;
          if ( v3 != (char *)v31 )
          {
            v36 = (__m128i *)v40;
            v45 = (const __m128i *)v3;
            do
            {
              v46 = _mm_loadu_si128(v45);
              v47 = _mm_loadu_si128(v45 + 1);
              v48 = _mm_loadu_si128(v45 + 2);
              v36[3] = _mm_loadu_si128(v45 + 3);
              v36[2] = v48;
              v36[1] = v47;
              *v36 = v46;
              v45 += 4;
              v36 += 4;
            }
            while ( v45 != v31 );
          }
          if ( v3 )
            operator delete(v3);
          v32 = (__m128i *)&v40[64 * v39];
          v3 = v40;
          v31 = v36 + 4;
          ++v22;
        }
        while ( v22 != (_QWORD *)v66 );
LABEL_60:
        if ( v3 != (char *)v31 )
        {
          v49 = v3;
          do
          {
            sub_2850(v49);
            v50 = v49 == (char *)v36;
            v49 += 64;
          }
          while ( !v50 );
        }
        if ( v3 )
          operator delete(v3);
      }
      if ( v67 )
        operator delete(v67);
      if ( v74[0] != v75 )
        operator delete(v74[0]);
      v17 = 0;
      goto LABEL_72;
    }
    if ( (__int64)v3 < 0 )
      goto LABEL_100;
    if ( (__int64)(v77 - 1) >= 0 )
    {
      v21 = (__int64 *)operator new(v77 - 1);
      v74[0] = v21;
      v75[0] = (__int64)v3;
      goto LABEL_36;
    }
    goto LABEL_88;
  }
  std::__ostream_insert<char,std::char_traits<char>>(&std::cout, "Usage: ", 7LL);
  v7 = *a2;
  if ( *a2 )
  {
    v8 = strlen(*a2);
    std::__ostream_insert<char,std::char_traits<char>>(&std::cout, v7, v8);
  }
  else
  {
    std::basic_ios<char,std::char_traits<char>>::clear(
      (char *)&std::cout + *(_QWORD *)(std::cout - 24LL),
      *(_DWORD *)((char *)&std::cout + *(_QWORD *)(std::cout - 24LL) + 32) | 1u);
  }
  std::__ostream_insert<char,std::char_traits<char>>(&std::cout, " {hex-string}", 13LL);
  v9 = *(_BYTE **)((char *)&std::cout + *(_QWORD *)(std::cout - 24LL) + 240);
  if ( !v9 )
    goto LABEL_92;
  if ( v9[56] )
  {
    v10 = v9[67];
  }
  else
  {
    std::ctype<char>::_M_widen_init(v9);
    v10 = (*(__int64 (__fastcall **)(_BYTE *, __int64))(*(_QWORD *)v9 + 48LL))(v9, 10LL);
  }
  v11 = (std::ostream *)std::ostream::put((std::ostream *)&std::cout, v10);
  std::ostream::flush(v11);
  std::__ostream_insert<char,std::char_traits<char>>(&std::cout, "Example: ", 9LL);
  v12 = *a2;
  if ( *a2 )
  {
    v13 = strlen(v12);
    std::__ostream_insert<char,std::char_traits<char>>(&std::cout, v12, v13);
  }
  else
  {
    std::basic_ios<char,std::char_traits<char>>::clear(
      (char *)&std::cout + *(_QWORD *)(std::cout - 24LL),
      *(_DWORD *)((char *)&std::cout + *(_QWORD *)(std::cout - 24LL) + 32) | 1u);
  }
  std::__ostream_insert<char,std::char_traits<char>>(&std::cout, " 0x3E08080818381808", 19LL);
  v14 = *(_QWORD *)(std::cout - 24LL);
  v3 = *(char **)((char *)&std::cout + v14 + 240);
  if ( !v3 )
  {
LABEL_92:
    // if ( __readfsqword(0x28u) != v79 )
    //   return std::__cxx11::basic_string<char,std::char_traits<char>,std::allocator<char>>::_M_mutate();
    std::__throw_bad_cast();
    goto LABEL_94;
  }
  if ( v3[56] )
  {
    v15 = v3[67];
  }
  else
  {
    std::ctype<char>::_M_widen_init(*(_QWORD *)((char *)&std::cout + v14 + 240));
    v15 = (*(__int64 (__fastcall **)(char *, __int64))(*(_QWORD *)v3 + 48LL))(v3, 10LL);
  }
  v16 = (std::ostream *)std::ostream::put((std::ostream *)&std::cout, v15);
  std::ostream::flush(v16);
  v17 = 1;
LABEL_74:
  // if ( __readfsqword(0x28u) == v79 )
  //   return v17;
  return std::__cxx11::basic_string<char,std::char_traits<char>,std::allocator<char>>::_M_mutate();
}