from pwn import *

print("B"*0x100)

print(hex(0x5555555553db + 125))