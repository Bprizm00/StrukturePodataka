#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 50

struct _Person;
typedef struct _Person* Position;

typedef struct _Person{
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthYear;
    Position next;
}Person;

int PrependList(Position head, char* name, char* surname, int birthYear);
void PrintList(Position P);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position head);
int AppendList(Position head, char* name, char* surname, int birthYear);
int FindBySurname(Position first, char* surname);
Position FindBefore(Position P, char* surname);
int DeleteAfter(Position position, char* surname);

int main(){
    Person Head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0};
    Position p = &Head;

    int choice = 1;
    char name[MAX_SIZE] = {0};
    char surname[MAX_SIZE] = {0};
    int birthYear = 0;
    char person = 

        printf("----------MENI---------\n");
        printf("Tipka 1 - Unos elementa na pocetak liste\n");
        printf("Tipka 2 - Unos elementa na kraj liste\n");
        printf("Tipka 3 - Ispis liste\n");
        printf("Tipka 4 - Pronalazak elementa po prezimenu\n");
        printf("Tipka 5 - Brisanje elementa iz liste\n");
        printf("Tipka 0 - Prekid programa\n");
    
    while(choice != 0){

        scanf("%d", &choice);

        switch(choice)
            {
                case 0: 
                    printf("Program prekinut!\n");
                    break;

                case 1: 
                    printf("Unesite ime studenta:\n");
                    scanf(" %s", name);
                    printf("Unesite prezime studenta:\n");
                    scanf(" %s", surname);
                    printf("Unesite godinu rodjenja studenta:");
                    scanf("%d", &birthYear);    

                    PrependList(p, name, surname, birthYear);
                    printf("Student uspjesno dodan na pocetak liste!");
                    break;

                case 2:
                    printf("Unesite ime studenta:\n");
                    scanf(" %s", name);
                    printf("Unesite prezime studenta:\n");
                    scanf(" %s", surname);
                    printf("Unesite godinu rodjenja studenta:");
                    scanf("%d", &birthYear);    

                    AppendList(p, name, surname, birthYear);
                    printf("Student uspjesno dodan na kraj liste!");
                    break; 

                case 3:
                    PrintList(p);   
                    break;

                case 4:
                    printf("Unesite prezime studenta kojeg trazite\n");
                    scanf(" %s", surname);

                    FindBySurname(p, surname);
                    break;
                case 5: 
                    printf("Unesite prezime studenta kojeg zelite izbrisati\n");
                    scanf(" %s", surname);

                    DeleteAfter(p, surname);
                    printf("Stuent izbrisan iz liste \n");
                    break;

            }
    }

    return 0;
}

void PrintList(Position P){
    P = P->next;
    printf(" NAME\t\tSURNAME\t\t\tBIRTH YEAR\t\t\n");
    printf("==================================================================\n");
     while(P != NULL){
         printf(" %-15s %-25s %d.\n", P->name, P->surname, P->birthYear);
         P = P->next;
     }
}

Position CreatePerson(char* name, char* surname, int birthYear){
    Position newPerson = NULL;

    newPerson = (Position)malloc(sizeof(Person));

    if(!newPerson){
        printf("Greska pri alociranju memorije!\n");
        return -1;
    }

    strcpy(newPerson->name, name);
    strcpy(newPerson->surname, surname);
    newPerson->birthYear = birthYear;
    newPerson->next = NULL;

    return newPerson;
}

int PrependList(Position head, char* name, char* surname, int birthYear) //dodaj na pocetak iste
{   Position newPerson = NULL;
    
    newPerson = CreatePerson(name, surname, birthYear);

    if(!newPerson){
        return EXIT_FAILURE;
    }

    InsertAfter(head, newPerson);

    return EXIT_SUCCESS;
}

int InsertAfter(Position position, Position newPerson){
    newPerson->next = position->next;
    position->next = newPerson;

    return EXIT_SUCCESS;
}

Position FindLast(Position head){
    Position temp = head;

    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    return temp;
}

int AppendList(Position head, char* name, char* surname, int birthYear)
{
    Position newPerson = NULL;
    Position last = NULL;

    newPerson = CreatePerson(name, surname, birthYear);

    if(!newPerson)
    {
        return EXIT_FAILURE;
    }

    last = FindLast(head);
    InsertAfter(last, newPerson);
    
    return EXIT_SUCCESS;
}

int FindBySurname(Position first, char* surname)
{
    Position temp = first;

    while(temp)
    {
        if(strcmp(temp->surname, surname) == 0);
        return temp;
    }

    return NULL;
}

Position FindBefore(Position P, char* surname)
{
    Position Previous;
    Previous = P;
    P = P->next;

    while(P != NULL && (strcmp(P->surname, surname) != 0))
    {
        Previous = P;
        P = P->next;
    }

    if(P == NULL)
        return NULL;
    else
        return Previous;
}

int DeleteAfter(Position position, char* surname)
{
    Position temp;
    Position previous;

    previous = FindBefore(position,surname);

    if(previous == NULL)
        printf("Greska!\n");
    else
    {
        temp = previous->next;
        previous->next = previous->next->next;
        free(temp);
    }    
    return EXIT_SUCCESS;
}