#include<stdio.h>
#include<stdlib.h>
#include<math.h>
void histeq(FILE *fp_r,FILE* fp_w );

void histeq(FILE *fp_r,FILE* fp_w ){
	int **a, b[10],i,j,k,l,x,c[5],m,n;
	float *temp,sum;
	for(i=0;i<2;i++){
		fscanf(fp_r,"%d ",&c[i]);
	}
	a=(int**)malloc(sizeof(int*)*c[1]);
	
	for(i=0;i<c[1];i++)
	{	
		a[i]=(int*)malloc(sizeof(int)*c[0]);
		
	}
	temp=(float*)malloc(sizeof(float)*255);
	for(i=0;i<256;i++){
		temp[i]=0;
	}
	i=0;j=0;
	
	
	while(!feof(fp_r)){
		if(i==c[0]){
			i=0;j++;
		}
		fscanf(fp_r,"%d ",&a[j][i]);
		i++;
	}

//taking the histogram
	for(i=0;i<c[1];i++){
		for(j=0;j<c[0];j++){
			x=a[i][j];
			temp[x]=temp[x]+1;
		}
		
	}
	
	//calculate pdf 
	for(i=0;i<256;i++){
		temp[i]=temp[i]/(c[0]*c[1]);
	}
	
	//calculate cdf and out hist
	sum=0; 
	for(i=0;i<256;i++){
		sum=temp[i]+sum;
		temp[i]=sum;
		temp[i]=temp[i]*255;
	}
	
	for(i=0;i<c[1];i++){
		for(j=0;j<c[0];j++){
			x=a[i][j];
			a[i][j]=round(temp[x]);
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
	free(temp);
	temp=NULL;
	a=NULL;
}




void main(){
	FILE *fp_r,*fp_w;
	fp_r=fopen("satellite.txt","r");
	fp_w=fopen("satellite_edited_histeq_function.pgm","w");
	histeq(fp_r,fp_w);
	fclose(fp_r);
	fclose(fp_w);

	
}
