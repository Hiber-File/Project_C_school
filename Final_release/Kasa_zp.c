#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

//void glowne
void baza_k();                  //wyswietla baze klientow
void mod_klienta();	            //modyfikacja danych klienta
void dodaj_klienta();	        //dodanie klienta do bazy danych
void usun_klienta();	        //usuniecie klienta z bazy danych
void baza_p();                  //wyswietlanie bazy pozyczek
void sort_nazw();	            //wyswietlanie listy klientow posortowanej po nazwisku
void sort_kwota();	            //wyswietlanie listy klientow posortowanej po wysokosci pozyczki
void splata_teraz();            //wyswietlanie listy klientow ktorzy skoncza splacac jakas pozyczke w tym miesiacu
void zadluzenie();	            //sprawdzanie ile zadluzony jest dany klient
void zapisz();                  //zapisuje baze danych po wprowadzonych zmianach
void zapisz_p();                //zapisuje baze pozyczek
void menu();		            //funkcja do obslugi interfejsu
//void pomocnicze
void wielka_litera();           //poprawia na wielka litere, reszta male
int pesel_check();              //sprawdza poprawnosc daty w peselu (nie sprawdza sumy kontrolnej) oraz dlugosc podanego peselu
int dowod_check();              //sprawdza poprawnosc wpisanego nr dowodu
void ulica_correct();           //poprawia format wpisanej ulicy/miasta
int kod_check();                //sprawdza poprawnosc wpisanego kodu pocztowego
int alfabet();                  //sprawdza ktory z podanych stringow jest bardziej alfabetyczny
void oblicz();                  //obliczenia zwiazane z baza pozyczek
void data();                    //pobieranie aktualnej daty od uzytkownika
int znajdz();                   //znajduje klienta o danym numerze pozyczki
void delay();                   //upiekszanie


int b_rok,b_miesiac,b_dzien;    //biezaca data
int i;                          //zmienna pomocnicza
int LK;                         //liczba klientow
int LP;                         //liczba pozyczek


typedef struct                  //struktura do obslugi klientow
{
int ident;                      //identyfikator
char imie[20];
char nazwisko[20];
char pesel[12];
char dowod[10];
char ulica[35];
char nr[5];
char kod[7];
char miasto[35];
int numer1;
int numer2;
int numer3;
int numer4;
int numer5;
float dlug;
}osoba;

typedef struct                  //struktura do obslugi pozyczek
{
int numer;                      //numer pozyczki
int kwota;
int rok;
int miesiac;
int dzien;
int na_ile;                     //na ile miesiecy
float procent;                  //w skali roku

int ile_m_spl;                  //ile miesiecy juz splacono
int ile_m_do_spl;               //ile miesiecy pozostalo do splaty
float ile_do_splaty;            //do sprawdzania ile zadluzony jest klient

float rata_kap;                 //rata kapitalowa
float odsetki;
float rata_lacz;                //rata laczna
}bank;

osoba klient[2000];
bank poz[10000];


//void glowne
void baza_k(void)
{
    char choice2;

    system("cls");
    for(i=0;i<LK;++i)
        {
            printf("\n\n\t%d",klient[i].ident);
            printf("  %s",klient[i].imie);
            printf("  %s",klient[i].nazwisko);
        }

    printf("\n\n\tCzy chcesz wyswietlic adresy? (Y/N)");
    fflush(stdin);
    scanf("%c",&choice2);
    choice2=toupper(choice2);

    system("cls");
    for(i=0;i<LK;++i)
        {

            printf("\n\n\t%d",klient[i].ident);
            printf("  %s",klient[i].imie);
            printf("  %s",klient[i].nazwisko);

            if(choice2=='Y')
                {
                    printf("\n\t   ul. %s",klient[i].ulica);
                    printf("  %s",klient[i].nr);
                    printf("  %s",klient[i].kod);
                    printf("  %s",klient[i].miasto);
                }
        }

}

void mod_klienta(void)
{
    int id;
    int pes=0,dow=0,kod=0;          //zero = true
    char choice;

    printf("\n\tPodaj numer klienta: \t\t");
    fflush(stdin);
    scanf("%d",&id);
    --id;

    system("cls");
    printf("\n\tDane osobowe:");
    printf("\n\n\tImie\t\t%s",klient[id].imie);
    printf("\n\tNazwisko\t%s",klient[id].nazwisko);
    printf("\n\tPESEL\t\t%s",klient[id].pesel);
    printf("\n\tNr dowodu\t%s",klient[id].dowod);
    printf("\n\n\tAdres:");
    printf("\n\t\t\tul.%s %s",klient[id].ulica,klient[id].nr);
    printf("\n\t\t\t%s",klient[id].kod);
    printf("\n\t\t\t%s",klient[id].miasto);

    printf("\n\n\tCzy chcesz wprowadzic zmiany? (Y/N)");
    fflush(stdin);
    scanf("%c",&choice);
    choice=toupper(choice);

    if(choice=='Y')
        {

        system("cls");
        printf("\n\tPodaj dane osobowe:");

        printf("\n\tImie\t\t");
        fflush(stdin);
        scanf("%s",klient[id].imie);
        wielka_litera(klient[id].imie);
        system("cls");
        printf("\n\tPodaj dane osobowe:");
        printf("\n\tImie\t\t%s",klient[id].imie);


        printf("\n\tNazwisko\t");
        fflush(stdin);
        scanf("%s",klient[id].nazwisko);
        wielka_litera(klient[id].nazwisko);
        system("cls");
        printf("\n\tPodaj dane osobowe:");
        printf("\n\tImie\t\t%s",klient[id].imie);
        printf("\n\tNazwisko\t%s",klient[id].nazwisko);


        printf("\n\tPESEL\t\t");
        do
        {
        fflush(stdin);
        scanf("%s",klient[id].pesel);
        pes=pesel_check(klient[id].pesel);

        if(pes!=0)
        {
            printf("\n\tPodaj poprawny PESEl !");
            delay(2000);
            system("cls");
            printf("\n\tPodaj dane osobowe:");
            printf("\n\tImie\t\t%s",klient[id].imie);
            printf("\n\tNazwisko\t%s",klient[id].nazwisko);
            printf("\n\tPESEL\t\t");
        }

        }while(pes!=0);


        printf("\tNr dowodu\t");
        do
        {
        fflush(stdin);
        scanf("%s",klient[id].dowod);
        klient[id].dowod[0]=toupper(klient[id].dowod[0]);
        klient[id].dowod[1]=toupper(klient[id].dowod[1]);
        klient[id].dowod[2]=toupper(klient[id].dowod[2]);
        system("cls");
        printf("\n\tPodaj dane osobowe:");
        printf("\n\tImie\t\t%s",klient[id].imie);
        printf("\n\tNazwisko\t%s",klient[id].nazwisko);
        printf("\n\tPESEL\t\t%s",klient[id].pesel);
        printf("\n\tNr dowodu\t%s",klient[id].dowod);
        dow=dowod_check(klient[id].dowod);

        if(dow!=0)
        {
            printf("\n\tPodaj poprawny Nr dowodu !");
            delay(2000);
            system("cls");
            printf("\n\tPodaj dane osobowe:");
            printf("\n\tImie\t\t%s",klient[id].imie);
            printf("\n\tNazwisko\t%s",klient[id].nazwisko);
            printf("\n\tPESEL\t\t%s",klient[id].pesel);
            printf("\n\tNr dowodu\t");

        }

        }while(dow!=0);


        printf("\n\n\tAdres:");

        printf("\n\tNazwa ulicy\t");
        fflush(stdin);
        gets(klient[id].ulica);
        ulica_correct(klient[id].ulica);
        system("cls");
        printf("\n\tPodaj dane osobowe:");
        printf("\n\tImie\t\t%s",klient[id].imie);
        printf("\n\tNazwisko\t%s",klient[id].nazwisko);
        printf("\n\tPESEL\t\t%s",klient[id].pesel);
        printf("\n\tNr dowodu\t%s",klient[id].dowod);
        printf("\n\n\tAdres:");
        printf("\n\tNazwa ulicy\t%s",klient[id].ulica);
        printf("\n\tNumer\t\t");
        fflush(stdin);
        scanf("%s",klient[id].nr);
        system("cls");
        printf("\n\tPodaj dane osobowe:");
        printf("\n\tImie\t\t%s",klient[id].imie);
        printf("\n\tNazwisko\t%s",klient[id].nazwisko);
        printf("\n\tPESEL\t\t%s",klient[id].pesel);
        printf("\n\tNr dowodu\t%s",klient[id].dowod);
        printf("\n\n\tAdres:");
        printf("\n\tNazwa ulicy\t%s",klient[id].ulica);
        printf("\n\tNumer\t\t%s",klient[id].nr);
        printf("\n\tKod\t\t");

        do
        {
        fflush(stdin);
        scanf("%s",klient[id].kod);
        kod=kod_check(klient[id].kod);

            if(kod!=0)
            {
                printf("\n\tPodaj poprawny kod pocztowy !");
                delay(2000);
                system("cls");
                printf("\n\tPodaj dane osobowe:");
                printf("\n\tImie\t\t%s",klient[id].imie);
                printf("\n\tNazwisko\t%s",klient[id].nazwisko);
                printf("\n\tPESEL\t\t%s",klient[id].pesel);
                printf("\n\tNr dowodu\t%s",klient[id].dowod);
                printf("\n\n\tAdres:");
                printf("\n\tNazwa ulicy\t%s",klient[id].ulica);
                printf("\n\tNumer\t\t%s",klient[id].nr);
                printf("\n\tKod\t\t");
            }

        }while(kod!=0);

        system("cls");
        printf("\n\tPodaj dane osobowe:");
        printf("\n\tImie\t\t%s",klient[id].imie);
        printf("\n\tNazwisko\t%s",klient[id].nazwisko);
        printf("\n\tPESEL\t\t%s",klient[id].pesel);
        printf("\n\tNr dowodu\t%s",klient[id].dowod);
        printf("\n\n\tAdres:");
        printf("\n\tNazwa ulicy\t%s",klient[id].ulica);
        printf("\n\tNumer\t\t%s",klient[id].nr);
        printf("\n\tKod\t\t%s",klient[id].kod);
        printf("\n\tMiasto\t\t");
        fflush(stdin);
        gets(klient[id].miasto);
        ulica_correct(klient[id].miasto);
        system("cls");
        printf("\n\tPodaj dane osobowe:");
        printf("\n\tImie\t\t%s",klient[id].imie);
        printf("\n\tNazwisko\t%s",klient[id].nazwisko);
        printf("\n\tPESEL\t\t%s",klient[id].pesel);
        printf("\n\tNr dowodu\t%s",klient[id].dowod);
        printf("\n\n\tAdres:");
        printf("\n\tNazwa ulicy\t%s",klient[id].ulica);
        printf("\n\tNumer\t\t%s",klient[id].nr);
        printf("\n\tKod\t\t%s",klient[id].kod);
        printf("\n\tMiasto\t\t%s",klient[id].miasto);


        system("cls");
        printf("\n\tDane osobowe:");
        printf("\n\tImie\t\t%s",klient[id].imie);
        printf("\n\tNazwisko\t%s",klient[id].nazwisko);
        printf("\n\tPESEL\t\t%s",klient[id].pesel);
        printf("\n\tNr dowodu\t%s",klient[id].dowod);

        printf("\n\n\tAdres:");

        printf("\n\t\t\tul.%s %s",klient[id].ulica,klient[id].nr);
        printf("\n\t\t\t%s",klient[id].kod);
        printf("\n\t\t\t%s",klient[id].miasto);
    }
}

void dodaj_klienta(void)
{
    int pes=0,dow=0,kod=0,nr=1,pom;          //zero = true
    char dalej;                              //czy chcesz pobrac kolejne pozyczki
    ++LK;
    klient[LK-1].ident=klient[LK-2].ident+1;
    system("cls");
    printf("\n\tPodaj dane osobowe:");

    printf("\n\tImie\t\t");
    fflush(stdin);
    scanf("%s",klient[LK-1].imie);
    wielka_litera(klient[LK-1].imie);
    system("cls");
    printf("\n\tPodaj dane osobowe:");
    printf("\n\tImie\t\t%s",klient[LK-1].imie);


    printf("\n\tNazwisko\t");
    fflush(stdin);
    scanf("%s",klient[LK-1].nazwisko);
    wielka_litera(klient[LK-1].nazwisko);
    system("cls");
    printf("\n\tPodaj dane osobowe:");
    printf("\n\tImie\t\t%s",klient[LK-1].imie);
    printf("\n\tNazwisko\t%s",klient[LK-1].nazwisko);


    printf("\n\tPESEL\t\t");
    do
    {
    fflush(stdin);
    scanf("%s",klient[LK-1].pesel);
    pes=pesel_check(klient[LK-1].pesel);

    if(pes!=0)
    {
        printf("\n\tPodaj poprawny PESEl !");
        delay(2000);
        system("cls");
        printf("\n\tPodaj dane osobowe:");
        printf("\n\tImie\t\t%s",klient[LK-1].imie);
        printf("\n\tNazwisko\t%s",klient[LK-1].nazwisko);
        printf("\n\tPESEL\t\t");
    }

    }while(pes!=0);


    printf("\tNr dowodu\t");
    do
    {
    fflush(stdin);
    scanf("%s",klient[LK-1].dowod);
    klient[LK-1].dowod[0]=toupper(klient[LK-1].dowod[0]);
    klient[LK-1].dowod[1]=toupper(klient[LK-1].dowod[1]);
    klient[LK-1].dowod[2]=toupper(klient[LK-1].dowod[2]);
    system("cls");
    printf("\n\tPodaj dane osobowe:");
    printf("\n\tImie\t\t%s",klient[LK-1].imie);
    printf("\n\tNazwisko\t%s",klient[LK-1].nazwisko);
    printf("\n\tPESEL\t\t%s",klient[LK-1].pesel);
    printf("\n\tNr dowodu\t%s",klient[LK-1].dowod);
    dow=dowod_check(klient[LK-1].dowod);

    if(dow!=0)
    {
        printf("\n\tPodaj poprawny Nr dowodu !");
        delay(2000);
        system("cls");
        printf("\n\tPodaj dane osobowe:");
        printf("\n\tImie\t\t%s",klient[LK-1].imie);
        printf("\n\tNazwisko\t%s",klient[LK-1].nazwisko);
        printf("\n\tPESEL\t\t%s",klient[LK-1].pesel);
        printf("\n\tNr dowodu\t");

    }

    }while(dow!=0);


    printf("\n\n\tAdres:");

    printf("\n\tNazwa ulicy\t");
    fflush(stdin);
    gets(klient[LK-1].ulica);
    ulica_correct(klient[LK-1].ulica);
    system("cls");
    printf("\n\tPodaj dane osobowe:");
    printf("\n\tImie\t\t%s",klient[LK-1].imie);
    printf("\n\tNazwisko\t%s",klient[LK-1].nazwisko);
    printf("\n\tPESEL\t\t%s",klient[LK-1].pesel);
    printf("\n\tNr dowodu\t%s",klient[LK-1].dowod);
    printf("\n\n\tAdres:");
    printf("\n\tNazwa ulicy\t%s",klient[LK-1].ulica);
    printf("\n\tNumer\t\t");
    fflush(stdin);
    scanf("%s",klient[LK-1].nr);
    system("cls");
    printf("\n\tPodaj dane osobowe:");
    printf("\n\tImie\t\t%s",klient[LK-1].imie);
    printf("\n\tNazwisko\t%s",klient[LK-1].nazwisko);
    printf("\n\tPESEL\t\t%s",klient[LK-1].pesel);
    printf("\n\tNr dowodu\t%s",klient[LK-1].dowod);
    printf("\n\n\tAdres:");
    printf("\n\tNazwa ulicy\t%s",klient[LK-1].ulica);
    printf("\n\tNumer\t\t%s",klient[LK-1].nr);
    printf("\n\tKod\t\t");

    do
    {
    fflush(stdin);
    scanf("%s",klient[LK-1].kod);
    kod=kod_check(klient[LK-1].kod);

        if(kod!=0)
        {
            printf("\n\tPodaj poprawny kod pocztowy !");
            delay(2000);
            system("cls");
            printf("\n\tPodaj dane osobowe:");
            printf("\n\tImie\t\t%s",klient[LK-1].imie);
            printf("\n\tNazwisko\t%s",klient[LK-1].nazwisko);
            printf("\n\tPESEL\t\t%s",klient[LK-1].pesel);
            printf("\n\tNr dowodu\t%s",klient[LK-1].dowod);
            printf("\n\n\tAdres:");
            printf("\n\tNazwa ulicy\t%s",klient[LK-1].ulica);
            printf("\n\tNumer\t\t%s",klient[LK-1].nr);
            printf("\n\tKod\t\t");
        }

    }while(kod!=0);

    system("cls");
    printf("\n\tPodaj dane osobowe:");
    printf("\n\tImie\t\t%s",klient[LK-1].imie);
    printf("\n\tNazwisko\t%s",klient[LK-1].nazwisko);
    printf("\n\tPESEL\t\t%s",klient[LK-1].pesel);
    printf("\n\tNr dowodu\t%s",klient[LK-1].dowod);
    printf("\n\n\tAdres:");
    printf("\n\tNazwa ulicy\t%s",klient[LK-1].ulica);
    printf("\n\tNumer\t\t%s",klient[LK-1].nr);
    printf("\n\tKod\t\t%s",klient[LK-1].kod);
    printf("\n\tMiasto\t\t");
    fflush(stdin);
    gets(klient[LK-1].miasto);
    ulica_correct(klient[LK-1].miasto);
    system("cls");
    printf("\n\tPodaj dane osobowe:");
    printf("\n\tImie\t\t%s",klient[LK-1].imie);
    printf("\n\tNazwisko\t%s",klient[LK-1].nazwisko);
    printf("\n\tPESEL\t\t%s",klient[LK-1].pesel);
    printf("\n\tNr dowodu\t%s",klient[LK-1].dowod);
    printf("\n\n\tAdres:");
    printf("\n\tNazwa ulicy\t%s",klient[LK-1].ulica);
    printf("\n\tNumer\t\t%s",klient[LK-1].nr);
    printf("\n\tKod\t\t%s",klient[LK-1].kod);
    printf("\n\tMiasto\t\t%s",klient[LK-1].miasto);




    printf("\n\n\tGeneruje numery pozyczek");                   //fun
    delay(1000);printf("\n\t.");delay(1000);printf("\n\t.");delay(1000);printf("\n\t.");delay(1000);
    klient[LK-1].numer1=LP+1;
    klient[LK-1].numer2=LP+2;
    klient[LK-1].numer3=LP+3;
    klient[LK-1].numer4=LP+4;
    klient[LK-1].numer5=LP+5;
    LP=LP+5;

    system("cls");
    printf("\n\tDane osobowe:");
    printf("\n\tImie\t\t%s",klient[LK-1].imie);
    printf("\n\tNazwisko\t%s",klient[LK-1].nazwisko);
    printf("\n\tPESEL\t\t%s",klient[LK-1].pesel);
    printf("\n\tNr dowodu\t%s",klient[LK-1].dowod);

    printf("\n\n\tAdres:");

    printf("\n\t\t\tul.%s %s",klient[LK-1].ulica,klient[LK-1].nr);
    printf("\n\t\t\t%s",klient[LK-1].kod);
    printf("\n\t\t\t%s",klient[LK-1].miasto);

    printf("\n\n\tNumery pozyczek:");
    printf("\n\t\t\t%d",klient[LK-1].numer1);
    printf("\n\t\t\t%d",klient[LK-1].numer2);
    printf("\n\t\t\t%d",klient[LK-1].numer3);
    printf("\n\t\t\t%d",klient[LK-1].numer4);
    printf("\n\t\t\t%d",klient[LK-1].numer5);

    printf("\n\n\tPrzydzielanie pozyczki");                   //fun
    delay(1000);printf("\n\t.");delay(1000);printf("\n\t.");delay(1000);printf("\n\t.");delay(1000);
    system("cls");

    pom=klient[LK-1].numer1-1;
    pom=LP-5;
    dalej='Y';
    do
    {
        if(dalej=='Y')
        {
            poz[pom].numer=pom+1;
            printf("\n\tPozyczka %d :",nr);
            printf("\n\tKwota \t\t");
            fflush(stdin);
            scanf("%d",&poz[pom].kwota);

            poz[pom].rok=b_rok;
            poz[pom].miesiac=b_miesiac;
            poz[pom].dzien=b_dzien;

            system("cls");
            printf("\n\tPozyczka %d :",nr);
            printf("\n\tKwota \t\t%d",poz[pom].kwota);
            printf("\n\tData zawarcia umowy %d.%d.%d",poz[pom].rok,poz[pom].miesiac,poz[pom].dzien);
            printf("\n\tNa ile miesiecy\t");
            fflush(stdin);
            scanf("%d",&poz[pom].na_ile);

            system("cls");
            printf("\n\tPozyczka %d :",nr);
            printf("\n\tKwota \t\t%d",poz[pom].kwota);
            printf("\n\tData zawarcia umowy %d.%d.%d",poz[pom].rok,poz[pom].miesiac,poz[pom].dzien);
            printf("\n\tNa ile miesiecy\t\t%d",poz[pom].na_ile);
            printf("\n\tNa jaki procent\t");
            fflush(stdin);
            scanf("%f",&poz[pom].procent);

            system("cls");
            printf("\n\tPozyczka %d :",nr);
            printf("\n\tKwota \t\t%d",poz[pom].kwota);
            printf("\n\tData zawarcia umowy %d.%d.%d",poz[pom].rok,poz[pom].miesiac,poz[pom].dzien);
            printf("\n\tNa ile miesiecy\t\t%d",poz[pom].na_ile);
            printf("\n\tNa jaki procent\t\t%.2f",poz[pom].procent);


            printf("\n\tCzy chcesz pobrac kolejna pozyczke? (Y/N)");
            fflush(stdin);
            scanf("%c",&dalej);
            dalej=toupper(dalej);
        }
        else
        {
           poz[pom].numer=pom+1;
           poz[pom].kwota=0;
           poz[pom].rok=0;
           poz[pom].miesiac=0;
           poz[pom].dzien=0;
           poz[pom].na_ile=0;
           poz[pom].procent=0;
        }

    ++nr;
    ++pom;
    }while(nr<=5);

    if(nr==6&&dalej=='Y')
    {
        printf("\n\tNie mozesz pobrac wiecej pozyczek!!");
    }
}

void usun_klienta(void)
{
    int klient_out,l;
    char choice4;
    printf("\n\tPodaj numer klienta: ");
    fflush(stdin);
    scanf("%d",&klient_out);
    --klient_out;

    if(klient_out<LK)
        {
            printf("\n\tDane osobowe:");
            printf("\n\t\t\t%s",klient[klient_out].imie);
            printf("\n\t\t\t%s",klient[klient_out].nazwisko);
            printf("\n\t\t\t%s",klient[klient_out].pesel);
            printf("\n\t\t\t%s",klient[klient_out].dowod);
            printf("\n\n\tAdres:");
            printf("\n\t\t\tul.%s %s",klient[klient_out].ulica,klient[klient_out].nr);
            printf("\n\t\t\t%s",klient[klient_out].kod);
            printf("\n\t\t\t%s",klient[klient_out].miasto);
            printf("\n\n\tNumery pozyczek:");
            printf("\n\t\t\t%d",klient[klient_out].numer1);
            printf("\n\t\t\t%d",klient[klient_out].numer2);
            printf("\n\t\t\t%d",klient[klient_out].numer3);
            printf("\n\t\t\t%d",klient[klient_out].numer4);
            printf("\n\t\t\t%d",klient[klient_out].numer5);

            printf("\n\n\tCzy chcesz usunac? (Y/N)");
            fflush(stdin);
            scanf("%c",&choice4);
            choice4=toupper(choice4);
            if(choice4=='Y')
                {
                    poz[klient[klient_out].numer1-1].kwota=0;
                    poz[klient[klient_out].numer2-1].kwota=0;
                    poz[klient[klient_out].numer3-1].kwota=0;
                    poz[klient[klient_out].numer4-1].kwota=0;
                    poz[klient[klient_out].numer5-1].kwota=0;
                    for(l=klient_out;l<LK;++l)
                    {
                        klient[klient_out]=klient[klient_out+1];
                        klient[klient_out].ident=klient[klient_out].ident-1;
                        ++klient_out;

                        if(l==LK-1)
                            {
                               --LK;
                               printf("\n\nLK=%d\n\n",LK);
                            }
                    }

                }
            system("cls");

         }
         else
            {
                printf("\n\tNie ma klienta o takim numerze");
            }
}

void baza_p(void)
{
    printf("\n\n\tNumer");
    printf("\tKwota");
    printf("\tData pobrania");
    printf("\tNa ile");
    printf("\tNa jaki procent");
    for (i=0;i<LP;++i)
    {
        printf("\n\n\t%d",poz[i].numer);
        printf("\t%d",poz[i].kwota);

        printf("\t%d.%d.%d",poz[i].rok,poz[i].miesiac,poz[i].dzien);

        printf("\t%d",poz[i].na_ile);
        printf("\t%.2f",poz[i].procent);
    }
}

void sort_nazw(void)
{
    int i,j,zamiana=0,zam,m=LK;
    osoba klients[LK];
    osoba pom;
    for(i=0;i<LK;++i)
    {
        klients[i]=klient[i];
    }
    i=0;

    while(i<LK-1&&zamiana==0)
    {
        zamiana=1;
		for (j=0; j<m-1; j++)
		  {
            zam=alfabet(klients[j].nazwisko,klients[j+1].nazwisko);
			if (zam==0)
			{
			    pom = klients[j+1];
			    klients[j+1] = klients[j];
			    klients[j] = pom;
                zamiana=0;
			}
		}
		i++;
		m--;
    }
    system("cls");
    for(i=0;i<LK;++i)
        {
            printf("\n\n\t%d",klients[i].ident);
            printf("  %s",klients[i].imie);
            printf("  %s",klients[i].nazwisko);
        }
}

void sort_kwota(void)
{
    int i,j,zamiana=0,zam,m=LP,LPP=LP,nr;
    bank pozs[LP];
    bank pom;
    for(i=0;i<LP;++i)
    {
        pozs[i]=poz[i];
    }
    i=0;

    while(i<LP-1&&zamiana==0)
    {
        zamiana=1;
		for (j=0; j<m-1; j++)
		  {
            //zam=alfabet(klients[j].nazwisko,klients[j+1].nazwisko);
			if (pozs[j].kwota<pozs[j+1].kwota)
			{
			    pom = pozs[j+1];
			    pozs[j+1] = pozs[j];
			    pozs[j] = pom;
                zamiana=0;
			}
		}
		i++;
		m--;
    }

    for(i=LP;i>0;--i)
    {
        if(pozs[i].kwota==0)
        {
            --LPP;
        }
    }

    system("cls");
    for(i=0;i<LPP;++i)
        {
            printf("\n\n\t%d",pozs[i].kwota);
            nr=pozs[i].numer;
            nr=znajdz(nr);
            printf("\t%s\t%s",klient[nr].imie,klient[nr].nazwisko);
        }
}

void splata_teraz(void)
{
    int i,pom=0;

    for(i=0;i<LK;++i)
    {
        if(poz[klient[i].numer1-1].ile_m_do_spl==1||poz[klient[i].numer2-1].ile_m_do_spl==1||poz[klient[i].numer3-1].ile_m_do_spl==1||poz[klient[i].numer4-1].ile_m_do_spl==1||poz[klient[i].numer5-1].ile_m_do_spl==1||poz[klient[i].numer1-1].na_ile==1||poz[klient[i].numer2-1].na_ile==1||poz[klient[i].numer3-1].na_ile==1||poz[klient[i].numer4-1].na_ile==1||poz[klient[i].numer5-1].na_ile==1)
        {
            printf("\n\t%s\t%s",klient[i].imie,klient[i].nazwisko);
            pom=1;
        }
    }
    if(pom==0)
    {
        printf("\n\n\tNikt nie konczy splacac pozyczki w tym miesiacu\n");
    }
}

void zadluzenie(void)
{
    int i,id;
    for(i=0;i<LK;++i)
    {
        klient[i].dlug=poz[klient[i].numer1-1].ile_do_splaty+poz[klient[i].numer2-1].ile_do_splaty+poz[klient[i].numer3-1].ile_do_splaty+poz[klient[i].numer4-1].ile_do_splaty+poz[klient[i].numer5-1].ile_do_splaty;
    }
    printf("\n\tPodaj numer klienta: \t");
    fflush(stdin);
    scanf("%d",&id);
    --id;
    system("cls");
    printf("\n\n\tImie\t\t%s",klient[id].imie);
    printf("\n\tNazwisko\t%s",klient[id].nazwisko);
    printf("\n\tZadluzenie\t\t%f",klient[id].dlug);
}

void zapisz (void)
{
    FILE *z;
    z=fopen("osoba.txt","w");
    fprintf(z,"%d",LK);

    for(i=0;i<LK;++i)
        {
            fprintf(z,"\n%d",klient[i].ident);
            fprintf(z,"\t%s",klient[i].imie);
            fprintf(z,"\t%s",klient[i].nazwisko);
            fprintf(z,"\t%s",klient[i].pesel);
            fprintf(z,"\t%s",klient[i].dowod);
            fprintf(z,"\t%s",klient[i].ulica);
            fprintf(z,"\t%s",klient[i].nr);
            fprintf(z,"\t%s",klient[i].kod);
            fprintf(z,"\t%s",klient[i].miasto);
            fprintf(z,"\t%d",klient[i].numer1);
            fprintf(z,"\t%d",klient[i].numer2);
            fprintf(z,"\t%d",klient[i].numer3);
            fprintf(z,"\t%d",klient[i].numer4);
            fprintf(z,"\t%d",klient[i].numer5);
        }
    fclose(z);
}

void zapisz_p (void)
{
    FILE *z;
    z=fopen("p.txt","w");
    fprintf(z,"%d",LP);

    for(i=0;i<LP;++i)
        {
            fprintf(z,"\n%d",poz[i].numer);
            fprintf(z,"\t%d",poz[i].kwota);
            fprintf(z,"\t%d",poz[i].rok);
            fprintf(z,"\t%d",poz[i].miesiac);
            fprintf(z,"\t%d",poz[i].dzien);
            fprintf(z,"\t%d",poz[i].na_ile);
            fprintf(z,"\t%f",poz[i].procent);
        }
    fclose(z);
}

void menu(void)
{
    int choice;                 //menu
    int test=0;

    do
    {
        printf("\n\n(1)	Wyswietl baze klientow");
        printf("\n(2)	Modyfikuj dane klienta");
        printf("\n(3)	Dodaj klienta");
        printf("\n(4)	Usun klienta");
        printf("\n(5)	Wyswietl baze pozyczek");
        printf("\n(6)	Wyswietl liste klientow posortowana po nazwisku");
        printf("\n(7)	Wyswietl liste klientow posortowana po wysokosci pozyczki");
        printf("\n(8)	Sprawdz ktorzy sposrod klientow koncza splacac pozyczke w tym miesiacu");
        printf("\n(9)	Sprawdz zadluzenie danego klienta");
        printf("\n(10)	Zapisz");
        printf("\n(11)	Zapisz i zakoncz");
        printf("\n(12)	Zakoncz");
        printf("\n\n\tPodaj numer: ");
        fflush(stdin);
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            {
                baza_k();
                break;
            }
        case 2:
            {
                mod_klienta();
                break;
            }
        case 3:
            {
                dodaj_klienta();
                break;
            }
        case 4:
            {
                usun_klienta();
                break;
            }
        case 5:
            {
                baza_p();
                break;
            }
        case 6:
            {
                sort_nazw();
                break;
            }
        case 7:
            {
                sort_kwota();
                break;
            }
        case 8:
            {
                oblicz();
                splata_teraz();
                break;
            }
        case 9:
            {
                oblicz();
                zadluzenie();
                break;
            }
        case 10:
            {
                zapisz();
                zapisz_p();
                break;
            }
        case 11:
            {
                zapisz();
                zapisz_p();
                choice=12;
                break;
            }
        }
    }
    while(choice!=12);
}

//void pomocnicze
void wielka_litera (char *x)                      // porpawia pierwsza litere na wielka reszta male
{
    int j;
    x[0]=toupper(x[0]);
    j=1;
    while(isalpha(x[j]))
    {
        x[j]=tolower(x[j]);
        j++;
    }
}

int pesel_check (char *x)
{
    int check=0;            //zero = true
    int suma_k=0;           /*suma kontrolna   (zeby nie zaakceptowalo   np: qwertyui9    tylko dlatego ze ostatni warunek sie zgadza)
                              suma_k   zbieznosc nazw z suma kontrolna zawarta w kazdym numerze PESEL
                              funkcja nie sprawdza poprawnosci calego peselu, jedynie wpisana date  */
    int luty;               //czy rok jest przestepny

    check=(x[0]=='0'||x[0]=='1'||x[0]=='2'||x[0]=='3'||x[0]=='4'||x[0]=='5'||x[0]=='6'||x[0]=='7'||x[0]=='8'||x[0]=='9') ? 0:1;
    suma_k=suma_k+check;
    check=(x[1]=='0'||x[1]=='1'||x[1]=='2'||x[1]=='3'||x[1]=='4'||x[1]=='5'||x[1]=='6'||x[1]=='7'||x[1]=='8'||x[1]=='9') ? 0:1;
    suma_k=suma_k+check;
    check=(x[2]=='0'||x[2]=='1') ? 0:1;
    suma_k=suma_k+check;
    if (x[2]=='0')
        {
            check=(x[3]=='1'||x[3]=='2'||x[3]=='3'||x[3]=='4'||x[3]=='5'||x[3]=='6'||x[3]=='7'||x[3]=='8'||x[3]=='9') ? 0:1;
            suma_k=suma_k+check;
        }
    if (x[2]=='1')
        {
            check=(x[3]=='0'||x[3]=='1'||x[3]=='2') ? 0:1;
            suma_k=suma_k+check;
        }
    check=(x[4]=='0'||x[4]=='1'||x[4]=='2'||x[4]=='3') ? 0:1;
    suma_k=suma_k+check;
    if (x[4]=='0')
        {
            check=(x[5]=='1'||x[5]=='2'||x[5]=='3'||x[5]=='4'||x[5]=='5'||x[5]=='6'||x[5]=='7'||x[5]=='8'||x[5]=='9') ? 0:1;
            suma_k=suma_k+check;
        }
    if (x[4]=='1')
        {
            check=(x[5]=='0'||x[5]=='1'||x[5]=='2'||x[5]=='3'||x[5]=='4'||x[5]=='5'||x[5]=='6'||x[5]=='7'||x[5]=='8'||x[5]=='9') ? 0:1;
            suma_k=suma_k+check;
        }
    if (x[4]=='2')
        {
            check=(x[5]=='0'||x[5]=='1'||x[5]=='2'||x[5]=='3'||x[5]=='4'||x[5]=='5'||x[5]=='6'||x[5]=='7'||x[5]=='8'||x[5]=='9') ? 0:1;
            suma_k=suma_k+check;
        }
    if (x[4]=='3')
        {
            check=(x[5]=='0'||x[5]=='1') ? 0:1;
            suma_k=suma_k+check;
        }

    if (x[2]=='0')                          // sprawdznie czy miesiac ma dobra ilosc dni...  (01/02/03/04/05/06/07/08/09)
    {
        if(x[3]=='1'||x[3]=='3'||x[3]=='5'||x[3]=='7'||x[3]=='8')    //31 dniowe miesiace  0x
        {
            if (x[4]=='3')
            {
                check=(x[5]=='0'||x[5]=='1') ? 0:1;
                suma_k=suma_k+check;
            }
        }

        if(x[3]=='4'||x[3]=='6'||x[3]=='9')    //30 dniowe miesiace    0x
        {
            if (x[4]=='3')
            {
                check=(x[5]=='0') ? 0:1;
                suma_k=suma_k+check;
            }
        }

        if(x[3]=='2')    //luty...
        {
            luty=10*(x[0]-48);
            luty=luty+(x[1]-48);
            luty=luty%4;

            if (luty==0)
            {
                check=(x[4]=='0'||x[4]=='1'||x[4]=='2') ? 0:1;
                suma_k=suma_k+check;

                if(x[4]=='2')
                {
                    check=(x[5]=='0'||x[5]=='1'||x[5]=='2'||x[5]=='3'||x[5]=='4'||x[5]=='5'||x[5]=='6'||x[5]=='7'||x[5]=='8'||x[5]=='9') ? 0:1;
                    suma_k=suma_k+check;
                }
            }

            if (luty!=0)
            {
                check=(x[4]=='0'||x[4]=='1'||x[4]=='2') ? 0:1;
                suma_k=suma_k+check;

                if(x[4]=='2')
                {
                    check=(x[5]=='0'||x[5]=='1'||x[5]=='2'||x[5]=='3'||x[5]=='4'||x[5]=='5'||x[5]=='6'||x[5]=='7'||x[5]=='8') ? 0:1;
                    suma_k=suma_k+check;
                }
            }
        }
    }

    if (x[2]=='1')                          // sprawdznie czy miesiac ma dobra ilosc dni...  (10/11/12)
    {
        if(x[3]=='0'||x[3]=='2')    //31 dniowe miesiace  1x
        {
            if (x[4]=='3')
            {
                check=(x[5]=='0'||x[5]=='1') ? 0:1;
                suma_k=suma_k+check;
            }
        }

        if(x[3]=='1')    //30 dniowe miesiace    1x
        {
            if (x[4]=='3')
            {
                check=(x[5]=='0') ? 0:1;
                suma_k=suma_k+check;
            }
        }
    }
    //koniec miesiecy, teraz juz tylko sprawdza czy liczby i czy nie za dlugie...
    check=(x[6]=='0'||x[6]=='1'||x[6]=='2'||x[6]=='3'||x[6]=='4'||x[6]=='5'||x[6]=='6'||x[6]=='7'||x[6]=='8'||x[6]=='9') ? 0:1;
    suma_k=suma_k+check;
    check=(x[7]=='0'||x[7]=='1'||x[7]=='2'||x[7]=='3'||x[7]=='4'||x[7]=='5'||x[7]=='6'||x[7]=='7'||x[7]=='8'||x[7]=='9') ? 0:1;
    suma_k=suma_k+check;
    check=(x[8]=='0'||x[8]=='1'||x[8]=='2'||x[8]=='3'||x[8]=='4'||x[8]=='5'||x[8]=='6'||x[8]=='7'||x[8]=='8'||x[8]=='9') ? 0:1;
    suma_k=suma_k+check;
    check=(x[9]=='0'||x[9]=='1'||x[9]=='2'||x[9]=='3'||x[9]=='4'||x[9]=='5'||x[9]=='6'||x[9]=='7'||x[9]=='8'||x[9]=='9') ? 0:1;
    suma_k=suma_k+check;
    check=(x[10]=='0'||x[10]=='1'||x[10]=='2'||x[10]=='3'||x[10]=='4'||x[10]=='5'||x[10]=='6'||x[10]=='7'||x[10]=='8'||x[10]=='9') ? 0:1;
    suma_k=suma_k+check;
    check=(x[11]==NULL) ? 0:1;
    suma_k=suma_k+check;

    if (suma_k!=0)
    {
        check=1;
    }

    return check;                       //jesli zwraca 0 to znaczy ze sprawdzany pesel jest poprawny (pod katem daty)
}

int dowod_check (char *x)
{
    int check;          //zero = true
    int suma_k=0;

    //litery
    check=(x[0]>=65&&x[0]<=90) ? 0:1;
    suma_k=suma_k+check;
    check=(x[1]>=65&&x[1]<=90) ? 0:1;
    suma_k=suma_k+check;
    check=(x[2]>=65&&x[2]<=90) ? 0:1;
    //cyfry
    check=(x[3]>=48&&x[3]<=57) ? 0:1;
    suma_k=suma_k+check;
    check=(x[4]>=48&&x[4]<=57) ? 0:1;
    suma_k=suma_k+check;
    check=(x[5]>=48&&x[5]<=57) ? 0:1;
    suma_k=suma_k+check;
    check=(x[6]>=48&&x[6]<=57) ? 0:1;
    suma_k=suma_k+check;
    check=(x[7]>=48&&x[7]<=57) ? 0:1;
    suma_k=suma_k+check;
    check=(x[8]>=48&&x[8]<=57) ? 0:1;
    suma_k=suma_k+check;
    check=(x[9]==NULL) ? 0:1;
    suma_k=suma_k+check;

    if (suma_k!=0)
    {
        check=1;
    }

    return check;       //zero = true
}

void ulica_correct (char *x)
{
    int j;

    for(j=0;j<35;j++)
    {
        x[j]=toupper(x[j]);
        ++j;
        while(isalpha(x[j]))
            {
                x[j]=tolower(x[j]);
                j++;
            }
        if (x[j]==32&&isalpha(x[j+1]))
        {
            x[j]='_';
        }
        else
        {
            j=40;
        }
    }

}

int kod_check (char *x)
{
    int check;          //zero = true
    int suma_k=0;

    check=(isdigit(x[0])) ? 0:1;
    suma_k=suma_k+check;
    check=(isdigit(x[1])) ? 0:1;
    suma_k=suma_k+check;

    check=(x[2]=='-') ? 0:1;
    suma_k=suma_k+check;

    check=(isdigit(x[3])) ? 0:1;
    suma_k=suma_k+check;
    check=(isdigit(x[4])) ? 0:1;
    suma_k=suma_k+check;
    check=(isdigit(x[5])) ? 0:1;
    suma_k=suma_k+check;
    check=(x[6]==NULL) ? 0:1;
    suma_k=suma_k+check;

    if (suma_k!=0)
    {
        check=1;
    }

    return check;       //zero = true
}

int alfabet (char *x,char *y)
{
    int i,zam=0;
    x[0]=tolower(x[0]);
    y[0]=tolower(y[0]);

    i=0;
    do
    {
        if(x[i]<y[i])
        {
            zam=1;         //x bardzeij alfabet
        }
        if(x[i]>y[i])
        {
            zam=2;         //y bardziej alfabet
        }
        ++i;
    }while(zam==0);

    if(zam==2)
    {
        zam=0;
    }
    x[0]=toupper(x[0]);
    y[0]=toupper(y[0]);
    return zam;             //1 jesli x, 0 jesli y
}

void oblicz (void)
{
    int pom_m,pom_b;        //pomocniczna liczba miesiecy / ile miesiecy teraz
    pom_b=(b_rok*12)+b_miesiac;

    int i,j;
    for (i=0;i<LP;++i)
    {
        poz[i].rata_kap=(float)poz[i].kwota/(float)poz[i].na_ile;
        //printf("\nrata_kap[%d]=%f",i,poz[i].rata_kap);              //rata kapitalowa

        pom_m=(poz[i].rok*12)+poz[i].miesiac;
        //printf("\npom_m=%d  pom_b=%d",pom_m,pom_b);


        poz[i].ile_m_spl = (poz[i].dzien<b_dzien) ? pom_b-pom_m:pom_b-pom_m-1;
        //printf("\npoz[%d].ile_m_spl=%d",i,poz[i].ile_m_spl);        //ile miesiecy juz splacono


        poz[i].ile_do_splaty=poz[i].kwota;
        if(poz[i].kwota!=0){for(j=0;j<poz[i].ile_m_spl;++j)
        {
            poz[i].odsetki=poz[i].ile_do_splaty*(poz[i].procent/12);
            poz[i].rata_lacz=poz[i].rata_kap+poz[i].odsetki;
            poz[i].ile_do_splaty=poz[i].ile_do_splaty-poz[i].rata_kap;
        }}

        poz[i].ile_m_do_spl=poz[i].na_ile-poz[i].ile_m_spl;
    }
}

void data (void)
{
    printf("\n\tPodaj dzisiejsza date:");
    printf("\n\tRok:");
    fflush(stdin);
    scanf("%d",&b_rok);
    printf("\n\tMiesiac:");
    fflush(stdin);
    scanf("%d",&b_miesiac);
    printf("\n\tDzien:");
    fflush(stdin);
    scanf("%d",&b_dzien);
//    b_rok=2017;
//    b_miesiac=04;
//    b_dzien=22;

}

int znajdz (nr)
{
    int i,pom;

    for(i=0;i<LK;++i)
    {
        if(klient[i].numer1==nr||klient[i].numer2==nr||klient[i].numer3==nr||klient[i].numer4==nr||klient[i].numer5==nr)
        {
            pom=klient[i].ident-1;
            break;
        }
    }

    return pom;
}

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}




int main (void)
{
printf("Loading data");                     //fun
delay(1000);printf("\n\a.");delay(1000);printf("\n\a.");delay(1000);printf("\n\a.");delay(1000);
printf("\nInitializing");
delay(1000);printf("\n.");delay(1000);printf("\n.");delay(1000);printf("\n.");delay(1000);
system("cls");delay(1000);

FILE *f;
f=fopen("osoba.txt","r");
FILE *g;
g=fopen("p.txt","r");

fscanf(f,"%d",&LK);
fscanf(g,"%d",&LP);

for(i=0;i<LK;++i)
{
fscanf(f,"%d",&klient[i].ident);
//printf("\n\nklient[%d].ident=%d",i,klient[i].ident);
fscanf(f,"%s",klient[i].imie);
//printf("\t%s",klient[i].imie);
fscanf(f,"%s",klient[i].nazwisko);
//printf("\t%s",klient[iFILE *f;
fscanf(f,"%s",klient[i].pesel);
//printf("\n%s",klient[i].pesel);
fscanf(f,"%s",klient[i].dowod);
//printf("\n%s",klient[i].dowod);
fscanf(f,"%s",klient[i].ulica);
//printf("\n%s",klient[i].ulica);
fscanf(f,"%s",klient[i].nr);
//printf("\n%s",klient[i].nr);
fscanf(f,"%s",klient[i].kod);
//printf("\n%s",klient[i].kod);
fscanf(f,"%s",klient[i].miasto);
//printf("\n%s",klient[i].miasto);
fscanf(f,"%d",&klient[i].numer1);
//printf("\n%d",klient[i].numer1);
fscanf(f,"%d",&klient[i].numer2);
//printf("\n%d",klient[i].numer2);
fscanf(f,"%d",&klient[i].numer3);
//printf("\n%d",klient[i].numer3);
fscanf(f,"%d",&klient[i].numer4);
//printf("\n%d",klient[i].numer4);
fscanf(f,"%d",&klient[i].numer5);
//printf("\n%d",klient[i].numer5);
}
fclose(f);
for (i=0;i<LP;++i)
{
fscanf(g,"%d",&poz[i].numer);
//printf("\n\n%d",poz[i].numer);
fscanf(g,"%d",&poz[i].kwota);
//printf("\n%d",poz[i].kwota);
fscanf(g,"%d",&poz[i].rok);
//printf("\n%d",poz[i].rok);
fscanf(g,"%d",&poz[i].miesiac);
//printf("\n%d",poz[i].miesiac);
fscanf(g,"%d",&poz[i].dzien);
//printf("\n%d",poz[i].dzien);
fscanf(g,"%d",&poz[i].na_ile);
//printf("\n%d",poz[i].na_ile);
fscanf(g,"%f",&poz[i].procent);
//printf("\n%.2f",poz[i].procent);
}
fclose(g);
data();
oblicz();

system("cls");
menu();

return 0;
}
