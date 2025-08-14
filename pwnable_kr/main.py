from pwn import *

s = ssh(
  user='bof',
  host='pwnable.kr',
  port=2222,
  password='guest'
)

rem = s.process(['nc', '0', '9000'])