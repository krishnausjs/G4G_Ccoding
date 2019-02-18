#include <stdio.h>
#include <stdlib.h>

//#define USE_RECURSION_METHOD
//#define USE_DUMMY_NODE_METHOD
#define USE_LOCAL_REFERENCE_METHOD

struct node
{
	int data;
	struct node *next;
};

void push(struct node **headRef, int data)
{
	struct node *newNode;
	newNode = malloc(sizeof(struct node));
	newNode->data = data;
	newNode->next = (*headRef);
	(*headRef) = newNode;
}

int print_list(struct node *head)
{
	while(head != NULL)
	{
		printf("%d ",head->data);
		head = head->next;
	}
	printf("\n");
}

#ifdef USE_DUMMY_NODE_METHOD
void move_node(struct node** dest_ref, struct node** src_ref)
{
	struct node* new_node = *src_ref;
 	*src_ref = new_node->next;
	new_node->next = *dest_ref;
	*dest_ref = new_node;
}

struct node* sorted_merge1(struct node *a, struct node *b)
{
	//Imagine a hanger where you hang a node and keep on appending sorted node down.
	//Dummy node is such hanger, the hook to which you are going to append is tail.
	struct node dummy;

	struct node *tail = &dummy;
	
	dummy.next = NULL;

	while(1)
	{
		if(a == NULL)
		{
			tail->next = b;
			break;
		}
		else if(b == NULL)
		{
			tail->next = a;
			break;
		}

		if(a->data <= b->data)
			move_node(&(tail->next),&a);
		else
			move_node(&(tail->next),&b);

		tail = tail->next;
	}
	return(dummy.next);
}
#endif

#ifdef USE_RECURSION_METHOD
struct node* sorted_merge_rec(struct node* a, struct node* b)
{
	//Declare a pointer to linked list and assign it to NULL
	struct node* result = NULL;

	//If a is NULL then return current b address
	if(a == NULL)
		return b;
	//If b is NULL then return current a address
	else if(b == NULL)
		return a;
	
	//If both have valid value, then merge and sort.
	if(a->data <= b->data)
	{
		//a data is less than b data, so assign a value to the result, deal with  [a->next to end] and b
		result = a;	
		result->next = sorted_merge_rec(a->next,b);	
	}
	else
	{
		//b data is less than a data, so assign b value to the result, deal with a and [b->next to end] 
		result = b;
		result->next = sorted_merge_rec(a,b->next);
	}

	//Finally return result
	return result;
}
#endif

#ifdef USE_LOCAL_REFERENCE_METHOD
void move_node(struct node** dest_ref, struct node** src_ref)
{
	struct node *new_node = *src_ref;
	*src_ref = new_node->next;
	new_node->next = *dest_ref;
	*dest_ref = new_node;
}

struct node* sorted_merge2(struct node* a, struct node* b)
{
	struct node* result = NULL;
	struct node** last_ptr_ref = &result;

	while(1)
	{
		if(a == NULL)
		{
			*last_ptr_ref = b;
			break;
		}	
		else if(b == NULL)
		{
			*last_ptr_ref = a;
			break;
		}
		
		if(a->data <= b->data)
			move_node(last_ptr_ref, &a);
		else
			move_node(last_ptr_ref, &b);
	
		last_ptr_ref = &((*last_ptr_ref)->next);
	}
	return result;
}
#endif

int main()
{
	//Pointers to two sorted linked lists
	struct node *a = NULL;
	struct node *b = NULL;

	//Pointer to final sorted merge list
	struct node *res = NULL;

	//Local variables
	int i = 0,an = 0,bn = 0;
	int node_data;

	//Read list a data
	printf("Enter number of elements in first list\n");
	scanf("%d",&an);
	printf("Enter %d list entries\n",an);
	for(i=0; i<an; i++)
	{
		scanf("%d",&node_data);
		push(&a,node_data);
	}
	
	//Read list b data
	printf("Enter number of elements in second list\n");
	scanf("%d",&bn);
	printf("Enter %d list entries\n",bn);
	for(i=0; i<bn; i++)
	{
		scanf("%d",&node_data);
		push(&b,node_data);
	}
	
	//Print list a data
	printf("First list entries are..\n");
	print_list(a);
	
	//Print list b data
	printf("Second list entries are..\n");
	print_list(b);

#ifdef USE_RECURSION_METHOD
	//Call sorted merge recursive function
	printf("Calling recursive sorted_merge_rec function\n");
	res = sorted_merge_rec(a,b);
#endif
	
	printf("Merged sorted list is\n");
#ifdef USE_DUMMY_NODE_METHOD
	res = sorted_merge1(a,b);
#endif

#ifdef USE_LOCAL_REFERENCE_METHOD
	res = sorted_merge2(a,b);
#endif
	print_list(res);
	return 0;
}
