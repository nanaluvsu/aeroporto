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

bool adicionar_rel(Grafo* grafo, U32 origem, U32 destino) {
    for (U32 i = 0; i < grafo->qtd_nodes; i++) {
        if (grafo->nodes[i].codigo == origem) {
            for (U32 j = 0; j < grafo->qtd_nodes; j++) {
                if (grafo->nodes[j].codigo == destino) {
                    //existe o nó de origem e destino, então adiciona a relação
                    grafo->matriz_adjacencia[i][j] = 1; 
                    grafo->matriz_adjacencia[j][i] = 1;
                    return true; 
                }
            }
        }
    }
}

static void listaAeroportos(Grafo* grafo) {
    if (!grafo || grafo->qtd_nodes == 0) {
        printf("Nenhum aeroporto cadastrado.\n");
        return;
    }
    printf("Lista:\n");
    for (U32 i = 0; i < grafo->qtd_nodes; i++) {
        printf("sigla: %s, codigo: %u\n", grafo->nodes[i].sigla, grafo->nodes[i].codigo);
    }
}

static void listaVoos(Grafo* grafo) {
    if (!grafo || grafo->qtd_nodes == 0) {
        printf("Nenhum voo cadastrado.\n");
        return;
    }
    printf("Lista de todos os voos:\n");
    for (U32 i = 0; i < grafo->qtd_nodes; i++) {
        for (U32 j = 0; j < grafo->qtd_nodes; j++) {
            if (grafo->matriz_adjacencia[i][j] == 1) {
                printf("%s (%u) -> %s(%u)\n", 
                       grafo->nodes[i].sigla, grafo->nodes[i].codigo,
                       grafo->nodes[j].sigla, grafo->nodes[j].codigo);
            }
        }
    }
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