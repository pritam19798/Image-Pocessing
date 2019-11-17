#include<stdio.h>
void heapyfy(int arr[],int n,int i);
void maxheap(int arr[],int n);
void heapsort(int arr[],int n);
void main(){
	int a[500][500],r,c,i=0,j=0,b[5],sum=0,avg,temp[10];
	FILE*fp_r,*fp_w;
	fp_r=fopen("matrix.txt","r");
	fp_w=fopen("matrix_edited2.txt","w");
	
	
	
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
		
		for(j=1;j<b[1]-1;j++){
			temp[0]=a[i][j];
			temp[1]=a[i-1][j];
			temp[2]=a[i+1][j];
			temp[3]=a[i+1][j+1];
			temp[4]=a[i+1][j-1];
			temp[5]=a[i-1][j-1];
			temp[6]=a[i-1][j+1];
			temp[7]=a[i][j+1];
			temp[8]=a[i][j-1];
			heapsort(temp,9);
			a[i][j]=temp[4];
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
void heapyfy(int arr[],int n,int i){
        int larg=i,t;
        int l=2*i+1;int r=2*i+2;
        if(l<n && arr[l]>arr[larg])
                larg=l;
        if(r<n && arr[r]>arr[larg])
                larg=r;
        if(larg!=i){
                t=arr[i];
                arr[i]=arr[larg];
                arr[larg]=t;
                heapyfy(arr,n,larg);
        }
}
void maxheap(int arr[],int n){
        int i,t;
        //printf("in heap sort");
        for(i=n/2-1;i>=0;i--)
                heapyfy(arr,n,i);
}
void heapsort(int arr[],int n){
        int i,t;
        maxheap(arr,n);
        for(i=n-1;i>=0;i--){
                t=arr[0];
                arr[0]=arr[i];
                arr[i]=t;
                n--;
                maxheap(arr,n);
        }
}
