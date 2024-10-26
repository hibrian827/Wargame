#!/usr/bin/env python3
from pwn import *

# context.log_level = 'debug'
context.terminal = ['tmux', 'splitw', '-h']

def create_account(username, pw_len, pw, memo):
    p.sendlineafter(b"> ", b"1")
    p.sendlineafter(b"username: ", username)
    p.sendlineafter(b"password?", str(pw_len).encode())
    p.sendafter(b"password: ", pw), sleep(0.1)
    p.sendlineafter(b"memo: ", memo)

def login(username, pw):
    p.sendlineafter(b"> ", b"2")
    p.sendlineafter(b"username: ", username)
    p.sendafter(b"password:", pw), sleep(0.1)

def change_pw(pw):
    p.sendlineafter(b"> ", b"3")
    p.sendafter(b"password:", pw)

def show_profile():
    p.sendlineafter(b"> ", b"4")

def logout():
    p.sendlineafter(b"> ", b"5")

def admin():
    p.sendlineafter(b"> ", b"-1")

p = process("./chall")
p.interactive()
