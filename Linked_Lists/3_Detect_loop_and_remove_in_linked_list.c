#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node* next;
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
	printf("Nodes in linked list \n");
	while(head != NULL)
	{
		printf("%d ",head->data);
		head = head->next;
	}	
	printf("\n");
}

void detect_a_loop_in_linked_list(struct node *head)
{
	struct node* slow = head;
	struct node* fast = head->next;

	while(fast != NULL && fast->next != NULL)
	{
		if(fast == slow)
			break;
		slow = slow->next;
		fast = fast->next->next;
	}

	if(fast == slow)
	{
		slow = head;
		while(slow->next != fast->next)
		{
			slow = slow->next;
			fast = fast->next;
		}
		fast->next = NULL;
		printf("Loop detected \n");
	}
	else
	{
		printf("No Loop detected\n");
	}
}

int main()
{
	struct node* head = NULL;
	int n,node_data,i;
	int only_once = 2;

	printf("Enter number of nodes in linked list\n");
	scanf("%d",&n);
	
	printf("Enter the %d nodes of linked list\n",n);
	for(i=0; i<n; i++)
	{
		scanf("%d",&node_data);
		if(only_once==2)
		{
			push(&head,node_data);	
			head->next = head;
			only_once = 0;	
		}
		else
		{
			push(&head,node_data);
		}
	}
	//print_linked_list(head);
	detect_a_loop_in_linked_list(head);
	print_linked_list(head);
}
