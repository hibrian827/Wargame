import requests

port = 14195
url_index = f"http://host3.dreamhack.games:{port}/"
url_live = url_index + "live"
url_verify = url_index + "verify"

param = {
    "csp": "script-src https://code.jquery.com/jquery-3.4.1.slim.min.js 'sha256-l1OSKODPRVBa1/91J7WfPisrJ6WCxCRnKFzXaOkpsY4='"
}

r = requests.post(url_verify, data=param)
print(r.text)
