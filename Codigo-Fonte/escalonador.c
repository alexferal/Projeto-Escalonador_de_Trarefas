#include <stdio.h>
#include <stdlib.h>

#define TAM 4

struct tarefa{
	int numTarefa;
	int ingresso;
	int duracao;
	int prioridade;
	struct tarefa *prox;
};
typedef struct tarefa Tarefa;

struct prontas{
	Tarefa *inicio;
};
typedef struct prontas Prontas;

Prontas *criaListaProntas(){
	Prontas *primeiro = (Prontas*) malloc(sizeof(Prontas));
	primeiro->inicio = NULL;
	return primeiro; 
}


////////////////////////EM ANDAMENTO//////////////////////////////////
void ordenarLista(Prontas *primeira, Tarefa *nova){      
//	if(primeira->inicio == NULL){
//		primeira->inicio = nova;
//	}else{
//		Tarefa *aux = primeira->inicio;
//		if((nova->prioridade>=aux->prioridade) && (aux == primeira->inicio){
//			primeira->inicio = nova;
//			nova->prox = aux;
//		}else if()
//	}
}


////////////////////////EM ANDAMENTO//////////////////////////////////
void Escalonador(Prontas *inicio, int mat[TAM][TAM]){
//	int i,j,k, vetPrioridade[];
//	
//	for(k=0; k<TAM; k++){
//		Tarefa *t = (Tarefa*) malloc(sizeof(Tarefa));
//		t->numTarefa = mat[0][k];
//		t->ingresso = mat[1][k]
//		t->duracao = mat[2][k];
//		t->prioridade = mat[3][k];
//		t->prox = NULL;
//	}
	
	
}


////////////////////////PROCEDIMENTO DE LEITURA DE ARQUIVO//////////////////////////////////
void lerDados (int mat[TAM][TAM]){
	
	FILE *file; //Cria ponteiro do tipo FILE
	file = fopen("teste.txt", "r"); //O pronteiro aponta para o arquico "teste.txt" e a leitura é aberta
	
	if(file == NULL){ //Teste para verificar ser o ponteiro realmente recebeu o arquivo
		printf("Arquivo nao encontrado. \n");
		system("pause");
		exit (0);
	}
	
	char linha[10]; //declaração da String que irá receber cada linha do arquivo
	int i=0, j; //declaração dos contadores auxiliares 
	
	while(fgets(linha,10,file) != NULL){ // Os caracteres de cada linha são copiados para a String e no momento que encontrar NULL a condição será falsa 
		for(j=0;j<TAM;j++){
			mat[i][j] = linha[j] - 48; //Conversão de cada caractere para tipo inteiro e o campo da matriz recebe o valor
		}
		i++;
	}
	
	fclose(file); //Finalização e fechamento de leitura
}

void imprimeMatriz (int mat[TAM][TAM]){
	int i,j;
	
	for(i=0;i<TAM;i++){
		
		switch(i){
			case 0:
				printf("\nTarefa:		");
				break;
			case 1:
				printf("\nIngresso:	");
				break;
			case 2:
				printf("\nDuracao:	");
				break;
			default:
				printf("\nPrioridade:	");
				break;
		}
		for(j=0;j<TAM;j++){
			printf("%d ", mat[i][j]);
		}
		
		printf("\n");
	}
}


int main(void){
	
	int dados[TAM][TAM];
	
	lerDados(dados);
	
	imprimeMatriz(dados);
	
	system("pause");
	return 0;
}
