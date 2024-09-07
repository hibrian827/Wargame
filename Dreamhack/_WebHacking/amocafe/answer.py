import requests
import string

port = 9157
url_index = f"http://host3.dreamhack.games:{port}/"

r = requests.get(url_index)
start = r.text.index("<code>") + 6
end = r.text.index("</code>")
code = list(r.text[start : end])

org = 0
for char in code :
  num = 0
  org *= 16
  if char == "_" :
    num = 11
  elif char in string.ascii_lowercase :
    num = int(char, 16)
  else :
    num = int(char)
  org += num

param = {
  "menu_input" : org
}
r = requests.post(url_index, data = param)
print(r.text)