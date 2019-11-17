#include<stdio.h>
#include<stdlib.h>
void edgeMap(FILE *fp_r,FILE* fp_w,int gx[3][3],int gy[3][3]);

void edgeMap(FILE *fp_r,FILE* fp_w,int gx[3][3],int gy[3][3]){
	int **a,**temp, b[10],i,j,k,l,x,y,v,c[5];
	for(i=0;i<2;i++){
		fscanf(fp_r,"%d ",&c[i]);
	}
	a=(int**)malloc(sizeof(int*)*c[0]);
	
	for(i=0;i<c[0];i++)
	{	
		a[i]=(int*)malloc(sizeof(int)*c[1]);
		
	}
	temp=(int**)malloc(sizeof(int*)*c[0]);
	
	for(i=0;i<c[0];i++)
	{	
		temp[i]=(int*)malloc(sizeof(int)*c[1]);
		
	}
	for(i=0;i<c[0];i++){
		for(j=0;j<c[1];j++){
			temp[i][j]=0;
		}
	}
	i=0;j=0;
	
	
	while(!feof(fp_r)){
		if(i==c[1]){
			i=0;j++;
		}
		fscanf(fp_r,"%d ",&a[j][i]);
		i++;
	}
	
	for(i=0;i<c[0]-2;i++){
		for(j=0;j<c[1]-2;j++){
			x=0;
			v=0;
			y=0;
			for(k=0;k<3;k++){
				for(l=0;l<3;l++){
					x=x+gx[k][l]*a[i+k][j+l];
					y=y+gy[k][l]*a[i+k][j+l];
					v=abs(x)+abs(y);
				}
			}
			if(v>255)
				v=255;
			if(v<0)
				v=0;
			temp[i+1][j+1]=v;
		}
	}

	fprintf(fp_w,"P2 %d %d %d\n",c[0],c[1],255);
	for(i=0;i<c[0];i++){
		for(j=0;j<c[1];j++){
			fprintf(fp_w,"%d ",temp[i][j]);
		}
		fprintf(fp_w,"\n");
	}
	free(a);
	a=NULL;
	free(temp);
	temp=NULL;
}

void main(){
	FILE *fp_r,*fp_w;
	int edge[3][3]={{-1,0,1},
					{-2,0,2},
					{-1,0,1}};
	int edge2[3][3]={{-1,-2,-1},
					{-0,0,0},
					{1,2,1}};
					
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			printf("%d ",edge2[i][j]);
		}
		printf("\n");
	}
	fp_r=fopen("matrix.txt","r");
	fp_w=fopen("lena_edge11.txt","w");
	printf("all files opend");
	edgeMap(fp_r, fp_w, edge,edge2 );
	fclose(fp_r);
	fclose(fp_w);
}
