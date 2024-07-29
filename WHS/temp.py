import requests

port = 19097
url_main = f"http://srv1.kitriwhs.kr:{port}"
url_gen = url_main + "/generate"
url_guess = url_main + "/guess"

guess = '1f'

for i in range(10000):
  requests.get(url_gen)  
