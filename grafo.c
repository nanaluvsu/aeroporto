#include "grafo.h"
#include <stdlib.h>

Grafo* criar_grafo() {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    if (!grafo) return NULL;

    grafo->total_nodes = 0;
    grafo->conta_nodes = 0;
    grafo->matriz_adjacencia = NULL;
    grafo->nodes = NULL;

    return grafo;
}

static removerGrafo(Grafo* grafo) {
    if (!grafo) return;

    for (UI32 i = 0; i < grafo->total_nodes; i++) {
        free(grafo->matriz_adjacencia[i]);
    }
    free(grafo->matriz_adjacencia);
    free(grafo->nodes);
    free(grafo);
}