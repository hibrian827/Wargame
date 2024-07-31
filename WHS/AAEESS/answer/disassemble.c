int sub_138C(int a1)
{
  int v1; // rbx
  int v2; // rax
  const char *v3; // rdx
  int result; // rax
  int v5; // [rsp+Ch] [rbp-7Ch] BYREF
  int v6[11]; // [rsp+10h] [rbp-78h] BYREF
  unsigned int v7; // [rsp+68h] [rbp-20h]

  v7 = __readfsqword(0x28u);
  v1 = EVP_CIPHER_CTX_new();
  memset(v6, 0, 80);
  v5 = 0;
  v2 = EVP_aes_128_ecb();
  EVP_DecryptInit_ex(v1, v2, 0, a1, 0);
  EVP_CIPHER_CTX_set_padding(v1, 0);
  EVP_DecryptUpdate(v1, v6, &v5, &unk_2040, 80);
  EVP_DecryptFinal_ex(v1, (char *)v6 + v5, &v5);
  EVP_CIPHER_CTX_free(v1);
  __printf_chk(1, "Flag is %s\n", (const char *)v6);
  result = v7 - __readfsqword(0x28u);
  if ( result )
    return sub_14B7(1, "Flag is %s\n", v3);
  return result;
}


int main(int a1, char **a2, char **a3)
{
  int *v3; // rbp
  int *v4; // rax
  int v6[2]; // [rsp+0h] [rbp-68h] BYREF
  int s2[2]; // [rsp+10h] [rbp-58h] BYREF
  int v8[2]; // [rsp+20h] [rbp-48h] BYREF
  int v9[2]; // [rsp+30h] [rbp-38h] BYREF
  int v10; // [rsp+40h] [rbp-28h] BYREF

  v9[0] = 0;
  v9[1] = 0;
  v10 = 0;
  sub_1349(a1, a2, a3);
  __printf_chk(1, "Enter your PIN: ");
  __isoc99_scanf("%17s", v9);
  v3 = (int *)v9;
  v4 = (int *)v9;
  do
  {
    if ( (unsigned int)(*(_BYTE *)v4 - 49) > 7u )
      goto LABEL_7;
    v4 = (int *)((char *)v4 + 1);
  }
  while ( v4 != &v10 );
  v6[0] = 0xB7AB67C1F8D54927;
  v6[1] = 0x5FFB3949C076D4C4;
  s2[0] = 0x1DC2F542B5A11946;
  s2[1] = 0xE509394FDF68037A;
  v8[0] = 0;
  v8[1] = 0;
  do
  {
    LOBYTE(v8[0]) = *(_BYTE *)v3;
    sub_14B7(v8, v6);
    v3 = (int *)((char *)v3 + 1);
  }
  while ( v3 != &v10 );
  if ( memcmp(v6, s2, 0x10) )
  {
    LABEL_7:
    puts("Failed");
    exit(0);
  }
  puts("Correct!");
  sub_138C(v9);
  return 0;
}