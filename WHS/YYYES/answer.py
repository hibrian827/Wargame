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
enc_p = r.recvline().rstrip()

r.sendlineafter(b"[3] Get Flag\n", b"2")
r.sendlineafter(b"(hex): ", p)
dec_p = r.recvline().rstrip()

r.sendlineafter(b"[3] Get Flag\n", b"2")
r.sendlineafter(b"(hex): ", dec_p)
r.sendline(dec_p)
dec2_p = r.recvline().rstrip()

r.sendlineafter(b"[3] Get Flag\n", b"2")
r.sendlineafter(b"(hex): ", dec2_p)
dec3_p = r.recvline().rstrip()

r.sendlineafter(b"[3] Get Flag\n", b"2")
r.sendlineafter(b"(hex): ", dec3_p)
dec4_p = r.recvline().rstrip()

r.sendlineafter(b"[3] Get Flag\n", b"2")
r.sendlineafter(b"(hex): ", dec4_p)
dec5_p = r.recvline().rstrip()

r.sendlineafter(b"[3] Get Flag\n", b"2")
r.sendlineafter(b"(hex): ", dec5_p + dec4_p + dec3_p + dec2_p + dec_p + p + enc_p)
iv = r.recvline().rstrip()[96:128]

# 키 구하기
key = iv
for i in range(5):
  key = p + key
  r.sendlineafter(b"[3] Get Flag\n", b"2")
  r.sendlineafter(b"(hex): ", key)
  key = r.recvline().rstrip()[32:64]


# 암호화된 flag 값 받아오기
r.sendlineafter(b"[3] Get Flag\n", b"3")
r.recvuntil(b"flag = ")

enc_flag = r.recvline().decode()
enc_flag = bytes.fromhex(enc_flag)


# flag 복호화
iv = bytes.fromhex(iv.decode())
key = bytes.fromhex(key.decode())
flag = unpad(AES.new(key, AES.MODE_CBC, iv).decrypt(enc_flag), BLOCK_SIZE)
print(flag)