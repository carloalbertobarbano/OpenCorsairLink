import colorsys

while True:
	for i in range(1000):
		color = colorsys.hsv_to_rgb(i/1000.0, 1.0, 1.0)
		r,g,b = int(color[0]*255), int(color[1]*255), int(color[2]*255)
		print("%02x%02x%02x" % (r,g,b))

