#include <cassert>
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class Node
{
public:
    int data;
    Node* next;
};

struct BinaryTreeNode
{
    int data;
    BinaryTreeNode* left, * right;
};

void MoveNode(Node** destRef, Node** sourceRef);

Node* SortedMerge(Node* list1, Node* list2)
{
    Node dummy;

    Node* tail = &dummy;

    dummy.next = NULL;
    while (1)
    {
        if (list1 == NULL)
        {
            tail->next = list2;
            break;
        }
        else if (list2 == NULL)
        {
            tail->next = list1;
            break;
        }
        if (list1->data <= list2->data)
            MoveNode(&(tail->next), &list1);
        else
            MoveNode(&(tail->next), &list2);

        tail = tail->next;
    }
    return(dummy.next);
}

void MoveNode(Node** destRef, Node** sourceRef)
{
    Node* newNode = *sourceRef;
    assert(newNode != NULL);

    *sourceRef = newNode->next;

    newNode->next = *destRef;

    *destRef = newNode;
}

void push(Node** head_ref, int new_data)
{
    Node* new_node = new Node();

    new_node->data = new_data;

    new_node->next = (*head_ref);

    (*head_ref) = new_node;
}

void reverseLL(Node** head)
{
    stack<Node*> s;
    Node* temp = *head;
    while (temp->next != NULL)
    {
        s.push(temp);
        temp = temp->next;
    }
    *head = temp;

    while (!s.empty())
    {
        temp->next = s.top();
        s.pop();

        temp = temp->next;
    }
    temp->next = NULL;
}

BinaryTreeNode* newBinaryTreeNode(int data)
{
    BinaryTreeNode* temp = new BinaryTreeNode;
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

void BinaryTree(Node* head, BinaryTreeNode*& root)
{
    queue<BinaryTreeNode*> q;
    if (head == NULL)
    {
        root = NULL;
        return;
    }
    root = newBinaryTreeNode(head->data);
    q.push(root);
    head = head->next;
    while (head)
    {
        BinaryTreeNode* parent = q.front();
        q.pop();

        BinaryTreeNode* leftChild = NULL, * rightChild = NULL;
        leftChild = newBinaryTreeNode(head->data);
        q.push(leftChild);
        head = head->next;
        if (head)
        {
            rightChild = newBinaryTreeNode(head->data);
            q.push(rightChild);
            head = head->next;
        }

        parent->left = leftChild;
        parent->right = rightChild;
    }
}

void inorderTraversal(BinaryTreeNode* root)
{
    if (root)
    {
        inorderTraversal(root->left);
        cout << root->data << " ";
        inorderTraversal(root->right);
    }
}

void printList(Node* node)
{
    while (node != NULL)
    {
        cout << node->data << " ";
        node = node->next;
    }
}

Node* AddObject(Node* node , int size)
{
    for (int i = 0; i < size; i++)
    {
        int num = rand() % 100;
        push(&node, num);

    }
    return node;
}

int main()
{
    Node* head = NULL;
    push(&head, 37);  
    push(&head, 30);
    push(&head, 25);
    push(&head, 15);
    push(&head, 12);
    push(&head, 10); 

    BinaryTreeNode* root;
    BinaryTree(head, root);

    cout << "Inorder Traversal of the constructed Binary Tree is: \n";
    inorderTraversal(root);

    return 0;
}