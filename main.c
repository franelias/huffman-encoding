#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 32
typedef struct {
  char letter;
  int amount;
} LetterFreq;

typedef struct _node {
  LetterFreq data;
  int weight;
  char* path;
  struct _node* left;
  struct _node* right;
} node;

typedef node* TreeNode;

typedef struct _nodeList {
  TreeNode tree;
  struct _nodeList* next;
} nodeList;
typedef nodeList* List;

int cmpfunc(const void* a, const void* b) {
  return (*(TreeNode*)a)->data.amount > (*(TreeNode*)b)->data.amount;
}

TreeNode newNode(LetterFreq data) {
  TreeNode temp = malloc(sizeof(node));
  temp->left = temp->right = NULL;
  temp->weight = data.amount;
  temp->data = data;

  return temp;
}

TreeNode* readText(FILE* fp) {
  int buff, amount = 0;
  LetterFreq* aux = malloc(sizeof(LetterFreq) * 256);

  for (int i = 0; i < 256; i++) {
    aux[i].letter = i;
    aux[i].amount = 0;
  }

  while ((buff = fgetc(fp)) != EOF) {
    // si esta insertando en un nuevo lugar incrementar la cantidad
    if (!aux[buff].amount)
      amount++;
    aux[buff].amount++;
  }
  TreeNode* array = malloc(sizeof(TreeNode) * amount);
  for (int i = 0, j = 0; i < 256; i++) {
    if (aux[i].amount) {
      array[j++] = newNode(aux[i]);
    }
  }

  qsort(array, amount, sizeof(TreeNode), cmpfunc);

  // for (int i = 0; i < amount; i++) printf("%c %d\n", array[i].letter, array[i].amount);
  return array;
}

// pasar a ingles que no me acuerdo el nombre
TreeNode UnirArboles(int weight, TreeNode left, TreeNode right) {
  TreeNode newNode = malloc(sizeof(node));
  // newNode->data = NULL;
  newNode->weight = weight;
  newNode->left = left;
  newNode->right = right;
  return newNode;
}

void sortedInsert(List* head, List node) {
  if (*head == NULL || (*head)->tree->weight >= node->tree->weight) {
    node->next = *head;
    *head = node;
  } else {
    List current = *head;
    while (current->next != NULL && current->next->tree->weight < node->tree->weight) {
      current = current->next;
    }

    node->next = current->next;
    current->next = node;
  }
}

TreeNode GenerateHuffmanTree(List nodes, int amount) {
  TreeNode firstNode, secondNode, newTree;
  int weight;

  while (amount > 1) {
    firstNode = nodes->tree;
    secondNode = nodes->next->tree;

    weight = firstNode->weight + secondNode->weight;

    newTree = UnirArboles(weight, firstNode, secondNode);

    nodes = nodes->next->next;
    List newNode = malloc(sizeof(nodeList));
    newNode->next = NULL;
    newNode->tree = newTree;

    sortedInsert(&nodes, newNode);
    amount--;
  }

  return nodes->tree;
}

void push(List* list, TreeNode data) {
  List newNode = malloc(sizeof(nodeList));
  newNode->tree = data;
  newNode->next = *list;
  *list = newNode;
}
List array_to_list(TreeNode array[], int amount) {
  List listOfTrees = NULL;
  for (int i = amount - 1; i >= 0; i--) {
    push(&listOfTrees, array[i]);
  }
  return listOfTrees;
}

void Tree_inOrder(TreeNode n, char prevPath[]) {
  if (!n)
    return;
  n->path = malloc(sizeof(char) * strlen(prevPath) + 2);
  strcpy(n->path, prevPath);
  if (n->left) {
    strcat(n->path, "0");
    Tree_inOrder(n->left, n->path);
  }

  if (n->data.amount)
    printf("%c %s\n", n->data.letter, n->path);
  strcpy(n->path, prevPath);
  if (n->right) {
    strcat(n->path, "1");
    Tree_inOrder(n->right, n->path);
  }
}

int main() {
  FILE* fp = fopen("prueba.txt", "r");

  if (fp == NULL) {
    printf("Error!");
    return 1;
  }

  TreeNode* array = readText(fp);
  List listOfTrees = array_to_list(array, 7);

  TreeNode arbol = GenerateHuffmanTree(listOfTrees, 7);
  Tree_inOrder(arbol, "");
  fclose(fp);

  return 0;
}
