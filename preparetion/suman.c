#include<stdio.h>
#include<stdlib.h.>
int main()
{
    FILE *fp1,*fp2;
    int i,j,k,l,m,n,x,temp;
    int a[600][600],c[10],d[20];
    fp1=fopen("matrix.txt","r");
    fp2=fopen("b.pgm","w");
    for(i=0;i<2;i++)
    {
        if(fscanf(fp1,"%d ",&x)!=EOF);
        {
            c[i]=x;
            //printf("%d ",x);
        }
    }
    for(i=1;i<=c[0];i++)
    {
        for(j=1;j<=c[1];j++)
        {
             if(fscanf(fp1,"%d ",&x)!=EOF);
                         a[i][j]=x;
        }
    }
    /*for(i=1;i<=c[0];i++){
    	for(j=1;j<=c[0];j++){
    		printf("%d ",a[i][j]);
		}
		printf("\n");
	}*/
    fprintf(fp2,"P2\t%d\t%d\t255\n",c[0],c[0]);
    for(i=2;i<c[0];i++)
     {
        for(j=2;j<c[1];j++)
         {
            x=1;
            for(k=i-1;k<=i+1;k++)
             {
                for(l=j-1;l<=j+1;l++)
                 {
                    d[x]=a[k][l];
                    printf("%d ",d[x]);
                    x=x+1;
                 }
             }
			 printf("\n");x=x-1;

            for(m=1;m<x;m++)
            {
                for(n=1;n<x-m;n++)
                 {
                  if(d[n]>d[n+1])
                     {
                       temp=d[n];
                       d[n]=d[n+1];
                       d[n+1]=temp;
                     }
                 }
             }
             
            
             a[i][j]=d[x/2+1];
         }
     }
    for(i=1;i<=c[0];i++)
        {
            for(j=1;j<=c[0];j++)
                {
                    fprintf(fp2,"%d\t",a[i][j]);
                }
    fprintf(fp2,"\n");
        }
    fclose(fp1);
    fclose(fp2);
}
