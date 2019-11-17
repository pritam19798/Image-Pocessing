#include<stdio.h>
#include<stdlib.h>
void heapyfy(int arr[],int n,int i);
void maxheap(int arr[],int n);
void heapsort(int arr[],int n);

void median_replacement(FILE *fp_r,FILE* fp_w,int intensity ){
	int a[700][700], b[10],i,j,k,l,x,c[5];
	for(i=0;i<2;i++){
		fscanf(fp_r,"%d ",&c[i]);
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
	
	fprintf(fp_w,"P2 %d %d %d\n",c[0],c[1],intensity);

	for(i=0;i<c[1];i++){
		for(j=0;j<c[0];j++){
			fprintf(fp_w,"%d ",a[i][j]);
		}
		fprintf(fp_w,"\n");
	}
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


void average_replacement(FILE *fp_r,FILE* fp_w,int intensity ){
	int a[700][700], b[10],i,j,k,l,x,c[5];
	for(i=0;i<2;i++){
		fscanf(fp_r,"%d ",&c[i]);
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
					x=x+a[k][l];
				}
			}
			x=x/9;
			a[i][j]=x;
		}
	}
	
	fprintf(fp_w,"P2 %d %d %d\n",c[0],c[1],intensity);

	for(i=0;i<c[1];i++){
		for(j=0;j<c[0];j++){
			fprintf(fp_w,"%d ",a[i][j]);
		}
		fprintf(fp_w,"\n");
	}
}




void edgeMap(FILE *fp_r,FILE* fp_w,int edge[3][3],int intensity){
	int **a,**temp, b[10],i,j,k,l,x,c[5];
	for(i=0;i<2;i++){
		fscanf(fp_r,"%d ",&c[i]);
	}
	a=(int**)malloc(sizeof(int*)*c[1]);
	
	for(i=0;i<c[1];i++)
	{	
		a[i]=(int*)malloc(sizeof(int)*c[0]);
		
	}
	temp=(int**)malloc(sizeof(int*)*c[1]);
	
	for(i=0;i<c[1];i++)
	{	
		temp[i]=(int*)malloc(sizeof(int)*c[0]);
		
	}
	for(i=0;i<c[1];i++){
		for(j=0;j<c[0];j++){
			temp[i][j]=0;
		}
	}
	i=0;j=0;
	
	
	while(!feof(fp_r)){
		if(i==c[0]){
			i=0;j++;
		}
		fscanf(fp_r,"%d ",&a[j][i]);
		i++;
	}
	
	for(i=0;i<c[1]-2;i++){
		for(j=0;j<c[0]-2;j++){
			x=0;
			for(k=0;k<3;k++){
				for(l=0;l<3;l++){
					x=x+edge[k][l]*a[i+k][j+l];
				}
			}
			if(x>255)
				x=255;
			if(x<0)
				x=0;
			temp[i+1][j+1]=x;
		}
	}
	
	fprintf(fp_w,"P2 %d %d %d\n",c[0],c[1],intensity);
	
	for(i=0;i<c[1];i++){
		for(j=0;j<c[0];j++){
			fprintf(fp_w,"%d ",temp[i][j]);
		}
		fprintf(fp_w,"\n");
	}
	free(a);
	a=NULL;
	free(temp);
	temp=NULL;
}




