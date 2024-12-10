// list/list.c
// 
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_alloc() { 
  list_t* mylist =  (list_t *) malloc(sizeof(list_t)); 
  mylist->head = NULL;
}

void list_free(list_t *l) {
  node_t *current = l->head;
  node_t *next_node;

  while(current != NULL) {
       next_node = current->next;
       free(current);
       current = next_node;

  }
}

void list_print(list_t *l) {
  node_t *curr_node = l->head;
  while (curr_nude != NULL){
      printf("%d ->", curr_node->value);
  }
  printf("NULL \n");
}

char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 10024);
  char tbuf[20];

	node_t* curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    curr = curr->next;
    strcat(buf, tbuf);
  }
  strcat(buf, "NULL");
  return buf;
}

int list_length(list_t *l){
  if (l == NULL){
    return -1;
  }
  int counter = 0;
  node_t* curr_node = l->head;
  while(curr_node!=NULL){
    counter++;
    curr_node= curr_node->next;
  }
  return counter;
} 
 

void list_add_to_back(list_t *l, elem value) {
  node_t* new_node = (node_t*)malloc(sizeof(node_t));
  cur_node->value = l->head;
  while (curr_node->next != NULL){
    curr_node=curr_node->next;

  }
  curr_node->next=new_node;

}



void list_add_to_front(list_t *l, elem value) {
     node_t *cur_node = (node_t *)malloc(sizeof(node_t));
     cur_node->value=value;
     cur_node->next = NULL;

     /* Insert to front */
     node_t *head = l->head;  // get head of list

     cur_node->next = head;
     head = cur_node;
}

/*node_t * getNode(elem value) {
  node_t *mynode;

  mynode = (node_t *) malloc(sizeof(node_t));
  mynode->value = value;
  mynode->next = NULL;

  return mynode;
}*/

void list_add_at_index(list_t *l, elem value, int index) {}

elem list_remove_from_back(list_t *l) {
  
}
//{ return -1; }
elem list_remove_from_front(list_t *l){
  if (l->head == NULL){
    return -1;
  }
  node_t *temp = l->head;
  elem value = temp->value;
  l->head = temp->next;
  free(temp);
  return value;
  
} //{ return -1; }
elem list_remove_at_index(list_t *l, int index){
  if (l-> head == NULL || index < 0){
    return -1;
  }
  if (index==0){
    return list_remove_from_front(l);
  }
  node_t *curr = l->head;
  node_t *prev = NULL;
  int counter = 0;

  while (curr != NULL && counter < index){
    prev = curr;
    curr = curr->next;
    counter++;
  }
  if(curr == NULL){
    return -1;
  }

  prev->next=curr->next;
  elem value = curr->value;
  free(curr);
  return value;
} 

bool list_is_in(list_t *l, elem value){
  node_t *curr = l->head;
  while ( curr != NULL){
    if (curr->value == value){
      return true;
    }
    curr = curr->next;
  }
  return false;
} 




elem list_get_elem_at(list_t *l, int index){
   if (l-> head == NULL || index < 0) {
    return -1;
   }
   node_t *curr= l->next;
   int counter = 0;
   while (curr != NULL && counter < index){
    curr = curr ->next;
    counter++;
   }
   if (curr == NULL){
    return -1;
   }
   return curr->value; 

} 


int list_get_index_of(list_t *l, elem value){
  node_t *curr = l->head;
  int index = 0;
  
  while (curr != NULL){
    if (curr->value == value){
      return index;

    }
    curr = curr->next;
    index++
    }
    return -1;
}   

