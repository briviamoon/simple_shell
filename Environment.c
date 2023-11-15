#include "shell.h"

/**
 * addNode - Adds a new Node to linked lisk.
 * @head: pointer to head Node of List.
 * @variable: environment variable to add.
 * @value: env variable value.
 *
 * Description: Takes a Node as a paramenter and
 *				A variable and Value, Then creates
 *				A new Node and returns its pointer.
 * Return: returns a pointer to a new node.
 */
struct EnvNode *addNode(struct EnvNode *head, char *variable, char *value)
{
	struct EnvNode *newNode = (struct EnvNode *)malloc(sizeof(struct EnvNode));

	if (newNode == NULL)
	{
		fprintf(stderr, "malloc Addnode fail\n");
		exit(EXIT_FAILURE);
	}

	newNode->variable = strdup(variable);
	newNode->value = strdup(value);
	newNode->Next = NULL;
	/*If the list is empty*/
	if (head == NULL)
	{
		/*newNode is assigned to head of the list*/
		head = newNode;
	}
	else
	{
		/*temporary node takes place of head*/
		struct EnvNode *current = head;
		/*move through list to reach the end*/
		while (current->Next != NULL)
		{
			current = current->Next;
		}
		/*at the end of the list, attach new node*/
		current->Next = newNode;
	}
	return (head);
}

/**
 * findEnvVariable - finds a specific Env variable value.
 * @head: pointer to a list Head Node.
 * @variable: pointer to variable.
 * Return: returns a pointer to a specific environment variable's s value.
 */
char *findEnvVariable(struct EnvNode *head, char *variable)
{
	struct EnvNode *current = head;

	while (current != NULL)
	{
		if (strcmp(current->variable, variable) == 0)
		{
			return (current->value);
		}
		current = current->Next;
	}
	return (NULL);
}

/**
 * freeTheNodes - frees the nodes in list.
 * @head: pointer to node head.
 */
void freeTheNodes(struct EnvNode *head)
{
	struct EnvNode *temporary;

	while (head != NULL)
	{
		temporary = head;
		head = head->Next;
		free(temporary->variable);
		free(temporary->value);
		free(temporary);
	}
}

/**
 * getEnvironment - gets all the environment variables.
 * Return: returns the value of the environment variable's value.
 */
struct EnvNode *getEnvironment(void)
{
	int i = 0;
	struct EnvNode *envList = NULL;
	char *variable = NULL;
	char *value = NULL;

	while (environ[i] != NULL)
	{
		variable = strtok(environ[i], "=");
		value = strtok(NULL, "=");
		envList = addNode(envList, variable, value);
		i++;
	}
	return (envList);
}

/**
 * printList - prints elements of linked list
 * @head: pointer to head node.
 * Return: 0 if successfull, -1 if failure.
 */
int printList(struct EnvNode *head)
{
	struct EnvNode *current = head;

	if (current != NULL)
	{
		while (current != NULL)
		{
			printf("%s=%s\n", current->variable, current->value);
			current = current->Next;
		}
		return (0);
	}
	return (-1);
}
