#include "tipos.h"

#pragma once

typedef struct node
{
  const char *sigla;
  U32 codigo;
  char *cidade;
} Node; // aeroporto

typedef struct grafo
{
  U32 total_nodes;
  U32 qtd_nodes;
  U32 **matriz_adjacencia;
  Node *nodes;
} Grafo;

typedef struct relacionamento
{
  U32 id;
  U32 origem;
  U32 destino;
} Relacionamento;

Grafo *criar_grafo();
bool adicionar_node(Grafo *grafo, 
  char *sigla, 
  U32 codigo, 
  char *cidade);
bool adicionar_rel(Grafo *grafo, 
  Relacionamento rel);
bool busca_og(Grafo *grafo, 
  U32 origem);                  
                                                                              // voos que partem de um aeroporto
bool busca_trajeto(Grafo *grafo, 
  U32 curr, 
  U32 destino, 
  U32 *path, 
  U32 *len,
  U32 *mapaVis);                                                              // busca um trajeto entre dois aeroportos, ou seja, busca por                                                       
                                                                              // voos que partem de um aeroporto e atinja outro. Importante mencionar que
                                                                              // passam significa que o voo nao necessariamente vai até um aeroporto, mas que ele passa por ele