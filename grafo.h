#include "tipos.h"

#pragma once
typedef unsigned int UI32;

typedef struct node_t
{
  const char* sigla;
  UI32 codigo;
} Node;

typedef struct grafo_t
{
  UI32 total_nodes;
  UI32 conta_nodes;
  UI32** matriz_adjacencia;
  Node* nodes;
} Grafo;

Grafo*   criar_grafo();
bool     adicionar_node(Grafo* grafo,   const char* sigla, UI32 codigo);
bool     adicionar_aresta (Grafo* grafo, UI32 origem, UI32 destino);
UI32     busca_node (Grafo* grafo, const char* sigla);