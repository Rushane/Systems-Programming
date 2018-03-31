#include <stdio.h>
#include <string.h>



struct phoneBook
{
	char name[30];
	char address[30];
	int telephone;
};

void printBooks(struct phoneBook *book) ;
int main()
{
	struct phoneBook book1;
	
	strcpy(book1.name,"Yellow Pages");
	strcpy(book1.address,"52 Crescent Road");
	book1.telephone = 1234567;
	
	printBooks(&book1);
	
	return 0;	
}

void printBooks(struct phoneBook *book) 
{
	printf("Phone Book name: %s\n",book->name);
	printf("Phone Book address: %s\n",book->address);
	printf("Phone Book telephone: %d\n",book->telephone);
	
	
}
