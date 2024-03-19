from pwn import remote
import binascii

def toHex(msg) :
  res = []
  for c in msg :
    temp = str(int(c, 16))
    res.append(temp)
  return ''.join(res)

def sendCmd(rem,num) :
  for i in range(3) :
    print(rem.recvline())
    rem.sendline(str(num).encode())    

port = 21590
rem = remote("srv1.kitriwhs.kr", port)

print(rem.recvline())

# sendCmd(rem, 3)
# encoded_flag = rem.recvline().decode('utf-8')
# flag_val = encoded_flag[encoded_flag.index('=') + 2 : ]

# sendCmd(rem, 1)
# print(rem.recvall())
# rem.sendline(toHex(b"a"))
# print(rem.recvline())

print(toHex("a"))