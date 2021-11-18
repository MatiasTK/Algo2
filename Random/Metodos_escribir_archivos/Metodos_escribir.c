#include <stdio.h> //! fprintf - fputc - fputs

typedef struct pokemon{
    char* nombre;
    int nivel;
    int fuerza;
    int inteligencia;
    int carisma;
}pokemon_t;

//? Escribe una linea en una archivo. Actua igual que un printf. primero el archivo, despues lo que vas a poner.
void _fprintf(pokemon_t pokemon, FILE* archivo){
    if(!archivo){
        return;
    }

    fprintf(archivo, "%s;%i;%i;%i;%i\n", pokemon.nombre, pokemon.nivel, pokemon.fuerza, pokemon.inteligencia, pokemon.carisma);
}

//? Escribe una letra en un archivo
void _fputc(char c, FILE* archivo){
    if(!archivo){
        return;
    }

    fputc(c, archivo);
}

//? Escribe una cadena en un archivo
//! No es muy recomendable usar fputs ya que hay que usar fputc para escribir por ejemplo un salto de linea y es incomodo.
void _fputs(pokemon_t pokemon, FILE* archivo){
    if(!archivo){
        return;
    }
    
    fputs(pokemon.nombre,archivo); 
}

//? Si bien esto escribe las cosas las escribe en binario por lo tanto no se puede leer a simple vista
void _fwrite(pokemon_t pokemon, FILE* archivo){
    if(!archivo){
        return;
    }

    fwrite(&pokemon, sizeof(pokemon_t), 1, archivo);
}


int main(){
    FILE* archivo = fopen("fprintf.txt", "w");
    if(archivo == NULL){
        printf("No se pudo abrir el archivo\n");
        return 1;
    }

    pokemon_t pikachu = {"Pikachu", 9, 2, 3, 2};
    pokemon_t bulbasaur = {"Bulbasaur", 0, 5, 10, 1};
    pokemon_t charmander = {"Charmander", 3, 3, 10, 10};

    _fprintf(pikachu, archivo);
    _fprintf(bulbasaur, archivo);
    _fprintf(charmander, archivo);
    //! ======================================================================================
    archivo = fopen("fputc.txt", "w");
    if(archivo == NULL){
        printf("No se pudo abrir el archivo\n");
        return 1;
    }

    _fputc('H', archivo);
    _fputc('O', archivo);
    //! ======================================================================================
    archivo = fopen("fputs.txt", "w");
    if(archivo == NULL){
        printf("No se pudo abrir el archivo\n");
        return 1;
    }

    _fputs(pikachu, archivo);
    _fputs(bulbasaur, archivo);
    _fputs(charmander, archivo);
    //! ======================================================================================
    archivo = fopen("fwrite.txt", "w");
    if(archivo == NULL){
        printf("No se pudo abrir el archivo\n");
        return 1;
    }

    _fwrite(pikachu, archivo);
    _fwrite(bulbasaur, archivo);
    _fwrite(charmander, archivo);
    //! ======================================================================================
    fclose(archivo);

    return 0;
}