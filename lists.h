#ifndef __LISTS_H_
#define __LISTS_H_
#include "tree.h"

typedef struct _nodeList
{
  TreeNode tree;
  struct _nodeList *next;
} nodeList;

typedef nodeList *List;

List create_list();

/*
  A partir de una lista enlazada y un nodo, reccore la lista hasta encontrar un nodo
   con mayor valor y lo inserta atras
*/
void sorted_insert(List *head, List node);

/*
  A partir del puntero de una lista y un nuevo nodo, inserta
  el nuevo nodo en primera posicion de la lista
*/
void push(List *list, TreeNode data);

/*
  A partir de un array de nodos y el largo del mismo, lo convierte en una lista enlazada
*/
List array_to_list(TreeNode *array, int length);

/*
 A partir de una lista, libera la memoria de cada nodo
*/
void destroy_list(List *list);

/*
  A partir de una lista, libera el primer nodo de la misma
*/
void remove_first(List *list);
#endif