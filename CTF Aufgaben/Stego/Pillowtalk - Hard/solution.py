from PIL import Image
import matplotlib.pyplot as plt

im = Image.open('pillowtalk.png')
pixelMap = im.load()

img = Image.new( im.mode, im.size)
pixelsNew = im.load()

flag = ""

for x in range(100,204):
    s = pixelMap[100,x]
    if(s[2] == 51):
        flag += "1"
    else:
        flag += "0"

print(flag)