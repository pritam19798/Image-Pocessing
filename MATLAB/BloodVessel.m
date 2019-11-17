clear 
close all
I=imread('retina.jpg')
%I=imresize(I,[576,576])
gc=I(:,:,2)
figure ,imshow(gc)
H = fspecial('average', [3 3]);
gc=imfilter(gc,H)
figure ,imshow(gc)
gch=histeq(gc)
%subplot(1,2,1)
figure ,imshow(gch)
s2=strel('disk',5)
s1=strel('disk',2)
res=imbothat(gch,s2)
res=im2bw(res,0.1);
res=wiener2(res,[3 3]);
%res=imopen(res,s1)
%res=imdilate(res,s1)
res=imerode(res,s1)
%subplot(1,2,2)
figure ,imshow(res)