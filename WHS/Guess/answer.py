import requests

port = 12505
url_main = f"http://srv1.kitriwhs.kr:{port}"
url_gen = url_main + "/generate"
url_guess = url_main + "/guess"

guess = '1f'

for i in range(100000):
  if (i + 1) % 1000 == 0:
    print(f"done {i + 1}")
  requests.get(url_gen)  

# 어느 정도 돌리고 나서 아무 16진수 4자리 값으로 찍어보기