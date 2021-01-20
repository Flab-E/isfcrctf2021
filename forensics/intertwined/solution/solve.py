from PIL import Image

chall = list(Image.open("twined.png").getdata())
img = Image.new("RGB", (1124,750))

dat = []
count = 0;

for i in chall:
    count += 1;
    if count %2 == 0:
        dat += [i]

img.putdata(dat)
img.save("test-flag.png")
