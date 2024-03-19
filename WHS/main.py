from pwn import remote

def sendCmd(rem,num) :
  for i in range(3) :
    print(rem.recvline())
    rem.sendline(str(num).encode())    

port = 13709
rem = remote("srv1.kitriwhs.kr", port)

print(rem.recvline())

sendCmd(rem, 3)
encoded_flag = rem.recvline().decode('utf-8')
flag_val = encoded_flag[encoded_flag.index('=') + 2 : ]

sendCmd(rem, 1)
rem.sendline(flag_val.encode())
print(rem.recvline())