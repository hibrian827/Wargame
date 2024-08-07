from pwn import *

port = 0
rem = remote("", port)

payload = b"cat flag"
