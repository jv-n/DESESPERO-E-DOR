#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
   int a;
   float b;
} teste;
int main()
{
   char controle[100] = "10 12";

   char* aux = strstr(controle, " ");
   printf("%d\n", atoi(aux));

   return 0;
}