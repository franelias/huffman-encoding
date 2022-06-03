#include "lists.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

void test_create_list() {
  List list = create_list();
  assert(list == NULL);
}

void test_push() {
  // test 1 pusheo a una lista vacia
  List list = NULL;
  TreeNode node1 = new_node('a', 1);
  push(&list, node1);
  assert(list->next == NULL);
  assert(list->tree->letter == 'a' && list->tree->weight == 1);
  // test 2 pusheo a una lista con un nodo
  TreeNode node2 = new_node('b', 2);
  push(&list, node2);
  assert(list->next->next == NULL);
  assert(list->tree->letter == 'b' && list->tree->weight == 2);
  assert(list->next->tree->letter == 'a' && list->next->tree->weight == 1);
}

List test_array_to_list() {
  // test 1 array vacio
  TreeNode *array1 = NULL;
  List list1 = array_to_list(array1, 0);
  assert(list1 == NULL);
  // test 2 array con un elemento
  TreeNode *array2 = malloc(sizeof(TreeNode));
  array2[0] = new_node('a', 1);
  List list2 = array_to_list(array2, 1);
  assert(list2->next == NULL);
  assert(list2->tree->letter == 'a' && list2->tree->weight == 1);
  // test 2 array con dos elementos
  TreeNode *array3 = malloc(sizeof(TreeNode) * 2);
  array3[0] = new_node('a', 1);
  array3[1] = new_node('b', 2);
  List list3 = array_to_list(array3, 2);
  assert(list3->next->next == NULL);
  assert(list3->tree->letter == 'a' && list3->tree->weight == 1);
  assert(list3->next->tree->letter == 'b' && list3->next->tree->weight == 2);
}

void test_destroy_list() {
  // test 1 destruyo una lista vacia
  List list1 = NULL;
  destroy_list(&list1);
  assert(list1 == NULL);
  // test 2 destruyo una lista con un elemento
  List list2 = NULL;
  TreeNode node1 = new_node('a', 1);
  push(&list2, node1);
  // explota
  destroy_list(&list2);
  assert(list2 == NULL);
}

void test_remove_first() {
  // test1 intento eliminar una lista vacia
  List list = NULL;
  remove_first(&list);
  assert(list == NULL);
  // test1 intento eliminar una lista con un elemento
  List list2 = NULL;
  TreeNode node1 = new_node('a', 1);
  push(&list2, node1);
  remove_first(&list2);
  assert(list2 == NULL);
  // // test1 intento eliminar una lista con dos elemento
  List list3 = NULL;
  TreeNode node2 = new_node('b', 2);
  push(&list3, node1);
  push(&list3, node2);
  remove_first(&list3);
  assert(list3->next == NULL);
  assert(list3->tree->letter == 'a' && list3->tree->weight == 1);
}

void test_sorted_insert() {
  // insertar en lista vacia
  List list1 = NULL;
  TreeNode node = new_node('a', 1);
  List listAux1 = NULL;
  push(&listAux1, node);
  sorted_insert(&list1, listAux1);
  assert(list1->next == NULL);
  assert(list1->tree->letter == 'a');

  // insertar en lista  un elemento mayor
  List list2 = NULL;
  TreeNode node1 = new_node('a', 2);
  List listAux2 = NULL;
  push(&listAux2, node1);
  TreeNode node2 = new_node('b', 1);
  push(&list2, node2);
  sorted_insert(&list2, listAux2);
  assert(list2->next->next == NULL);
  assert(list2->tree->letter == 'b' && list2->tree->weight == 1);
  assert(list2->next->tree->letter == 'a' && list2->next->tree->weight == 2);

  // insertar en lista  un elemento menor
  List list3 = NULL;
  List listAux3 = NULL;
  push(&listAux3, node2);
  push(&list3, node1);

  sorted_insert(&list3, listAux3);
  assert(list3->next->next == NULL);
  assert(list3->tree->letter == 'b' && list3->tree->weight == 1);
  assert(list3->next->tree->letter == 'a' && list3->next->tree->weight == 2);
  // insertar en el medio de una lista

  List list4 = NULL;
  List listAux4 = NULL;
  push(&listAux4, node1);
  TreeNode node3 = new_node('c', 4);
  push(&list4, node3);
  push(&list4, node2);

  sorted_insert(&list4, listAux4);
  assert(list4->next->next->next == NULL);
  assert(list4->tree->letter == 'b' && list4->tree->weight == 1);
  assert(list4->next->tree->letter == 'a' && list4->next->tree->weight == 2);
  assert(list4->next->next->tree->letter == 'c' && list4->next->next->tree->weight == 4);
}

int main() {
  test_push();
  test_array_to_list();
  test_destroy_list();
  test_remove_first();
  test_sorted_insert();

  // consultar al papa
  // test_create_list();
  printf("Todos los tests pasaron\n");
  return 0;
}