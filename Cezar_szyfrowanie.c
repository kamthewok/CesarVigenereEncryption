#include <stdio.h>
#include <stdlib.h>
#include "Cezar_szyfrowanie.h"

#define SHIFT_COEFFICIENT 3 //stala oznaczajaca wartosc przesuniecia podczas szyfrowania
#define ENCODED_UNSUCCESSFULLY 0 //flaga oznaczajaca, ze szyfrowanie nie powiodlo sie
#define ENCODED_SUCCESSFULLY 1 //flaga oznaczajaca, ze szyfrowanie powiodlo sie

void initializeFilenames(char* baseFilename, char* encodedFilename){ //Funkcja inicjalizujaca sciezki do plikow

    printf("Podaj plik, ktory chcesz zaszyfrowac (z rozszerzeniem): ");
    scanf("%s", baseFilename);
    printf("Podaj nazwe pliku, w ktorym zostanie zapisana zaszyfrowana tresc: ");
    scanf("%s", encodedFilename);

}

typedef struct t_charsToEncode{ //struktura reprezentujaca ciag znakow do zaszyfrowania

    char* chars;
    int count;

}CharsToEncode;

CharsToEncode* readBaseFile(char* baseFilename){ //funkcja wczytujaca znaki do zaszyfrowania

    FILE* file = fopen(baseFilename, "r");
    int getNumberOfCharsInAFile(char* filename);
    if(file == NULL){
        printf("Zla sciezka pliku do zaszyfrowania!\n");
        return NULL;
    }

    CharsToEncode* cToEncode = (CharsToEncode*)malloc(sizeof(CharsToEncode)); //dynamicznie stworzenie struktury do przechowania znakow
    (*cToEncode).count = getNumberOfCharsInAFile(baseFilename); //wczytanie ilosci znakow do zaszyfrowania
    (*cToEncode).chars = (char*)malloc(sizeof(char) * (*cToEncode).count); //dynamiczna alokacja pamieci do przechowania znakow

    int nChar = 0;
    char buffer;
    while((buffer = fgetc(file)) != EOF){ //wczytywanie poszczegolnych znakow z pliku do czasu natrafienia na flage EOF
        (*cToEncode).chars[nChar] = buffer;
        nChar++;
    }

    fclose(file);

    return cToEncode;
}

int getNumberOfCharsInAFile(char* filename){ //funkcja zwracajaca ilosc znakow znajdujacych sie w pliku
    FILE* file = fopen(filename, "r");

    if(file == NULL)
        return 0;

    fseek(file, 0L, SEEK_END); //funkcja ustawiajaca wskaznik pliku na jego koniec

    int nOfChars = ftell(file); //odczytanie ilosci znakow w pliku dzieki funkcji ftell, ktora zwraca aktualna pozycje wskaznika pliku
    fclose(file);

    return nOfChars;
}

int encode(CharsToEncode* cToEncode){ //funkcja szyfrujaca

    int i = 0;
    for(; i < (*cToEncode).count; i++){
            char c;
        c = (*cToEncode).chars[i];

        if(c == ' ' || c == '\n' || c == '\r' || c == '\0')
            continue;

        if(c >= 97 && c <= 122 - SHIFT_COEFFICIENT)
            (*cToEncode).chars[i] = (int)c + SHIFT_COEFFICIENT;
        else if(c <= 122 && c > 122 - SHIFT_COEFFICIENT)
            (*cToEncode).chars[i] = (int)c + SHIFT_COEFFICIENT - 26 ;
        else if(c >= 65 && c <= 90-SHIFT_COEFFICIENT)
            (*cToEncode).chars[i] = (int)c + SHIFT_COEFFICIENT;
        else if(c <= 90 && c > 90-SHIFT_COEFFICIENT)
            (*cToEncode).chars[i] = (int)c + SHIFT_COEFFICIENT - 26;
        else{
            printf("Plik do zaszyfrowania zawiera niedozwolone znaki!");
            return ENCODED_UNSUCCESSFULLY;
        }
    }

    return ENCODED_SUCCESSFULLY;
}

void saveToFile(char* filename, CharsToEncode* cToEncode){ //funkcja zapisujaca zaszyfrowane znaki

    FILE* file = fopen(filename, "w");

    if(file == NULL){
        printf("Zla sciezka pliku do zapisu!");
        return;
    }

    fputs((*cToEncode).chars, file);

    fclose(file);

    printf("Zaszyfrowano pomyslnie!\n\n");
}

void encodeCaesar(){ //glowna funkcja do wywolania szyfrowania

    char baseFilename[128], encodedFilename[128]; //zmienne do przechowywania sciezek plikow
    initializeFilenames(baseFilename, encodedFilename);

    CharsToEncode* cToEncode = readBaseFile(baseFilename);

    if(cToEncode == NULL)
        return;

    int encodingFlag = encode(cToEncode);
    if(encodingFlag == ENCODED_UNSUCCESSFULLY)
        return;

    saveToFile(encodedFilename, cToEncode);
}
