#include<stdio.h>
#include<stdlib.h>
#define HEAP_SIZE 2000 //predefined size for contigious allocation
// structure defintion of metadata
typedef struct block_tag{
    int size;  //size of the block described
    int free;  //tells whether block is allocated or not. flag free->1, else 0
    struct block_tag *next;  // points to the metadata of next block
    struct block_tag *prev;  //points to the metadata of prev block
}block;

//intializing the block of memory
void* intialize()
{
    block *head=malloc(HEAP_SIZE); //pointing to main block of memory which is free no storage allocation
    head->size=HEAP_SIZE-sizeof(block);//size of the block==> HEAP_SIZE-size of one metadata block
    head->free=1;//indicate that block is not yet allocated , flag is 1
    head->prev=NULL; 
    head->next=NULL;
    //return head;
}

//splitting  free block for a new block allocation
void split_memory(block* ptr,int req_size)
{
    block *new=(void*)((void*)ptr+req_size+sizeof(block));
    new->prev=ptr;
    new->next=ptr->next;
    new->size=ptr->size-req_size-sizeof(block);
    new->free=1;
    ptr->next=new;
    ptr->size=req_size;
    ptr->free=0;
}
void* Malloc(int req_size,void* heap)
{
    block *ptr=heap; // temporary ptr to point to start of metadata block list
    void* result;
    while(ptr && (ptr->size < req_size || ptr->free==0))
    {
        ptr=ptr->next;   
    }
    if(ptr==NULL)
    {
        printf("\nMemory is full\n");//no suffcient memory to allocate
    }
    else
    {
        ptr->free=0;
        if(ptr->size-req_size>sizeof(block))   // we only split the block if space remaining is sufficient enough to accomodate another block
        {
            split_memory(ptr,req_size);
        }
        result=(void*)++ptr;   
		//by incrementing we make it point to the location beyond metadata and allows user to access that part(i.e pointer arithmetic)
        printf("\nSUCCESSFULLY ALLOCATED MEMORY OF SIZE %d\n",req_size);
    }
    return ptr;
}

//Merge consecutive free blocks by removing the metadata block in the middle. This will save space
block* merge(block *ptr1,block *ptr2)
{
    ptr1->next=ptr2->next;
    if(ptr2->next)
    {
        ptr2->next->prev=ptr1;
    }
    ptr1->size+=(ptr2->size+sizeof(block));
    return ptr1;
}
//Deallocate the memory after using it
void Free(void *ptr,void *heap)
{
    if(ptr>=heap && ptr<=heap+HEAP_SIZE)   //checking whether the address given by user lies within the heap created by us.
    {
        block *curr=ptr;
        --curr;     //by decrementing curr we make it point to the metadata part(i.e pointer arithmetic)
        curr->free=1;
        int size=curr->size;
        if(curr->prev && curr->next && curr->prev->free==1 && curr->next->free==1)
        {
            curr=merge(curr->prev,curr);
            merge(curr,curr->next);
        }
        else if(curr->prev && curr->prev->free==1)
        {
            merge(curr->prev,curr);
        }
        else if(curr->next && curr->next->free==1)
        {
            merge(curr,curr->next);
            
        }
        printf("\nSUCCESSFULLY FREED MEMORY OF SIZE %d\n ",size);
    }
    else
    {
        printf("\nTHIS MEMORY IS NOT WITHIN THE HEAP\n");
    }
}
void Display(void *heap)
{
    block *ptr=heap;
    printf("\nBLOCK-SIZE\tAVAILABILITY\tADDRESS");
    while(ptr)
    {
        printf("\n%d\t\t%d\t\t%p",ptr->size,ptr->free,ptr);
        ptr=ptr->next;
    }
}
void main()
{
    void* heap=intialize();
    int *p=(int*)Malloc(450,heap);
    int *t=(int*)Malloc(100,heap);
    t=NULL; //it is the responsibilty of programmer to make t point to null
    char *q=(char*)Malloc(50,heap);
    int *s=(int*)Malloc(20,heap);
    Display(heap);
    Free(s,heap);
    Display(heap);
    free(heap);    //deallocating the space which was used to implement the heap
}
