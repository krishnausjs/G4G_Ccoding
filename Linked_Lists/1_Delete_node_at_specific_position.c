#include <stdio.h>

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

void deleteNode(struct node **headRef, int position)
{
	int i;
	struct node *temp;

	if(*headRef == NULL)
		return;

	struct node *current = *headRef;

	if(position == 0)
	{
		(*headRef)=current->next;
		free(current);
		return;
	}

	for(i=0; current != NULL && i<position-1; i++)	
		current=current->next;
	
	if(current == NULL || current->next == NULL)
		return;
	
	temp = current->next->next;

	free(current->next);
	current->next = temp;
		
}
int main()
{
	struct node *head = NULL;
	push(&head,1);
	push(&head,2);
	push(&head,3);
	push(&head,4);
	push(&head,5);
	push(&head,6);
	print_list(head);
	deleteNode(&head, 4);
	print_list(head);
	return 0;
}
