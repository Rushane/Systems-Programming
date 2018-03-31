#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
   char program[80],*args[3];
   int i;
   
   printf("Ready to exec\n");
   strcpy(program,"ls");
   args[0]="ls";
   args[1]="-l";
   args[2]=NULL;
   i = execvp(program,args);
   printf("%d",i);

   return 0;
}
