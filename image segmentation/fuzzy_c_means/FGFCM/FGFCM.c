#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define MAX(a,b) (a>b?a:b)
void fuzzy_c_means(double **data,int r,int co,int c,double *centroid,double m,double **ndata);
//int up[10][256];
int main(){
	int i,j,k=3,c[5];			//k is number of clusters,data stores the data points
	double centroid[10]={25,50,100,125,150,175,200,220,230,250};
	double **datap,*data,**ndata;
	FILE *fp_r,*fp_w;
	fp_r=fopen("cd2.txt","r");
	fp_w=fopen("cd2_FGFCM_3segments.pgm","w");
	
	for(i=0;i<2;i++){
		fscanf(fp_r,"%d ",&c[i]);
		printf("%d ",c[i]);
	}

	datap=(double**)malloc(sizeof(double*)*(c[1]+2));
	ndata=(double**)malloc(sizeof(double*)*(c[1]+2));
	for(i=0;i<(c[1]+2);i++){
		datap[i]=(double*)malloc(sizeof(double)*(c[0]+2));
		ndata[i]=(double*)malloc(sizeof(double)*(c[0]+2));
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

	fuzzy_c_means(datap,c[1]+2,c[0]+2,k,centroid,2,ndata);
	fprintf(fp_w,"P2 %d %d %d\n",c[0],c[1],255);
	for(i=1;i<c[1]+1;i++){
		for(j=1;j<c[0]+1;j++)
		//printf("%d ",(int)data[i]);
		fprintf(fp_w,"%d ",(int)ndata[i][j]);
		
	}
	for(i=0;i<k;i++)
		printf("%lf ",centroid[i]);
	fclose(fp_w);
	fclose(fp_r);
	free(datap);
	datap=NULL;

	return 0;
}

void fuzzy_c_means(double **data,int r,int co,int c,double *centroid,double m,double **ndata){
	printf("%d %d",r,co);
	int i,j,k,l,n,o,p,itr=0,optimized,d,h[256];
	double s1,s2,s,**avg,**up,**ss,**sg,**sf,mp,tol=0.1,b,new_centroid[10],alpha=2,lamdas=2,lamdag=6.5,*sigmag;
	up=(double**)malloc(sizeof(double*)*c);
	for(i=0;i<c;i++){
		up[i]=(double*)malloc(sizeof(double)*(r*co));
	}
	avg=(double**)malloc(sizeof(double*)*r);
	for(i=0;i<r;i++){
		avg[i]=(double*)malloc(sizeof(double)*co);
	}
	
	ss=(double**)malloc(sizeof(double*)*(r*co));
	sg=(double**)malloc(sizeof(double*)*(r*co));
	sf=(double**)malloc(sizeof(double*)*(r*co));
	for(i=0;i<(r*co);i++){
		ss[i]=(double*)malloc(sizeof(double)*9);
		sg[i]=(double*)malloc(sizeof(double)*9);
		sf[i]=(double*)malloc(sizeof(double)*9);
	}
	sigmag=(double*)malloc(sizeof(double)*(r*co));
	
	
	for(l=1;l<r-1;l++){
		for(n=1;n<co-1;n++){
			s=0;
			for(o=l-1;o<=l+1;o++){
				for(p=n-1;p<=n+1;p++){
					s+=data[o][p];
				}
			}
			avg[l][n]=s/9;
		}
	}
	
	
	for(i=1;i<r-1;i++){
		for(j=1;j<co-1;j++){
			k=co*i+j;
			l=0;
			for(o=i-1;o<=i+1;o++){
				for(n=j-1;n<=j+1;n++){
					//printf("k=%d l=%d ",k,l);
					ss[k][l]=exp(-MAX(fabs(i-o),fabs(j-n))/lamdas);
					//printf("ss[%d][%d]=%lf ",k,l,ss[k][l]);
					l++;
				}
			}
			//printf("\n\n");
		}
	}
	
	
	for(i=1;i<r-1;i++){
		for(j=1;j<co-1;j++){
			k=co*i+j;
			s=0;
			for(o=i-1;o<=i+1;o++){
				for(n=j-1;n<=j+1;n++){
					s+=pow((data[o][n]-data[i][j]),2);
				}
			}
			sigmag[k]=pow(s/((r-2)*(co-2)),1);
			if(sigmag[k]==0)
				sigmag[k]=0.1;
			//printf("sigmag[%d]=%lf  ",k,sigmag[k]);
		}
	}
	
	
	for(i=1;i<r-1;i++){
		for(j=1;j<co-1;j++){
			k=co*i+j;
			l=0;
			for(o=i-1;o<=i+1;o++){
				for(n=j-1;n<=j+1;n++){
					//printf("k=%d l=%d ",k,l);
					sg[k][l]=exp(-pow((data[i][j]-data[o][n]),2)/(lamdag*sigmag[k]));
					//printf("sg[%d][%d]=%lf ",k,l,sg[k][l]);
					l++;
				}
			}
			//printf("\n\n");
		}
	}
	
	
	for(i=1;i<r-1;i++){
		for(j=1;j<co-1;j++){
			k=co*i+j;
			l=0;
			for(o=i-1;o<=i+1;o++){
				for(n=j-1;n<=j+1;n++){
					if(l==4)
						sf[k][l]=0;
					else
						sf[k][l]=ss[k][l]*sg[k][l];
					//printf("sf[%d][%d]=%lf ",k,l,sf[k][l]);
					l++;
				}
			}
			//printf("\n\n");
		}
	}
	
	printf("ok");
	
	//new image 
	for(i=1;i<r-1;i++){
		for(j=1;j<co-1;j++){
			k=co*i+j;
			l=0;
			s1=0;s2=0;
			for(o=i-1;o<=i+1;o++){
				for(n=j-1;n<=j+1;n++){
					s1+=sf[k][l]*data[o][n];
					s2+=sf[k][l];
					//printf("s2=%lf ",s2);
					l++;
				}
			}
			if(s2==0){
				s2=0.01;
			}
			ndata[i][j]=s1/s2;
			//printf("ndata[%d][%d]=%lf final s2=%lf",i,j,ndata[i][j],s2);
		}
		//printf("\n\n");
	}
	
	//histogram
	for(i=0;i<255;i++)
		h[i]=0;
	for(i=1;i<r-1;i++){
		for(j=1;j<co-1;j++){
			k=(int)ndata[i][j];
			h[k]+=1;
		}
	}
	k=0;
	
	
	
	mp=1/(m-1);
	printf("mp=%lf\n",mp);
	while(1){
	d=0;	
	for(i=0;i<c;i++){
		for(l=1;l<r-1;l++){
			for(n=1;n<co-1;n++){
			k=co*l+n;
			s=0;
			s1=fabs((centroid[i]-ndata[l][n]));
			if(s1==0.00)
				s1=0.01;
			for(j=0;j<c;j++){
				s2=fabs((centroid[j]-ndata[l][n]));
				if(s2==0)
					s2=0.01;
				s+=pow((s1*s1)/(s2*s2),mp);
				
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
				p=(int)ndata[j][k];
				s1+=h[p]*pow(up[i][l],m)*ndata[j][k];
				s2+=h[p]*pow(up[i][l],m);
				//printf("s1=%lf s2=%lf \n",s1,s2);
			}
		}
		//printf("s1=%lf s2=%lf \n",s1,s2);
		new_centroid[i]=s1/s2;
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
			ndata[i][j]=centroid[k];
			//printf("%lf ",ndata[i]);
		}
	}
	free(avg);
	avg=NULL;
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
