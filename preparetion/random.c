#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int a[500];
int main(){
	int val,r;
	srand(time(0));
	for(r=0;r<=5;r++){
		do{
			val=rand()%10;
			
		}while(a[val]==2);
	a[val]=2;
	printf("%d ",val);
			
	}

	//printf("%d ",rand()%10);
	return 0;
}
