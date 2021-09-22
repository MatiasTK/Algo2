#include <stdio.h>
#include "log.h"

int main()
{
	double a,b;
    printf("Ingresa el numero a sacar el log: ");
    scanf("%lf",&a);

    printf("\nIngresa la base del log: ");
    scanf("%lf",&b);

    printf("\nEl resultado es: %lf",log_base(a,b));

    return 0;
}