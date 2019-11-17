clear 
close all
I=imread('1retina.tif')
I=I(:,:,2)
I_comp=(255-I);
figure (1),imshow(I_comp)
I_adHist=adapthisteq(I_comp,'clipLimit',0.02,'Distribution','rayleigh')
figure (2),imshow(I_adHist);title("adHist")
se1=strel('disk',13)
se2=strel('square',7)
I_adHist_open=imopen(I_adHist,se1)
figure (3),imshow(I_adHist_open);title("I_adHist_open")
I_sub=I_adHist-I_adHist_open
figure (4),imshow(I_sub);title("I_sub")
I_sub_med=medfilt2(I_sub,[3 3])
I_back=imopen(I_sub,se2)
figure (5),imshow(I_back);title("I_back")
I_res=I_sub_med-I_back
figure(6),imshow(I_res);title("I_res")
GLd_max=max(max(I_res))
GLd_min=min(min(I_res))
I_en=(GLd_max-GLd_min)/255*(I_res-0)+GLd_min
%I_en=(255-0)/(GLd_max-GLd_min)*(I_res-GLd_min)+0
level=graythresh(I_en)
I_bw=im2bw(I_en,level)
figure ,imshow(I_bw)
figure ,imshow(I_en)
I_fres=imopen(I_bw,strel('square',3))
figure ,imshow(I_fres)

