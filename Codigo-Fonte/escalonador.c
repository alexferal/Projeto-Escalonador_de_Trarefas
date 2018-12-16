#include <stdio.h>
#include <stdlib.h>

#define TAM 4
#define PRONTA 0
#define TERMINADA 1

int TEMPO = 0;

typedef struct tarefa{
	int tarefa;
	int duracao;
	int prioridade;
	int status;
	struct tarefa *prox;
	struct tarefa *ant;
}Tarefa;

typedef struct{
	Tarefa *p;
}Fila;

Fila *criaFila(){
	Fila *inicio = (Fila*) malloc(sizeof(Fila));
	inicio->p = NULL;
	return inicio; 
}

Tarefa *encontraProxima(Fila *inicio){
	
	if(inicio->p->prox == NULL || inicio->p->status == PRONTA){
		return inicio->p;
	}else{
		Tarefa *aux = inicio->p;
	
		while(aux->status != PRONTA && aux->prox != NULL){
	 		aux=aux->prox; 
		}
		return aux;
	}
}


void ordenarFila(Fila *inicio, Tarefa *nova){
	if(inicio->p == NULL){
		inicio->p = nova;
	}
	else if(inicio->p->prioridade < nova->prioridade && inicio->p->status == PRONTA){
		nova->prox = inicio->p;
		inicio->p->ant = nova;
		inicio->p = nova;
	}
	
		else{
			Tarefa *aux = inicio->p;
			aux = encontraProxima(inicio);
		
			while(aux->prox != NULL && aux->prioridade > nova->prioridade){  
			 	aux = aux->prox;
			}
			if(aux->prioridade<nova->prioridade){
		 		nova->ant = aux->ant;
		 		aux->ant->prox = nova;
		 		aux->ant = nova;
		 		nova->prox = aux;
		 	}else{
		 		aux->prox = nova;
		 		nova->ant = aux;
		 	}
		}
	}

void preencherFila(Fila *inicio, int mat[TAM][TAM], int vet[TEMPO]){
	int t, pos=0, k=0;
	int duracao=0;
	
	
	for(t=0; t<TEMPO; t+=duracao){
		while(mat[1][k]<=t && k<TAM){
			Tarefa *nova = (Tarefa*) malloc(sizeof(Tarefa));
			nova->tarefa = mat[0][k];
			nova->duracao = mat[2][k];
			nova->prioridade = mat[3][k];
			nova->status = PRONTA;
			nova->prox = NULL;
			nova->ant = NULL;
				
			duracao = nova->duracao;
				
			ordenarFila(inicio,nova);
			k++;
		}
		if(inicio->p != NULL){
			Tarefa *aux = encontraProxima(inicio); 
			int n;
			for(n=pos; n<(aux->duracao+pos); n++){
				vet[n] = aux->tarefa;
			}
			aux->status = TERMINADA;
			
			pos+=aux->duracao;
		}
	}
}

////////////////////////---LEITURA DE ARQUIVO---//////////////////////////////////
void lerDados (int mat[TAM][TAM]){
	
	FILE *file; //Cria ponteiro do tipo FILE
	file = fopen("tarefas.txt", "r"); //O pronteiro aponta para o arquico "teste.txt" e a leitura é aberta
	
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

int calcularDuracao(int mat[TAM][TAM]){
	int k,contDuracao = mat[2][0];
	
	for(k=1; k<TAM; k++)
		contDuracao += mat[2][k];
	
	return contDuracao;
}

void tempoMedio(Fila *inicio, int mat[TAM][TAM]){
	int k;
	float tempoExe=0, tempoEsp=0;
	
	for(k=0; k<TAM; k++){
		Tarefa *aux = inicio->p;
		float contExe = aux->duracao;
		while(aux->tarefa != k+1){
			aux = aux->prox;
			contExe = contExe + (float)aux->duracao;
		}
		tempoExe = tempoExe + (contExe - (float)mat[1][k]);
	}
	tempoExe = tempoExe/TAM;
	
	printf("\nTEMPO DE EXECUCAO: %.2f", tempoExe);
	
	for(k=0; k<TAM; k++){
		Tarefa *aux = inicio->p;
		float contEsp = 0;
		while(aux->tarefa != k+1){
			contEsp = contEsp + (float)aux->duracao;
			aux = aux->prox;
		}
		tempoEsp = tempoEsp + (contEsp - (float)mat[1][k]);
	}
	tempoEsp = tempoEsp/TAM;
	
	printf("\nTEMPO DE ESPERA: %.2f", tempoEsp);
	
	printf("\n");
	
}

void imprimeGrafico(int vet[TEMPO]){
	int k, i;
	
	system("cls");
	
	printf("ID TAREFAS");
	
	for(i=TAM; i>0; i--){
		
		printf("\n%d ´", i);
		for(k=0; k<TEMPO; k++){
			if(vet[k] == i){
				printf("|°|");
			}else{
				printf("   ");
			}
		}
	}
	
	printf("\n  ");
	
	for(k=0; k<=TEMPO; k++){
		printf("---");
	}
	
	printf(">T\n  ");
	
	for(k=0; k<=TEMPO; k++){
		if(k<10){
			printf("0%d ", k);
		}else{
			printf("%d ", k);
		}
	}
	
	printf("\n");
}




int main(void){
	
	int dados[TAM][TAM];
	
	lerDados(dados);
	
	TEMPO = calcularDuracao(dados);
	
	int execucao[TEMPO];
	
	Fila *inicio = criaFila();
	
	preencherFila(inicio, dados, execucao);
	
	imprimeGrafico(execucao);
	
	tempoMedio(inicio, dados);

	system("pause");
	return 0;
}
