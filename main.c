#include <stdio.h>
#include <stdlib.h>

#include "Vigenere_szyfrowanie.h"
#include "Vigenere_deszyfrowanie.h"
#include "Cezar_szyfrowanie.h"
#include "Cezar_deszyfrowanie.h"



int main()
{
while(1){
    int wybor=0, opcja=0;
    printf("Chcesz zaszyfrowac czy odszyfrowac? \n[1]. Zaszyfrowac\n[2]. Odszyfrowac\n[3]Exit\n");
    scanf("%d", &opcja);
    if(opcja==1){
    printf("\nWybierz szyfr ktorego chcesz uzyc: \n[1]. Cezara\n[2]. Vigenere'a\n");
    scanf("%d", &wybor);
    puts("\n");
    if (wybor==1){
        encodeCaesar();

    }
    else if (wybor==2){
        Vigenere();
    }
    else
        printf("Nie prawidlowy wybor!\n");
    }
    else if(opcja==2){

        printf("\nWybierz szyfr ktorym chcesz odszyfrowac: \n[1]. Cezara\n[2]. Vigenere'a\n");
        scanf("%d", &wybor);
    if (wybor==1){
        puts("\n");
        decodeCaesar();

    }
    else if (wybor==2){puts("\n");
        Vigenere_deszyfrowanie();

    }
    else
        printf("\nNie prawidlowy wybor!\n\n");
    }
    else if(opcja==3){
        exit(0);
    }
    else
        printf("\nNie prawidlowy wybor!\n\n");
}
}

