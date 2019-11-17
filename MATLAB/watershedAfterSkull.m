clear
close all;
img=imread('cd2.tif');
%img=(img(:,:,1)+img(:,:,2)+img(:,:,3))/3
H = fspecial('average', [3 3]);
%img = imfilter(img, H);
subplot(1,2,1);
imshow(img);
title("original")

%skulp stripping

insideSkull = (img > 0.3*255);   
%figure (1),imshow(insideSkull)
insideSkull = imfill(insideSkull, 'holes'); 
%figure (2),imshow(~insideSkull)
bw = (img > 0.4*255);
lbl = bwlabel(bw);
a=(max(lbl))
props = regionprops(lbl, 'Solidity', 'Area','convexarea');
solidity = [props.Solidity];
skull = find(solidity < 0.3);
skull = ismember(lbl, skull);
%figure (4),imshow(skull);
skullOrBorder = skull | ~insideSkull;
%figure(5),imshow(skullOrBorder);
noSkull = img;
noSkull(skullOrBorder)=0;
subplot(1,2,2);
imshow(noSkull);
title('after skullstriping')
%edege detection and watershed


IG=imgradient(noSkull);
LW=watershed(IG);
rs = uint8(255 * LW);
figure(3) ,imshow(rs)
title('watersheding')