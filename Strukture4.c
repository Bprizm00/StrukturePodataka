#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE (1024)

struct _polinom;
typedef struct _polinom *Position;
typedef struct _polinom{
    int coeff;
    int exp;
    Position next;
}Polinom;

int ReadFromFile(Position head1, Position head2, char* Polinomi);
void PrintList(Position head);
int AddPoly(Position resultA, Position head1, Position head2);
Position CreateElement(int coeff, int expt);
int InsertSort(Position head, Position newElement);
int MultiplyPoly(Position result, Position head1, Position head2);

int main(){
    Polinom head1 = {
        .coeff = 0,
        .exp = 0,
        .next = NULL
    };
    Polinom head2 = {
        .coeff = 0,
        .exp = 0,
        .next = NULL
    };
    Polinom resultM = {
        .coeff = 0,
        .exp = 0,
        .next = NULL
    };
    Polinom resultA = {
        .coeff = 0,
        .exp = 0,
        .next = NULL
    };

    
    ReadFromFile(&head1, &head2, "Polinomi.txt");
    printf("First polynomial is:\n");
    PrintList(&head1);
    printf("Second polynomial is:\n");
    PrintList(&head2);

    MultiplyPoly(&resultM, &head1, &head2);
    printf("Umnozak polinoma glasi:\n");
    PrintList(&resultM);

    AddPoly(&resultA, &head1, &head2);
 
    return 0;
}

int ReadFromFile(Position head1, Position head2, char* Polinomi)
{
    char buffer[MAX_LINE] = { 0 };
    char* p = NULL;
    int coeff = 0;
    int exp = 0;
    int n = 0;
    Position newElement = NULL;
    

    FILE* fp = NULL;
    fp = fopen(Polinomi, "r");

    if(!fp){
        perror("Datoteka nije pronadena!n");
        return EXIT_FAILURE;
    }
    
    
    fgets(buffer, MAX_LINE, fp);
    p = buffer;
    while(strlen(p) > 0){
        sscanf(p, "%d %d %n", &coeff, &exp, &n);
        newElement = CreateElement(coeff, exp);
        if(!newElement)
        {
            perror("No memmory\n");
            return EXIT_FAILURE;
        }
        InsertSort(head1, newElement);
        p += n;
    }
    

    fgets(buffer, MAX_LINE, fp);
    p = buffer;
    while(strlen(p) > 0){
        sscanf(p, "%d %d %n", &coeff, &exp, &n);
        InsertSort( head2, CreateElement(coeff, exp));
        p += n;
    }


    fclose(fp);

    return EXIT_SUCCESS;
}

Position CreateElement(int coeff, int exp)
{
	Position element = NULL;

	element = (Position)malloc(sizeof(Polinom));
	if (!element)
	{
		perror("Greska pri alociranju memorije!\n");
		return EXIT_FAILURE;
	}

	element->coeff = coeff;
	element->exp = exp;
	element->next = NULL;

	return element;
}

int InsertSort(Position head, Position newElement)
{
    Position temp = NULL;

    if(head == NULL || head->exp > newElement->exp)
    {
        newElement->next = head;
        head = newElement;
    }
    else
    {
        temp = head;
        while(temp->next != NULL && temp->next->exp > newElement->exp)
            temp = temp->next;
        newElement->next = temp->next;
        temp->next = newElement;    
    }


    return EXIT_SUCCESS;
}

void PrintList(Position head)
{
    Position temp = head->next;

    while(temp != NULL)
    {
        printf(" %dx^(%d) ", temp->coeff, temp->exp);
        temp = temp->next;
    }

    printf("\n");
}

int AddPoly(Position resultA, Position head1, Position head2)
{   Position result = resultA;
    Position p1 = head1->next;
    Position p2 = head2->next;

    while(p1 != NULL && p2 != NULL)
    {
        if(p1->exp == p2->exp)
        {
            InsertSort(result, CreateElement(p1->coeff + p2->coeff, p1->exp));
            p1 = p1->next;
            p2 = p2->next;
        }
        else if(p1->exp > p2->exp)
        {
            InsertSort(result, CreateElement(p1->coeff, p1->exp));
            p1 = p1->next;
        }
        else if(p1->exp < p2->exp)
        {
            InsertSort(result, CreateElement(p2->coeff, p2->exp));
            p2 = p2->next;
        }       

    }

    while(p1 != NULL)
    {
        InsertSort(result, p1);
        p1 = p1->next;
    }

    while(p2 != NULL)
    {
        InsertSort(result, head2);
        p2 = p2->next;
    }

    printf("Zbroj polinoma glasii:\n");
    PrintList(result);

    return EXIT_SUCCESS;
}

int MultiplyPoly(Position result, Position head1, Position head2)
{
	Position i = NULL;
	Position j = NULL;
    Position newElement = NULL;

    newElement = (Position)malloc(sizeof(Polinom));

    if (!newElement)
	{
		perror("Nije moguce alocirati memoriju!\n");
        return EXIT_FAILURE;
	}

	for (i = head1->next; i != NULL; i = i->next)
	{
		for (j = head2->next; j != NULL; j = j->next)
		{
			newElement = CreateElement(i->coeff * j->coeff, i->exp + j->exp);
			
			InsertSort(result, newElement);
		}
	}
	return EXIT_SUCCESS;
}