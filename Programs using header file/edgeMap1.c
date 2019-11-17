#include<stdio.h>
#include<ImageProcessing_algo.h>

void main(){
	FILE *fp_r,*fp_w;
	int edge[3][3]={{-1,0,1},
					{-2,0,2},
					{-1,0,1}};
	int edge2[3][3]={{-1,-2,-1},
					{0,0,0},
					{1,2,1}};
	fp_r=fopen("airplane_edited_median_function_copy.txt","r");
	fp_w=fopen("airplane_edge1.pgm","w");
	printf("all files opend");
	edgeMap(fp_r, fp_w, edge,edge2,255 );
	fclose(fp_r);
	fclose(fp_w);
}
