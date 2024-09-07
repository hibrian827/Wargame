import requests

port = 16671
url_index = f"http://host3.dreamhack.games:{port}/"


param = {"id": "GUEST", "ps": "guest"}

r = requests.post(url_index, data=param)
print(r.text)
