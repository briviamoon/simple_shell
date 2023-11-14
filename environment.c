#include "shell.h"

/*
 * addNode - Adds a new Node to linked lisk
 * @head: pointer to head Node of List.
 * @variable: environment variable to add.
 * @value: env variable value
 */


void addNode(struct EnvNode **head, char *variable, char *value)
{
	struct EnvNode *newNode = malloc(sizeof(struct EnvNode));	
	if (newNode == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	newNode->variable = strdup(variable);
	newNode->value = strdup(value);
	newNode->Next = *head;

	*head = newNode;
}

/*
 * findEnvVariable - finds a specific Env variable value
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
 * @EnvNode head: pointer to node head.
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
 * @enVariable: poiner to the environment variable string.
 * Return: returns the value of the environment variable's value.
 */
char *getEnvironment(char *enVariable)
{
	return (getenv(enVariable));
}
