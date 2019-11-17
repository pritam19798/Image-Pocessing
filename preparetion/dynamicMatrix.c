#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void main(){
	int **ptr;
	int i,j;
	srand(time(0));
	
	ptr=(int**)malloc(sizeof(int*)*5);
	
	for(i=0;i<5;i++)
	{	
		ptr[i]=(int*)malloc(sizeof(int)*5);
		
	}
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			ptr[i][j]=rand()%100;
		}
	}
		for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			printf("%d ",ptr[i][j]);
		}
		printf("\n");
	}
}
