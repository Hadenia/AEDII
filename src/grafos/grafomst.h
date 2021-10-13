/* DCA0209 - ALGORITMOS E ESTRUTURAS DE DADOS II 
Desenvolvido por Hadênia Rodrigues
Minimum Spanning Trees */

#include <iostream>
#include <vector>
#include <queue>
#include "stdbool.h"

using namespace std;
#define POS_INF 1000000000

class GrafoListaAdj {
private:
    vector<string> vertices;  

    //first é o indice do vertice, second é o peso (caso o grafo seja ponderado)
    vector<vector<pair<int, int>>> arestas;

    /**
    * A principio nao temos nenhuma ordenacao usando os rotulos.
    * Portanto, usaremos busca linear.
    **/
    int obterIndiceVertice(string rotuloVertice) {
        //reusar implementacao de exercicios anteriores
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
    *       2) toda vez que inserirmos um novo vértice, precisaremos
    *          inserir um vetor para representar as conexões daquele 
    *          vértice na lista de adjacências
    **/
    void inserirVertice(string rotuloVertice) {
        //reusar implementacao de exercicios anteriores
        for (string v : this->vertices)
        {
            if (v == rotuloVertice)
                return;
        }
        this->vertices.push_back(rotuloVertice);
        this->arestas.push_back(vector<pair<int, int>>{});  
    }

    /**
     * Sempre que o grafo for não ponderado, adicionaremos o peso 1,
     * por conveniência.
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
        //reusar implementacao de exercicios anteriores
        
        int vOrigem = this->obterIndiceVertice(rotuloVOrigem);
        int vDestino = this->obterIndiceVertice(rotuloVDestino);

        if (vOrigem == -1 || vDestino == -1)
        {
            return;
        }

        this->arestas[vOrigem].push_back(pair<int, int>(vDestino, peso));     
          
    }

    //Grupo do union-find
    class Grupo {
    public:
        int pai;
        int tamanho;
    };

    //encontrar raiz 
    //pode ser com ou sem path compression
    int encontrarRaiz(Grupo* grupos, int i) {
        //IMPLEMENTAR
        if(grupos[i].pai == i)
            return i;
        else
            return encontrarRaiz(grupos, grupos[i].pai);
    }

    bool mesmoGrupo(Grupo* grupos, int a, int b) {
        //IMPLEMENTAR
        if(encontrarRaiz(grupos, a) == encontrarRaiz(grupos, b)){
            return true;
        }else{
            return false;
        }        
    }

    int tamanhoGrupo(Grupo* grupos, int a) {
        //IMPLEMENTAR
        return grupos[a].tamanho;
    }

    
    void unirGrupos(Grupo* grupos, int a, int b) {

        //Encontrar as raizes de a e b
        int raizA = encontrarRaiz(grupos, a);    
        int raizB = encontrarRaiz(grupos, b);  

        //Verificar se estão as raizes são iguais, se são do mesmo grupo
        if (raizA == raizB) return;

        //se não descobrir qual raiz possui tamanho maior
        if (tamanhoGrupo(grupos, raizA) < tamanhoGrupo(grupos, raizB) ){
             grupos[raizB].tamanho +=  grupos[raizA].tamanho;
             grupos[raizA].pai = raizB;
        }else{
             grupos[raizA].tamanho +=  grupos[raizB].tamanho;
             grupos[raizB].pai = raizA; //apontar o grupo de B para o grupo de A
        }

    }

    //criei essa classe pra facilitar a ordenacao
    //das arestas com menor peso (que faz parte do
    //algoritmo de Kruskal)
    class Aresta {
    public:
        int origem;
        int destino;
        int peso;
        Aresta(int origem, int destino, int peso)
            : origem(origem), destino(destino), peso(peso)
        {}
    };
    

    //sobrescrever operator< para que a priority_queue
    //ordene como desejamos
    friend bool operator<(const Aresta& a1, const Aresta& a2) {
        //IMPLEMENTAR
        return a1.peso < a2.peso;        
    }

    GrafoListaAdj* KruskalMST() {
        //IMPLEMENTAR

        //instanciamos um novo grafo, que armazenara
        //apenas as arestas da MST
        GrafoListaAdj* mst = new GrafoListaAdj();

         //adicionar vertices
        for (int i = 0; i < vertices.size(); i++)
        {
            mst->inserirVertice(vertices.at(i));
        }

                       
        //inicializar estrutura do union-find (array de grupos)

        Grupo* grupos = new Grupo;

        for (int i = 0; i < vertices.size(); i++)
        {
            grupos[i].pai = i;
            grupos[i].tamanho = 1;
        }
       
        //inicializar priority_queue
      priority_queue<Aresta> arestasMenorPeso;
        //adicionar arestas na fila    

       /* Não consegui implementar a adiçao das arestas na fila de prioridade */
       
     /**    for (int i = 0; i < arestas.size(); i++)
            arestasMenorPeso.push(arestas.at(i));   **/
      

        //iterar na fila de arestas
            //se os vertices da arestas nao pertencem ao mesmo grupo
            //una-os, e adicione a aresta no MST       

       /* ***comentado para poder rodar**** */

     /*   while(!arestasMenorPeso.empty()){
            Aresta arestaAtual = arestasMenorPeso.top();

            arestasMenorPeso.pop();

            if(mesmoGrupo(grupos, arestaAtual.origem, arestaAtual.destino)){
                //não faz nada pois pertencem ao mesmo grupo
            }else{
                unirGrupos(grupos, arestaAtual.origem, arestaAtual.destino);
            } 

        } 
     */     

        return mst;
    }   

    vector<string> getVertices() {
        return vertices;
    }

    vector<vector<pair<int, int>>> getArestas() {
        return arestas;
    }
};