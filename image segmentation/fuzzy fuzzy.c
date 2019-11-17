#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int avg(int *a,int n);
void fuzzy_c_means(int *data,int n,int k,int *centroid,int m);
//int set[10][256];
int main(){
	int i,j,k,c=3,data[20]={70,20,1,56,10,15,100,200,4,29,86,72,98},d,n=13;		
	int centroid[10]={4,35,90},new_centroid[10],itr=0;
	double s1,s2,s,set[10][10],m=1.8,mp;
	mp=1/(m-1);
	while(1){
	d=0;
	for(i=0;i<c;i++){
		for(k=0;k<n;k++){
			s=0;
			s1=(double)fabs((centroid[i]-data[k]));
			for(j=0;j<c;j++){
				s2=(double)fabs((centroid[j]-data[k]));
				if(s2!=0)
					s+=(s1*s1)/(s2*s2);
				else
					s=pow(set[i][k],-1);
				
			}
			s=pow(s,-1);
			//printf("%lf ",m);
			set[i][k]=pow(s,mp);
			printf("%lf\t",set[i][k]);
		}
		printf("\n\n");
	}

	s=0;
	for(i=0;i<c;i++){
		s1=0;
		s2=0;
		for(j=0;j<n;j++){
			//printf("set[%d][%d]=%lf   ",i,j,set[i][j]);
			s1+=pow(set[i][j],m)*data[j];
			s2+=pow(set[i][j],m);
			//printf("s1=%lf  s2=%lf \n",s1,s2);
		}
		new_centroid[i]=s1/s2;
		printf("%lf/%lf=%d ",s1,s2,new_centroid[i]);
		d+=fabs(new_centroid[i]-centroid[i]);
		centroid[i]=new_centroid[i];
	}
	printf("\n\n\n");
	itr++;
	if((d<0.01)||(itr>4))
		break;
		}

	


	return 0;
}



