#!/usr/bin/env python3
from pwn import *

context.terminal = ['tmux', 'splitw', '-h']

def create_message(index, msg):
    p.sendlineafter(b'Your choice: ', b'1')
    p.sendlineafter(b'Select message index (0 ~ 9): ', str(index).encode())
    p.sendlineafter(b'Input message: ', msg)

def delete_message(index):
    p.sendlineafter(b'Your choice: ', b'2')
    p.sendlineafter(b'Select message index (0 ~ 9): ', str(index).encode())

def show_message(index):
    p.sendlineafter(b'Your choice: ', b'3')
    p.sendlineafter(b'Select message index (0 ~ 9): ', str(index).encode())

def create_feedback(length, feedback):
    p.sendlineafter(b'Your choice: ', b'4')
    p.sendlineafter(b'How long is your feedback: ', str(length).encode())
    p.sendafter(b'Give me your feedback: ', feedback), sleep(0.1)

def show_feedback():
    p.sendlineafter(b'Your choice: ', b'5')

def update_feedback(feedback):
    p.sendlineafter(b'Your choice: ', b'6')
    p.sendlineafter(b'Give me your new feedback: ', feedback)

p = process("./chall")
e = ELF("./chall", checksec=False)

p.interactive()
