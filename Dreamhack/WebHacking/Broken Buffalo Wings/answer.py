import requests

port = 12662
url_index = f"http://host3.dreamhack.games:{port}/"
url_flag = url_index + "flag.txt"
r = requests.get(url_flag)

print(r.text)