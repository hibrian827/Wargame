__int64 sub_4216()
{
  __int64 v0; // rax
  __int64 v1; // rax
  __int64 v2; // rax
  __int64 v3; // rax
  __int64 v4; // rax
  __int64 v5; // rax
  __int64 v6; // rax

  v0 = std::operator<<<std::char_traits<char>>(&std::cout, "==== Linux Forest ====");
  std::ostream::operator<<(v0, &std::endl<char,std::char_traits<char>>);
  v1 = std::operator<<<std::char_traits<char>>(&std::cout, "0. Exit");
  std::ostream::operator<<(v1, &std::endl<char,std::char_traits<char>>);
  v2 = std::operator<<<std::char_traits<char>>(&std::cout, "1. Execute a command");
  std::ostream::operator<<(v2, &std::endl<char,std::char_traits<char>>);
  v3 = std::operator<<<std::char_traits<char>>(&std::cout, "2. Manage environments");
  std::ostream::operator<<(v3, &std::endl<char,std::char_traits<char>>);
  v4 = std::operator<<<std::char_traits<char>>(&std::cout, "3. Create a temp directory");
  std::ostream::operator<<(v4, &std::endl<char,std::char_traits<char>>);
  v5 = std::operator<<<std::char_traits<char>>(&std::cout, "4. Write a file to temp directory");
  std::ostream::operator<<(v5, &std::endl<char,std::char_traits<char>>);
  v6 = std::operator<<<std::char_traits<char>>(&std::cout, "==== ------------ ====");
  return std::ostream::operator<<(v6, &std::endl<char,std::char_traits<char>>);
}

__int64 __fastcall main(__int64 a1, char **a2, char **a3)
{
  void (*v3)(void); // rax
  int v5; // [rsp+Ch] [rbp-4h]

  while ( 1 )
  {
    sub_4216(a1, a2, a3);
    v5 = sub_434E();
    if ( !v5 )
      break;
    a1 = (unsigned int)(v5 - 1);
    v3 = (void (*)(void))sub_2D76(a1);
    v3();
  }
  return 0LL;
}