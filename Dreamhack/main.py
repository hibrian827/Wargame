from pwn import *

port = 1234
rem = remote("localhost", port)
