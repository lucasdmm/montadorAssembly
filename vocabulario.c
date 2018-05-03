#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//V2
typedef struct tok {
	unsigned int id;
	char tipo[50];
	char word[255];
	struct tok *next;
}token;


token* create_token(){
	token *new_token = (token*) malloc (sizeof(token));
	new_token->id = 0;
	new_token->next = NULL;
	return new_token;
}

void inserirToken(char *word){
	
	//strcmp(word,);
}


int main(){
	token *symbolTable = create_token();
	strcpy(symbolTable->tipo, "Raiz");
	char instrucao[40][255];
	char registrador[260][255];
	FILE *pFile = fopen("instrucoesreservadas.txt","r");
	
	int i;
	char word[255];
	
	if(pFile == NULL){
		printf("Erro ao abrir o arquivo!");
		exit(1);
	}

	for(i=0;!feof(pFile);i++){
		fgets(word,255,pFile);
		if(!feof(pFile))
			strcpy(instrucao[i],word);
	}	
	fclose(pFile);
	
	// imprime as instrucoes reservadas para verificacao
	//for(i=0; i<40; i++)
	//	printf("%s",instrucao[i]);

	pFile = fopen("registradoresreservados.txt","r");
	
	if(pFile == NULL){
		printf("Erro ao abrir o arquivo!");
		exit(1);
	}

	rewind(pFile);
	for(i=0;!feof(pFile);i++){
		fgets(word,255,pFile);
		if(!feof(pFile))
			strcpy(registrador[i],word);
	}
	fclose(pFile);
	
	// imprime os registradores reservados para verificacao
	//for(i=0; i<260; i++)
	//	printf("%s",registrador[i]);

	return 0;
}

