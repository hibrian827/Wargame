from pwn import *

# port = 0 
# rem = remote("", port)

elf = ELF("./Pwnable/send_sig/problem/send_sig")

syscall = next(elf.search(asm("syscall")))

payload = b'A'