#include<stdio.h>
#include<time.h>


void heapyfy(int arr[],int n,int i);
void maxheap(int arr[],int n);
void heapsort(int arr[],int n);


void median(FILE *fp_r,FILE* fp_w ){
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
					b[x]=a[k][l];
					x++;
				}
			}
			heapsort(b,9);
			a[i][j]=b[4];
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
	fp_r=fopen("text1.txt","r");
	fp_w=fopen("text1_edited_median_function.txt","w");
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
