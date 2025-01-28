const char *sub_401090()
{
  return "/bin/sh";
}

long sub_4010A6()
{
  long savedregs; // [rsp+0h] [rbp+0h]

  return savedregs;
}

ssize_t sub_4010B6()
{
  char buf[8]; // [rsp+8h] [rbp-8h] BYREF

  write(1, "Signal:", 7);
  return read(0, buf, 0x400);
}

void start()
{
  setvbuf(stdout, 0, 2, 0);
  setvbuf(stdin, 0, 1, 0);
  write(1, "++++++++++++++++++Welcome to dreamhack++++++++++++++++++\n", 0x39);
  write(1, "+ You can send a signal to dreamhack server.           +\n", 0x39);
  write(1, "++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n", 0x39);
  sub_4010B6();
  exit(0);
}