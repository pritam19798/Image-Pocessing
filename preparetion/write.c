#include<stdio.h>
void main(){
	/*this code is for write a file */
	int i=0,j=0,n=5,a[10][10];
	FILE *fptr;		//file pointer
	for(i=0;i<n;i++){			//initializing array
		for(j=0;j<n;j++){
			a[i][j]=i*j;
		}
	}
	fptr=fopen("abc.txt","w");		//file oppen
		for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			fprintf(fptr,"%d ",a[i][j]);	//write the array in file
		}
		fprintf(fptr,"\n");
	}
	fclose(fptr);	//close  the file
	
	
}
