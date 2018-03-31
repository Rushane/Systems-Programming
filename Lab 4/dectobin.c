#include <stdio.h>

int main()
{
	int decimal,binary,i=0,j,array[100];
	
	printf("Enter decimal to convert to binary: ");
	scanf("%d",&decimal);

    while(decimal>0)
    {
    	array[i] = decimal % 2;
    	decimal = decimal/2;
    	i++;
    }
    
    for(i=i-1;i>=0;i--) {
       printf("%d\n",array[i]);
    }
    		
	return 0;
}
