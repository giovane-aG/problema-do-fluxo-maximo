/*
    Paulo Henrique de Oliveira
    Giovane Aguiar de Almeida
    Wagner Moretti
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////
vector<vector<int>> FormAdjMatrix(int qtd, int v1[], int v2[], int peso[], int linhas)
{
  // Lista de adjacência.
  vector<vector<int>> adjMatrix;
  // [
  //    [0,0,0,0,0],
  //    [0,0,0,0,0],
  //    [0,0,0,0,0],
  //    [0,0,0,0,0],
  // ]

  const int n = qtd;
  // Inicializando todos os valores com 0.
  for (int i = 0; i < n; i++)
  {
    vector<int> row;
    adjMatrix.push_back(row);
    for (int j = 0; j < n; j++)
    {
      adjMatrix[i].push_back(0);
    }
  }

  // Inserindo o peso das arestas.
  for (int j = 0; j < linhas; j++)
  {
    adjMatrix[v1[j]][v2[j]] = peso[j];
  }

  return adjMatrix;
}
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
// Uma versão da busca em largura que retorna true se existe um caminho ligando a origem ao destino.
bool BFS(vector<vector<int>> &resAdjMatrix, int &source, int &sink, vector<int> &parent)
{
  // Cria um vetor de visitados, inicializando todas as posições com falso.
  int n = resAdjMatrix.size();
  bool visited[n] = {false};

  // Fila de execução
  queue<int> q;

  // Insere o valor origem passado como parâmetro e o marca como visitado.
  q.push(source);
  visited[source] = true;
  parent[source] = -1;

  while (q.empty() == false)
  {
    int u = q.front();
    q.pop();

    // Explorando o vértice u.
    for (int i = 0; i < n; i++)
    {
      int v = i;
      int capacity = resAdjMatrix[u][v];

      // Encotramos um vizinho que não foi visitado e com capacidade maior que zero.
      if (visited[v] == false && capacity > 0)
      {
        // Inserimos o vizinho na fila, setamos o vértice pai e o marcamos como visitado.
        q.push(v);
        parent[v] = u;
        visited[v] = true;
      }
    }
  }

  // Se o vértice destino está marcado como visitado é sinal que exite um caminho entre a origem e ele, retornamos true.
  if (visited[sink] == true)
  {
    return true;
  }

  return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
// Algoritmo de Ford Fulkerson que retorna o fluxo máximo.
int FordFulkerson(vector<vector<int>> &adjMatrix, int &source, int &sink)
{
  int maxflow = 0;

  // Cria um grafo residual.
  vector<vector<int>> resAdjMatrix;
  int n = adjMatrix.size();
  for (int i = 0; i < n; i++)
  {
    vector<int> row;
    resAdjMatrix.push_back(row);
    for (int j = 0; j < adjMatrix[i].size(); j++)
    {
      resAdjMatrix[i].push_back(adjMatrix[i][j]);
    }
  }

  // Cria uma lista de pais para a busca em largura guardar os caminhos aumentantes.
  vector<int> parent;
  for (int i = 0; i < n; i++)
  {
    parent.push_back(-1);
  }

  // Enquanto a busca retornar true continuamos executar o algoritmo.
  while (BFS(resAdjMatrix, source, sink, parent) == true)
  {
    // Devemos encontrar o fluxo máximo no caminho que acabamos de encontrar.
    int pathflow = 10000007;

    // Percorremos o caminho.
    int v = sink;
    while (v != source)
    {
      int u = parent[v]; // O vértice pai.

      // Atualizamos o fluxo do caminho para essa capacidade caso ele seja menor.
      int capacity = resAdjMatrix[u][v];
      pathflow = min(pathflow, capacity);

      // Atualizamos o valor de v para a próxima aresta do caminho.
      v = u;
    }

    // Atualizamos as capacidades residuais das arestas e arestas reversas.
    v = sink;
    while (v != source)
    {
      int u = parent[v]; // O vértice pai.

      // Atualizando as capacidades.

      resAdjMatrix[u][v] -= pathflow;
      resAdjMatrix[v][u] += pathflow;

      // Atualizamos o valor de v para a próxima aresta do caminho.
      v = u;
    }

    // Incrementamos o valor atual de fluxo ao fluxo total.
    maxflow += pathflow;
  }

  return maxflow;
}
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
int maxFlux(int src, int snk, vector<vector<int>> adjMatrix)
{
  // Cria a lista de adjacência.

  return FordFulkerson(adjMatrix, src, snk);
}
/////////////////////////////////////////////////////////////////////////////////////////
