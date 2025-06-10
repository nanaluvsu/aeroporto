#include "grafo.h"
#include "tipos.h"
#include <stdlib.h>

Grafo *criar_grafo()
{
    Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
    if (!grafo)
        return NULL;

    grafo->total_nodes = 0;
    grafo->qtd_nodes = 0;
    grafo->matriz_adjacencia = NULL;
    grafo->nodes = NULL;

    return grafo;
} // cria um grafo vazio

bool adicionar_node(Grafo *grafo, char *sigla, U32 cod)
{
    for (U32 i = 0; i < grafo->qtd_nodes; i++)
    {
        if (grafo->nodes[i].codigo == cod)
        {
            return false;
        }
    }
    grafo->qtd_nodes++; // incrementa a quantidade de nós do grafo
    grafo->nodes = (Node *)realloc(grafo->nodes, grafo->qtd_nodes * sizeof(Node)); // realoca o vetor de 'nodes', definindo o tamanho dele como o número de nós que ele tem
    if (!grafo->nodes)
        return false; // se a realocação falhar, retorna falso(obvio)

    grafo->nodes[grafo->qtd_nodes - 1].sigla = sigla; // adiciona o novo nó ao vetor de nós
    grafo->nodes[grafo->qtd_nodes - 1].codigo = cod;  // define o código do nó
    grafo->total_nodes++;                             // incrementa o número total de nós(antes apenas a quantidade de nós era incrementada)

    // Realocação da matriz de adjacência
    grafo->matriz_adjacencia = (U32 **)realloc(grafo->matriz_adjacencia, grafo->total_nodes * sizeof(U32 *));
    if (!grafo->matriz_adjacencia)
        return false; // se a realocação falhar, retorna falso
    for (U32 i = 0; i < grafo->total_nodes; i++)
    {
        grafo->matriz_adjacencia[i] = (U32 *)realloc(grafo->matriz_adjacencia[i], grafo->total_nodes * sizeof(U32));
        if (!grafo->matriz_adjacencia[i])
            return false; // se a realocação falhar, retorna falso
    }
    for (U32 i = 0; i < grafo->total_nodes; i++)
    {
        grafo->matriz_adjacencia[grafo->qtd_nodes - 1][i] = 0; // inicializa a nova linha com 0
        grafo->matriz_adjacencia[i][grafo->qtd_nodes - 1] = 0; // inicializa a nova coluna com 0
    }
    return true; // se ele n morrer ele retorna true
}

bool adicionar_rel(Grafo *grafo, Relacionamento rel)
{
    for (U32 i = 0; i < grafo->qtd_nodes; i++)
    {
        for (U32 j = 0; j < grafo->qtd_nodes; j++)
        {
            if (grafo->matriz_adjacencia[i][j] == rel.id) //checa se o id existe. Se existir, id++
            {
                rel.id++; 
            }
        }
    }
    printf("rel.id: %u\n", rel.id); // talvez desse errado entao fiz ele mostrar o id(nao muda o codigo so serve pra testar msm)
    for (U32 i = 0; i < grafo->qtd_nodes; i++)
    {
        if (grafo->nodes[i].codigo == rel.origem)
        {
            for (U32 j = 0; j < grafo->qtd_nodes; j++)
            {
                if (grafo->nodes[j].codigo == rel.destino)
                {
                    // existe o nó de origem e destino, então adiciona a relação
                    grafo->matriz_adjacencia[i][j] = rel.id;
                    grafo->matriz_adjacencia[j][i] = rel.id;
                    return true;
                }
            }
        }
    }
    return false;
}

bool busca_rel(Grafo *grafo, Relacionamento rel)
{
    for (U32 i = 0; i < grafo->qtd_nodes; i++)
    {
        if (grafo->nodes[i].codigo == rel.origem)
        {
            for (U32 j = 0; j < grafo->qtd_nodes; j++)
            {
                if (grafo->nodes[j].codigo == rel.destino)
                {
                    if (grafo->matriz_adjacencia[i][j] == rel.id)
                    {
                        printf("Relacionamento encontrado: Origem %s (%u), Destino %s (%u), ID %u\n",
                               grafo->nodes[i].sigla, rel.origem,
                               grafo->nodes[j].sigla, rel.destino,
                               rel.id);
                        return true;
                    }
                }
            }
        }
    }
    printf("Relacionamento não encontrado.\n");
    return false;
} // busca um relacionamento específico no grafo

bool remove_rel(Grafo *grafo, Relacionamento rel)
{
    for (U32 i = 0; i < grafo->qtd_nodes; i++)
    {
        if (grafo->nodes[i].codigo == rel.origem)
        {
            for (U32 j = 0; j < grafo->qtd_nodes; j++)
            {
                if (grafo->nodes[j].codigo == rel.destino)
                {
                    grafo->matriz_adjacencia[i][j] = 0; // define a relação como inexistente
                    grafo->matriz_adjacencia[j][i] = 0; // define a relação como inexistente
                    return true;
                }
            }
        }
    }
    return false;
}

static void listaAeroportos(Grafo *grafo)
{
    if (!grafo || grafo->qtd_nodes == 0)
    {
        printf("Nenhum aeroporto cadastrado.\n");
        return;
    }
    printf("Aeroportos:\n");
    for (U32 i = 0; i < grafo->qtd_nodes; i++)
    {
        printf("sigla: %s, codigo: %u\n", grafo->nodes[i].sigla, grafo->nodes[i].codigo);
    }
}

static removerGrafo(Grafo *grafo)
{
    if (!grafo)
        return;

    for (U32 i = 0; i < grafo->total_nodes; i++)
    {
        free(grafo->matriz_adjacencia[i]);
    }
    free(grafo->matriz_adjacencia);
    free(grafo->nodes);
    free(grafo);
} // função de apoio para remover o grafo (eu não quero ficar com minha memória toda xoxa :3)