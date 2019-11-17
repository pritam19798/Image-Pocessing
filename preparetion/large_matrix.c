#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int a[600][600];
int main(){
	int val,i,j,row,col;
	FILE *fp;
	//srand(time(0));
	printf("enter row and col");
	scanf("%d,%d",&row,&col);
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			if(i==j)
			{
				a[i][j]=i*j;
			}
			else
			{
			a[i][j]=rand()%256;
            }
		}
	}
	/*	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}*/
	fp=fopen("matrix.pgm","w");
	fprintf(fp,"P2\t%d\t%d\t255\n",col,row);
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			fprintf(fp,"%d ",a[i][j]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	
	//printf("%d ",rand()%10);
	return 0;
}
