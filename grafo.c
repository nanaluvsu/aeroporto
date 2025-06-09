#include "grafo.h"
#include "tipos.h"
#include <stdlib.h>

Grafo* criar_grafo() {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    if (!grafo) return NULL;

    grafo->total_nodes = 0;
    grafo->qtd_nodes = 0;
    grafo->matriz_adjacencia = NULL;
    grafo->nodes = NULL;

    return grafo;
} // cria um grafo vazio



bool adicionar_node(Grafo* grafo, char* sigla, U32 cod) {
    for (U32 i = 0; i < grafo->qtd_nodes; i++) {
        if (grafo->nodes[i].codigo == cod) {
            return false; 
        }
    }
    grafo->qtd_nodes++;
    grafo->nodes = (Node*)realloc(grafo->nodes, grafo->qtd_nodes * sizeof(Node)); // realoca o vetor de 'nodes', definindo o tamanho dele como o número de nós que ele tem
    if (!grafo->nodes) return false; // se a realocação falhar, retorna falso(obvio)

    grafo->nodes[grafo->qtd_nodes - 1].sigla = sigla; // adiciona o novo nó ao vetor de nós
    grafo->nodes[grafo->qtd_nodes - 1].codigo = cod;  // define o código do nó
    grafo->total_nodes++; // incrementa o número total de nós(antes apenas a quantidade de nós era incrementada)

    //Realocação da matriz de adjacência
    grafo->matriz_adjacencia = (U32**)realloc(grafo->matriz_adjacencia, grafo->total_nodes * sizeof(U32*));
    if (!grafo->matriz_adjacencia) return false; // se a realocação falhar, retorna falso
    for (U32 i = 0; i < grafo->total_nodes; i++) {
        grafo->matriz_adjacencia[i] = (U32*)realloc(grafo->matriz_adjacencia[i], grafo->total_nodes * sizeof(U32));
        if (!grafo->matriz_adjacencia[i]) return false; // se a realocação falhar, retorna falso
    }
    for (U32 i = 0; i < grafo->total_nodes; i++) {
        grafo->matriz_adjacencia[grafo->qtd_nodes - 1][i] = 0; // inicializa a nova linha com 0
        grafo->matriz_adjacencia[i][grafo->qtd_nodes - 1] = 0; // inicializa a nova coluna com 0
    }
    return true; // se tudo der certo, retorna verdadeiro
    
}



static removerGrafo(Grafo* grafo) {
    if (!grafo) return;

    for (U32 i = 0; i < grafo->total_nodes; i++) {
        free(grafo->matriz_adjacencia[i]);
    }
    free(grafo->matriz_adjacencia);
    free(grafo->nodes);
    free(grafo);
} // função de apoio para remover o grafo (eu não quero ficar com minha memória toda xoxa :3)