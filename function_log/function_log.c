#include<stdio.h>
#include<stdlib.h>
#include<math.h>
void log_transform(FILE *fp_r,FILE* fp_w );
void log_transform(FILE *fp_r,FILE* fp_w ){
	int **a, b[10],i,j,k,l,x,c[5],m,n;
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


	for(i=0;i<c[1];i++){
		for(j=0;j<c[0];j++){
			x=log(1+a[i][j]);
			a[i][j]=x;
		}
	}
	m=maxm(a,c[1],c[0]);
	n=minm(a,c[1],c[0]);
	for(i=0;i<c[1];i++){
		for(j=0;j<c[0];j++){
			a[i][j]=(255*a[i][j])/(m-n);
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

int minm(int **a,int row,int col){
	int i,j,min=9999;
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			if(a[i][j]<min)
				min=a[i][j];
		}
	}
	return min;	
}
int maxm(int **a,int row,int col){
	int i,j,max=-9999;
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			if(a[i][j]>max)
				max=a[i][j];
		}
	}
	return max;	
}

void main(){
	FILE *fp_r,*fp_w;
	fp_r=fopen("low_barbara.txt","r");
	fp_w=fopen("low_barbara_edited_log_function.pgm","w");
	log_transform(fp_r,fp_w);
	fclose(fp_r);
	fclose(fp_w);

	
}
