from PIL import Image
import matplotlib.pyplot as plt

im = Image.open('drop.jpg')
pixelMap = im.load()

img = Image.new( im.mode, im.size)
pixelsNew = im.load()

for x in range(99,101):
    #01101110
    pixelMap[x,100] = (200,50,50,50)
    pixelMap[x,101] = (200,50,51,50)
    pixelMap[x,102] = (200,50,51,50)
    pixelMap[x,103] = (200,50,50,50)
    pixelMap[x,104] = (200,50,51,50)
    pixelMap[x,105] = (200,50,51,50)
    pixelMap[x,106] = (200,50,51,50)
    pixelMap[x,107] = (200,50,50,50)

#01101x
    pixelMap[x,108] = (200,50,50,50)
    pixelMap[x,109] = (200,50,51,50)
    pixelMap[x,110] = (200,50,51,50)
    pixelMap[x,111] = (200,50,50,50)
    pixelMap[x,112] = (200,50,51,50)
    pixelMap[x,113] = (200,50,51,50)
    pixelMap[x,114] = (200,50,50,50)
    pixelMap[x,115] = (200,50,50,50)

#01x001
    pixelMap[x,116] = (200,50,50,50)
    pixelMap[x,117] = (200,50,51,50)
    pixelMap[x,118] = (200,50,51,50)
    pixelMap[x,119] = (200,50,50,50)
    pixelMap[x,120] = (200,50,50,50)
    pixelMap[x,121] = (200,50,50,50)
    pixelMap[x,122] = (200,50,50,50)
    pixelMap[x,123] = (200,50,51,50)

#01101110
    pixelMap[x,124] = (200,50,50,50)
    pixelMap[x,125] = (200,50,51,50)
    pixelMap[x,126] = (200,50,51,50)
    pixelMap[x,127] = (200,50,50,50)
    pixelMap[x,128] = (200,50,51,50)
    pixelMap[x,129] = (200,50,51,50)
    pixelMap[x,130] = (200,50,51,50)
    pixelMap[x,131] = (200,50,50,50)

#01xx
    pixelMap[x,132] = (200,50,50,50)
    pixelMap[x,133] = (200,50,51,50)
    pixelMap[x,134] = (200,50,51,50)
    pixelMap[x,135] = (200,50,50,50)
    pixelMap[x,136] = (200,50,50,50)
    pixelMap[x,137] = (200,50,51,50)
    pixelMap[x,138] = (200,50,50,50)
    pixelMap[x,139] = (200,50,50,50)

#01111011
    pixelMap[x,140] = (200,50,50,50)
    pixelMap[x,141] = (200,50,51,50)
    pixelMap[x,142] = (200,50,51,50)
    pixelMap[x,143] = (200,50,51,50)
    pixelMap[x,144] = (200,50,51,50)
    pixelMap[x,145] = (200,50,50,50)
    pixelMap[x,146] = (200,50,51,50)
    pixelMap[x,147] = (200,50,51,50)

#00110111
    pixelMap[x,148] = (200,50,50,50)
    pixelMap[x,149] = (200,50,50,50)
    pixelMap[x,150] = (200,50,51,50)
    pixelMap[x,151] = (200,50,51,50)
    pixelMap[x,152] = (200,50,50,50)
    pixelMap[x,153] = (200,50,51,50)
    pixelMap[x,154] = (200,50,51,50)
    pixelMap[x,155] = (200,50,51,50)

#00110x
    pixelMap[x,156] = (200,50,50,50)
    pixelMap[x,157] = (200,50,50,50)
    pixelMap[x,158] = (200,50,51,50)
    pixelMap[x,159] = (200,50,51,50)
    pixelMap[x,160] = (200,50,50,50)
    pixelMap[x,161] = (200,50,51,50)
    pixelMap[x,162] = (200,50,50,50)
    pixelMap[x,163] = (200,50,50,50)

#001x01
    pixelMap[x,164] = (200,50,50,50)
    pixelMap[x,165] = (200,50,50,50)
    pixelMap[x,166] = (200,50,51,50)
    pixelMap[x,167] = (200,50,51,50)
    pixelMap[x,168] = (200,50,50,50)
    pixelMap[x,169] = (200,50,50,50)
    pixelMap[x,170] = (200,50,50,50)
    pixelMap[x,171] = (200,50,51,50)

#01101011
    pixelMap[x,172] = (200,50,50,50)
    pixelMap[x,173] = (200,50,51,50)
    pixelMap[x,174] = (200,50,51,50)
    pixelMap[x,175] = (200,50,50,50)
    pixelMap[x,176] = (200,50,51,50)
    pixelMap[x,177] = (200,50,50,50)
    pixelMap[x,178] = (200,50,51,50)
    pixelMap[x,179] = (200,50,51,50)

#001x11
    pixelMap[x,180] = (200,50,50,50)
    pixelMap[x,181] = (200,50,50,50)
    pixelMap[x,182] = (200,50,51,50)
    pixelMap[x,183] = (200,50,51,50)
    pixelMap[x,184] = (200,50,50,50)
    pixelMap[x,185] = (200,50,50,50)
    pixelMap[x,186] = (200,50,51,50)
    pixelMap[x,187] = (200,50,51,50)

#011x10
    pixelMap[x,188] = (200,50,50,50)
    pixelMap[x,189] = (200,50,51,50)
    pixelMap[x,190] = (200,50,51,50)
    pixelMap[x,191] = (200,50,51,50)
    pixelMap[x,192] = (200,50,50,50)
    pixelMap[x,193] = (200,50,50,50)
    pixelMap[x,194] = (200,50,51,50)
    pixelMap[x,195] = (200,50,50,50)

#01111101
    pixelMap[x,196] = (200,50,50,50)
    pixelMap[x,197] = (200,50,51,50)
    pixelMap[x,198] = (200,50,51,50)
    pixelMap[x,199] = (200,50,51,50)
    pixelMap[x,200] = (200,50,51,50)
    pixelMap[x,201] = (200,50,51,50)
    pixelMap[x,202] = (200,50,50,50)
    pixelMap[x,203] = (200,50,51,50)

im.save("pillowtalk.png")
plt.imshow(im)
plt.show()