#include "tipos.h"

#pragma once

typedef struct node
{
  const char* sigla;
  U32 codigo;
} Node; //aeroporto

typedef struct grafo
{
  U32 total_nodes;
  U32 qtd_nodes;
  U32** matriz_adjacencia;
  Node* nodes;
} Grafo;


typedef struct relacionamento
{
  U32 origem;
  U32 destino;
} Relacionamento;



Grafo*   criar_grafo();
bool     adicionar_node(Grafo* grafo, char* sigla, U32 codigo);
bool     adicionar_relacionamento (Grafo* grafo, U32 origem, U32 destino);
U32     busca_node (Grafo* grafo, char* sigla);