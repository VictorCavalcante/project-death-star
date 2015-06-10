/*
 * hashtable_list.c
 *  Created on: May 17, 2015
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define H_MAX 13

typedef struct h_node{
	char binary[9];
	char keyLetter;
	struct h_node* nextElement;
}H_node;

typedef struct hashtable{
	H_node *table[H_MAX];
}Hashtable;

Hashtable* createHashTable(){
	Hashtable* newTable = malloc(sizeof(Hashtable));
	int i;
	for(i = 0; i < H_MAX; i++){
		newTable->table[i] = NULL;
	}
	return newTable;
}

int hashGenerator(char key){
	return key % H_MAX;
}

void put(Hashtable* ht, char *binary, char keyLetter){
	int h = hashGenerator(keyLetter);
	H_node* newElement = (H_node*)malloc(sizeof(H_node));
	strcpy(newElement->binary, binary);
	newElement->keyLetter = keyLetter;
	newElement->nextElement = ht->table[h];
	ht->table[h] = newElement;
}

char* get(Hashtable* ht, char keyLetter){
	int h = hashGenerator(keyLetter);
	H_node* current = ht->table[h];
	while(current != NULL && current->keyLetter != keyLetter){
		current = current->nextElement;
	}
	if(current == NULL){
		return "not found";
	} else {
		return current->binary;
	}
}

void printHashTable(Hashtable *ht){
    int i;
    H_node *current;
    for(i = 0; i < H_MAX; i++){
		printf("\n[%d.]--", i);
		current = ht->table[i];
		while(current != NULL){
			printf("%c|%s -> ", current->keyLetter, current->binary);
			current = current->nextElement;
		}
    }
}

void freeHashTable(Hashtable *ht){
    int i;
    H_node *current, *previous;
    for(i = 0; i < H_MAX; i++){
		current = ht->table[i];
		while(current != NULL){
			previous = current;
			current = current->nextElement;
			free(previous);
		}
    }
}