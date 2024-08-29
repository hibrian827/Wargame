old_f = open('./findmypassword/problem/deploy/packed.bin', 'rb')
new_f = open('./findmypassword/answer/target.exe', 'wb')

old_txt = old_f.readline()
new_txt = b''
size = len(old_txt)

for b in old_txt:
  print(b)
  new_txt += bytes.fromhex(str(hex(b ^ 0xEF))[2:].zfill(2))

new_f.write(new_txt)

old_f.close()
new_f.close()