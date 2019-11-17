#include<stdio.h>
#include<ImageProcessing_algo.h>

void main(){
	FILE *fp_w,*fp_r;
	fp_r=fopen("lena.txt","r");
	fp_w=fopen("lena_avg.pgm","w");
	average_replacement(fp_r,fp_w,255 );
	fclose(fp_r);
	fclose(fp_w);
}
