#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct node *Insert(struct node *root,int val)
{
    if(root==NULL)
    {
        root=(struct node *)malloc(sizeof(struct node));
        if(root==NULL)
        {
            printf("\nMemory Error...!");
            return NULL;
        }
        root->data=val;
        root->left=NULL;
        root->right=NULL;
    }
    else
    {
        if(val<=root->data)
            root->left=Insert(root->left,val);
        else
            root->right=Insert(root->right,val);
    }
    return root;
}


/*time : O(n) (that is in worst case of right skew tree) and space : O(n) for recursive stack*/
struct node *FindMax(struct node *root)  
{
    if(root==NULL)
        return NULL;
    else if(root->right==NULL)
        return root;
    else
        return FindMax(root->right);
}

struct node *Delete(struct node *root, int val)
{
    struct node *temp=NULL;
    if(root==NULL)
        printf("\nElement not found.....!");
    else if(val<root->data)
        root->left=Delete(root->left,val);
    else if(val>root->data)
        root->right=Delete(root->right,val);
    else
    {
        //found element
        if(root->left && root->right)
        {
            /*replace with largest in left subtree*/
            temp=FindMax(root->left);
            root->data=temp->data;
            root->left=Delete(root->left,root->data);
        }
        else if(root->left==NULL && root->right==NULL)
        {
            return NULL;
        }
        else
        {
            /*one child*/
            temp=root;
            if(root->left==NULL)
                root=root->right;
            if(root->right==NULL)
                root=root->left;
            free(temp);
        }
    }
    return root;
}
/*Time Complexity: O(n). Space Complexity: O(n) for recursive stack. For iterative version, space
complexity is O(1).*/

void InOrderDisplay(struct node *root)
{
    if(root==NULL)
    {
        return;
    }
    else
    {
        InOrderDisplay(root->left);
        printf("\n\t%d",root->data);
        InOrderDisplay(root->right);
    }
}

int HeightOfBinaryTree(struct node *root)
{
    int left_height,right_height;
    if(root==NULL)
    return 0;
    else
    {
        /*computing the depth of each subtree*/
        left_height=HeightOfBinaryTree(root->left);
        right_height=HeightOfBinaryTree(root->right);

        if(left_height>right_height)
        {
            return (left_height+1);
        }
        else
        {
            return (right_height+1);
        }
    }
}

struct node *Search(struct node *root,int key)
{
    struct node *temp=root;
    while(temp->data!=key)
    {
        if(temp!=NULL)
        {
            printf(" %d",temp->data);
            if(temp->data>key)
            {
                temp=temp->left;
            }
            else
            {
                temp=temp->right;
            }

            if(temp==NULL)
            {
                return NULL;
            }
        }
    }
    return temp;
}

int main()
{
    int n,m;
    int val;
    char ch;
    struct node *root=NULL,*ptr=NULL;
    l1:
    printf("\n1. Insert ");
    printf("\n2. Delete");
    printf("\n3. Display InOrder");
    printf("\n4. Height of the tree");
    printf("\n5. Search");
    printf("\nEnter your choice : ");
    scanf("%d",&n);

    switch(n)
    {
        case 1 :    printf("\nEnter the element you have to insert : ");
                    scanf("%d",&val);
                    root=Insert(root,val);
                    break;
        case 2 :    printf("\nEnter the element you want to delete : ");
                    scanf("%d",&val);
                    root=Delete(root,val);
                    break;
        case 3 :    printf("\nInOrder Traversal : ");
                    InOrderDisplay(root);
                    break;
        case 4 :    printf("\nHeight of the BST is : %d ",HeightOfBinaryTree(root));
                    break;
        case 5 :    printf("\nEnter the element to search : ");
                    scanf("%d",&m);
                    ptr=Search(root,m);
                    if(ptr==NULL)
                        printf("\nElement not found....!");
                    else
                        printf("\nElement found......!");
                    break;
        default :   printf("\nInvalid Input....!");
                    break;
    }
    printf("\nDo you want to perform more? (y/n) : ");
    while(getchar()!='\n');
    scanf("%c",&ch);
    if(ch=='y' || ch=='Y')
    goto l1;
    return 0;
}