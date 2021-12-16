int main(){
    char clave[5];
    clave[0] = 'A';
    clave[1] = 'B';
    clave[2] = 'C';
    clave[3] = 0;

    hash_insertar(clave);

    clave[0] = 'B';
}