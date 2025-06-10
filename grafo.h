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



Grafo* criar_grafo();
bool adicionar_node(Grafo* grafo, char* sigla, U32 codigo);
bool adicionar_rel(Grafo* grafo, U32 origem, U32 destino);
bool busca_og(Grafo* grafo, U32 origem); //voos que partem de um aeroporto
bool busca_dt(Grafo* grafo, U32 origem, U32 destino); //voos que chegam a um aeroporto