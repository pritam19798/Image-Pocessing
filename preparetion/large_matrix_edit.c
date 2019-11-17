#include<stdio.h>
void main(){
	int a[500][500],r,c,i=0,j=0,b[5],sum=0,avg;
	FILE*fp_r,*fp_w;
	fp_r=fopen("matrix.txt","r");
	fp_w=fopen("matrix_edited.txt","w");
	
	
	
	for(i=0;i<=1;i++)
		fscanf(fp_r,"%d ",&b[i]);
	i=0;
	
	
	while(!feof(fp_r)){
		if(i==b[1]){
			i=0;j++;
		}
		fscanf(fp_r,"%d ",&a[j][i]);
		i++;
	}
	
	
	
	
	
	for(i=0;i<b[0];i++){
		for(j=0;j<b[1];j++){
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	
	
	

	for(i=1;i<b[0]-1;i++){
		sum=0;
		for(j=1;j<b[1]-1;j++){
			sum=0;
			sum=sum+a[i][j]+a[i-1][j]+a[i+1][j]+a[i+1][j+1]+a[i+1][j-1]+a[i-1][j-1]+a[i-1][j+1]+a[i][j+1]+a[i][j-1];
			avg=sum/9;
			a[i][j]=avg;
		}
	}
	
	
	for(i=0;i<b[0];i++){
		for(j=0;j<b[1];j++){
			fprintf(fp_w,"%d ",a[i][j]);
		}
		fprintf(fp_w,"\n");
	}
	fclose(fp_r);
	fclose(fp_w);
}
