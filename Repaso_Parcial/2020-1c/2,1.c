a = 2 b = 2 f(n) -> O(n)

for (int x = 0; x < n; x++) -> Itera n
    for (int y = 0; y < n; y++) -> Itera n
        for (int z = 0; z < n; z++) -> Itera n
            if (3*x + 9*y + 8*z == 79) -> O(1) -> peor de los casos
                printf("%i, %i, %i son solución de la ecuación", x, y, z); -> O(1)

O(n^3)

Si if fuera 
if(a%2==0){
    printf("%i es par", a); //O(1)
}else{
    printf("El primer mas cercano es %i", buscar_primo_mas_cercano(a)); // O(algo>1)
}

El peor de los casos seria O(algo)
