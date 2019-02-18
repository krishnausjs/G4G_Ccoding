#include <stdio.h>
#include <stdlib.h>

#define USE_TWO_POINTER_METHOD

struct node 
{
	int data;	
	struct node *next;
};

void push(struct node** head_ref, int data)
{
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	new_node->data = data;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}

void print_linked_list(struct node* head)
{
	printf("Linked list nodes are ...\n");
	while(head != NULL)
	{
		printf("%d ",head->data);
		head = head->next;
	}
	printf("\n");
}

#ifdef USE_TWO_POINTER_METHOD
void remove_last_node_in_linked_list(struct node** head_ref)
{
	struct node *slow = *head_ref;
	struct node *fast = (*head_ref)->next;
	struct node *prev_node;

	if(slow == NULL)
		return;

	if(slow->next == NULL)
	{
		free(slow);
		return;
	}	

	while(fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
		prev_node = fast;
	}
	//odd nodes case
	if(prev_node->next == NULL)
	{
		free(prev_node->next);
		prev_node->next = NULL;
	}
	else if(prev_node->next->next == NULL)
	{
		free(prev_node->next);
		prev_node->next = NULL;
	}	
}
#else
void remove_last_node_in_linked_list(struct node** head_ref)
{
	struct node* current = *head_ref;
	struct node* second_last;
	
	if(current == NULL)
		return;

	if(current->next == NULL)
	{
		free(current);
		return;
	}
	while(current->next->next != NULL)
	{
		current = current->next;
		second_last = current;
	}

	if(second_last != NULL)
	{	
		free(second_last->next);
		second_last->next = NULL;
	}
}
#endif

int main()
{
	struct node* head = NULL;
	int n, node_data, i;

	printf("Enter number of nodes in linked list\n");
	scanf("%d",&n);
		
	printf("Enter %d nodes in linked list\n",n);
	for(i=0; i<n; i++)
	{
		scanf("%d",&node_data);
		push(&head, node_data);
	}
	
	print_linked_list(head);
	remove_last_node_in_linked_list(&head);	
	print_linked_list(head);
}
