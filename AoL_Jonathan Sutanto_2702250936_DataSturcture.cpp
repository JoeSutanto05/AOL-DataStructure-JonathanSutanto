#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct trie{
	struct trie *childNode[26];
	char desc[50];
	bool stringEnd;
};

int checkWord(char *word)
{
	int len = strlen(word);
	if(len < 2)
	{
		return 0;
	}
	for(int i=0;i<len;i++)
	{
		if(word[i] == ' ')
		{
			return 0;
		}
	}
	return 1;
}

int checkDesc(char *desc)
{
	int len = strlen(desc);
	int count = 0;
	int flag = 0;
	
	for(int i=0;i<len;i++)
	{
		if(desc[i] == ' ' && flag == 0)
		{
			count++;
			flag = 1;
		}
		if(desc[i] != ' ')
		{
			flag = 0;
		}
	}
	if(count >= 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
   
trie *root;

trie *newnode()
{
	trie *node = (trie*)malloc(sizeof(trie));
	for(int i=0; i<26; i++)
	{
		node->childNode[i] = NULL;
	}
	node->stringEnd = false;
	return node;
}

void insertSlang(char *word, char *desc)
{
	trie *node;
	if(root == NULL)
	{
		node = newnode();
		root = node;
	}
	node = root;
	int len = strlen(word);
	for(int i=0; i<len; i++)
	{
		int index = word[i]-'a';
		if(node->childNode[index] == NULL)
		{
			node->childNode[index] = newnode();
		}
		node = node->childNode[index];
	}
	
	if(node->stringEnd)
	{
		strcpy(node->desc, desc);
		printf("Successfully updated a slang word.\n");
		return;
	}
	else
	{
		strcpy(node->desc, desc);
		node->stringEnd = true;
		printf("Successfully released new slang word.\n");
		return;
	}
}

void recursivePrint(trie *node, char *prefix, int depth, int *iteration)
{
    if(node == NULL)
    {
    	return;
	}
	
    if(node->stringEnd)
    {
    	printf("%d. %s\n", *iteration, prefix);
    	(*iteration)++;
	}
    for(int i=0; i<26; i++)
	{
        if(node->childNode[i] != NULL)
		{
            prefix[depth] = 'a' + i;
            prefix[depth + 1] = '\0';
            recursivePrint(node->childNode[i], prefix, depth + 1, iteration);
        }
    }
}

void searchData(char *word)
{
	if(root == NULL)
	{
		printf("There is no word \"%s\" in the dictionary.\n", word);
        return;
	}
	trie *node = root;
	int len = strlen(word);
	char prefix[30];
	
	for(int i=0; i<len; i++)
	{
		int index = word[i]-'a';
        if(node->childNode[index] == NULL)
		{
            printf("There is no word \"%s\" in the dictionary.\n", word);
            return;
        }
        prefix[i] = word[i];
        node = node->childNode[index];
    }
    prefix[len] = '\0';
    
    if(node->stringEnd)
    {
    	printf("Slang Word	: %s\n", prefix);
    	printf("Description	: %s\n", node->desc);
	}
	else
	{
		printf("There is no word \"%s\" in the dictionary.\n", word);
	}
}

void printByPrefix(char *prefix)
{
	if(root == NULL)
	{
		printf("There is no prefix \"%s\" in the dictionary.\n", prefix);
        return;
	}
	
    trie *node = root;
    int len = strlen(prefix);
    char prefixCopy[30];
    
    for (int i=0; i<len; i++)
	{
        int index = prefix[i] - 'a';
        if(node->childNode[index] == NULL)
		{
            printf("There is no prefix \"%s\" in the dictionary.\n", prefix);
            return;
        }
        prefixCopy[i] = prefix[i];
        node = node->childNode[index];
    }
    prefixCopy[len] = '\0';
    int iteration = 1;
    recursivePrint(node, prefixCopy, len, &iteration);
}

void printAll()
{
    if(root == NULL)
	{
        printf("There is no slang word yet in the dictionary.\n");
        return;
    }
    char prefix[30] = "";
    int iteration = 1;
    recursivePrint(root, prefix, 0, &iteration);
}

int main()
{
	bool result;
	int choose;
	
	do{
		system("cls");
		printf("\n");

		printf("1. Release a new slang word\n");
		printf("2. Search a slang word\n");
		printf("3. View all slang words starting with a certain prefix word\n");
		printf("4. View all slang words\n");
		printf("5. Exit\n");
		

		printf("Enter your choose: ");
		scanf("%d",&choose);
		printf("\n");
		
		switch(choose){
			case 1://input data
				{
					char word[30];
					int validWord = 0;
					
					do{
						printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
						getchar();
						scanf("%[^\n]", word);
					
						validWord = checkWord(word);
					}while(validWord == 0);
					
					char desc[30];
					int validDesc = 0;
				
					do{
						printf("Input a new slang word description [Must be more than 2 words]: ");
						getchar();
						scanf("%[^\n]", desc);
					
						validDesc = checkDesc(desc);
					}while(validDesc == 0);
					
					printf("\n");
					
					insertSlang(word, desc);
					
					getchar();
					printf("Press enter to continue...\n");
					getchar();
				}
				break;
				
			case 2://search data
				{
					char word[30];
					int validWord = 0;
					
					do{
						printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
						getchar();
						scanf("%[^\n]", word);
						
						validWord = checkWord(word);
					}while(validWord == 0);
					
					printf("\n");
					
					searchData(word);
					
					getchar();
					printf("Press enter to continue...\n");
					getchar();
				}
				break;	
				
			case 3://view with prefix
				{
					char word[30];
					printf("Input a prefix to be searched: ");
					scanf("%s", word);
					printf("\n");
					
					printByPrefix(word);
					
					getchar();
					printf("Press enter to continue...\n");
					getchar();
				}
				break;
					
			case 4://view all
				{
					printAll();
					getchar();
					printf("Press enter to continue...\n");
					getchar();
				}
				break;
				
			case 5://EXIT
				{
					printf("Thank you... Have a nice day :) \n");
					return 0;
				}
				break;
				
			default:
				
				printf("Please enter a valid choose.\n");
				getchar();
				
				printf("Press enter to continue...\n");
				getchar();
				break;
		}
	}while(choose != 5);
	
	return 0;
}
