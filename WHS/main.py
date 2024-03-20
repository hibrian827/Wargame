from pwn import remote
from Crypto.Util.number import bytes_to_long
import binascii

def messageToHex(m):
  return hex(bytes_to_long(m.encode("utf-8")))[2:].encode("utf-8")

def sendCmd(rem,num) :
  for i in range(3) :
    print(rem.recvline())
    rem.sendline(str(num).encode())    

port = 24401
rem = remote("srv1.kitriwhs.kr", port)

print(rem.recvline())

# sendCmd(rem, 3)
# encoded_flag = rem.recvline().decode('utf-8')
# flag_val = encoded_flag[encoded_flag.index('=') + 2 : ]
# print(flag_val)

sendCmd(rem, 1)
print(rem.recvuntil(b": "))
rem.sendline(messageToHex('hello'))
print(rem.recvall())
