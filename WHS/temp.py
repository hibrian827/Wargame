from pwn import *
from Crypto.Util.Padding import unpad
from Crypto.Cipher import AES


# 서버 연결
host = "srv1.kitriwhs.kr"
port = 13573
r = remote(host, port)

BLOCK_SIZE = 16

# iv 구하기
p = bytes(16).hex().encode()

r.sendlineafter(b"[3] Get Flag\n", b"1")
r.sendlineafter(b"(hex): ", p)
enc_p = bytes.fromhex(r.recvline().decode())
print(enc_p)

r.sendlineafter(b"[3] Get Flag\n", b"2")
r.sendlineafter(b"(hex): ", p)
dec_p = bytes.fromhex(r.recvline().decode())
print(dec_p)
print(r.recvline())
print(r.recvline())
print(r.recvline())
r.sendline(b"2")
print(r.recvuntil(b"(hex): "))
r.sendline(dec_p)
dec2_p = bytes.fromhex(r.recvline().decode())
print(dec2_p)

r.sendlineafter(b"[3] Get Flag\n", b"2")
r.sendlineafter(b"(hex): ", dec2_p)
dec3_p = bytes.fromhex(r.recvline().decode())
print(dec3_p)

r.sendlineafter(b"[3] Get Flag\n", b"2")
r.sendlineafter(b"(hex): ", dec3_p)
dec4_p = bytes.fromhex(r.recvline().decode())
print(dec4_p)

r.sendlineafter(b"[3] Get Flag\n", b"2")
r.sendlineafter(b"(hex): ", dec4_p)
dec5_p = bytes.fromhex(r.recvline().decode())
print(dec5_p)

r.sendlineafter(b"[3] Get Flag\n", b"2")
r.sendlineafter(b"(hex): ", dec5_p + dec4_p + dec3_p + dec2_p + dec_p + p + enc_p)
iv = bytes.fromhex(r.recvline().decode())[48:64]

print(iv)

# 키 구하기
r.sendlineafter(b"[3] Get Flag\n", b"2")
r.sendlineafter(b"(hex): ", p * 4 + enc_iv.hex().encode())

iv = r.recvline().decode()
iv = (bytes.fromhex(iv)[16:32]).hex()

for i in range(5):
  r.sendlineafter(b"[3] Get Flag\n", b"2")
  r.sendlineafter(b"(hex): ", iv)
  iv = r.recvline().decode()

key = iv
print("key: ", key)


# 암호화된 flag 값 받아오기
r.sendlineafter(b"[3] Get Flag\n", b"3")
r.recvuntil(b"flag = ")

enc_flag = r.recvline().decode()
enc_flag = bytes.fromhex(enc_flag)


# flag 복호화

flag = unpad(AES.new(key, AES.MODE_CBC, key).decrypt(enc_flag), BLOCK_SIZE)

print(flag)
