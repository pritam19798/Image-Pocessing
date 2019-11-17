#include<stdio.h>
void main(){
int i,j,k=200,l=100,a[700][700],x,y;
FILE *fp1= fopen("text1.txt","w");
for(i=0;i<512;i++){
	x=i-255;
	for(j=0;j<512;j++){
		y=j-255;
		if((((x*x)+(y*y)<=(k*k))&&((x*x)+(y*y)>=(l*l)))||(i==j)||(i==512-j)){
			//printf("%d,%d,%d ",i*i,j*j,k*k);
			a[i][j]=100;
		}
		else
		a[i][j]=255;
		fprintf(fp1,"%d ",a[i][j]);
	}
	fprintf(fp1,"\n");
}
	fclose(fp1);
}
