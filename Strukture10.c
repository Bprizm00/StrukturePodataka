#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)

struct link;
struct treeNode;

typedef struct link* LinkPtr;
typedef struct treeNode* TreeNodePtr;

typedef struct link
{
    char state[MAX_SIZE]; 
    TreeNodePtr tree; 
    LinkPtr next; 
} Link;

typedef struct treeNode{
	char city[MAX_SIZE];
    int citizens;
    TreeNodePtr left;
    TreeNodePtr right;
}TreeNode;


int LoadCountries(char* dat, LinkPtr head);
int InsertCountry(LinkPtr head, LinkPtr noviEl, char* datGradovi);
int CreateATree(char* datGradovi, LinkPtr drzava);
TreeNodePtr InsertCity(TreeNodePtr root, TreeNodePtr newElement);
LinkPtr CreateCountry(char* stateName);
TreeNodePtr CreateCity(char* cityName, int citizens);


int main()
{
    LinkPtr head;

    int LoadCountries("drzave.txt", &head);

    return 0;
}

int LoadCountries(char* fp, LinkPtr head)
{
    FILE* fp = NULL;
    char buffer[MAX_SIZE] = {0};
    char imeDr[MAX_SIZE] = {0};
    char imeDat[MAX_SIZE] = {0};
    TreeNodePtr root = NULL;

    fp = fopen(fp, "r");

    if(!fp)
    {
        printf("Cannot open file\n");
        return 1;
    }

    while(!feof)
    {
        fgets(buffer, MAX_SIZE, fp);
        sscanf(buffer, " %s %s", imeDr, imeDat);
        InsertCountry(head, CreateCountry(imeDr);
    }

    fclose(fp);

    return 0;
}

int InsertCountry(LinkPtr head, LinkPtr newElement, char* datGradovi)
{
    LinkPtr p = head;

    while(p->next != NULL)
    {
        p = p->next;
    }

    p->next = newElement;
    newElement->next = NULL;

    CreateAndLoadTree(datGradovi, newElement);

    return 0;
}

int CreateAndLoadTree(char* datGradovi, LinkPtr state)
{
    FILE* fp = NULL;

    fp = fopen(datGradovi, "r");


}

TreeNodePtr InsertCity(TreeNodePtr root, TreeNodePtr newElement) 
{
    if(!root)
        return newElement;
    else if(newElement->citizens > root->citizens) 
        root->right = InsertCity(root->right, newElement);
    else if(newElement->citizens < root->citizens)
        root->left = InsertCity(root->left, newElement);
    else if(newElement->citizens == root->citizens) 
    {
        if(strcmp(newElement->city, root->city) < 0)
            root->left = InsertCity(root->left, newElement);
        else
            root->right = InsertCity(root->right, newElement);
    }

    return root;
}

LinkPtr CreateCountry(char* stateName)
{
    LinkPtr state = NULL;

    state = (LinkPtr)malloc(sizeof(Link));

    if(!state)
    {
        printf("Cannot allocate memory\n");
        return NULL;
    }

    strcpy(state->state, stateName);
    state->next = NULL;
    state->tree = NULL;

    return state;
}

TreeNodePtr CreateCity(char* cityName, int citizens)
{
    TreeNodePtr city = NULL;

    city = (TreeNodePtr)malloc(sizeof(TreeNode));

    if(!city)
    {
        printf("Cannot allocate memory\n");
        return NULL;
    }

    strcpy(city->city, cityName);
    city->citizens = citizens;
    city->right = NULL;
    city->left = NULL;

    return city;
}