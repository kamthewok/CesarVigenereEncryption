#include "Vigenere_szyfrowanie.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
void Vigenere()
{
    FILE *in, *out;
    int i=0, licznik=0;
    int tablica_pomocnicza[10000]= {};  //Ta tablica przechowuje litery odpowiadajace haslu.
    char znak=0;                   //Znak odczytywany z podanego pliku do szyfrowania.
    char haslo[10000]= {};         //Tablica sluzy do przechowania hasla podanego przez uzytkownika.
    char plik_do_zaszyfrowania[10000]= {}; //Nazwa pliku ktory ma byc zaszyfrowany.
    char plik_zaszyfrowany[10000]= {};    //Nazwa pliku, w ktorym bedzie zaszyfrowany tekst.
    for (i=0; i<10000; i++)               //Ta petla umozliwia wypelnienie tablicy pustymi znakami
        haslo[i]=42;
    int pozycja=0;
    printf("Podaj nazwe pliku do zaszyfrowania (z rozszerzeniem!): ");
    scanf("%s", plik_do_zaszyfrowania);

    in = fopen(plik_do_zaszyfrowania, "r");

    if(in == NULL)
    {
        printf("Zla sciezka pliku do zaszyfrowania!\n");
        return NULL;
    }

    printf("Podaj nazwe pliku, do ktorego chcesz zapisac: ");
    scanf("%s", plik_zaszyfrowany);
    printf("Podaj haslo (tylko duze litery, bez spacji  bez znakow specjalnych!): ");
    scanf("%s", haslo);
    for (i=0; i<10000; i++)
    {
        if ((haslo[pozycja]<65) || (haslo[pozycja]>90))
        {
            printf("Nie prawidlowe haslo!\n");
            return NULL;
        }
        pozycja++;
    }

    for(i=0; i<10000; i++)
        if(haslo[pozycja]!=42)
        {
            tablica_pomocnicza[i]=haslo[pozycja];     //Pod znaki z tablicy jest podstawiane haslo, zgodnie z zasada szyfrowania vigener'a.
            pozycja++;
        }
        else
        {
            pozycja=0;                           //Haslo wczytywane od poczatku, gdy jest za krotkie, by 'podstawic sie' pod tekst.
            i--;
            tablica_pomocnicza[i]=haslo[pozycja];
            pozycja++;
        }

    for(i=0; i<10000; i++)
        tablica_pomocnicza[i]-=65;                    //Operacja, dzieki ktorej wiadomo o ile 'zmienic' (teskst do szyfrowania).
    licznik=0;


    if((in=fopen(plik_do_zaszyfrowania, "r"))!=NULL)  //Otwieranie pliku do zaszyfrowania.
    {
        if((out=fopen(plik_zaszyfrowany, "w+"))!=NULL) //Tworzenie pliku z zaszyfrowanym tesktem.
        {
            while((znak=getc(in))!=EOF)     //Kazda litera jest pobierana, az program nie natrafi na znak konca pliku.
            {
                //Znaki sa rozdzielane na male, badz wielkie litery.
                if((znak>=65)&&(znak<=90))
                {
                    znak -= 65;
                    znak += tablica_pomocnicza[licznik];  //Operacja powodujaca przesuniecie zgodnie z teskstem i haslem (szyfrowanie).
                    if (licznik == 10000)            //Zerowanie licznika w przypadku, gdy teskt jest dluzszy niz 10000 znakow, dzieki temu haslo bedzie pobierane od poczatku.
                        licznik = 0;
                    else
                        licznik++;

                    znak = fmod(znak, 26);            //Tutaj i ponizej sa operacje szyfrowania dzialajaca zgodnie z zasada szyfru Vigener'a.
                    znak += 65;
                    putc(znak, out);

                }
                else if ((znak>=97)&&(znak<=122))     //Tutaj i ponizej sa operacje szyfrowania dzialajaca zgodnie z zasada szyfru Vigener'a.
                {
                    znak-=97;
                    znak+=tablica_pomocnicza[licznik];
                    if(licznik==10000)
                        licznik=0;
                    else                               //Tutaj i ponizej sa operacje szyfrowania dzialajaca zgodnie z zasada szyfru Vigener'a.
                        licznik++;
                    znak=fmod(znak,26);
                    znak+=97;
                    putc(znak,out);
                }
            }
            fclose(out);
        }
        fclose(in);
    }
    printf("Szyfrowanie zakonczone!\n\n");

}


