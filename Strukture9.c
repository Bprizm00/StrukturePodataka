#include <stdio.h>
#include <stdlib.h>
#define space 5

struct treeNode;
typedef struct treeNode* TreeNodePtr;

typedef struct treeNode{
    int data;
    TreeNodePtr left;
    TreeNodePtr right;
}TreeNode;

TreeNodePtr CreateNewNode(int data);
TreeNodePtr Insert(TreeNodePtr root, int data);
int InorderPrint(TreeNodePtr root);
int Replace(TreeNodePtr root);
//void draw_tree_hor2(TreeNodePtr root, int distance);
//void draw_tree_hor(TreeNodePtr root);

int main(){
    TreeNodePtr root = NULL;
    //TreeNodePtr temp = NULL;
    int a[10] = {2,5,7,8,11,1,4,2,3,7};
    int n = 10;
    int i = 0;
    int choice = 1;

    for(i = 0; i < n; i++){
        root = Insert(root, a[i]);
    }

    while(choice != 0){
        printf("\n Pritisnite tipku 1 za ispis stabla\n ");
        printf("Pritisnite tipku 2 za izmjenu stabla\n ");
        scanf(" %d", &choice);

        switch(choice){

            case 0:
                printf("Prekid programa\n");
                break;

            case 1:
                if (root == NULL){
                    printf("Tree is empty!\n");
                    return EXIT_SUCCESS;
                }

                InorderPrint(root);
                break;

            case 2:
                if (root == NULL){
                    printf("Tree is empty!\n");
                    return EXIT_SUCCESS;
                }  
                printf("Ispis\n");
                Replace(root);
               // root = Insert(root, root->data);
                InorderPrint(root);
                break;

            default:
                printf("Wrong choice!\n");
                break;    

        }
    }


    return 0;
}

TreeNodePtr CreateNewNode(int data)
{   TreeNodePtr newNode = NULL;

    newNode = (TreeNodePtr)malloc(sizeof(TreeNode));

    if(!newNode){
        printf("Can not allocate memory!\n");
        return NULL;
    }

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

TreeNodePtr Insert(TreeNodePtr root, int data)
{   if(root == NULL){
        root = CreateNewNode(data);
    }

    else if(data > root->data){
        root->left = Insert(root->left, data);
    }

    else if(data <= root->data){
        root->right = Insert(root->right, data);
    }
    
    

    return root;
}

int InorderPrint(TreeNodePtr root)
{   
    if(root != NULL){
    InorderPrint(root->left);
    printf("%d ", root->data);
    InorderPrint(root->right);
    }

    return EXIT_SUCCESS;
}


int Replace(TreeNodePtr root)
{   int old = 0;
    // base case: empty tree
    if (root == NULL) {
        return 0;
    }
 
    // special case: leaf node
    if (root->left == NULL && root->right == NULL) {
        old = root->data;
        root->data = 0;
        return old ;
    }

    int left = Replace(root->left);
    int right = Replace(root->right);
 
    //old = root->data;

    root->data = left + right;

	return root->data ;
}


/*int Replace(TreeNodePtr root)
{
    TreeNodePtr temp1 = NULL;
    TreeNodePtr temp2 = NULL;
    //TreeNodePtr temp = NULL;
    int Pribrojnik1 = 0, Pribrojnik2 = 0, suma = 0;
    int old = 0;

    temp1 = (TreeNodePtr)malloc(sizeof(TreeNode));
    temp2 = (TreeNodePtr)malloc(sizeof(TreeNode));
    //temp = (TreeNodePtr)malloc(sizeof(TreeNode));

    if(!temp1){
        perror("Can not allocate memory\n");
        return -1;
    }

    if(root == NULL)
        return 0;

    while(root->left != NULL || root->right != NULL){
        if(root->left != NULL){
            temp1->data = Replace(root->left);
            old = temp1->data;
            Pribrojnik1 = temp1->left->data;
            temp1->left->data = 0;
        }
        else 
            Pribrojnik1 = 0;
        if(temp1->right != NULL){
            //temp2->data = Replace(root->right->data);
            temp2 = temp1->right;
            Pribrojnik2 = temp2->data;
            temp2->data = 0;
        }
        else 
            Pribrojnik2 = 0;
    }    
    suma = Pribrojnik1 + Pribrojnik2;
    temp1->data = suma;

    return suma + old;
}*/


/*int Replace(TreeNodePtr root){

    int leftSum = 0, rightSum = 0, old = 0;

	if (root == NULL)
        return 0;
	
    leftSum =  Replace(root->left);

	rightSum = Replace(root->right);


    
	old = root->data;

    root->data = leftSum + rightSum;

	return root->data + old;
}*/

/*TreeNodePtr Replace(TreeNodePtr root)
{   TreeNodePtr temp1 = NULL;
    TreeNodePtr temp2 = NULL;
    TreeNodePtr temp = NULL;
    int pribrojnik1 = 0, pribrojnik2 = 0;
    int suma = 0;

    temp1 = (TreeNodePtr)malloc(sizeof(TreeNode));
    temp2 = (TreeNodePtr)malloc(sizeof(TreeNode));

    if(root != NULL){
       
        temp = CreateNewNode(root->data);  //ili temp = root;
       
        if(root->left != NULL || root->right != NULL){
            temp1 = root->left;
            temp2 = root->right;
        

                if(temp1->left == NULL && temp1->right == NULL){
            
                    pribrojnik1 = temp1->data;
                    temp1->left->data = temp1->right->data = 0;
                }
                else{
                    temp = temp1;
                    temp = Replace(temp); // ili root = ...
                }
                if(temp2->left == NULL && temp2->right == NULL){

                    pribrojnik2 = temp2->data;
                    temp2->left->data = temp2->right->data = 0;
                }    
                else{
                    temp = temp2;
                    temp = Replace(temp);
                }
        }
        suma = pribrojnik1 + pribrojnik2;
        temp->data = suma;        
        return temp;   
    }
   
   return temp; 
}*/

