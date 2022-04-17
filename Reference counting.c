#include<stdio.h>
#include <stdlib.h>
typedef struct node {
	unsigned int rc;
	int value;
	struct node *node1;
	struct node *node2;
	struct node *node3;
}Node;
Node *address_arr[10];
Node *root_arr[15];

int adjcency_matrix_root1[10][10];
int adjcency_matrix_root2[10][10];

const Node *empty = NULL;
Node *node(int value, Node *node1, Node *node2, Node *node3);
void inc_ref(Node *node);
void dec_ref(Node *node);

Node *node(int value, Node *node1, Node *node2, Node *node3){
	Node* r = (Node*)malloc(sizeof(Node));
	r->rc = 0;
	r->value = value;

	r->node1 = node1;
	inc_ref(node1);

	r->node2 = node2;
	inc_ref(node2);
	
	r->node3 = node3;
	inc_ref(node3);
	return r;
}
void inc_ref(Node *node) {
	if (node != NULL) {
		node->rc += 1;
	}
}
void dec_ref(Node *node) {
	if (node != NULL) {
		if (node->rc > 1) {
			node->rc -= 1;
		}
		else{
			dec_ref(node->node1);
			dec_ref(node->node2);
			dec_ref(node->node3);
			free(node);
		}
	}
}
void set_node1(Node *node, Node *newval){
	inc_ref(newval);
	node->node1 = newval;
}
void set_node2(Node *node, Node *newval){
	inc_ref(newval);
	node->node2 = newval;
}
void set_node3(Node *node, Node *newval){
	inc_ref(newval);
	node->node3 = newval;
}
void *reference() {
	Node *n5 = node(5, NULL, NULL, NULL);
	Node *n1 = node(1, NULL, NULL, NULL);
	
	root_arr[0] = n5;
	inc_ref(n5);
	root_arr[1] = n1;
	inc_ref(n1);
	
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

void delete(){
	int i,j;
	for(i=0; i<11; i++){
		if(address_arr[i]->rc == 0){
			dec_ref(address_arr[i]);
			Node *dummy = node(-1, NULL, NULL, NULL);
			address_arr[i] = dummy;
		}
	}
}

int main(){
	
	
	Node *dummy = node(-1, NULL, NULL, NULL);
	int i,j;
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
    
    reference();
	
	printf("printing all the roots \n");
	for (i = 0; i < 2; i++) {
      printf("Value of var[%d] = %d\n", i, root_arr[i]->value);
    }
    printf("\n \n");
	
	printf("printing all the nodes \n");
	for (i = 0; i < 11; i++) {
      printf("Value of var[%d] = %d\n", i, address_arr[i]->rc);
    }
    printf("\n \n");
    
    delete();
    
    printf("printing all the nodes after deletion  \n");
	for (i = 0; i < 11; i++) {
      printf("Value of var[%d] = %d\n", i, address_arr[i]->rc);
    }
    printf("\n \n");

    
    printf("printing adjacency matrix for root 1 \n");
    for(i=0; i<10; i++){
    	for(j=0; j<10; j++){
    		printf("%d ", adjcency_matrix_root1[i][j]);
		}
		printf("\n");
	}
	printf("printing adjacency matrix for root 2  \n");
    for(i=0; i<10; i++){
    	for(j=0; j<10; j++){
    		printf("%d ", adjcency_matrix_root2[i][j]);
		}
		printf("\n");
	}
	return 0;
}

