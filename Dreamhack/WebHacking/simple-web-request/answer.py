import requests

port = 23207
url_index = f"http://host3.dreamhack.games:{port}/"
url_step1 = url_index + "step1"
url_flag = url_index + "flag"

r = requests.get(url_step1 + "?param=getget&param2=rerequest")

start = r.text.find("value=") + 7
end = r.text.find(">", start) - 1
hidden_value = r.text[start : end]

param = {
  "check" : hidden_value,
  "param" : "pooost",
  "param2" : "requeeest"
}

r = requests.post(url_flag, data = param)
print(r.text)