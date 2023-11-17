#ifndef NODES_H
#define NODES_H

/**
* struct EnvNode - Structure of linked-list of environment vars.
* @variable: The environment variable.
* @value: data of the environment variable.
* @Next: poiner to next node in list.
*
* Description: Structure containing environment data
*				A variable name, A value, and a pointer
*				To the Next Node in The lnked List
*/
struct EnvNode
{
	char *variable;
	char *value;
	struct EnvNode *Next;
};

/*Node Related functions*/
void freeTheNodes(struct EnvNode *head);
struct EnvNode *addNode(struct EnvNode *head, char *variable, char *value);
char *findEnvVariable(struct EnvNode *head, char *variable);
struct EnvNode *getEnvironment(void);
int printList(struct EnvNode *head);
char **ConvertEnvListToArray(struct EnvNode *envList);

#endif
