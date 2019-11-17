#include<stdio.h>
#include<math.h>
#include<time.h>

int rand(void);
void srand(unsigned);
double pow(double, double);

void fillRandom(int[10][10]);
void displayMatrix(int[10][10]);
int valueOf(int[10]);
void geneticAlgorithm(int[10][10], int, int);
void swap(int*, int*);
void cross(int[10],int[10]);
void mutate(int[10],int);

int main()
{
	int mat[10][10], iterations;

	printf("Enter the number of iterations >> ");
	scanf("%d", &iterations);

	srand(time(NULL));

	fillRandom(mat);
	printf("The Generated Matrix:-\n\n");
	displayMatrix(mat);

	geneticAlgorithm(mat, 1, iterations); 
}

void fillRandom(int mat[10][10])
{
	int i,j;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			mat[i][j]=rand()%2;
		}
	}
}
int valueOf(int a[10])
{
	int i, val = 0;
	for(i=0;i<10;i++)
	{
		val += a[i] * pow(2, 9-i);
	}

	return val;
}

void displayMatrix(int mat[10][10])
{
	int i,j;

	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			printf("%d ",mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


void geneticAlgorithm(int mat[10][10], int generation, int iterations)
{
	int i, j, v, flag, fitIndices[10], fitCount = 0, r;
	if(generation > iterations)
	{
		printf("%d iterations are over, this is the final matrix", iterations);
		return;
	}

	printf("\nCurrent generation -> %d\n\n", generation);

	for(i=0;i<10;i++)
	{
		v = valueOf(mat[i]);
		printf("The decimal value of row %d -> %d", i, v);
		if(valueOf(mat[i])<512)
		{
			for(j=0;j<10;j++)
			{
				mat[i][j] = 0;
			}
		}
		else
		{
			fitIndices[fitCount++] = i;
		}
		printf("\n");
	}

	if(fitCount != 10)
		printf("\nUnfit rows deleted:-\n\n");
	else
		printf("\nNo unfit rows in this generation\n\n");

	displayMatrix(mat);
	if(fitCount == 0) 
	{
		printf("\nNo one in this generation is fit... Generating random data for next generation\n");
		fillRandom(mat);
		geneticAlgorithm(mat, generation+1, iterations);
	}
	else
	{
		for(i=0;i<10;i++)
		{
			if(valueOf(mat[i]) == 0) 
			{
				r = fitIndices[rand()%fitCount];
				for(j=0;j<10;j++)
				{
					mat[i][j] = mat[r][j];
				}
				mutate(mat[i], 1);
			}
		}
		cross(mat[fitIndices[rand()%fitCount]], mat[fitIndices[rand()%fitCount]]);

		geneticAlgorithm(mat, generation+1, iterations);
	}
}
void cross(int a[10], int b[10])
{
	int r = rand() % 10,i;

	for(i=0;i<=r;i++)
	{
		swap(&a[i], &b[i]);
	}
}
void mutate(int a[10], int mutationRate)
{
	int i,r;
	for(i=0;i<10;i++)
	{
		r = rand() % 101; 
		if(r <= mutationRate)
		{
			a[i] = rand() % 2; 
		}
	}
}
void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}