#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
   char controle[5] = "1 2";
   int x = atoi(controle);
   printf("%d\n", x);
   char* aux = strstr(controle, " ");
   x = atoi(aux);
   printf("%d\n", x);

   return 0;
}