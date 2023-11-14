#include "shell.h"

/*
 * addNode - Adds a new Node to linked lisk
 * @head: pointer to head Node of List.
 * @variable: environment variable to add.
 * @value: env variable value
 *
 */

void addNode(struct EnvNode **head, char *variable, char *value)
{
	struct EnvNode *new = (struct EnvNode *)malloc(sizeof(struct EnvNode));

	if (new == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	new->variable = strdup(variable);
	new->value = strdup(value);
	new->Next = *head;

	*head = new;
}

/*
 * findEnvVariable - finds a specific Env variable value
 * @EnvNode: pointer to a list HEad Node.
 * @variable: pointer to variable.
 * Return: returns a pointer to a specific environment variable's s value.
 */
char *findEnvVariable(struct EnvNode *head, char *variable)
{
	struct EnvNode *current = head;

	while (current != NULL)
	{
		if (current->variable == variable)
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
	struct EnvNode *temporary = (struct EnvNode *)malloc(sizeof(struct EnvNode *));

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
