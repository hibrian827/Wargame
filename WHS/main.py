from pwn import remote
from Crypto.Util.number import bytes_to_long
import binascii

def messageToHex(m):
  return binascii.hexlify(m.encode())

def sendCmd(rem, num) :
  print(rem.recvuntil(b"Flag\n"))
  rem.sendline(str(num).encode())
  if num == 1 or num == 2:
    rem.recvuntil(b": ")

port = 11675
rem = remote("srv1.kitriwhs.kr", port)

print(rem.recvline())

# sendCmd(rem, 3)
# encoded_flag = rem.recvline().decode('utf-8')
# flag_val = encoded_flag[encoded_flag.index('=') + 2 : -1]
# print(flag_val)

sendCmd(rem, 1)
rem.sendline(messageToHex("hello"))
test = rem.recvline().decode()
print(test)

sendCmd(rem, 2)
rem.sendline(test.encode())
print(bytes.fromhex(rem.recvline().decode()).decode("utf-8"))
