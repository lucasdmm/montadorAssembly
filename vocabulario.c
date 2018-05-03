#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// GLOBAL VARIABLES: oi
char instrucao[40][255];
char registrador[260][255];

typedef struct tok {
	int id;
	char tipo[50];
	char word[255];
	struct tok *next;
}token;


token* create_token(int id, char *tipo, char *word){
	token *new_token = (token*) malloc (sizeof(token));
	new_token->id = id;
	strcpy(new_token->tipo, tipo);
	strcpy(new_token->word, word);
	new_token->next = NULL;
	return new_token;
}

_Bool isDigit(char c){
	if (c >= '0' && c <= '9')
		return 1;
	else
		return 0;
}

int isAlpha(char c){
	if((c >= 'a' && c <= 'z')||(c >= 'A' && c <= 'Z'))
		return 1;
	else
		return 0;
}
int isAlphaHex(char c){
	if((c >= 'a' && c <= 'f')||(c >= 'A' && c <= 'F')||(isDigt(c)))
		return 1;
	else
		return 0;
}

int isBit(char c){
	if(c == '0' || c == '1')
		return 1;
	else
		return 0;
}

_Bool isNum(char *word){
	char *c = word;	
	while(*c != '\0'){
		if(!isDigit(*c))
			return 0;
		c++;
	}
	return 1;
}


_Bool isHex(char *word){
	char *c = word;
	if(*c == 'H')
		c++;
	if(*c == '\''){
		do{
			c++;
		} while(isDigit(*c));
		if(*c != '\'')
			return 0;
		c++;
		if(*c != '\0')
			return 0;
		return 1;
	}
	else if(*c != '0')
		return 0;
	c++;
	if(*c != 'X')
		return 0;
	do{
		c++;
	} while(isDigit(*c) || isAlphaHex(*c));
	if(*c != '\0')
		return 0; 
	
	return 1;
}

_Bool isBin(char *word){
	char *c = word;
	if(*c != 'B')
		return 0;
	c++;
	if(*c == '\''){
		do{
			c++;
		} while(isBit(*c));
		if(*c != '\'')
			return 0;
		c++;
		if(*c != '\0')
			return 0;
	}
	return 1;
}

_Bool isDec(char *word){
	char *c = word;
	if(*c != 'D')
		return 0;
	c++;
	if(*c == '\''){
		do{
			c++;
		} while(isDigit(*c));
		if(*c != '\'')
			return 0;
		c++;
		if(*c != '\0')
			return 0;
	}
	return 1;
}

void insert_token(char *word, token *symbolTable){
	int i;
	token *aux = symbolTable;

// Implementar Se BNF == Identificador
// Bloco para buscar por RESERVADOS

	for(i=0; instrucao[i][0]!= EOF; i++){
		if(strcmp(word, instrucao[i]) == 0){
			while(aux->next != NULL)
				aux = aux->next;			
			aux->next = create_token(100 + i, "Instrucao", word);
			return;
		}
	}
	for(i=0; registrador[i][0]!= EOF; i++)
		if(strcmp(word, registrador[i]) == 0){
			while(aux->next != NULL)
				aux = aux->next;			
			aux->next = create_token(200 + i, "Registrador", word);
			return;
		}
// FIM DO BLOCO PALAVRAS RESERVADAS
/*
	
	Se o Identificador nao for palavra reservada, sera uma label
*/

}

void preprocess(FILE *inputFile){
	int c;
	FILE * outputFile = fopen("preprocessed.asm", "w");
	if(outputFile == NULL){
		printf("Erro ao abrir o arquivo!");
		exit(1);
	}
	while(!feof(inputFile)){					
		c = fgetc(inputFile);							
		if(c == ';'){							//Remover os comentarios
			while(c != '\n'){
				c = fgetc(inputFile);
			}
			fseek(inputFile, -1, SEEK_CUR);
		}
		if(c == ',')
			fprintf(outputFile, "%s", " , ");
		if(c == ' ' || c == '\t' ){				//Remover espaÃ§os e tabs repetidos
			fprintf(outputFile, "%c" , '*');
			while(c == ' ' || c == '\t' ){
				c = fgetc(inputFile);
			}
			fseek(inputFile, -1, SEEK_CUR);
		}
		if(c>0){
			fprintf(outputFile, "%c" , c);	
		}
	}	
	fclose(outputFile);

	//printf("//Remover separando 1 e 2 operadores\n");

	
}

int main(){
	token *symbolTable = create_token(0, "SymbolTable", "Raiz");

	FILE *pFile = fopen("instrucoesreservadas.txt","r");
	
	int i;
	char word[255];
	if(pFile == NULL){
		printf("Erro ao abrir o arquivo!");
		exit(1);
	}

	for(i=0;!feof(pFile);i++){
		fgets(word,255,pFile);
		word[strlen(word)-1] = '\0';
		if(!feof(pFile))
			strcpy(instrucao[i],word);
	}	
	fclose(pFile);
	instrucao[i][0]= EOF;
	
	// imprime as instrucoes reservadas para verificacao
	//for(i=0; instrucao[i][0]!= EOF; i++)
	//	printf("%s\n",instrucao[i]);

	pFile = fopen("registradoresreservados.txt","r");
	
	if(pFile == NULL){
		printf("Erro ao abrir o arquivo!");
		exit(1);
	}

	rewind(pFile);
	for(i=0;!feof(pFile);i++){
		fgets(word,255,pFile);
		word[strlen(word)-1] = '\0';
		if(!feof(pFile))
			strcpy(registrador[i],word);
	}
	fclose(pFile);
	registrador[i][0]= EOF;
	
	// imprime os registradores reservados para verificacao
	//for(i=0; registrador[i][0]!= EOF; i++)
	//	printf("%s\n",registrador[i]);
	
	pFile = fopen("codigofonte.asm","r");
	if(pFile == NULL){
		printf("Erro ao abrir o arquivo!");
		exit(1);
	}
	preprocess(pFile);
	fclose(pFile);

	token *aux = symbolTable;
	insert_token("MOVF", symbolTable);
	insert_token("TRISA", symbolTable);
	do{
		printf("\nID: %d  TIPO: %s  PALAVRA: %s", aux->id, aux->tipo, aux->word);
		aux = aux->next;
	} while(aux != NULL);
	
	char teste[255] = "D'0010'";
	if(isDec(teste))
		printf("\n %s Eh um decimal", teste);
	else
		printf("\n %s Nao eh um decimal", teste);

	return 0;
}

