#include <stdio.h>

int main() 
{
	float a[2][3],b[3][2],c[2][2];
	int i,j,k,arow,acol,brow,bcol,sum=0;
	
	printf("Please rows and columns of Matrix A. It cannot be more than two rows and three columns");
	
	printf("Please enter row\n");
	scanf("%d",&arow);
	printf("Please enter column\n");
	scanf("%d",&acol);
	
	printf("Please rows and columns of Matrix A. It cannot be more than 3 rows and two columns");
	
	printf("Please enter row\n");
	scanf("%d",&brow);
	printf("Please enter column\n");
	scanf("%d",&bcol);
	
	for(i=0;i<arow;i++){
		for(j=0;j<acol;j++) {
			printf("Enter elements a%d%d: ",i+1, j+1);
            scanf("%f", &a[i][j]);	
		}
	}
	
	for(i=0;i<brow;i++){
		for(j=0;j<bcol;j++) {
			printf("Enter elements a%d%d: ",i+1, j+1);
            scanf("%f", &b[i][j]);	
		}
	}
	
	for (i = 0; i < arow; i++) {
      for (j = 0; j < bcol; j++) {
        for (k = 0; k < acol; k++) {
          sum = sum + a[i][k]*b[k][j];
        }
 
        c[i][j] = sum;
        sum = 0;
      }
    }
    
    for (i = 0; i < arow; i++) {
      for (j = 0; j < bcol; j++)
        printf("%f\t", c[i][j]);
 
      printf("\n");
    }
  }
     
	return 0;
}
