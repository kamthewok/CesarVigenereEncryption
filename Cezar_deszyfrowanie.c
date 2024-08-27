#include <stdio.h>
#include <stdlib.h>
#include "Cezar_deszyfrowanie.h"

#ifndef SHIFT_COEFFICIENT
#define SHIFT_COEFFICIENT 3 //stala oznaczajaca wartosc przesuniecia podczas deszyfrowania
#endif

#define DECODED_UNSUCCESSFULLY 0 //flaga oznaczajaca, ze deszyfrowanie nie powiodlo sie
#define DECODED_SUCCESSFULLY 1 //flaga oznaczajaca, ze deszyfrowanie powiodlo sie

void e_initializeFilenames(char* baseFilename, char* decodedFilename){ //Funkcja inicjalizujaca sciezki do plikow

    printf("Podaj plik, ktory chcesz odszyfrowac (z rozszerzeniem): ");
    scanf("%s", baseFilename);
    printf("Podaj nazwe pliku, w ktorym zostanie zapisana odszyfrowana tresc: ");
    scanf("%s", decodedFilename);
}

typedef struct t_charsToDecode{ //struktura reprezentujaca ciag znakow do deszyfrowania

    char* chars;
    int count;

}CharsToDecode;

int e_getNumberOfCharsInAFile(char* filename){ //funkcja zwracajaca ilosc znakow znajdujacych sie w pliku
    FILE* file = fopen(filename, "r");

    if(file == NULL)
        return 0;

    fseek(file, 0L, SEEK_END); //funkcja ustawiajaca wskaznik pliku na jego koniec

    int nOfChars = ftell(file)-1; //odczytanie ilosci znakow w pliku dzieki funkcji ftell, ktora zwraca aktualna pozycje wskaznika pliku
    fclose(file);

    return nOfChars;
}

CharsToDecode* e_readBaseFile(char* baseFilename){ //funkcja wczytujaca znaki do deszyfrowania

    FILE* file = fopen(baseFilename, "r");
    int getNumberOfCharsInAFile(char* filename);
    if(file == NULL){
        printf("Zla sciezka pliku do odszyfrowania!\n");
        return NULL;
    }

    CharsToDecode* cToDecode = (CharsToDecode*)malloc(sizeof(CharsToDecode)); //dynamicznie stworzenie struktury do przechowania znakow
    (*cToDecode).count = getNumberOfCharsInAFile(baseFilename); //wczytanie ilosci znakow do deszyfrowania
    (*cToDecode).chars = (char*)malloc(sizeof(char) * (*cToDecode).count); //dynamiczna alokacja pamieci do przechowania znakow

    int nChar = 0;
    char buffer;
    while((buffer = fgetc(file)) != EOF){ //wczytywanie poszczegolnych znakow z pliku do czasu natrafienia na flage EOF
        (*cToDecode).chars[nChar] = buffer;
        nChar++;
    }

    fclose(file);

    return cToDecode;
}

int decode(CharsToDecode* cToDecode){ //funkcja deszyfrujaca

    int i = 0;
    for(; i < (*cToDecode).count; i++){
        char c;
        c = (*cToDecode).chars[i];

        if(c == ' ' || c == '\n' || c == '\r' || c == '\0')
            continue;

        if(c >= 97 + SHIFT_COEFFICIENT && c <= 122)
            (*cToDecode).chars[i] = (int)c - SHIFT_COEFFICIENT;
        else if(c >= 97 && c < 97 + SHIFT_COEFFICIENT)
            (*cToDecode).chars[i] = (int)c + 26 - SHIFT_COEFFICIENT;
        else if(c >= 65 + SHIFT_COEFFICIENT && c <= 90)
            (*cToDecode).chars[i] = (int)c - SHIFT_COEFFICIENT;
        else if(c >= 65 && c < 65 + SHIFT_COEFFICIENT)
            (*cToDecode).chars[i] = (int)c + 26 - SHIFT_COEFFICIENT;
        else{
            printf("Plik do zaszyfrowania zawiera niedozwolone znaki!\n");
            return DECODED_UNSUCCESSFULLY;
        }
    }

    return DECODED_SUCCESSFULLY;
}

void e_saveToFile(char* filename, CharsToDecode* cToDecode){ //funkcja zapisujaca odszyfrowane znaki

    FILE* file = fopen(filename, "w");

    if(file == NULL){
        printf("Zla sciezka pliku do zapisu!");
        return;
    }

    fputs((*cToDecode).chars, file);

    fclose(file);

    printf("Odszyfrowano pomyslnie!\n\n");
}

void decodeCaesar(){ //glowna funkcja do wywolania deszyfrowania

    char baseFilename[128], decodedFilename[128]; //zmienne do przechowywania sciezek plikow
    e_initializeFilenames(baseFilename, decodedFilename);

    CharsToDecode* cToDecode = e_readBaseFile(baseFilename);

    if(cToDecode == NULL)
        return;

    int encodingFlag = decode(cToDecode);
    if(encodingFlag == DECODED_UNSUCCESSFULLY)
        return;

    e_saveToFile(decodedFilename, cToDecode);
}
