/* DCA0209 - ALGORITMOS E ESTRUTURAS DE DADOS II 
Desenvolvido por Hadênia Rodrigues
Lista de Adjacencia*/

#include <iostream>
#include <vector>
using namespace std;

class GrafoListaAdj {
private:
    vector<string> vertices;

    //first � o indice do vertice, second � o peso (caso o grafo seja ponderado)
    vector<vector<pair<int, int>>> arestas;

    /**
    * A principio nao temos nenhuma ordenacao usando os rotulos.
    * Portanto, usaremos busca linear.
    **/
    int obterIndiceVertice(string rotuloVertice) {
        
        int size = (int)this->vertices.size();

        for (int i = 0; i < size; i++)
        {
            if (this->vertices[i] == rotuloVertice)
                return i;
        }

        return -1;
    }

public:
    /**
    * Lembrem-se:
    *       1) nao podemos inserir vertices com mesmo rotulo
    *       2) toda vez que inserirmos um novo v�rtice, precisaremos
    *          inserir um vetor para representar as conex�es daquele
    *          v�rtice na lista de adjac�ncias
    **/
    void inserirVertice(string rotuloVertice) {
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
    void inserirArestaDirecionada(string rotuloVOrigem, string rotuloVDestino) {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
    }

    void inserirArestaNaoDirecionada(string rotuloVOrigem, string rotuloVDestino) {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
        inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, 1);
    }

    void inserirArestaNaoDirecionada(string rotuloVOrigem, string rotuloVDestino, int peso) {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, peso);
        inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, peso);
    }

    /**
    * Inserir uma aresta entre rotuloVOrigem e rotuloVDestino com o peso
    * especificado.
    **/
    void inserirArestaDirecionada(string rotuloVOrigem, string rotuloVDestino, int peso) {
        //IMPLEMENTAR
        int vOrigem = this->obterIndiceVertice(rotuloVOrigem);
        int vDestino = this->obterIndiceVertice(rotuloVDestino);

        if (vOrigem == -1 || vDestino == -1)
        {
            return;
        }

        //Adiciona a nova aresta no vetor de arestas
        this->arestas[vOrigem].push_back(pair<int, int>(vDestino, peso));
    }

    /**
    * Verifica se v�rtice rotuloVOrigem e v�rtice rotuloVDestino s�o
    * conectados (vizinhos).
    **/
    bool saoConectados(string rotuloVOrigem, string rotuloVDestino) {
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

    vector<string> getVertices() {
        return vertices;
    }

    vector<vector<pair<int, int>>> getArestas() {
        return arestas;
    }
};