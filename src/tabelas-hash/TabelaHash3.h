#include <vector>
#include<iostream>
using namespace std;

template <typename K, typename V>
class Tupla {
	private:
		K chave;
		V valor;
		Tupla* prox;
	public:
		Tupla(K c, V v) {
			chave = c;
			valor = v;
			prox = NULL;
		}

		K getChave() {
			return chave;
		}

		V getValor() {
			return valor;
		}

		Tupla* getProx() {
			return prox;
		}

		void setProx(Tupla* prox) {
			Tupla::prox = prox;
		}
};

template <typename Chave, typename Valor>
class TabelaHash {

	private:
		Tupla<Chave, Valor>** tabela;  //fazer malloc

		//tamanho atual do array
		int qtde_buckets; // inicializar com 8
		//qtdade de elementos já inseridos na tabela hash
		int tamanho; //inicializa com 0

		/**
		* Função para inserir a tupla <c,v> na tabela.
		* É preciso calcular o código hash a partir da chave c.
		* Em seguida, usamos qtde_buckets para descobrir o índice
		* dessa tupla. Prestar atenção na alocação de tupla quando
		* há colisões. A função hash às vezes retorna valores
		* negativos: use ) para evitar índices neativos.
		**/
		void inserir(Chave c, Valor v, Tupla<Chave, Valor>** tabela) {
			//IMPLEMENTAR
			size_t hashchave = hash<Chave>{}(c);
			int index = hashchave % qtde_buckets;

			Tupla<Chave, Valor>* tupla = new Tupla<Chave, Valor>(c, v);
			tupla->setProx(NULL);

			if(this->tabela[index] == NULL)
				tabela[index] = tupla;			

			else{
				
				Tupla<Chave, Valor>* front = tabela[index];

				//Navegar na lista encadeada
				while(front->getProx() != NULL){
					if(front->getChave() != c)
						front = front->getProx();
					else{
						//Chave já existe
						return;
					}
						 
				}

				front->setProx(tupla);

			}
		
		}

		/**
		* Função para aumentar o tamanho do array quando o
		* fator de carga for >= 1. O tamanho do array
		* (qtde_buckets) deve ser multiplicado por 8 para
		* que essa operação seja feita com pouca frequência.
		* Por fim, precisamos reposicionar as tuplas, considerando
		* que a posição nesse novo array com maior tamanho
		* será diferente.
		**/
		void aumentaArray() {
			//IMPLEMENTAR
			if(this->load_factor() >= 1){
				//Aumentar tamanho do array
				int qtde_buckets_ant = qtde_buckets;
				qtde_buckets = qtde_buckets * 8;
				//alocar inserir(); 

				Tupla<Chave, Valor>** new_table = new Tupla<Chave, Valor>*[qtde_buckets]();
					
				for (int i = 0; i < qtde_buckets_ant; i++) {
					if (tabela[i] != NULL) {
						Tupla<Chave, Valor>* front = tabela[i];

						while (front != NULL) {
							inserir(front->getChave(), front->getValor(), new_table);
							front =  front->getProx();
						}
					}
				}
			
				delete[] tabela;
				tabela = new_table;

			}else{
				return;
			}

		}

	public:

		/**
		* Inicializar o array de tuplas com capacidade = qtde_buckets.
		* Lembrar de setar todas as posições do array inicializado
		* para NULL. [calloc] 
		**/
		TabelaHash() {
			//IMPLEMENTAR

			qtde_buckets = 8;
			tamanho = 0;

			tabela = new Tupla<Chave, Valor>*[qtde_buckets]();
			for (int i = 0; i < qtde_buckets; i++)
				tabela[i] = NULL;

		}

		/**
		* Essa é a função pública que nos permite inserir
		* uma tupla <c,v> na tabela. Nessa função nós
		* verificamos se é preciso aumentar o array de acordo
		* com o load factor. Essa função pode reusar sua versão
		* sobrecarregada para inserir a tupla na tabela.
		* Essa função também incrementa a quantidade de elementos
		* na tabela (variável tamanho).
		**/
		void inserir(Chave c, Valor v) {
			//IMPLEMENTAR
			this->tamanho++;

			if(load_factor() >= 1)
				aumentaArray(); //Verifica o fator de carga e aumenta

			inserir(c, v, tabela);

		}

		/**
		* Essa função retorna o fator de carga da Tabela Hash.
		**/
		double load_factor() {
			//IMPLEMENTAR
			return  (double)tamanho / (double)qtde_buckets;
		}

		/**
		* Há apenas um valor associado a uma chave.
		* Essa função retorna esse valor, caso a chave exista.
		* Se a chave não existir a função retorna NULL.
		* Lembre-se: em caso de colisão, é preciso navegar
		* no bucket (lista ligada) para ter certeza se a chave
		* existe ou não.
		**/
		Valor getValor(Chave chave) {
			//IMPLEMENTAR
			size_t hashchave = hash<Chave>{}(chave);
			int index = hashchave % qtde_buckets;

			if(tabela[index] != NULL){
				
				Tupla<Chave, Valor>* front = tabela[index];

				//Navegar na lista encadeada
				while(front->getChave() != chave){
					if(front->getProx() == NULL)
						return 0;

					front = front->getProx();															
						 
				}
				return front->getValor();
			}

			return 0;

		}

		/**
		* Essa função retorna true caso a chave exista,
		* false caso contrário.
		* Lembre-se: em caso de colisão, é preciso navegar
		* no bucket (lista ligada) para ter certeza se a chave
		* existe ou não.
		**/
		bool contemChave(Chave chave) {
				size_t hashchave = hash<Chave>{}(chave);
				int index = hashchave % qtde_buckets;

				if(this->tabela[index] != NULL){
					
					Tupla<Chave, Valor>* front = this->tabela[index];

					//Navegar na lista encadeada
					while(front->getChave() != chave){
						if (front->getProx() == NULL) {
							return false;
						}
						front = front->getProx();	
					}
					return true;

				}
				
				return false;				
				
			}

		/**
		* Essa função retorna um vetor com todas as chaves
		* já inseridas na tabela.
		**/
		vector<Chave> getChaves() {
				//IMPLEMENTAR				

			vector<Chave> chaves;

			for (int i = 0; i < qtde_buckets; i++){
				if(this->tabela[i] != NULL){
						
					Tupla<Chave, Valor>* front = tabela[i];
						
					while(front != NULL){
						chaves.push_back(front->getChave());
						front = front->getProx();
					}
							
				}
			}
			return chaves;

		}

		/**
		* Essa função desaloca os nós previamente alocados, e muda
		* o tamanho do array de tuplas para 8.
		**/
		void clear() {
			//IMPLEMENTAR
	
			for (int i = 0; i < qtde_buckets; i++){
				Tupla<Chave, Valor>* front = tabela[i];
				while (front != NULL){
					Tupla<Chave, Valor>* temp = front;
					delete front; 
					front = temp->getProx();
				}
				tabela[i] = NULL;
			}

			delete[] tabela;

			qtde_buckets = 8;
			tamanho = 0;

			tabela = new Tupla<Chave, Valor>*[qtde_buckets]();
			for (int i = 0; i < qtde_buckets; i++)
				tabela[i] = NULL;	
		}

		/**
		* Há apenas um nó associado com uma mesma chave.
		* Essa função remove esse nó da tabela, caso a chave exista.
		* Se a chave não existir a função não faz nada.
		* Lembre-se: em caso de colisão, é preciso navegar
		* no bucket (lista ligada) para ter certeza se a chave
		* existe ou não.
		* Dica: olhar algoritmo de remoção em lista ligada, pois
		* após a remoção de um nó a lista precisa permanecer íntegra,
		* ou seja, navegável.
		**/
		void remover(Chave chave) {
			//IMPLEMENTAR
			size_t hashchave = hash<Chave>{}(chave);
			int index = hashchave % qtde_buckets;


			if (tabela[index] != NULL) {
			Tupla<Chave, Valor>* front = tabela[index];
			Tupla<Chave, Valor>* ant = NULL;

			while (front->getChave() != chave) {
				ant = front;
				front = front->getProx();
				if (front == NULL) {
					//Chave não existe
					return;
				}
			}

			if (ant == NULL) {
				tabela[index] = front->getProx();
			} else {
				ant->setProx(front->getProx());
			}
			tamanho--;
			delete front;
		}	
			
		}

		/**
		* Essa função retorna a quantidade de pares
		* que já foram inseridos na Tabela Hash.
		**/
		int size() {
			return tamanho;
		}

		/**
		* Essa função retorna o tamanho atual do
		* array usado para armazenar a Tabela Hash.
		**/
		int bucket_count() {
			return qtde_buckets;
		}

			friend std::ostream& operator<<(std::ostream& os, TabelaHash<Chave, Valor> hash_table) {
		for (int i = 0; i < hash_table.qtde_buckets; i++) {
			if (hash_table.tabela[i] != NULL) {
				os << std::setw(3) << i << ": (" << hash_table.tabela[i]->getChave() << ", " << hash_table.tabela[i]->getValor() << ")";

				if (hash_table.tabela[i]->getProx() != NULL) {
					auto next = hash_table.tabela[i]->getProx();
					do {
						os << " -> (" << next->getChave() << ", " << next->getValor() << ")";

						next = next->getProx();

					} while (next != NULL);

					os << " -> NULL\n";

				} else {
					os << " -> NULL\n";
				}
			} else {
				os << std::setw(3) << i << ": NULL\n";
			}
		}

		return os;
	}
};