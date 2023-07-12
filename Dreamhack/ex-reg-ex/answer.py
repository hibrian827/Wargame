import requests

port = 15069
url_index= f"http://host3.dreamhack.games:{port}/"

param = {
  "input_val" : "draaaaae0am@aaa.a"
}

r = requests.post(url_index, data = param)
print(r.text)