from pwn import *

s = ssh(
  user='fd',
  host='pwnable.kr',
  port=2222,
  password='guest'
)

rem = s.process()