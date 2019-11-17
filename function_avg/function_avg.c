#include<stdio.h>
#include<stdlib.h>
void average(FILE *fp_r,FILE* fp_w );
void average(FILE *fp_r,FILE* fp_w ){
	int **a, b[10],i,j,k,l,x,c[5];
	for(i=0;i<2;i++){
		fscanf(fp_r,"%d ",&c[i]);
	}
	a=(int**)malloc(sizeof(int*)*c[1]);
	
	for(i=0;i<c[1];i++)
	{	
		a[i]=(int*)malloc(sizeof(int)*c[0]);
		
	}
	i=0;j=0;
	
	
	while(!feof(fp_r)){
		if(i==c[0]){
			i=0;j++;
		}
		fscanf(fp_r,"%d ",&a[j][i]);
		i++;
	}


	for(i=1;i<c[1]-1;i++){
		for(j=1;j<c[0]-1;j++){
			x=0;
			for(k=i-1;k<=i+1;k++){
				for(l=j-1;l<=j+1;l++){
					x=x+a[k][l];
				}
			}
			x=x/9;
			a[i][j]=x;
		}
	}
	
	fprintf(fp_w,"P2 %d %d %d\n",c[0],c[1],255);
	for(i=0;i<c[1];i++){
		for(j=0;j<c[0];j++){
			fprintf(fp_w,"%d ",a[i][j]);
		}
		fprintf(fp_w,"\n");
	}
	free(a);
	a=NULL;
}



void main(){
	FILE *fp_r,*fp_w;
	fp_r=fopen("lena.txt","r");
	fp_w=fopen("lena_edited_avg_function.pgm","w");
	average(fp_r,fp_w);
	fclose(fp_r);
	fclose(fp_w);

	
}
