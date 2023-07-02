import requests

port = 24446
url_index = f"http://host3.dreamhack.games:{port}/"

param = {"json": '{"key":0}'}

r = requests.post(url_index, data=param)
print(r.text)
