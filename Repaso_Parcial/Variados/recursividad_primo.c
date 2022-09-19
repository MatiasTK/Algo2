//EJ -> https://i.imgur.com/CAP8JPJ.png
#include <stdio.h>
#include <stdbool.h>

bool es_primo_aux(int n, int m){
    if(m == 1)
        return true;
    if(n % m == 0)
        return false;
    return es_primo_aux(n, m-1);
}

bool es_primo(int n){
    if(n == 1){
        return false;
    }

    return es_primo_aux(n, n-1);
}

int main(){
    int n = 2;
    if(es_primo(n)){
        printf("%d es primo\n", n);
    }else{
        printf("%d no es primo\n", n);
    }

    return 0;
}