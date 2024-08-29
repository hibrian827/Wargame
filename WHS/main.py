old_f = open('./findmypassword/problem/deploy/packed.bin', 'rb')
new_f = open('./findmypassword/answer/target.exe', 'wb')

old_txt = old_f.readline()
new_txt = b''
size = len(old_txt)

for b in old_txt:
  new_txt += bytes.fromhex(str(hex(b ^ 0xEF))[2:].zfill(2))
  if len(new_txt) > 5 :
    if new_txt[-5:] == b'\x81\x7c\x24\x20\xaa':
      new_txt = new_txt[:-1] + b'\xa0'
      

print(new_txt)
new_f.write(new_txt)

old_f.close()
new_f.close()