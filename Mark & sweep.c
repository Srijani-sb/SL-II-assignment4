#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct node {
	bool mark;
	int value;
	struct node *node1;
	struct node *node2;
	struct node *node3;
}Node;
Node *address_arr[10];
Node *root_arr[15];
int len;

int adjcency_matrix_root1[10][10];
int adjcency_matrix_root2[10][10];

const Node *empty = NULL;
Node *node(int value, Node *node1, Node *node2, Node *node3);

Node *node(int value, Node *node1, Node *node2, Node *node3){
	Node* r = (Node*)malloc(sizeof(Node));
	r->mark = false;
	r->value = value;
	r->node1 = node1;
	r->node2 = node2;
	r->node3 = node3;
	return r;
}
void set_node1(Node *node, Node *newval){
	node->node1 = newval;
}
void set_node2(Node *node, Node *newval){
	node->node2 = newval;
}
void set_node3(Node *node, Node *newval){
	node->node3 = newval;
}
void foo(){
	Node *n5 = node(5, NULL, NULL, NULL);
	Node *n1 = node(1, NULL, NULL, NULL);
	
	root_arr[0] = n5;
	len++;
	
	root_arr[1] = n1;
	len++;
	
	address_arr[5] = n5;
	address_arr[1] = n1;
	
	set_node1(n5, n1);
	adjcency_matrix_root1[n5->value - 1][n1->value - 1] = 1;
	
	Node *n2 = node(2, NULL, NULL, NULL);
	n1->node1 = n2;
	set_node1(n1, n2);
	adjcency_matrix_root1[n1->value - 1][n2->value - 1] = 1;
	adjcency_matrix_root2[n1->value - 1][n2->value - 1] = 1;
	
	address_arr[2] = n2;
	
	Node *n9 = node(9, NULL, NULL, NULL);
	n1->node2 = n9;
	set_node2(n1, n9);
	adjcency_matrix_root1[n1->value - 1][n9->value - 1] = 1;
	adjcency_matrix_root2[n1->value - 1][n9->value - 1] = 1;
	
	address_arr[9] = n9;
	
	Node *n10 = node(10, NULL, NULL, NULL);
	n1->node3 = n10;
	set_node3(n1, n10);
	adjcency_matrix_root1[n1->value - 1][n10->value - 1] = 1;
	adjcency_matrix_root2[n1->value - 1][n10->value - 1] = 1;
	
	address_arr[10] = n10;
	
	Node *n8 = node(8, NULL, NULL, NULL);
	set_node1(n8, n9);
	
	address_arr[8] = n8;

	Node *n7 = node(7, NULL, NULL, NULL);
	set_node1(n7, n1);
	set_node2(n7, n8);
	
	address_arr[7] = n7;

	Node *n3 = node(3, NULL, NULL, NULL);
	set_node1(n3, n8);
	set_node2(n3, n10);
	
	address_arr[3] = n3;
}

void mark_node(Node *node) {
	Node *current = node, *prev = NULL, *ptr = NULL;
	int flag = 0;
	
	while(current != NULL){
		if(current->mark == 0){
			current->mark = 1;
		}
		
		if(current->node1 != NULL && current->node1->mark == 0){
			ptr = prev;
			prev = current;
			current = current->node1;
		}
		else if(current->node2 != NULL && current->node2->mark == 0){
			ptr = prev;
			prev = current;
			current = current->node2;
		}
		else if(current->node3 != NULL && current->node3->mark == 0){
			ptr = prev;
			prev = current;
			current = current->node3;
		}
		else{
			current = prev;
			prev = ptr;
			ptr = NULL;
		}
	}
}
void mark(){
	
	int i;
	for(i=0; i<len; i++){
		mark_node(root_arr[i]);
	}
}
void sweep(){
	int i;
	for(i=0; i<11; i++){
		if(address_arr[i]->mark == false){
			printf("deleting %d node \n", address_arr[i]->value);
			free(address_arr[i]);
			Node *dummy = node(-1, NULL, NULL, NULL);
			address_arr[i] = dummy;
		}
		else{
			address_arr[i]->mark = false;
		}
	}
}
int main(){
	
	//initialising arrays
	int i,j;
	Node *dummy = node(-1, NULL, NULL, NULL);
	for (i = 0; i < 11; i++) {
		address_arr[i] = dummy;
    }
    
    for(i=0; i<10; i++){
    	for(j=0; j<10; j++){
    		adjcency_matrix_root1[i][i] = 0;
		}
	}
	for(i=0; i<10; i++){
    	for(j=0; j<10; j++){
    		adjcency_matrix_root2[i][i] = 0;
		}
	}
    foo();
	
	printf("printing all the root \n");
	for (i = 0; i < 2; i++) {
      printf("Value of var[%d] = %d\n", i, root_arr[i]->value);
    }
    printf("\n \n");
	
	printf("printing all the nodes \n");
	for (i = 0; i < 11; i++) {
      printf("Value of var[%d] = %i\n", i, address_arr[i]->mark);
    }
    printf("\n \n");
    
    mark();
    
    printf("printing all the nodes after marked \n");
    for (i = 0; i < 11; i++) {
      printf("Value of var[%d] = %i\n", i, address_arr[i]->mark);
    }
    printf("\n \n");
    
    sweep();
    
    printf("printing all the nodes after sweep \n");
	for (i = 0; i < 11; i++) {
      printf("Value of var[%d] = %i\n", i, address_arr[i]->mark);
    }
    printf("\n \n");
    
    printf("printing adjacency matrix for root 1 \n");
    for(i=0; i<10; i++){
    	for(j=0; j<11; j++){
    		printf("%d ", adjcency_matrix_root1[i][j]);
		}
		printf("\n");
	}
	
	printf("printing adjacency matrix for root 2  \n");
    for(i=0; i<10; i++){
    	for(j=0; j<11; j++){
    		printf("%d ", adjcency_matrix_root2[i][j]);
		}
		printf("\n");
	}
}
