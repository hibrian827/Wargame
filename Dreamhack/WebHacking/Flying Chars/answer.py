import requests
import io
from PIL import Image

port = 13725
url_index = f"http://host3.dreamhack.games:{port}/"

r = requests.get(url_index)
print(r)

# index 페이지에서 써 있는 그림들의 순서에 따라 사진들 재조합
for i in range(20) :
  url = url_index + f"static/images/{i}.png"
  r = requests.get(url)
  stream = io.BytesIO(r.content)
  img = Image.open(stream)
  img.show()