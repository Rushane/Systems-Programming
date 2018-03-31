#include <stdio.h>

int main()
{
   int a[30][30],b[30][30],sum[30][30];
   int i,j,arow,acol,brow,bcol;
   
   printf("Please rows and columns of Matrix A.\n");
	
   printf("Please enter row\n");
   scanf("%d",&arow);
   printf("Please enter column\n");
   scanf("%d",&acol);
   
   printf("Please rows and columns of Matrix B.\n");
	
   printf("Please enter row\n");
   scanf("%d",&brow);
   printf("Please enter column\n");
   scanf("%d",&bcol);
   
   for(i=0;i<arow;i++){
		for(j=0;j<acol;j++) {
			printf("Enter elements a%d%d: ",i+1, j+1);
            scanf("%d", &a[i][j]);	
		}
	}
	
	for(i=0;i<arow;i++){
		for(j=0;j<acol;j++) {
			printf("Enter elements b%d%d: ",i+1, j+1);
            scanf("%d", &b[i][j]);	
		}
	}
	
	for (i = 0; i < arow; i++) {
      for (j = 0; j < bcol; j++) {
          sum[i][j] = a[i][j] + b[i][j];
        }
    }
    
    for (i = 0; i < arow; i++) {
      for (j = 0; j < bcol; j++)
        printf("%d\t", sum[i][j]);
 
      printf("\n");
    }
   
   
   return 0;
}
