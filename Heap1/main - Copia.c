#include <malloc.h>
#include <stdio.h>
#define true 1
#define false 0

typedef int bool;
int anota;

typedef struct heap{
	int * valor;
	int tamanhoAtual;
	int tamanhoMaximo;
} HEAP;

//Inicializa��o do Heap
void inicializaHeap(HEAP * heap, int tamanhoMaximo){
	heap->valor = (int*) malloc(sizeof(int)*(tamanhoMaximo+1));
	heap->tamanhoAtual = 1;
	heap->tamanhoMaximo = tamanhoMaximo;
}

//Exclus�o 
void excluiHeap(HEAP * heap){
	int tamanho = heap->tamanhoMaximo;
	free(heap->valor);
	heap->tamanhoMaximo = 0;
	heap->tamanhoAtual = 0;
}

void excluiRaiz(HEAP * heap, int valor){
	
	int indice, auxiliar, temporaria;
	int atual = heap->tamanhoAtual;

	if(heap->valor[1] == valor){
		//auxiliar recebe o valor atual da posicao
		auxiliar = heap->valor[1];
		
		//a posicao atual recebe o valor do ultimo elemento
		heap->valor[1] = heap->valor[atual];
		heap->valor[atual] = NULL;
		
		//chama heap pra reordenar!!!
		constroiHeapMaximo(&heap);
	}
	return true;
}




//Declara��o de Pai, Filho da Esquerda e da Direita
int pai(int indice){
  return indice/2;
}
int filhoEsquerda(int indice){
  return 2 * indice;
}
int filhoDireita(int indice){
  return 2 * indice + 1;
}

/*Quando o heap para qualquer j>i est� ordenado, por�m o indice n�o � necessariamente maior que seus filhos*/
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
		maximoHeap(heap, indice);/*j� est� ordenado por�m, o indice n�o � necessariamente maior que seus filhos*/
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
  
  int indice, tamanho = heap.tamanhoAtual;
  
  for (indice=1; indice<=tamanho; indice++) 
  		printf("%d ",heap.valor[indice]);
  
  printf("\n");
}

// Imprime elementos em ordem decrescente e esvazia o heap
void heapSort(HEAP * heap){
	int indice, auxiliar, tamanho = heap->tamanhoAtual;
	
	constroiHeapMaximo(heap);  // se o grupo de dados j� � um heap, nao precisa desta linha
	
	for (indice = tamanho; indice > 1; indice--){
		auxiliar = heap->valor[1];
		heap->valor[1] = heap->valor[indice];
		heap->valor[indice] = auxiliar;
		(heap->tamanhoAtual)--;
		maximoHeap(heap, 1);
	}
	heap->tamanhoAtual = tamanho;
}

//insere normalmente
bool insere(HEAP * heap, int valor){
	
	int indice, auxiliar;
	
	if (heap->tamanhoAtual == heap->tamanhoMaximo) 
		return false;
		
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

//pr�-ordem
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
  
  inicializaHeap(&heap, 100);
  
  printf("= = = = = = = = = = = = = = = = = = = = = =");
  printf("\n\tH\tE\tA\tP\n");
  printf("= = = = = = = = = = = = = = = = = = = = = =\n");
  
  
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
  
  printf("\n\t- - - VALORES INSERIDOS - - -\n");
  imprime(heap);
  printf("\n");
  
  //Chama a constru��o do Heap, neste caso o m�ximo
  constroiHeapMaximo(&heap);
  
  
  
  
  
  printf("    - - - TROCA PARA HEAP MINIMO - - -\n");
  imprime(heap);
  
  preOrdem(&heap,1);
  printf("\n");
  heapSort(&heap);  
  imprime(heap);
 // excluiHeap(&heap);
  
  excluiRaiz(&heap, 40);
  printf("\n\n\n*********Apos exclusao do 40\n");
  imprime(heap);
  
  
  
  
  
  
  printf("\n\n\t- - - INSERCAO - - -\n");  
  inicializaHeap(&heap, 50);
  
  printf("\n**Niveis atingidos:\n");
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
  
  printf("\n\n");
  printf("Atualizacao do heap: ");
  imprime(heap);
  
  /*o Heap ja esta corretamente montado, o comando a seguir nao alterara nada*/
  constroiHeapMaximo(&heap);
  printf("Impressao do heap: ");
  imprime(heap);
  
  printf("Pre-order do heap: ");
  preOrdem(&heap,1);
  printf("\n");  
  heapSort(&heap);  
  
  printf("Heap minimo: ");
  imprime(heap);
  printf(".\n.\n.\n.\nExcluindo heap\n\n\n");
  excluiHeap(&heap);
 
}

