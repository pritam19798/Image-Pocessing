#include<stdio.h>
#include<ImageProcessing_algo.h>

void main(){
	FILE *fp_w,*fp_r;
	fp_r=fopen("airplane.txt","r");
	fp_w=fopen("airplane_median.pgm","w");
	median_replacement(fp_r,fp_w,255 );
	fclose(fp_r);
	fclose(fp_w);
}
