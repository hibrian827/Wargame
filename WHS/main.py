from pwn import *

port = 5000
rem = remote("52.79.50.147", port)

payload = b"hi"
rem.sendlineafter(b"post?", payload)
rem.recvuntil(b"post:\n")
msg = rem.recvline()
print(msg)

payload = b"hi" 
rem.sendlineafter(b"post?\n", payload)
msg = rem.recvline()
print(msg)