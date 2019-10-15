#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct node
{
    struct node *left;
    struct node *right;
    char data[10];
};

void findPreSuc(struct node* root, struct node** pre,  struct node** suc, char key[]);
struct node* newNode(char key[]);
void inorder(struct node *root);
struct node* insert(struct node* node, char key[]);
int size(struct node *root);
int  MAX(int h1, int h2);
int search(struct node *root, char d[]);
struct node* leaf (struct node* root,char word[]);
struct node * minNode(struct node* node);
struct node * Successor(struct node *root, struct node *n);
struct node * predeccessor(struct node *root, struct node *n);
struct node * maxNode(struct node* node);

int main()
{

    FILE * fp = fopen("Dictionary.txt","r");
    if (fp == NULL)
    {
        printf("File not found!");
        exit(0);
    }
    char  Word[50];
    char str[50];

    const char d[2] = " ";
    char * token;

    struct node *root = NULL;



    //inserting first word in the root
    fscanf(fp,"%s",Word);
    root = insert(root, Word);
    struct node *temp = root;
    struct node *temp2 = NULL;

    //inserting the rest of the tree
    while(!feof(fp))
    {
        fscanf(fp,"%s",Word);
        insert(root,Word);
    }

    //making sure its working
    printf("The size of the tree: %d\n",size(root));
    printf("The height of the tree:%d\n",height(root));
    //forgot to add close it guess that's why the program would not run sometimes
    fclose(fp);
    while(1)
    {
        //getting input from user and putting in a tokenizer and making delimiter space
        gets(str);
        token= strtok(str,d);

        while(token)
        {
            if(search(root,token)==1)
            {
                printf("\nFound:%s\n",token);
                //getting the rest of the tokens
                token = strtok(NULL, d);
            }



            else
            {
                //if word wasnt found i search for the its leaf and get the pre and succ of the leaf
                printf("\nCould not find:%s\n",token);
                temp2 = leaf(root,token);
                printf("Leaf : %s\n",temp2->data);
                printf("successor: %s\n",(Successor(root,temp2))->data);
                printf("predecessor: %s\n",(predeccessor(root,temp2))->data);

                token = strtok(NULL, d);

            }
        }
    }
    return 0;
}


struct node *newNode(char key[])
{
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    strcpy(temp->data,key);
    temp->left = temp->right = NULL;
    return temp;
}
void inorder(struct node *root)
{
    //used it to print the tree to make sure the insertion is correct
    if (root != NULL)
    {
        inorder(root->left);
        printf("%s \n", root->data);

        inorder(root->right);
    }
}

struct node* insert(struct node* node, char key[])
{

    if (node == NULL)
        return newNode(key);

    if (strcmp(key,node->data)<0)
        node->left  = insert(node->left, key);
    else if (strcmp(key,node->data)>0)
        node->right = insert(node->right, key);

    return node;
}
int size(struct node *root)
{
    return (root == NULL) ? 0 :
           1 + size(root->left) + size(root->right);
}

int height(struct node *root)
{
    return (root == NULL) ? -1 :
           1 + MAX(height(root->left), height(root->right));
}

int  MAX(int h1, int h2)
{
    //returns the height of the bigger subtree
    if(h1>h2)
        return h1;

    else if(h1<h2)
        return h2;
    else
        return h1;

}

int search(struct node *root, char d[])
{
    if (root == NULL)
        return 0;
    else if (strcmp(d,root->data)==0)
        return 1;
    else if (strcmp(d,root->data)<0)
        return search(root->left, d);
    else
        return search(root->right, d);
}

struct node* leaf (struct node* root,char word[])
{
    //if no not found it gets me the leaf which is the node right before it becomes null

    if(root->left==NULL&&root->right==NULL)
        return root;
    else if (strcmp(root->data,word)>0)
        if(root->left==NULL)
            return root;
        else
            return leaf(root->left,word);
    else if (strcmp(root->data,word)<0)
        if(root->right==NULL)
            return root;
    return leaf(root->right,word);


}

struct node * minNode(struct node* node)
{

    struct node* current = node;

    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

struct node * maxNode(struct node* node)
{
    struct node* current = node;

    while (current->right != NULL)
    {
        current = current->right;
    }
    return current;
}


struct node * Successor(struct node *root, struct node *n)
{
    //if there is a right send it to the minNode to get its hard left and get the smallest node bigger than the leaf
    if( n->right != NULL )
        return minNode(n->right);

    struct node *succ = NULL;
    //if not then we compare to the root and search for it if its smaller we make the root the succ and move to the left
    while (root != NULL)
    {
        if (strcmp(n->data,root->data)<0)
        {
            succ = root;
            root = root->left;
        }
        //if the the data is bigger the we shift to the right
        else if (strcmp(n->data,root->data)>0)
            root = root->right;
        else

            break;
    }

    return succ;
}



struct node * predeccessor(struct node *root, struct node *n)
{
    if( n->left != NULL )
        return maxNode(n->left);

    struct node *pre = NULL;

    while (root != NULL)
    {
        if (strcmp(n->data,root->data)>0)
        {
            pre = root;
            root = root->right;
        }
        else if (strcmp(n->data,root->data)<0)
            root = root->left;
        else
            return n;
        //removed the break cause it was crashing to prg when there is no pre
            //break;
    }

    return pre;
}


