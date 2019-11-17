#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int a[500][500];
int main(){
	int val,i,j,row,col;
	FILE *fp;
	srand(time(0));
	printf("enter row and col");
	scanf("%d,%d",&row,&col);
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			if(i==j)
				a[i][j]=249;
			else
				a[i][j]=250;
		}
	}
	/*	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}*/
	fp=fopen("matrix.txt","w");
	fprintf(fp,"%d %d \n",row,col);
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
