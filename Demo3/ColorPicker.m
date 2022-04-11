function [PixelRGB] = ColorPicker(RGBImage)
image(RGBImage);
[x, y] = ginput(1);
intY = round(y);
intX = round(x);
R = RGBImage(intY, intX, 1);
G = RGBImage(intY, intX, 2);
B = RGBImage(intY, intX, 3);
PixelRGB = [R,G,B];

fprintf("The RGB value of the pixel (%d, %d) is (%d, %d %d)\n", intX, intY, R, G, B);

end