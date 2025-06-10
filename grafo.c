#include "grafo.h"
#include "tipos.h"
#include <stdlib.h>
#include <stdio.h>

Grafo *criar_grafo()
{

    Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
    if (!grafo)
        return NULL;

    grafo->total_nodes = 5; // define o número total de nós como 5, pois inicialmente o grafo terá 5 nós
    grafo->qtd_nodes = 0;

    // inicializa a matriz de adjacência com zeros
    grafo->matriz_adjacencia = (U32 **)malloc(grafo->total_nodes * sizeof(U32 *));
    for (int i = 0; i < grafo->total_nodes; i++)
    {
        grafo->matriz_adjacencia[i] = (U32 *)malloc(grafo->total_nodes * sizeof(U32));
        for (int j = 0; j < grafo->total_nodes; j++)
        {
            grafo->matriz_adjacencia[i][j] = 0;
        }
    }
    grafo->nodes = NULL;

    return grafo;
} // cria um grafo vazio

bool adicionar_node(Grafo *grafo, char *sigla, U32 cod, char *cidade)
{
    for (U32 i = 0; i < grafo->qtd_nodes; i++)
    {
        if (grafo->nodes[i].codigo == cod)
        {
            return false;
        }
    }
    grafo->qtd_nodes++;                                                            // incrementa a quantidade de nós do grafo
    grafo->nodes = (Node *)realloc(grafo->nodes, grafo->qtd_nodes * sizeof(Node)); // realoca o vetor de 'nodes', definindo o tamanho dele como o número de nós que ele tem

    grafo->nodes[grafo->qtd_nodes - 1].sigla = sigla;   // adiciona o novo nó ao vetor de nós
    grafo->nodes[grafo->qtd_nodes - 1].codigo = cod;    // define o código do nó
    grafo->nodes[grafo->qtd_nodes - 1].cidade = cidade; // define a cidade do nó

    // Realocação da matriz de adjacência
    U32 novo_total = grafo->total_nodes + 1;
    grafo->matriz_adjacencia = (U32 **)realloc(grafo->matriz_adjacencia, novo_total * sizeof(U32 *));
    if (!grafo->matriz_adjacencia)
        return false; // se a realocação falhar, retorna falso
    for (U32 i = 0; i < novo_total; i++)
    {
        if (i >= grafo->total_nodes)
        {
            grafo->matriz_adjacencia[i] = (U32 *)malloc(novo_total * sizeof(U32));
        }
        else
        {
            grafo->matriz_adjacencia[i] = (U32 *)realloc(grafo->matriz_adjacencia[i], novo_total * sizeof(U32));
        }

        if (!grafo->matriz_adjacencia[i])
            return false; // se a realocação falhar, retorna falso

        for (U32 j = 0; j < novo_total; j++)
        {
            if (i == novo_total - 1 || j == novo_total - 1)
            {
                grafo->matriz_adjacencia[i][j] = 0;
            }
        }
    }
    grafo->total_nodes = novo_total; // incrementa o número total de nós(antes apenas a quantidade de nós era incrementada)
    return true;                     // se ele n morrer ele retorna true
}

bool adicionar_rel(Grafo *grafo, Relacionamento rel)
{
    printf("rel.id: %u\n", rel.id); // talvez desse errado entao fiz ele mostrar o id(nao muda o codigo so serve pra testar msm)
    for (U32 i = 0; i < grafo->qtd_nodes; i++)
    {

        if (grafo->nodes[i].codigo == rel.origem)
        {
            for (U32 j = 0; j < grafo->qtd_nodes; j++)
            {
                if (grafo->nodes[j].codigo == rel.destino)
                {
                    grafo->matriz_adjacencia[i][j] = rel.id;
                    grafo->matriz_adjacencia[j][i] = rel.id;
                    printf("Voo %u: %s-> Destino %s\n", rel.id, grafo->nodes[i].sigla, grafo->nodes[j].sigla);
                    return true;
                }
            }
        }
    }
    return false;
}

bool busca_og(Grafo *grafo, U32 origem_codigo)
{
    if (!grafo || grafo->qtd_nodes == 0)
    {
        printf("Nenhum voo cadastrado.\n"); //se nao tem no obviamente nao tem voo ne
        return false;
    }

    bool encontrou = false;
    bool origem_existe = false;
    for (U32 i = 0; i < grafo->qtd_nodes; i++)
    {
        if (grafo->nodes[i].codigo == origem_codigo)
        {
            origem_existe = true;
            printf("Voos com origem em %s (%u):\n", grafo->nodes[i].sigla, origem_codigo);
            for (U32 j = 0; j < grafo->qtd_nodes; j++)
            {
                if (grafo->matriz_adjacencia[i][j] != 0)
                {
                    printf("Destino: %s (%u), ID do voo: %u\n",
                           grafo->nodes[j].sigla, grafo->nodes[j].codigo,
                           grafo->matriz_adjacencia[i][j]);
                    encontrou = true;
                }
            }
            break;
        }
    }

    if (!origem_existe)
    {
        printf("Nenhum aeroporto encontrado com o código especificado.\n");
        return false;
    }

    if (!encontrou)
    {
        printf("Nenhum voo encontrado com origem no aeroporto especificado.\n");
    }
    return encontrou;
}
/*


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
                    if (grafo->matriz_adjacencia[i][j] == rel.id)
                    {
                        grafo->matriz_adjacencia[i][j] = 0;
                        grafo->matriz_adjacencia[j][i] = 0; // remove o voo da matriz de adjacência
                        printf("engoli\n");
                        return true;
                    }
                }
            }
        }
    }
    printf("Voo nao encontrado ou ID incorreto.\n");
    return false;
}*/
//meu metodo nao tava funcionando, entao rezei e joguei pro augusto isso
//no fim nao deu certo mas arrumei o dele e ta tendo
bool remover_rel(Grafo *grafo, Relacionamento rel)
{
    for (U32 i = 0; i < grafo->qtd_nodes; i++)
    { // itera os nós
        if (grafo->nodes[i].codigo == rel.origem)
        { // se encontrar a origem
            for (U32 j = 0; j < grafo->qtd_nodes; j++)
            { // itera a matriz
                if (grafo->nodes[j].codigo == rel.destino)
                { // se encontrar o destino
                    if (grafo->matriz_adjacencia[i][j] == rel.id)
                    {
                        grafo->matriz_adjacencia[i][j] = 0;
                        grafo->matriz_adjacencia[j][i] = 0; // remove o voo da matriz de adjacência
                        return true;
                    }
                }
            }
        }
    }
    return true;
}

Relacionamento cade(Grafo *grafo, U32 id)
{
    Relacionamento rel;
    rel.id = 0; // Valor padrão para indicar que não encontrou

    for (U32 i = 0; i < grafo->qtd_nodes; i++)
    {
        for (U32 j = 0; j < grafo->qtd_nodes; j++)
        { // itera a matriz
            if (grafo->matriz_adjacencia[i][j] == id)
            { // se encontrar
                rel.id = id;
                rel.origem = grafo->nodes[i].codigo;
                rel.destino = grafo->nodes[j].codigo;
                return rel; // retorna o relacionamento encontrado
            }
        }
    }

    return rel;
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
        printf("sigla: %s, codigo: %u, estado: %s\n", grafo->nodes[i].sigla, grafo->nodes[i].codigo, grafo->nodes[i].cidade);
    }
}

static void removerGrafo(Grafo *grafo)
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
    return;
} // função de apoio para remover o grafo (eu não quero ficar com minha memória toda xoxa :3)