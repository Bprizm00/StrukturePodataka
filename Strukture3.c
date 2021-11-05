#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE (1024)

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
int InsertBefore(Position position, Position newPerson, char* surname);
int InsertPersonAfter(Position position, Position newPerson, char* surname);
int WriteToFile(char* fileName, Position first);
int ReadFromFile(char* List, Position first);
void Sort(Position first);

int main(){
    Person Head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0};
    Position p = &Head;

    int choice = 1;
    char name[MAX_SIZE] = {0};
    char surname[MAX_SIZE] = {0};
    char wanted[MAX_SIZE] = {0};
    char fileName[MAX_SIZE] = {0};
    int birthYear = 0;
    char* List = NULL;
    Position Person;

        printf("---------------MENI---------------\n");
        printf("Tipka 1  -  Unos elementa na pocetak liste\n");
        printf("Tipka 2  -  Unos elementa na kraj liste\n");
        printf("Tipka 3  -  Ispis liste\n");
        printf("Tipka 4  -  Pronalazak elementa po prezimenu\n");
        printf("Tipka 5  -  Brisanje elementa iz liste\n");
        printf("Tipka 6  -  Unos novog elementa iza odredenog clana\n");
        printf("Tipka 7  -  Unos novog elementa ispred odredenog clana\n");
        printf("Tipka 8  -  Sortiranje liste po prezimenima\n");
        printf("Tipka 9  -  Upisivanje liste u datoteku\n");
        printf("Tipka 10  - Citanje liste iz datoteke\n");
        printf("Tipka 0  -  Prekid programa\n");
    
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

                case 6: 
                    printf("Unesite prezime studenta iza kojeg zelite unijeti novi clan\n");
                    scanf(" %s", wanted);

                    printf("Unesite ime novog studenta:\n");
                    scanf(" %s", name);
                    printf("Unesite prezime novog studenta:\n");
                    scanf(" %s", surname);
                    printf("Unesite godinu rodjenja novog studenta:");
                    scanf("%d", &birthYear);
                    
                    Person = CreatePerson(name, surname, birthYear);
                    InsertPersonAfter(p, Person, wanted);

                    printf("Student dodan u listu!\n");
                    break;

                case 7:
                    printf("Unesite prezime studenta ispred kojeg zelite unijeti novi clan\n");
                    scanf(" %s", wanted);

                    printf("Unesite ime novog studenta:\n");
                    scanf(" %s", name);
                    printf("Unesite prezime novog studenta:\n");
                    scanf(" %s", surname);
                    printf("Unesite godinu rodjenja novog studenta:");
                    scanf("%d", &birthYear);
                    
                    Person = CreatePerson(name, surname, birthYear);
                    InsertBefore(p, Person, wanted);

                    printf("Student dodan u listu!\n");
                    break;

                case 8:
                    Sort(p);
                    break;    

                case 9:
                    printf("Unesite ime datoteke: \n");
                    scanf(" %s", fileName);

                    WriteToFile("fileName.txt", p );
                    break;

                case 10:
                    ReadFromFile("List.txt", p);
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
        return EXIT_FAILURE;
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
    int brojac = 0;
    while(temp)
    {
        if(strcmp(temp->surname, surname) == 0)
        {
            printf("Student pronaden!\n");
            brojac++;
        return temp;
        }
        temp = temp->next;
        
    }
    if(!brojac)
    printf("Student nije pronaden\n");
    return EXIT_FAILURE;
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

int InsertBefore(Position position, Position newPerson, char* surname){
    Position q = newPerson;
    Position p = position;    
    int brojac = 0;
    while(p->next != NULL && (strcmp(p->next->surname, surname) != 0))
        p = p->next; 
        if(p != NULL)//jer ulazi ovaj p->next od gore
        {
            q->next = p->next;
            p->next = q;
            
            brojac++;
            //InsertAfter(p, newPerson);
            printf("Uspjeh ");
            return 0;
        }
        //p = p->next;  
      
        if(!brojac)
        {
            printf("Greska student ne postoji\n");
            return NULL;
        }  
     
    
}
int InsertPersonAfter(Position position, Position newPerson, char* surname)
{
    Position q = newPerson;
    Position p = position;    
    int brojac = 0;
   

    while(p->next != NULL && (strcmp(p->next->surname, surname) != 0))
        p = p->next; 
        if(p != NULL)//jer ulazi ovaj p->next od gore
        {
            q->next = p->next->next;
            p->next->next = q;
            
            brojac++;

            printf("Uspjeh ");
            return 0;
        }
        //p = p->next;  
      
        if(!brojac)
        {
            printf("Greska student ne postoji\n");
            return NULL;
        }  
       
}

int WriteToFile(char* fileName, Position first)
{   FILE* fp = NULL;
    fp = fopen(fileName, "w");
    Position temp = NULL;
    temp = first;
    
    if(!fp){
        perror("Nema me!\n");
        return EXIT_FAILURE;
    }
    fprintf(fp," NAME\t\tSURNAME\t\t\tBIRTH YEAR\t\t\n");
    fprintf(fp,"==================================================================\n");
    while(temp){
        fprintf(fp, " %-15s %-25s %d.\n", temp->name, temp->surname, temp->birthYear);
        temp = temp->next;
    }

    printf("Upis u datoteku uspjesno izvrsen\n");

    fclose(fp);

    return EXIT_SUCCESS;
}

int ReadFromFile(char* List, Position first)
{   char name[MAX_SIZE] = {0};
    char surname[MAX_SIZE] = {0};
    int birthYear = 0;
    char buffer[MAX_SIZE] = {0};
    Position temp = NULL;
    temp = first;
    
    FILE* fp = NULL;
    fp = fopen(List , "r");
    

    if(!fp){
        perror("Nema me!\n");
        return EXIT_FAILURE;
    }

    while(!feof(fp)){
            //fgets(buffer, MAX_SIZE, fp);
            fscanf(fp, " %s %s %d.", name, surname, &birthYear);
            AppendList(temp, name, surname, birthYear);         
    }

    printf("Podaci upisani u listu\n");
    fclose(fp);

    return EXIT_SUCCESS;
}

void Sort(Position first)
{   Position previous = NULL;
    Position current = NULL;
    Position temp = NULL;
    Position end;

    end = NULL;

    while(first->next != end)
    {
        previous = first;
        current = first->next;
        while(current->next != end)
        {
            if(strcmp(current->surname, current->next->surname) > 0)
            {
                temp = current->next;
                previous->next = temp;
                current->next = temp->next;
                temp->next = current;

                current = temp;
            }
            previous = current;
            current = current->next;
        }
        end = current;
    }
    printf("Lista uspjesno sortirana\n");
    return EXIT_SUCCESS;
}
