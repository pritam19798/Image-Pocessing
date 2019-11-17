#include<stdio.h>
void average(FILE *fp_r,FILE* fp_w );
void average(FILE *fp_r,FILE* fp_w ){
	int a[700][700], b[10],i,j,k,l,x,c[5];
	for(i=0;i<2;i++){
		fscanf(fp_r,"%d ",&c[i]);
	}
	i=0;j=0;
	
	
	while(!feof(fp_r)){
		if(i==c[1]){
			i=0;j++;
		}
		fscanf(fp_r,"%d ",&a[j][i]);
		i++;
	}


	for(i=1;i<c[0]-1;i++){
		for(j=1;j<c[1]-1;j++){
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

	for(i=0;i<c[0];i++){
		for(j=0;j<c[1];j++){
			fprintf(fp_w,"%d ",a[i][j]);
		}
		fprintf(fp_w,"\n");
	}
}



void main(){
	FILE *fp_r,*fp_w;
	fp_r=fopen("matrix.txt","r");
	fp_w=fopen("matrix_edited2_function.txt","w");
	average(fp_r,fp_w);
	fclose(fp_r);
	fclose(fp_w);

	
}
