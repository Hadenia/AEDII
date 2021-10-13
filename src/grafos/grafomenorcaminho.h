/* DCA0209 - ALGORITMOS E ESTRUTURAS DE DADOS II 
Desenvolvido por Hadênia Rodrigues
Grafo Menor Caminho*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define POS_INF 1000000000
#define NEG_INF -1000000000

class GrafoListaAdj
{
private:
    vector<string> vertices;

    //first � o indice do vertice, second � o peso (caso o grafo seja ponderado)
    vector<vector<pair<int, int>>> arestas;

    /**
    * A principio nao temos nenhuma ordenacao usando os rotulos.
    * Portanto, usaremos busca linear.
    **/
    int obterIndiceVertice(string rotuloVertice)
    {
        //IMPLEMENTAR
        int size = (int)this->vertices.size();

        for (int i = 0; i < size; i++)
        {
            if (this->vertices[i] == rotuloVertice)
                return i;
        }

        return -1;
    }

    /**
    * O argumento indicesVerticesVisitados serve para controlar quais
    * vertices j� foram visitados.
    * Lembrando que DFS � uma fun��o recursiva.
    **/
    void dfs(string rotuloVOrigem, bool *indicesVerticesVisitados)
    {
        //IMPLEMENTAR
        int origem = this->obterIndiceVertice(rotuloVOrigem);

        if (indicesVerticesVisitados[origem])
            return;
        indicesVerticesVisitados[origem] = true;

        vector<pair<int, int>> vizinhos = this->arestas[origem];
        for (auto a : vizinhos)
        {
            dfs(this->vertices[a.first], indicesVerticesVisitados);
        }
    }

public:
    /**
    * Lembrem-se:
    *       1) nao podemos inserir vertices com mesmo rotulo
    *       2) toda vez que inserirmos um novo v�rtice, precisaremos
    *          inserir um vetor para representar as conex�es daquele
    *          v�rtice na lista de adjac�ncias
    **/
    void inserirVertice(string rotuloVertice)
    {
        //IMPLEMENTAR
        for (string v : this->vertices)
        {
            if (v == rotuloVertice)
                return;
        }
        this->vertices.push_back(rotuloVertice);
        this->arestas.push_back(vector<pair<int, int>>{});
    }

    /**
    * Sempre que o grafo for n�o ponderado, adicionaremos o peso 1,
    * por conveni�ncia.
    **/
    void inserirArestaDirecionada(string rotuloVOrigem, string rotuloVDestino)
    {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
    }

    void inserirArestaNaoDirecionada(string rotuloVOrigem, string rotuloVDestino)
    {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
        inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, 1);
    }

    void inserirArestaNaoDirecionada(string rotuloVOrigem, string rotuloVDestino, int peso)
    {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, peso);
        inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, peso);
    }

    /**
    * Inserir uma aresta entre rotuloVOrigem e rotuloVDestino com o peso
    * especificado.
    **/
    void inserirArestaDirecionada(string rotuloVOrigem, string rotuloVDestino, int peso)
    {
        //IMPLEMENTAR
        int vOrigem = this->obterIndiceVertice(rotuloVOrigem);
        int vDestino = this->obterIndiceVertice(rotuloVDestino);

        if (vOrigem == -1 || vDestino == -1)
        {
            return;
        }

        this->arestas[vOrigem].push_back(pair<int, int>(vDestino, peso));
    }

    /**
    * Verifica se v�rtice rotuloVOrigem e v�rtice rotuloVDestino s�o
    * conectados (vizinhos).
    **/
    bool saoConectados(string rotuloVOrigem, string rotuloVDestino)
    {
        //IMPLEMENTAR
        int vOrigem = this->obterIndiceVertice(rotuloVOrigem);
        int vDestino = this->obterIndiceVertice(rotuloVDestino);

        if (vOrigem == -1 || vDestino == -1)
        {
            return false;
        }

        for (pair<int, int> a : this->arestas[vOrigem])
        {
            if (a.first == vDestino)
                return true;
        }

        return false;
    }

    /**
    * Verifica se h� algum caminho entre v�rtice rotuloVOrigem e 
    * v�rtice rotuloVDestino.
    * A melhor forma de fazer isto � reusando a fun��o dfs.
    **/
    bool haCaminho(string rotuloVOrigem, string rotuloVDestino)
    {
        //IMPLEMENTAR
              
        int vDestino = this->obterIndiceVertice(rotuloVDestino);
        int vOrigem = this->obterIndiceVertice(rotuloVOrigem);
       
        if(vDestino == vOrigem && saoConectados(rotuloVOrigem, rotuloVDestino) == false){
            return false;
        }
        
        if (vDestino == -1 || vOrigem == -1)
            return false;

        bool *indicesVerticesVisitados = (bool *)malloc(this->vertices.size() * sizeof(bool));

        for (int i = 0; i < this->vertices.size(); i++)
            indicesVerticesVisitados[i] = false;

        dfs(rotuloVOrigem, indicesVerticesVisitados);

        bool visitado = indicesVerticesVisitados[vDestino];

        free(indicesVerticesVisitados);
        return visitado;    
    }

    /**
    * Muda os r�tulos do v�rtices dos diferentes componentes para
    * nomes que representam cores.
    * Dica: procura componentes partindo do v�rtice v0 ou v1, em ordem
    * crescente (mas voc� pode usar outra ordem se desejar). 
    * Retorna a quantidade de componentes.
    * A melhor forma de fazer isto � reusando a fun��o dfs.
    **/
    int colorir()
    {
        int qtdComponente = 0;
        int qtdVertice = this->vertices.size();
        bool* indicesVerticesVisitados = (bool*)malloc(qtdVertice * sizeof(bool));
        bool* verticesColoridos = (bool*)malloc(qtdVertice * sizeof(bool));


        for (int i = 0; i < qtdVertice; i++)
            verticesColoridos[i] = false;

        for (int i = 0; i < qtdVertice; i++){

            if (verticesColoridos[i])
                continue;
            
            for (int i = 0; i < qtdVertice; i++)
                indicesVerticesVisitados[i] = false;
            

            dfs(this->vertices[i], indicesVerticesVisitados);

            for (int j = 0; j < qtdVertice; j++)
            {
                if (indicesVerticesVisitados[j])
                {
                    this->vertices[j] = this->vertices[i];
                    verticesColoridos[j] = true;
                }
            }

            qtdComponente++;
        }
        return qtdComponente; 
    }

    /**
    * Usa a abordagem de navega��o BFS para listar as dist�ncias
    * entre o v�rtice rotuloVOrigem e cada um dos demais v�rtices.
    * A fun��o BFS consegue listar a menor dist�ncia entre um v�rtice
    * e os demais se o grafo for N�O-PONDERADO.
    * Retorna um vetor de inteiros com a quantidade de arestas 
    * (dist�ncia) e o v�rtice rotuloVOrigem e cada um dos demais v�rtices.
    * N�o � uma fun��o recursiva. 
    * � necess�rio utilizar a ED fila.
    **/
    int *bfs(string rotuloVOrigem)
    {
      //IMPLEMENTAR
        int vOrigem = obterIndiceVertice(rotuloVOrigem);

        if (vOrigem == -1)
            return NULL;

        int qtVertices = this->vertices.size();

        queue<int> q;
        q.push(vOrigem);

        int *distance = (int *)malloc(sizeof(int) * qtVertices);
        for (int i = 0; i < qtVertices; i++)
            distance[i] = 0;

        bool *visited = (bool *)malloc(sizeof(bool) * qtVertices);
        for (int i = 0; i < qtVertices; i++)
        {
            visited[i] = false;
        }
        visited[vOrigem] = true;

        while (!q.empty())
        {
            int vFrontQueue = q.front();
            q.pop();

            // for (int vAresta = 0; vAresta < this->arestas[vFrontQueue].size(); vAresta++)
            for (pair<int, int> v : this->arestas[vFrontQueue])
            {
                if (!visited[v.first])
                {
                    visited[v.first] = true;

                    distance[v.first] = distance[vFrontQueue] + 1;

                    q.push(v.first);
                }
            }
        }

        return distance;
    }

    /**
    * Usamos o BellmanFord para encontrar menor caminho
    * em grafos com arestas com pesos negativos.
    * O BellmanFord consegue detectar ciclos negativos
    * e atribuir o valor NEG_INF (constante definida nesse arquivo)
    * aos v�rtices que perten�am ao ciclo.
    * POS_INF deve ser atribu�do aos v�rtices inalcan��veis.
    * O aspecto negativo � sua complexidade de tempo: O(V*E).
    * Isto acontece pois, como possui arestas negativas, cada v�rtice 
    * do grafo precisa ser processado V vezes.   
    * Pseudo-c�digo: https://github.com/eduardolfalcao/edii/blob/master/conteudos/Grafos.md#bellman-ford
    **/
    int *bellmanFord(string rotuloVOrigem)
    {        
       int qtVertices = vertices.size();

        int* distancia = new int[vertices.size()];        
        for (int i = 0; i < qtVertices; i++) {
            distancia[i] = POS_INF;
        }

        int vOrigem = GrafoListaAdj::obterIndiceVertice(rotuloVOrigem);
        distancia[vOrigem] = 0;

        for (int i = 1; i <= qtVertices - 1; i++) {
            for (int j = 0; j < vertices.size(); j++) {
                for (int k = 0; k < arestas[j].size(); k++) {
                    distancia[arestas[j][k].first] = min(distancia[arestas[j][k].first], distancia[j] + arestas[j][k].second);
                }
            }
        }
        for (int j = 0; j < vertices.size(); j++) {
            for (int k = 0; k < arestas[j].size(); k++) {
                if ((distancia[j] + arestas[j][k].second) < distancia[arestas[j][k].first]) {
                    distancia[arestas[j][k].first] = NEG_INF;
                }
            }
        }
        return distancia;
    }

    /**
    * Usamos o Dijkstra para encontrar menor caminho
    * em grafos sem arestas com pesos negativos.
    * O Dijkstra retorna respostas incorretas caso o grafo
    * possua arestas negativas, e portanto n�o consegue
    * detectar ciclos negativos. Este � o aspecto negativo.
    * POS_INF deve ser atribu�do aos v�rtices inalcan��veis.
    * O aspecto positivo � sua complexidade de tempo: O(V+E).
    * Isto acontece pois, como o grafo n�o possui arestas negativas, 
    * cada v�rtice do grafo precisa ser processado apenas 1 vez.
    * Pseudo-c�digo: https://github.com/eduardolfalcao/edii/blob/master/conteudos/Grafos.md#dijkstra
    * Ilustra��o: https://docs.google.com/drawings/d/1NmkJPHpcg8uVcDZ24FQiYs3uHR5n-rdm1AZwD74WiMY/edit?usp=sharing
    **/
    int *dijkstra(string rotuloVOrigem)
    {
        //IMPLEMENTAR
        priority_queue<pair<int, int>> q;
        int qtdVertice = this->vertices.size();

        int* distancias = new int[qtdVertice];
        for (int i = 0; i < qtdVertice; i++)
            distancias[i] = POS_INF;

        bool* visitados = new bool[qtdVertice];
        for (int i = 0; i < qtdVertice; i++)
            visitados[i] = false;

        int vOrigem = obterIndiceVertice(rotuloVOrigem);
        if (vOrigem == -1)
            return distancias;

        distancias[vOrigem] = 0;
        q.push({ 0, vOrigem });

        while (!q.empty())
        {
            int verticeAtual = q.top().second;
            q.pop();
            if (visitados[verticeAtual])
                continue;

            visitados[verticeAtual] = true;

            for (pair<int, int> a : this->arestas[verticeAtual])
            {
                int vDestino = a.first, peso = a.second;

                if (distancias[verticeAtual] + peso < distancias[vDestino])
                {
                    distancias[vDestino] = distancias[verticeAtual] + peso;
                    q.push({ -distancias[vDestino], vDestino });
                }
            }
        }

        return distancias;
    }

    vector<string> getVertices()
    {
        return vertices;
    }

    vector<vector<pair<int, int>>> getArestas()
    {
        return arestas;
    }
};