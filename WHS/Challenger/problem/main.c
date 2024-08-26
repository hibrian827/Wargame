// public _check_table
//    0   1   2   3   4   5   6   7   8   9   10  11
// -----------------------------------------------------
//    2   0   0   0   0   0   0   0   0   0   0   0
//    3   0   0   0   0   0   0   0   FF  FF  FF  FF
//    5   0   0   0   0   0   0   0   FD  FF  FF  FF
//    49  0   0   0   0   0   0   0   FC  FF  FF  FF
//    B   0   0   0   0   0   0   0   2   0   0   0
//    25  0   0   0   0   0   0   0   8   0   0   0

//    0   0   0   0   0   0   0   0   7B480F5F5F5D134B  6E5168747451687E  6D3A337F5F7A232F  6E3E6A6C
//    61


int check_key(int key, int table, unsigned int a3)
{
  for ( i = 0; i < a3; ++i )
  {
    if ( (unsigned int)(*(_DWORD *)(12 * i + table + 8) + key) % *(_DWORD *)(12 * i + table) != *(_DWORD *)(12 * i + table + 4) )
      return 0;
  }
  return 1;
}


int decode_text(int encoded, unsigned int a2, unsigned int key, int a4)
{
  int result; // rax
  unsigned int i; // [rsp+0h] [rbp-28h]

  for ( i = 0; i < a2; ++i )
    *(_BYTE *)(a4 + i) = (key >> (8 * (i & 3))) ^ *(_BYTE *)(encoded + i);
  result = a4;
  *(_BYTE *)(a4 + a2) = 0;
  return result;
}


int main(int argc, const char **argv, const char **envp)
{
  void *v3; // rsp
  _BYTE v5[4]; // [rsp+0h] [rbp-70h] BYREF
  int v6; // [rsp+4h] [rbp-6Ch]
  int v7; // [rsp+8h] [rbp-68h]
  const char *v8; // [rsp+10h] [rbp-60h]
  int v9; // [rsp+18h] [rbp-58h]
  _BYTE *v10; // [rsp+20h] [rbp-50h]
  unsigned int key; // [rsp+2Ch] [rbp-44h] BYREF
  int v12 = 29; // [rsp+30h] [rbp-40h]
  int v13; // [rsp+3Ch] [rbp-34h]
  int encoded[3]; // [rsp+40h] [rbp-30h] BYREF
  int v15[4]; // [rsp+58h] [rbp-18h] BYREF
  int v16; // [rsp+68h] [rbp-8h]

  v13 = 0;
  encoded[0] = 0x7B480F5F5F5D134B;
  encoded[1] = 0x6E5168747451687E;
  encoded[2] = 0x6D3A337F5F7A232F;
  qmemcpy(v15, "lj>na", 5);
  key = 0;
  printf("**************************************\n");
  printf("**************************************\n");
  printf("**** WELCOME NEXT GEN CHALLENGERS ****\n");
  printf("**************************************\n");
  printf("**************************************");
  printf("\n\n");
  printf("Enter the key: ");
  scanf("%d", &key);
  if ( key <= 0x989680 )
  {
    if ( (unsigned int)check_key(key, &check_table, 6) )
    {
      v8 = v5;
      decode_text(encoded, v12, key, v5);
      printf("\n");
      printf("CONGRATURATIONS!\n");
      printf("Decoded: %s\n", v8);
    }
    else
    {
      printf("Wrong key!\n");
    }
    v13 = 0;
  }
  else
  {
    printf("Key is too big!\n");
    v13 = 0;
  }
  v6 = v13;
  if ( __stack_chk_guard != v16 )
    BUG();
  return v6;
}