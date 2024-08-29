# -------------------------------------- 1st phase --------------------------------------

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

# -------------------------------------- 2nd phase --------------------------------------

# 코드 분석하여
# 14개 문자 중 9개는 H, e, l, o, I, t에서 사용 / 5개는 -, M, s에서 사용했음을 발견
# 또한 5, 8, 11번째가 -
# 이를 종합하여 Hello-It-Is-Me로 추측