clear
close all;
I=imread('1retina.tif')
I=I(:,:,2)
I_med=medfilt2(I,[3,3])
I_gaus= imgaussfilt(I_med,2)
se1 = strel('disk',9);
se2=strel('disk',3);
I_bothat=imbothat(I_med,se1)
I_sharp=imsharpen(I_bothat,'Radius',2,'Amount',1)
level=graythresh(I_sharp)
I_sharp_bw=im2bw(I_sharp,level)
I_sharp_bw=(I_sharp>11)
imshow(I_sharp_bw)
