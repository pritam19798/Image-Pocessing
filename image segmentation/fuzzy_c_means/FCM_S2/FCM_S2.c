#include<stdio.h>
#include<math.h>
#include<stdlib.h>
void fuzzy_c_means(double **data,int r,int co,int c,double *centroid,double m);
//int u[10][256];
int main(){
	int i,j,k=3,c[5];			//k is number of clusters,data stores the data points
	double centroid[10]={25,50,100,125,150,175,200,220,230,250};
	double **datap,*data;
	FILE *fp_r,*fp_w;
	fp_r=fopen("cd2.txt","r");
	fp_w=fopen("cd2_FCM_S2_3segments.pgm","w");
	
	for(i=0;i<2;i++){
		fscanf(fp_r,"%d ",&c[i]);
		printf("%d ",c[i]);
	}

	datap=(double**)malloc(sizeof(double*)*(c[1]+2));
	for(i=0;i<(c[1]+2);i++){
		datap[i]=(double*)malloc(sizeof(double)*(c[0]+2));
	}
	
	i=1;j=1;
	while(!feof(fp_r)){
		if(i==(c[0]+1)){
			i=1;j++;
		}
		fscanf(fp_r,"%lf ",&datap[j][i]);
		i++;
	}

	for(i=1;i<=c[0];i++){
		datap[0][i]=datap[2][i];
		datap[(c[1]+1)][i]=datap[(c[1]-1)][i];
	}
	
	for(i=0;i<=c[1]+1;i++){
		datap[i][0]=datap[i][2];
		datap[i][(c[0]+1)]=datap[i][(c[1]-1)];
	}

	fuzzy_c_means(datap,c[1]+2,c[0]+2,k,centroid,2);
	fprintf(fp_w,"P2 %d %d %d\n",c[0],c[1],255);
	for(i=1;i<c[1]+1;i++){
		for(j=1;j<c[0]+1;j++)
		//printf("%d ",(int)data[i]);
		fprintf(fp_w,"%d ",(int)datap[i][j]);
		
	}
	for(i=0;i<k;i++)
		printf("%lf ",centroid[i]);
	fclose(fp_w);
	fclose(fp_r);
	free(datap);
	datap=NULL;

	return 0;
}

void fuzzy_c_means(double **data,int r,int co,int c,double *centroid,double m){
	printf("%d %d",r,co);
	int i,j,k,l,n,o,p,itr=0,optimized,d;
	double s1,s2,s,**mid,**up,**h,mp,tol=0.1,b,new_centroid[10],alpha=2,temp[10];
	up=(double**)malloc(sizeof(double*)*c);
	for(i=0;i<c;i++){
		up[i]=(double*)malloc(sizeof(double)*(r*co));
	}
	mid=(double**)malloc(sizeof(double*)*r);
	for(i=0;i<r;i++){
		mid[i]=(double*)malloc(sizeof(double)*co);
	}

	mp=1/(m-1);
	printf("mp=%lf\n",mp);
	while(1){
	d=0;
	
	for(l=1;l<r-1;l++){
		for(n=1;n<co-1;n++){
			k=0;
			for(o=l-1;o<=l+1;o++){
				for(p=n-1;p<=n+1;p++){
					temp[k++]=data[o][p];
				}
			}
			heapsort(temp,9);
			k=k/2;
			mid[l][n]=temp[k];
		}
	}
	
	k=0;	
	
	
	for(i=0;i<c;i++){
		for(l=1;l<r-1;l++){
			for(n=1;n<co-1;n++){
			k=co*l+n;
			s=0;
			s1=pow((centroid[i]-data[l][n]),2)+alpha*pow((centroid[i]-mid[l][n]),2);
			if(s1==0.00)
				s1=0.01;
			for(j=0;j<c;j++){
				s2=pow((centroid[j]-data[l][n]),2)+alpha*pow((centroid[j]-mid[l][n]),2);
				if(s2==0)
					s2=0.01;
				s+=pow(s1/s2,mp);
				
			}
			b=pow(s,-1);
			//printf("up b[%d][%d]=%lf ",i,k,b);
			//printf("%lf ",m);
			//up[i][k]=pow(b,mp);
			up[i][k]=b;
			//printf("up 1st[%d][%d]=%lf\t",i,k,up[i][k]);
			
		}
	}
	//printf("\n\n");	
	}
	

	
	//printf("\n\n");	
	s=0;
	for(i=0;i<c;i++){
		s1=0;
		s2=0;
		for(j=1;j<r-1;j++){
			for(k=1;k<co-1;k++){
				l=co*j+k;
				s1+=pow(up[i][l],m)*(data[j][k]+alpha*mid[j][k]);
				s2+=pow(up[i][l],m);
				//printf("s1=%lf s2=%lf \n",s1,s2);
			}
		}
		//printf("s1=%lf s2=%lf \n",s1,s2);
		new_centroid[i]=s1/(s2*(1+alpha));
		//printf("%lf/%lf=%lf \n",s1,s2,new_centroid[i]);
		d+=fabs(new_centroid[i]-centroid[i]);
		centroid[i]=new_centroid[i];
		//printf("\n\n");
	}
	printf("itr=%d d=%d optimized a step\n",itr,d);
	itr++;
	if((d<tol)||(itr>3000))
		break;
		
	
	}
	for(i=1;i<r-1;i++){
		for(j=1;j<co-1;j++){
			k=co*i+j;
			k=find(up,k,c);
			data[i][j]=centroid[k];
			//printf("%lf ",data[i]);
		}
	}
	free(mid);
	mid=NULL;
	free(up);
	up=NULL;

}

int find(double **u,int n,int c){
	int i,m;
	m=0;
	for(i=0;i<c;i++){
		//printf("u[m=%d][n=%d]=%lf\tu[i=%d][n=%d]=%lf\n",m,n,u[m][n],i,n,u[i][n]);
		if(u[m][n]<=u[i][n]){
			m=i;
		}
	}
	//printf("\n%d\n",m);
	return m;
}



void heapyfy(double arr[],int n,int i){
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
void maxheap(double arr[],int n){
        int i,t;
        //printf("in heap sort");
        for(i=n/2-1;i>=0;i--)
                heapyfy(arr,n,i);
}
void heapsort(double arr[],int n){
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
