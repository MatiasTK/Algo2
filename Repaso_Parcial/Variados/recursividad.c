
/*Dado el tda pila_t y sus operaciones definidas: pila_crear, pila_tope, pila_apilar, pila_desapilar, pila_cantidad, pila_destruir, y sin
usar while / for / do:
a. Complete la función uno_y_uno que reciba una pila y muestre por pantalla los elementos de la pila de forma alternada
empezando por el elemento tope y luego el del fondo hasta vaciar la pila.
void uno_y_uno(pila_t* pila);
Por ejemplo, si se insertan en la pila los valores [7,6,5,4,3,2,1] (1 es el ultimo elemento insertado), el resultado esperado es:
1,7,2,6,3,5,4.
Puede asumir que las primitivas de pila no fallan nunca y no deben ser verificadas.*/

void pasar_a_vector(pila_t* pila, int* cantidad, int vector[], int tamanio_pila){
	if(cantidad == tamanio_pila) return;

	vector[cantidad] = pila_desapilar(pila);
	(*cantidad)++;
	
	pasar_a_vector(pila, cantidad, vector, tamanio_pila);
}

void imprimir_alternado(int vector[], int cantidad, int inicio){
	if(inicio >= cantidad)	return;

	printf("%i,", vector[inicio]);
	printf("%i,", vector[cantidad]);
	imprimir_alternado(vector, cantidad-1, inicio+1);
}

void uno_y_uno(pila_t* pila){
	int cantidad = 0;
	int vector[pila_cantidad(pila)];
	pasar_a_vector(pila, &cantidad, vector, pila_cantidad(pila));
	imprimir_alternado(vector, cantidad, 0);
}


/*Calcular la altura del abb hasta la hojas mas alejada.*/
typedef struct nodo{
	int fe;
	struct nodo* izquierda;
	struct nodo* derecha;
}nodo_t;


int max(int iz, int der){
	if(iz >= derecha)
		return iz;
	
	return der;
}

int calcular_altura(nodo_t* raiz){
	if(!raiz) return 0;
	return 1+max(calcular_altura(raiz->izquierda), calcular_altura(raiz->derecha));
}

/*Llenar el fe de cada nodo del arbol.*/
void calcular_factor_equilibrio(nodo_t* raiz){
	if(!raiz) return;
	
	raiz->fe = calcular_altura(raiz->izquierda) - calcular_altura(raiz->derecha);
	calcular_factor_equilibrio(raiz->derecha);
	calcular_factor_equilibrio(raiz->izquierda);
}

/*Contar la cantidad de nodos hoja de la estructura.*/
typedef struct nodo{
	struct nodo* i;
	struct nodo* d;
}nodo_t;

int contar_hojas(nodo_t* raiz){
	if(!raiz) return 0;

	if(!raiz->i && !raiz->d) //como son NULL ya no puedo seguir bajando
		return 1;
	return contar_hojas(raiz->i) + contar_hojas(raiz->d);
}

/*Devolver la cantidad de nodos que poseen tanto hijo i como d.*/
int contar_nodos_con_dos_hijos(nodo_t* raiz){
	if(!raiz) return 0;

	if(raiz->i && raiz->d) //puedo seguir bajando retorno 1+...
		return 1+contar_nodos_con_dos_hijos(raiz->i) + contar_nodos_con_dos_hijos(raiz->d);;
	
	return contar_nodos_con_dos_hijos(raiz->i) + contar_nodos_con_dos_hijos(raiz->d);
}

/*Determinar si el numero es primo o no.*/
bool es_primo_aux(int n, int divisor){
	if(n == divisor)
		return true;
	if(n % divisor == 0) //es divisible por otro q no es el mismo
		return false;
	return es_primo_aux(n, divisor+1);
}

bool es_primo(int n){
	if(n <= 1)
		return false;

	return es_primo_aux(n, 2); //desde el 2 voy incrementando para ver si es divisible
}

/*Devovler un vector dinámico con n numeros primos.*/
void primeros_n_primos_aux(int* primos, int cantidad_agregar, int divisor){
	if(cantidad == 0) return;

	if(es_primo(numero)){
		*primos = numero;
		primeros_n_primos_aux(primos+1, cantidad_agregar-1, numero+1);
	}
	primeros_n_primos_aux(primos, cantidad_agregar, numero+1);

}

int* primeros_n_primos(int n){
	int* primos = malloc(n*sizeof(int));
	if(!primos) return NULL;

	primeros_n_primos_aux(primos, n, 2);
}

/*Devolver el string con la posicion de los caracteres de a pares invertidos.
ej: "ABCDEF" -> "BADCFE"*/

void invertir_de_a_pares(char* s){
	if(!s || s[0] == '/0') return;

	if(s[1] == '/0') //si el q le sigue es barra cero no intercambio
		return;

	//swap
	char aux = s[0];
	s[0] = s[1];
	s[1] = aux;

	invertir_de_a_pares(s+2);
}

/*Dado un entero n > 0 calcular la potencia de 2 mayor o igual a n mas cercana.
ej: 1 -> 1
	2 -> 2
	3 -> 4
	5 -> 8
*/
int proxima_potencia_de_dos_aux(int max, int cantidad){
	if(cantidad >= max) return cantidad;
	proxima_potencia_de_dos_aux(max, cantidad*2):
}

int proxima_potencia_de_dos(int n){
	return proxima_potencia_de_dos_aux(n, 1);
}