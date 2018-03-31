#include <stdio.h>
#include <string.h>

int main()
{
	char string[30],temp;
	int i;
	
	printf("Enter string to sort: ");
	scanf("%s",&string);
	
	for(i=0; i < strlen(string); i++) {
		if(string[i] > string[i+1]) {
			temp = string[i];	
			string[i] = string[i+1];
			string[i+1] = temp;
		} 
	}
		
	printf("\n%s\n", string);
	return 0;	
}
