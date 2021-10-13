/* DCA0209 - ALGORITMOS E ESTRUTURAS DE DADOS II 
Desenvolvido por Hadênia Rodrigues
Matriz de Adjacencia*/

#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
 
struct GrafoMatrizAdj {
    int** arestas;
    char** rotuloVertices;
    int verticesInseridos;
    int maxNumVertices;     
    //faz mais sentido ser apenas numVertices (consertar para a prox turma)
};

/**
 * Se o grafo for ponderado, inicializamos cada posicao da matriz com INT_MAX.
 * Se o grafo for não ponderado, inicializamos cada posicao da matriz com 0.
 **/
struct GrafoMatrizAdj* inicializar(int numVertices, bool ponderado) {
   GrafoMatrizAdj* G = (struct GrafoMatrizAdj*)malloc(sizeof(struct GrafoMatrizAdj));	
	
	G->rotuloVertices = (char**)malloc(numVertices * sizeof(char*));
	G->arestas = (int**)malloc(numVertices * sizeof(int*));
	G->maxNumVertices = numVertices;
	G->verticesInseridos = 0;

	for (int i = 0; i < numVertices; i++) {
		G->arestas[i] = (int*)malloc(numVertices * sizeof(int));
	}

	if (ponderado == true) {
		for (int i = 0; i < numVertices; i++)
		{
			for (int j = 0; j < numVertices; j++)
			{
			    G->arestas[i][j] = INT_MAX;
			}
		}
	}
	else {
		//[i][j] = 0
		for (int i = 0; i < numVertices; i++)
		{
			for (int j = 0; j < numVertices; j++)
			{
				 G->arestas[i][j] = 0;
			}
		}
	}


	return G;
}

/**
 * A principio nao temos nenhuma ordenacao usando os rotulos.
 * Portanto, usaremos busca linear
 **/
int obterIndiceVertice(struct GrafoMatrizAdj* grafo, char* rotuloVertice) {
    for (int i = 0; i < grafo->maxNumVertices; i++) {
		if (strcmp(rotuloVertice, grafo->rotuloVertices[i]) == 0)
			return i;		
	}
	return -1;
}

/**
 * Se o grafo for ponderado, usamos a variavel peso para especificar o peso da aresta.
 * Se o grafo for não ponderado, passaremos o valor 1 para a variavel peso, de modo que represente existência da aresta.
 * Se um dos rotulos dos vertices nao existir, simplesmente nao faremos nada.
 **/
void inserirAresta(struct GrafoMatrizAdj* grafo, char* rotuloVOrigem, char* rotuloVDestino, int peso) {
    int vOrigem = obterIndiceVertice(grafo, rotuloVOrigem);
	int vDestino = obterIndiceVertice(grafo, rotuloVDestino);

	if (vOrigem != -1 && vDestino != -1) {
			grafo->arestas[vOrigem][vDestino] = peso;
			grafo->arestas[vDestino][vOrigem] = peso;
	}
}

/**
 * Usamos a variavel grafo->verticesInseridos para controlar a quantidade de vertices que ja foi inserido no grafo.
 * Logo, ela pode/deve ser usada para especificar em qual posicao o vertice a ser inserido sera alocado.
 **/
void inserirVertice(struct GrafoMatrizAdj* grafo, char* rotuloVertice) {
   if (grafo->verticesInseridos > grafo->maxNumVertices) {
		printf("Erro! Número máximo de vértices atingido %d > %d\n", grafo->verticesInseridos, grafo->maxNumVertices);
		return;
	}
	else {
		grafo->rotuloVertices[grafo->verticesInseridos] = rotuloVertice;
		grafo->verticesInseridos++;
		return;
	} 
}

/**
 * Tomar cuidado com as diferenças semânticas entre haver conexão entre dois vertices em um grafo ponderado,
 * e haver conexão entre dois vertices em um grafo nao-ponderado.
 **/
bool saoConectados(struct GrafoMatrizAdj* grafo, char* rotuloVOrigem, char* rotuloVDestino) {
    int vOrigem = obterIndiceVertice(grafo, rotuloVOrigem);
    if (vOrigem == -1)
    {
        return false;
    }

    int vDestino = obterIndiceVertice(grafo, rotuloVDestino);
    if (vDestino == -1)
    {
        return false;
    }

    if(grafo->arestas[vOrigem][vDestino] > 0 || vOrigem == vDestino){
        return true;
    }
}
