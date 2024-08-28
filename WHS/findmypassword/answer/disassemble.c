int main(int argc, const char **argv, const char **envp)
{
  FILE *target; // rdi
  FILE *org_bin; // rax
  FILE *new_bin; // rbp
  size_t v6; // rbx
  char *v7; // rsi
  unsigned int v8; // r9
  __m128 si128; // xmm2
  const __m128i *v10; // rax
  __m128 v11; // xmm0
  char *v12; // rax
  size_t v13; // rcx

  target = fopen("target.exe", "rb");
  org_bin = fopen("packed.bin", "wb");
  new_bin = org_bin;
  if ( target && org_bin )
  {
    fseek(target, 0, 2);
    v6 = fte(target);
    fseek(target, 0, 0);
    v7 = (char *)maoc(v6);
    fread(v7, 1, v6, target);
    v8 = 0;
    if ( v6 )
    {
      if ( v6 < 0x40 ) goto LABEL_8;
      si128 = (__m128)_mm_load_si128((const __m128i *)&xmmword_14005DEB0);
      v10 = (const __m128i *)(v7 + 32);
      do
      {
        v11 = (__m128)_mm_loadu_si128(v10 - 2);
        v10 += 4;
        v8 += 64;
        v10[-6] = (const __m128i)_mm_xor_ps(v11, si128);
        v10[-5] = (const __m128i)_mm_xor_ps(si128, (__m128)_mm_loadu_si128(v10 - 5));
        v10[-4] = (const __m128i)_mm_xor_ps(si128, (__m128)_mm_loadu_si128(v10 - 4));
        v10[-3] = (const __m128i)_mm_xor_ps((__m128)_mm_loadu_si128(v10 - 3), si128);
      }
      while ( v8 < (v6 & 0xFFFFFFFFFFFFFFC0) );

      if ( v8 < v6 )
      {
        // LABEL_8:
        v12 = &v7[v8];
        v13 = v6 - v8;
        do
        {
          *v12++ ^= 0xEFu;
          --v13;
        }
        while ( v13 );
      }
    }
    fwrite(v7, 1, v6, new_bin);
    fclose(target);
    fclose(new_bin);
    free(v7);
    return 0;
  }
  else
  {
    perror("File opening failed");
    return 0;
  }
}