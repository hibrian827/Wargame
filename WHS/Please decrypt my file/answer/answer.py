enc_file = open("./Please decrypt my file/problem/flag.png.enc" , "rb")
org_file = open("./Please decrypt my file/problem/flag.png" , "wb")

file_content = enc_file.read()
total_size = len(file_content)
half_pt = int((total_size - 0x20) / 2)
key_size = 0x20

key = file_content[half_pt : half_pt + key_size]

for i in range(half_pt):
  org_file.write(bytes.fromhex(hex(file_content[i] ^ key[i % 32])[2:].zfill(2)))

for i in range(half_pt + key_size, total_size):
  org_file.write(bytes.fromhex(hex(file_content[i] ^ key[(i - key_size) % 32])[2:].zfill(2)))