#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{   
    struct Trie *children[26];
    int count;
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *pCrawl = pTrie;
    int index;
    for (int i = 0; i < strlen(word); i++)
    {
        index = word[i] - 'a';
        if (!pCrawl->children[index])
        {
            pCrawl->children[index] = (struct Trie *)malloc(sizeof(struct Trie));
            pCrawl->children[index]->count = 0;
            for (int j = 0; j < 26; j++)
            {
                pCrawl->children[index]->children[j] = NULL;
            }
        }
        pCrawl = pCrawl->children[index];
    }
    pCrawl->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie *pCrawl = pTrie;
    int index;
    for (int i = 0; i < strlen(word); i++)
    {
        index = word[i] - 'a';
        if (!pCrawl->children[index])
        {
            return 0;
        }
        pCrawl = pCrawl->children[index];
    }
    return pCrawl->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < 26; i++)
    {
        deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    pTrie->count = 0;
    for (int i = 0; i < 26; i++)
    {
        pTrie->children[i] = NULL;
    }
    return pTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: File not found\n");
        exit(1);
    }
    int numWords = 0;
    pInWords = (char **)malloc(256 * sizeof(char *));
    while (!feof(fp))
    {
        pInWords[numWords] = (char *)malloc(256);
        fscanf(fp, "%s", pInWords[numWords]);
        numWords++;
    }
    fclose(fp);
    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}