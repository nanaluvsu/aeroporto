#include "grafo.h"
#include "tipos.h"
#include <stdlib.h>
#include <stdio.h>

Grafo *criar_grafo()
{

    Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
    if (!grafo)
        return NULL;

    grafo->total_nodes = 0; // define o número total de nós como 5, pois inicialmente o grafo terá 5 nós
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

bool adicionar_node(Grafo *grafo, char *sigla, char *cidade)
{
    // Verifica se já existe um nó com a mesma sigla
    for (U32 i = 0; i < grafo->qtd_nodes; i++) {
        if (strcmp(grafo->nodes[i].sigla, sigla) == 0) {
            return false; // Nó duplicado
        }
    }

    // Aumenta a quantidade de nós no grafo
    grafo->qtd_nodes++;
    grafo->nodes = realloc(grafo->nodes, grafo->qtd_nodes * sizeof(Node));
    if (!grafo->nodes) return false; // Falha na realocação

    // Copia as strings para novos espaços de memória
    grafo->nodes[grafo->qtd_nodes - 1].sigla = strdup(sigla);
    grafo->nodes[grafo->qtd_nodes - 1].cidade = strdup(cidade);

    // Realoca a matriz de adjacência
    U32 novo_total = grafo->total_nodes + 1;
    grafo->matriz_adjacencia = realloc(grafo->matriz_adjacencia, novo_total * sizeof(U32 *));
    if (!grafo->matriz_adjacencia) return false;

    for (U32 i = 0; i < novo_total; i++) {
        if (i >= grafo->total_nodes) {
            grafo->matriz_adjacencia[i] = malloc(novo_total * sizeof(U32));
        } else {
            grafo->matriz_adjacencia[i] = realloc(grafo->matriz_adjacencia[i], novo_total * sizeof(U32));
        }
        if (!grafo->matriz_adjacencia[i]) return false;
    }

    // Inicializa as novas células da matriz com zero
    for (U32 i = 0; i < novo_total; i++) {
        for (U32 j = 0; j < novo_total; j++) {
            if (i >= grafo->total_nodes || j >= grafo->total_nodes) {
                grafo->matriz_adjacencia[i][j] = 0;
            }
        }
    }

    // Atualiza o número total de nós da matriz
    grafo->total_nodes = novo_total;
    return true;
}


bool adicionar_rel(Grafo *grafo, Relacionamento rel)
{
    for (U32 i = 0; i < grafo->qtd_nodes; i++)
    {
        printf("iterou1: i = %u, sigla = %s\n", i, grafo->nodes[i].sigla);

        if (strcmp(grafo->nodes[i].sigla, rel.origem) == 0)
        {
            printf("achou origem: %s\n", grafo->nodes[i].sigla);

            for (U32 j = 0; j < grafo->qtd_nodes; j++)
            {
                printf("  iterou2: j = %u, sigla = %s\n", j, grafo->nodes[j].sigla);

                if (strcmp(grafo->nodes[j].sigla, rel.destino) == 0)
                {
                    printf("  achou destino: %s\n", grafo->nodes[j].sigla);

                    // Protege contra acesso fora da matriz, embora i e j venham do loop
                    if (i < grafo->qtd_nodes && j < grafo->qtd_nodes)
                    {
                        grafo->matriz_adjacencia[i][j] = rel.id;
                        grafo->matriz_adjacencia[j][i] = rel.id;

                        printf("Voo %u cadastrado: %s -> %s\n", rel.id, grafo->nodes[i].sigla, grafo->nodes[j].sigla);
                        return true;
                    }
                    else
                    {
                        printf("Erro: índices fora do limite da matriz.\n");
                        return false;
                    }
                }
            }

            printf("Destino '%s' não encontrado.\n", rel.destino);
            return false; // Parar se origem achada, mas destino não
        }
    }

    printf("Origem '%s' não encontrada.\n", rel.origem);
    return false;
}


bool busca_og(Grafo *grafo, char* origem)
{
    if (!grafo || grafo->qtd_nodes == 0)
    {
        printf("Nenhum voo cadastrado.\n"); //se nao tem node obviamente nao tem voo ne
        return false;
    }
    bool encontrou = false;
    bool origem_existe = false;
    for (U32 i = 0; i < grafo->qtd_nodes; i++)
    {
        if (strcmp(grafo->nodes[i].sigla, origem) == 0) //se encontrar origem, define var como true
        {
            origem_existe = true; 
            printf("%s", grafo->nodes[i].sigla);
            printf("Voos com origem em %s (%s):\n", grafo->nodes[i].sigla, origem);
            for (U32 j = 0; j < grafo->qtd_nodes; j++)
            {
                if (grafo->matriz_adjacencia[i][j] != 0) //se existir
                {
                    printf("Destino: %s (%s), ID do voo: %u\n", //retorna detalhes do voo
                           grafo->nodes[j].sigla, grafo->nodes[j].sigla,
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
    return encontrou;
}

bool remover_rel(Grafo* grafo, Relacionamento rel) {
    if (!grafo || grafo->qtd_nodes == 0) return false; // Se o grafo não existir ou não tiver nós não faz

    U32 i_origem = -1, i_destino = -1; //definindo i_origem e i_destino como -1, que é um valor inválido para índices

    // Reaproveitei o for pra procurar agora os nós informados 
    for (U32 i = 0; i < grafo->qtd_nodes; i++) {
        if (grafo->nodes[i].sigla == rel.origem) i_origem = i; //define o indice de origem como o node atual
        if (grafo->nodes[i].sigla == rel.destino) i_destino = i; //defone o indice de destino como o node atual
    }

    // Se não encontrar um dos dois nós ele retorna falso pq nn tem o aeroporto cadastrado
    if (i_origem == (U32)-1 || i_destino == (U32)-1) {
        return false;
    }

    // Zera as entradas da matriz, removendo assim o voo
    grafo->matriz_adjacencia[i_origem][i_destino] = 0;
    grafo->matriz_adjacencia[i_destino][i_origem] = 0;

    return true;
}

Relacionamento cade(Grafo *grafo, U32 id)
{
    Relacionamento rel;
    rel.id = 0;         // Valor padrão indicando "não encontrado"
    rel.origem = NULL;  // Inicializa para evitar lixo
    rel.destino = NULL;

    for (U32 i = 0; i < grafo->qtd_nodes; i++)
    {
        for (U32 j = 0; j < grafo->qtd_nodes; j++)
        {
            if (grafo->matriz_adjacencia[i][j] == id)
            {
                // Encontrou o voo: retorna as siglas de origem e destino
                rel.id = id;
                rel.origem = grafo->nodes[i].sigla;
                rel.destino = grafo->nodes[j].sigla;
                return rel;
            }
        }
    }

    // Caso não encontre, retorna rel com id = 0 e siglas NULL
    return rel;
}


bool busca_trajeto(
    Grafo* grafo,
    char* curr,
    char* destino,
    char path[][4],  // Cada sigla é uma string de até 3 letras + '\0'
    U32 pathLen,
    U32* mapVis
) {
    U32 currIndex = -1, destinoIndex = -1;
    for (U32 i = 0; i < grafo->qtd_nodes; i++) {
        if (strcmp(grafo->nodes[i].sigla, curr) == 0) {
            currIndex = i;
        }
        if (strcmp(grafo->nodes[i].sigla, destino) == 0) {
            destinoIndex = i;
        }
    }

    if (currIndex == -1 || destinoIndex == -1) {
        return false;
    }

    mapVis[currIndex] = 1;
    strcpy(path[pathLen], curr); // Copia a sigla atual para o caminho
    pathLen++;

    if (currIndex == destinoIndex) {
        printf("Trajeto encontrado: ");
        for (U32 i = 0; i < pathLen; i++) {
            printf("%s ", path[i]);
        }
        printf("\n");
        mapVis[currIndex] = 0; // Libera para outras buscas
        return false; // <- Continua a buscar outros caminhos
    }

    for (U32 i = 0; i < grafo->qtd_nodes; i++) {
        if (grafo->matriz_adjacencia[currIndex][i] != 0 && !mapVis[i]) {
            busca_trajeto(grafo, grafo->nodes[i].sigla, destino, path, pathLen, mapVis);
        }
    }

    mapVis[currIndex] = 0;
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
        printf("sigla: %s, codigo: %u, estado: %s\n", grafo->nodes[i].sigla, grafo->nodes[i].sigla, grafo->nodes[i].cidade);
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