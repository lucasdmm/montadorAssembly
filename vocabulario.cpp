#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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
	char instrucoes[40][255];
	
	FILE *pfile = fopen("instrucoesreservadas.txt","r");
	
	
	if(pfile == NULL){
		printf("Erro ao abrir o arquivo!");
		exit(1);
	}else{
		int i;
		char word[255];
		for(i=0;!feof(pfile);i++){
			fgets(word,255,pfile);

			if(!feof(pfile))strcpy(instrucoes[i],word);
		}	
		fclose(pfile);
		for(i=0; i<40; i++)
					printf("%s",instrucoes[i]);
	}
	return 0;
}

