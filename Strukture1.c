#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#define MAX_SIZE (128)
#define MAX_LINE (1024)

typedef struct _student{
    char ime[MAX_SIZE];
    char prezime[MAX_SIZE];
    int bodovi;
} student;

int ProcitajBrojRedakaIzDatoteke(char* Podaci);
student* AlocirajMemorijuIProcitajStudente(int brojStudenata, char* Podaci);
int maxBrojBodova(int brojStudenata, student* studenti );
void ispisPodataka(int brojStudenata, int maxBrBodova, student* studenti);

int main(){
    int brojStudenata = 0;
    int maxBrBodova = 0;
    student* studenti = NULL;

    brojStudenata = ProcitajBrojRedakaIzDatoteke("Podaci.txt");
    studenti = AlocirajMemorijuIProcitajStudente(brojStudenata, "Podaci.txt");
    maxBrBodova = maxBrojBodova(brojStudenata, studenti);
    
    ispisPodataka(brojStudenata, maxBrBodova, studenti);

    return 0;
}
int ProcitajBrojRedakaIzDatoteke(char* Podaci){
    int brojac = 0;
    FILE* fp = NULL;
    char buffer[MAX_LINE] = {0};

    fp = fopen(Podaci, "r");

    if(!fp){
        printf("Greska!");
        return -1;
    } 

    while (!feof(fp)){
          fgets(buffer, MAX_LINE, fp);
          brojac++;
    }

    fclose(fp);

    return brojac;
}
student* AlocirajMemorijuIProcitajStudente(int brojStudenata, char* Podaci){
    FILE* fp = NULL;
    student* studenti = NULL;
    int brojac = 0;

    studenti = (student*)malloc(brojStudenata * sizeof(student));
    fp = fopen(Podaci, "r");

    if(!fp){
         printf("Greska pri alociranju!\n");
         free(studenti);
         return -1;
    }

    while(!feof(fp)){
        fscanf(fp, " %s %s %d", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);
        brojac++;
    }

    fclose(fp);

    return studenti;
}
int maxBrojBodova(int brojStudenata, student* studenti )
{
    int maxBrBodova = 0;
    int i = 0;

    maxBrBodova = studenti[0].bodovi;

    for(i=1 ; i<brojStudenata; i++){
        if(studenti[i].bodovi > maxBrBodova)
        maxBrBodova = studenti[i].bodovi;
    }

    return maxBrBodova;
}
void ispisPodataka(int brojStudenata, int maxBrBodova, student* studenti){
    double relativniBrojBodova = 0.0;
    int i = 0;


    printf("\n IME\tPREZIME\tBODOVI\tRELATIVNI \n ");
    for(i = 0; i < brojStudenata; i++){
        relativniBrojBodova = (double)studenti[i].bodovi / maxBrBodova * 100;
        printf("\n %s\t%s\t%d\t%.2lf\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, relativniBrojBodova);
    }
}