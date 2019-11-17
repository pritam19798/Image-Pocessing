#include<stdio.h>
#include<stdlib.h>
#include<math.h>
void histmatch(FILE *fp_r,FILE *fp_t,FILE* fp_w );

void histeq(FILE *fp_r,FILE *fp_t,FILE* fp_w ){
	int **ar,**at, b[5],i,j,k,l,x,c[5],m,n;
	float *temp_r,*temp_t,*res,sum;
	
	//loding refrence image
	for(i=0;i<2;i++){
		fscanf(fp_r,"%d ",&c[i]);
	}
	
	ar=(int**)malloc(sizeof(int*)*c[1]);
	for(i=0;i<c[1];i++)
	{	
		ar[i]=(int*)malloc(sizeof(int)*c[0]);
		
	}
	
	temp_r=(float*)malloc(sizeof(float)*255);
	for(i=0;i<256;i++){
		temp_r[i]=0;
	}
	
	i=0;j=0;
	while(!feof(fp_r)){
		if(i==c[0]){
			i=0;j++;
		}
		fscanf(fp_r,"%d ",&ar[j][i]);
		i++;
	}
	//printf("refrenc image loded");
	
	//taking the histogram of ref
	for(i=0;i<c[1];i++){
		for(j=0;j<c[0];j++){
			x=ar[i][j];
			temp_r[x]=temp_r[x]+1;
		}	
	}	
	//calculate pdf of ref
	for(i=0;i<256;i++){
		temp_r[i]=temp_r[i]/(c[0]*c[1]);
	}
	//calculate cdf and equilized histogram of ref
	sum=0; 
	for(i=0;i<256;i++){
		sum=temp_r[i]+sum;
		temp_r[i]=sum;
		//temp_r[i]=temp_r[i]*255;
	}
	//printf("ref histogram equilized");
	
	//loding target image
	for(i=0;i<2;i++){
		fscanf(fp_t,"%d ",&b[i]);
	}
	
	at=(int**)malloc(sizeof(int*)*b[1]);
	for(i=0;i<b[1];i++)
	{	
		at[i]=(int*)malloc(sizeof(int)*b[0]);
		
	}
	temp_t=(float*)malloc(sizeof(float)*255);
	for(i=0;i<256;i++){
		temp_t[i]=0;
	}
	
	i=0;j=0;
	while(!feof(fp_t)){
		if(i==b[0]){
			i=0;j++;
		}
		fscanf(fp_t,"%d ",&at[j][i]);
		i++;
	}
	//printf("target image loded");
	
	
	//taking the histogram of target
	for(i=0;i<b[1];i++){
		for(j=0;j<b[0];j++){
			x=at[i][j];
			temp_t[x]=temp_t[x]+1;
		}	
	}	
	//calculate pdf of target
	for(i=0;i<256;i++){
		temp_t[i]=temp_t[i]/(b[0]*b[1]);
	}
	//calculate cdf and equilized histogram of target
	sum=0; 
	for(i=0;i<256;i++){
		sum=temp_t[i]+sum;
		temp_t[i]=sum;
		//temp_t[i]=temp_t[i]*255;
	}
	for(i=0;i<256;i++)
		printf("i(%d)=%f,%f ",i,(temp_r[i]),(temp_t[i]));
	printf("\n\n");
	
	
	res=(float*)malloc(sizeof(float)*255);
	for(i=0;i<256;i++){
		res[i]=0;
	}
	
	
	for(i=0;i<256;i++){
		j=255;
		while(1){
			res[i]=j;
			j=j-1;
			if((temp_r[j]<temp_t[i])||(j<0)){
				break;
			}
		}
	}
	for(i=0;i<256;i++)
		printf("i(%d)=%f ",i,res[i]);
	
	for(i=0;i<b[1];i++){
		for(j=0;j<b[0];j++){
			x=at[i][j];
			at[i][j]=round(res[x]);
		}
	}

	//output
	fprintf(fp_w,"P2 %d %d %d\n",b[0],b[1],255);
	for(i=0;i<b[1];i++){
		for(j=0;j<b[0];j++){
			fprintf(fp_w,"%d ",at[i][j]);
		}
		fprintf(fp_w,"\n");
	}
	free(ar);
	free(temp_r);
	temp_r=NULL;
	ar=NULL;
	free(at);
	free(temp_t);
	temp_t=NULL;
	at=NULL;
}




void main(){
	FILE *fp_r,*fp_t,*fp_w;
	fp_r=fopen("barbara.txt","r");
	fp_t=fopen("low_lena.txt","r");
	fp_w=fopen("low_lena_edited_histmatch_function1.pgm","w");
	histeq(fp_r,fp_t,fp_w);
	fclose(fp_r);
	fclose(fp_t);
	fclose(fp_w);

	
}
