const char *sub_401090()
{
  return "/bin/sh";
}

__int64 sub_4010A6()
{
  __int64 savedregs; // [rsp+0h] [rbp+0h]

  return savedregs;
}

ssize_t sub_4010B6()
{
  char buf[8]; // [rsp+8h] [rbp-8h] BYREF

  write(1, "Signal:", 7uLL);
  return read(0, buf, 0x400uLL);
}

void __noreturn start()
{
  setvbuf(stdout, 0LL, 2, 0LL);
  setvbuf(stdin, 0LL, 1, 0LL);
  write(1, "++++++++++++++++++Welcome to dreamhack++++++++++++++++++\n", 0x39uLL);
  write(1, "+ You can send a signal to dreamhack server.           +\n", 0x39uLL);
  write(1, "++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n", 0x39uLL);
  sub_4010B6();
  exit(0);
}