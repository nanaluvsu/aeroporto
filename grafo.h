#include "tipos.h"

#pragma once

typedef struct node
{
  const char* sigla;
  char* cidade;
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
  U32 id;
  char* origem;
  char* destino;
} Relacionamento;



Grafo* criar_grafo();
bool adicionar_node(Grafo* grafo, char* sigla, char* cidade);
bool adicionar_rel(Grafo* grafo, Relacionamento rel);
bool busca_og(Grafo* grafo, char* origem); //voos que partem de um aeroporto
bool busca_trajeto(Grafo* grafo, char* curr, char* destino, char* path, U32* pathLen,U32* mapVis); //voos que partem de um aeroporto e atinja outro. Importante mencionar que
// passam significa que o voo nao necessariamente vai até um aeroporto, mas que ele passa por ele