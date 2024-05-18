#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){

   int filas[10];
   int columnas[10];
   int sub_mat[10];

   //para filas
   for(int i = 0; i < 9; i++){
      for(int j = 0 ; j < 10 ; j++){
         filas[j] = 0;
         columnas[j] = 0;
      }
      //columnas
      for(int j = 0 ; j < 9 ; j++){
         //ver filas
         if(n->sudo[i][j] !=0)
         {
            if(filas[n->sudo[i][j]] == 1)
            {
               return 0;
            }
            else
            {
               filas[n->sudo[i][j]] = 1;
            }
         }
         //ver columnas
         if(n->sudo[j][i] !=0)
         {
            if(columnas[n->sudo[j][i]] == 1)
            {
               return 0;
            }
            else
            {
               columnas[n->sudo[j][i]] = 1;
            }
         }
      }
   }

   for(int k = 0 ; k < 9; k++){
      for(int i = 0 ; i < 10 ; i++){
         sub_mat[i] = 0;
      }

      for(int i = 3 * (k/3) ; i < 3 * (k/3) + 3; i++){
         for(int j = 3 * (k % 3) ; j < 3 * (k % 3) + 3; j++){
            if(n->sudo[i][j] != 0)
            {
               if(sub_mat[n->sudo[i][j]] == 1)
               {
                  return 0;
               }
               else
               {
                  sub_mat[n->sudo[i][j]] = 1;
               }
            }
         }
      }
   }
    return 1;
}


List* get_adj_nodes(Node* n){
   List* list=createList();

   for(int i = 0 ; i < 9 ; i++)
   {
      for(int k = 0 ; k < 9 ; k++)
      {
         if(n->sudo[i][k] == 0)
         {
            int num;
            for(num = 1 ; num <= 9 ; num++)
            {
               Node* new_node = copy(n);
               new_node->sudo[i][k] = num;
               if(is_valid(new_node)){
                  pushBack(list, new_node);
               }
               else{
                  free(new_node);
               }
            }
            return list;
         }
      }
   }
   return list;
}


int is_final(Node* n){
    for (int i = 0; i < 9; i++) {
        for (int k = 0; k < 9; k++) {
            if (n->sudo[i][k] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/