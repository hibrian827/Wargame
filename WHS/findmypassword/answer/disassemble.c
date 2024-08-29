int main(int argc, const char **argv, const char **envp)
{
  FILE *target; // rdi
  FILE *org_bin; // rax
  FILE *new_bin; // rbp
  size_t file_end; // rbx
  char *v7; // rsi
  unsigned int cursor; // r9
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
    fseek(target, 0, 2); // to the end
    file_end = ftell(target);
    fseek(target, 0, 0); // to the start
    
    v7 = (char *)malloc(file_end);
    fread(v7, 1, file_end, target);
    cursor = 0;

    if ( file_end )
    {
      if ( file_end < 0x40 ) goto LABEL_8;

      si128 = (__m128)_mm_load_si128((const __m128i *) &xmmword_14005DEB0); // 0xEFEFEFEFEFEFEFEFEFEFEFEFEFEFEFEF
      v10 = (const __m128i *)(v7 + 32);
      
      do
      {
        v11 = (__m128)_mm_loadu_si128(v10 - 2);
        v10 += 4;
        v10[-6] = (const __m128i)_mm_xor_ps(v11, si128);
        v10[-5] = (const __m128i)_mm_xor_ps(si128, (__m128)_mm_loadu_si128(v10 - 5));
        v10[-4] = (const __m128i)_mm_xor_ps(si128, (__m128)_mm_loadu_si128(v10 - 4));
        v10[-3] = (const __m128i)_mm_xor_ps((__m128)_mm_loadu_si128(v10 - 3), si128);
        cursor += 64;
      }
      while ( cursor < (file_end & 0xFFFFFFFFFFFFFFC0) );

      if ( cursor < file_end )
      {
        // LABEL_8:
        v12 = &v7[cursor];
        v13 = file_end - cursor;
        do
        {
          *v12++ ^= 0xEFu;
          --v13;
        }
        while ( v13 );
      }
    }

    fwrite(v7, 1, file_end, new_bin);


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