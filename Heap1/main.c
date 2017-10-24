#include <malloc.h>
#include <stdio.h>
#define true 1
#define false 0

typedef int bool;

typedef struct heap{
	int * valor;
	int tamanhoAtual;
	int tamanhoMaximo;
} HEAP;

//Inicialização do Heap
void inicializaHeap(HEAP * heap, int tamanhoMaximo){
	heap->valor = (int*) malloc(sizeof(int)*(tamanhoMaximo + 1));
	heap->tamanhoAtual = 1;
	heap->tamanhoMaximo = tamanhoMaximo;
}

//Exclusão 
void excluiHeap(HEAP * heap){
	int tamanho = heap->tamanhoMaximo;
	free(heap->valor);
	heap->tamanhoMaximo = 0;
	heap->tamanhoAtual = 0;
}

//Declaração de Pai, Filho da Esquerda e da Direita
int pai(int indice) {return indice/2; }
int filhoEsquerda(int indice) {return 2 * indice;}
int filhoDireita(int indice) {return 2 * indice + 1;}

/*Quando o heap para qualquer j>i está ordenado, porém o indice não é necessariamente maior que seus filhos*/
void maximoHeap(HEAP * heap, int indice){
	int auxiliar, esquerda = filhoEsquerda(indice), direita = filhoDireita(indice), maior = indice;
	
	if ((esquerda <= heap->tamanhoAtual) && (heap->valor[esquerda] > heap->valor[indice])) 
		maior = esquerda;
	if ((direita <= heap->tamanhoAtual) && (heap->valor[direita] > heap->valor[maior])) 
		maior = direita;
	if (maior != indice) {		
		auxiliar = heap->valor[indice];
		heap->valor[indice] = heap->valor[maior];
		heap->valor[maior] = auxiliar;
		maximoHeap(heap, maior);
	}
}

// Constroi heap usando o metodo maximoHeap
void constroiHeapMaximo(HEAP * heap){
	int indice, metadeTamanho = heap->tamanhoAtual/2;
	for (indice = metadeTamanho; indice > 0; indice--) 
		maximoHeap(heap, indice);/*já está ordenado porém, o indice não é necessariamente maior que seus filhos*/
}

// Insere no final do heap
bool insereForaDeOrdem(HEAP * heap, int valor){
	
  if (heap->tamanhoAtual < heap->tamanhoMaximo){
		heap->tamanhoAtual++;
		heap->valor[heap->tamanhoAtual] = valor;
		return true;
	}
	return false;
}

// Imprime a arvore (na ordem que estiver)
void imprime(HEAP heap){  
  int indice;  
  if(heap.tamanhoAtual > 0){
  	for (indice = 1; indice <= heap.tamanhoAtual; indice++) 
  		printf("%d ",heap.valor[indice]);
  }else
  	printf("\t--> Nao ha valores para imprimir!");
  
  printf("\n");
}

// Imprime elementos em ordem decrescente e esvazia o heap
void heapSort(HEAP * heap){
	int indice, auxiliar, tamanho = heap->tamanhoAtual;
	
	constroiHeapMaximo(heap);  // se o grupo de dados já é um heap, nao precisa desta linha
	
	for (indice = tamanho; indice > 1; indice--){
		auxiliar = heap->valor[1];
		heap->valor[1] = heap->valor[indice];
		heap->valor[indice] = auxiliar;
		(heap->tamanhoAtual)--;
		maximoHeap(heap, 1);
	}
	heap->tamanhoAtual = tamanho;
}

void corrigeHeap(HEAP* heap){
	int indice, pai, filhoEsquerda, filhoEscolhido, filhoDireita;
	
	for(indice=1; indice < heap->tamanhoAtual; indice++){
		pai = indice/2+1; 
		filhoEsquerda = 2 * indice;
		filhoDireita = 2 * indice + 1;
		
		//printf("\nto na correcao...\n");
		//if (filhoDireita >= heap->tamanhoAtual) filhoDireita = filhoEsquerda;
		
		if (heap->valor[filhoEsquerda] > heap->valor[filhoDireita])	filhoEscolhido = filhoEsquerda;
		else filhoEscolhido = filhoDireita;	
					
		if (heap->valor[pai] < heap->valor[filhoEscolhido]){
			int aux = heap->valor[pai];
			heap->valor[pai] = heap->valor[filhoEscolhido];
			heap->valor[filhoEscolhido] = aux;
		}else
			break;
		pai = filhoEscolhido;
		
	}
} 

void removeRaizAtual(HEAP *heap){
	if (heap->tamanhoAtual > 0) {
		 float topo = heap->valor[1];
		 heap->valor[1] = heap->valor[heap->tamanhoAtual];
		 heap->tamanhoAtual--;
		 corrigeHeap(heap);
	}
}

//aqui removo um valor especifico
void removeValor(HEAP *heap, int valor){
	int indice;
	for(indice=0; indice < heap->tamanhoMaximo; indice++){
		if(valor == heap->valor[indice]){
			float topo = heap->valor[indice];
			heap->valor[indice] = heap->valor[heap->tamanhoAtual];
			heap->tamanhoAtual--;
			printf("\tValor a ser removido: %d...\n", valor);
			corrigeHeap(heap);
		}
	}	
}

//aqui eu faço consulta de valores
void consultaValor(HEAP *heap, int valor){
	int indice;
	for(indice=0; indice < heap->tamanhoMaximo; indice++){
		if(valor == heap->valor[indice]){
			if(heap->valor[pai(indice)>0]){
				printf("-Valor consultado: %d", valor);
				printf("\n\t-Seu pai: %d", heap->valor[pai(indice)]);
				printf("\n\t-Filho da esquerda deste pai: %d", heap->valor[filhoEsquerda(pai(indice))]);
				printf("\n\t-Filho da direita deste pai: %d", heap->valor[filhoDireita(pai(indice))]);
				if(heap->valor[filhoEsquerda(indice)])
					printf("\n\t-Filho da esquerda do valor consultado: %d", heap->valor[filhoEsquerda(indice)]);
				else
					printf("\n\t-Este valor nao tem filhos a esquerda.");
				if(heap->valor[filhoDireita(indice)])
					printf("\n\t-Filho da direita do valor consultado: %d", heap->valor[filhoDireita(indice)]);
				else
					printf("\n\t-Este valor nao tem filhos a direita.");
			}
		}
	}	
}

//insere normalmente
bool insere(HEAP * heap, int valor){	
	int indice, auxiliar;
	
	if (heap->tamanhoAtual == heap->tamanhoMaximo) return false;
		
	heap->tamanhoAtual++;
	indice = heap->tamanhoAtual;
	heap->valor[indice] = valor;
	
	while ((indice > 1) && (heap->valor[pai(indice)] < heap->valor[indice])){
		auxiliar = heap->valor[indice];
		heap->valor[indice] = heap->valor[pai(indice)];
		heap->valor[pai(indice)] = auxiliar;       
		indice = pai(indice);
	}
	return true;
}

//pré-ordem
int preOrdem(HEAP* heap, int atual){
  if (atual <= heap->tamanhoAtual){
    printf("%i ", heap->valor[atual]);
    preOrdem(heap, filhoEsquerda(atual));
    preOrdem(heap, filhoDireita(atual));
  }
}

int alturaHeap(HEAP* heap){
	int i, altura = -1, indice = 1;
	
	while (indice <= heap->tamanhoAtual){
		indice = filhoEsquerda(indice);
		altura++;
		for(i = 1; i < indice; i++){
			printf(" ");
		}
	}
	return altura;
}

main(){
  
  HEAP heap;
  
  inicializaHeap(&heap, 50);
  
  printf("= = = = = = = = = = = = = = = = = = = = = = = = = =");
  printf("\n\t   H\t   E\t   A\t   P\n");
  printf("= = = = = = = = = = = = = = = = = = = = = = = = = =\n");  
  
  //insere os valores na arvore binaria heap 
  insereForaDeOrdem(&heap,10);
  insereForaDeOrdem(&heap,5);
  insereForaDeOrdem(&heap,3);
  insereForaDeOrdem(&heap,20);
  insereForaDeOrdem(&heap,8);
  insereForaDeOrdem(&heap,6);
  insereForaDeOrdem(&heap,15);
  insereForaDeOrdem(&heap,1);
  insereForaDeOrdem(&heap,18);
  insereForaDeOrdem(&heap,40);
  insereForaDeOrdem(&heap,17);
  insereForaDeOrdem(&heap,12);
  
  printf("\n=> VALORES INSERIDOS\n\t");
  imprime(heap);
  
  printf("\n=> CONSTRUCAO DOS HEAP MAXIMO\n\t");
  constroiHeapMaximo(&heap);
  imprime(heap);
  
  printf("\n=> CONSULTA DE VALOR\n\t");
  consultaValor(&heap, 8);
  //consultaValor(&heap, 17);
  //consultaValor(&heap, 20);
  
  printf("\n\n=> REMOCAO DE RAIZ\n\t");
  imprime(heap);
  removeRaizAtual(&heap);
  printf("\t");
  imprime(heap);
  
  printf("\n=> REMOCAO DE VALOR QUALQUER\n\t");
  //insere(&heap, 40);
  imprime(heap);
  //removeValor(&heap, 5);
  //removeValor(&heap, 15);
  removeValor(&heap, 1);
  printf("\t");
  imprime(heap);
    
  printf("\n\n=> TROCA PARA HEAP MINIMO\n\t");  
  imprime(heap);
  printf("\t");
  preOrdem(&heap,1);
  printf("\n\t");
  heapSort(&heap);  
  imprime(heap);
  
  //aqui estou separtando os niveis das inserções, uma balaquinha hahahahahaha
  printf("\n\n=> INSERCAO (**Niveis atingidos)\n");
  inicializaHeap(&heap, 50);
  insere(&heap,10);  
  printf("(%i)\n", alturaHeap(&heap));
  insere(&heap,5); 
  printf("(%i)\n", alturaHeap(&heap));
  insere(&heap,3);
  printf("(%i)\n", alturaHeap(&heap));
  insere(&heap,20);
  printf("(%i)\n", alturaHeap(&heap));
  insere(&heap,8);
  printf("(%i)\n", alturaHeap(&heap));
  insere(&heap,6);
  printf("(%i)\n", alturaHeap(&heap));
  insere(&heap,15);
  printf("(%i)\n", alturaHeap(&heap));
  insere(&heap,1);
  printf("(%i)\n", alturaHeap(&heap));
  insere(&heap,18);
  printf("(%i)\n", alturaHeap(&heap));
  insere(&heap,40);
  printf("(%i)\n", alturaHeap(&heap));
  insere(&heap,17);
  printf("(%i)\n", alturaHeap(&heap));
  insere(&heap,12);
  printf("(%i)\n", alturaHeap(&heap));
  
  printf("\n");
  printf("Atualizacao do heap: ");
  imprime(heap);
  
  /*o Heap ja esta corretamente montado, o comando a seguir nao alterara nada*/
  constroiHeapMaximo(&heap);
  printf("Impressao do heap: ");
  imprime(heap);
  
  printf("Pre-order do heap: ");
  preOrdem(&heap,1);
  
  printf("\nHeap minimo: ");
  heapSort(&heap);  
  imprime(heap);
  
  printf(".\n.\n.\n.\nExcluindo heap completamente...\n\n\n");
  excluiHeap(&heap);
  //imprimi apenas para mostrar que o heap foi excluido por completo!
  imprime(heap);
}


