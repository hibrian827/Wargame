#!/usr/bin/env python3

import requests
import signal
import datetime

signal.alarm(5)

pw = open("pw", "rt").read().strip()
flag_poison = open("flag_poison", "rt").read().strip()

auth_data = {"id": "admin_watchdog", "pw": pw}
test_params = {"scheme": "http", "host": "cproxy", "port": "8080", "path": "/api/ping"}

r = requests.Session()
r.post("http://cproxy:8080/auth", data=auth_data).raise_for_status()
ping = r.get("http://cproxy:8080/proxy", params=test_params, data=flag_poison)
ping.raise_for_status()
assert ping.text == "pong"

print(f"[{datetime.datetime.now()}] Watchdog success.")
