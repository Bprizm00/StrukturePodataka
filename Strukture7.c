#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _stablo;
typedef struct _stablo* pos;
struct _stog;
typedef struct _stog* pos2;

typedef struct _stablo
{
   char ime[10];

   pos child;
   pos next;
}stablo;

typedef struct _stog
{
   pos element;

   pos2 next;
}stog;

pos CreateNode();
int Menu();
int NapraviDir(pos,char*);
int IspisiDir(pos,char*);
pos FindLast(pos );
pos PromijeniDir(pos, char*, pos2);
pos2 CreateNode2();
int PushStog(pos2, pos);

int main()
{
	pos s=NULL;
	pos2 p=NULL;
	int a=0;
	int izbor;
	char ime[100];

	p=CreateNode2();
	if(p==NULL)
	{
		printf("Neusjesno alocirana memorija\n");
		return NULL;
	}

	p->next=NULL;
	p->element=NULL;
	
	s=CreateNode();

	if(s==NULL)
	 {
		 printf("Memorija nije dobro alocirana\n");
		 return -1;
	 }

	s->next=NULL;
	s->child=NULL;

	printf("Unesite ime vaseg osnovnog direktorija\n");
	scanf(" %s", s->ime);

	izbor=Menu();

do{ 
	while(izbor!=1 && izbor!=2 && izbor!=3 && izbor!=0)
		{
			printf("Niste unijeli dobar izbor, ponovite\n");
	        scanf("%d", &izbor);
	    }

 
	switch(izbor)  
	  {
	   case 1:
		    {
				printf("Unesite ime novog direktorija\n");
		        scanf("%s", &ime);
				NapraviDir(s, ime);
				izbor=Menu();
				break;  
			}

	    case 2:
			{
				 IspisiDir(s, s->ime);
				 izbor=Menu();
				 break; 
			 }

		case 3:
			{   printf("Napisite ime poddirektorija u kojeg zelite uci?\n");
			    scanf(" %s",ime);
				s=PromijeniDir(s, ime, p);
				izbor=Menu();
			    break;
			}

	    default:
		    {   a++;
		        system("cls");
			    printf("\nUgodan ostatak dana.\n\n");
		        break;
		    }
	  
  }

 }while(a==0);



return 0;
}

pos CreateNode()
{ pos q;
  q=(pos) malloc(sizeof(stablo));

  if(q==NULL)
	  return NULL;

  return q;
}

pos2 CreateNode2()
{ pos2 q;
  q=(pos2) malloc(sizeof(stog));

  if(q==NULL)
	  return NULL;

  return q;
}

int Menu()
{ int izbor;

  printf("\n\n***********\t\tM E N U\t\t***********\n\n");
  printf("Unesite broj za naredbu koju zelite izvrsiti\n");
  printf("1) za StvoriDir\n");
  printf("2) za IspisiDir\n");
  printf("3) za PromijeniDir\n");
  printf("0) Za zavrsetak s radom\n");

  scanf("%d", &izbor);


return izbor;
}

pos FindLast(pos p)
{
	while(p->next!=NULL)
		p=p->next;

    return p;
}

int NapraviDir (pos s, char* ime)
{  pos q;
   pos temp;
   pos l;
   q=CreateNode();

   if(q==NULL)
	   return -1;

   q->next=NULL;
   q->child=NULL;

   temp=s->child;
   while(temp!=NULL && strcmp(ime, temp->ime))
	   temp=temp->next;

   if(temp!=NULL)
	   {   
		   system("cls"); //da se ocisti ekran
		   printf("Ne mozete unijeti dir s imenom koje vec postoji!\n");
           return -1;
       }

   strcpy(q->ime, ime);

   if(s->child==NULL)
	  s->child=q;
   
   
   else
   {   
	   l= FindLast(s->child);



	   q->next = l->next; 
	   l->next = q; 
   }

   return 0;
}

int IspisiDir (pos s, char* ime_dir)
{   
	system("cls");
	printf("Vas direktorij %s: \n", ime_dir);
    s=s->child;

	while(s!=NULL)
		{
			printf("%s\t", s->ime);
		       s=s->next;
	       }

	return 0;
}

pos PromijeniDir(pos s, char* ime, pos2 p)
{   pos temp;
	temp=s->child;

	while(temp!=NULL && strcmp(temp->ime,ime))
		temp=temp->next;

	if(temp==NULL)
		{
			printf("Ne postoji poddirektorij s tim imenom!\n");
			return s;
	       }
	
	PushStog(p, s);

	return temp;

	return 0;

}

int PushStog(pos2 p, pos s)
{ pos2 q;
  q=CreateNode2();

  if(q==NULL)
  {
	  printf("Neuspjesno alocirana memorija\n");
	  return -1;
  }

  q->next=NULL;
  q->element=s;

  q->next=p->next;
  p->next=q;

 return 0;
}
