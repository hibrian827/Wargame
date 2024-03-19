from pathlib import Path

hex_list = [(hex(i)[2:].zfill(2).upper()) for i in range(256)]

path_str = Path(__file__).parent.resolve()
path = Path(str(path_str) + r"\problem\encfile")
with open(path, 'rb') as f:
  encrypted = f.read()
encrypted = encrypted.decode('utf-8')

enc_list = [encrypted[i : i + 2] for i in range(0, len(encrypted), 2)]

plain_list = list(range(len(enc_list)))
for i in range(len(enc_list)):
  hex_b = enc_list[i]
  index = hex_list.index(hex_b)
  plain_list[i] = hex_list[(index - 128) % len(hex_list)]

plain_list = ''.join(plain_list)
plain_list = bytes.fromhex(plain_list)

path_str = Path(__file__).parent.resolve()
path = Path(str(path_str) + r"\answer.png")
with open(path, 'wb') as f:
  f.write(plain_list)