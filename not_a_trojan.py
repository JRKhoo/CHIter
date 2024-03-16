import requests
from PIL import Image

def trojan():
    img_url = "https://www.team17.com/wp-content/uploads/2020/08/W-BANNER1-2048x608.jpg"
    response = requests.get(img_url)
    if response.status_code:
        fp = open("worms.png", "wb")
        fp.write(response.content)
        fp.close()
    Image.open("worms.png").show()


if __name__ == "__main__":
    trojan()
