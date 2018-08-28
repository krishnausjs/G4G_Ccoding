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
	return 0;
}
