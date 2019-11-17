#include<stdio.h>
#include<stdlib.h>


void heapyfy(int arr[],int n,int i);
void maxheap(int arr[],int n);
void heapsort(int arr[],int n);


void median(FILE *fp_r,FILE* fp_w ){
	int **a, b[100],i,j,k,l,x,c[5];
	for(i=0;i<2;i++){
		fscanf(fp_r,"%d ",&c[i]);
	}
	a=(int**)malloc(sizeof(int*)*c[1]);
	
	for(i=0;i<c[1];i++)
	{	
		a[i]=(int*)malloc(sizeof(int)*c[0]);
		
	}
	i=0;j=0;
	
	
	while(!feof(fp_r)){
		if(i==c[0]){
			i=0;j++;
		}
		fscanf(fp_r,"%d ",&a[j][i]);
		i++;
	}


	for(i=1;i<c[1]-1;i++){
		for(j=1;j<c[0]-1;j++){
			x=0;
			for(k=i-1;k<=i+1;k++){
				for(l=j-1;l<=j+1;l++){
					b[x]=a[k][l];
					x++;
				}
			}
			heapsort(b,9);
			a[i][j]=b[4];
		}
	}
	fprintf(fp_w,"P2 %d %d %d\n",c[0],c[1],255);
	for(i=0;i<c[1];i++){
		for(j=0;j<c[0];j++){
			fprintf(fp_w,"%d ",a[i][j]);
		}
		fprintf(fp_w,"\n");
	}
	free(a);
	a=NULL;
}



void main(){
	FILE *fp_r,*fp_w;
	fp_r=fopen("lena.txt","r");
	fp_w=fopen("lena_edited_median_function.pgm","w");
	median(fp_r,fp_w);
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
