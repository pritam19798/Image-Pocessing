I=imread('lena.pgm');
j=imread('lena_edited_median_function.pgm');
I=medfilt2(I);
figure(1);imshow(I);
figure(2);imshow(j);