#include<stdio.h>
void heapyfy(int arr[],int n,int i);
void maxheap(int arr[],int n);
void heapsort(int arr[],int n);
int main(){
	FILE *fptr,*fp;
	char ch;
	int ih,i=0,a[100],n;
	fptr=fopen("abc.txt","r");	//file open
	while(!feof(fptr)){
	/*while the end of file will not occer,the loop will continue*/
	fscanf(fptr,"%d ",&ih);		//read file and store each charecter as an integer
	//printf("file pointer is at: %ld ",ftell(fptr));
	//printf("%d ",ih);
	a[i]=ih;		//storing the integers in 1d array
	i++;	//to count the total elements
}
	
	//fclose(fp);
	fclose(fptr);	//close the file
	printf("\n");
	heapsort(a,i);
	for(n=0;n<i;n++)
		printf("%d ",a[n]);
	if((i%2))
		printf("\nmiddle element is %dth element and element is: %d ",i/2+1,a[i/2+1]);	
	else
		printf("\nmiddle element is %dth possition and element is: %d ",i/2,a[i/2]);
	
	return 0;
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
