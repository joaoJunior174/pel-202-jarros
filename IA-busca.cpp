#include <iostream>
#include <cstdlib>
#include<stdio.h>
#include <stack> //para DFS
#include <queue> //para BFS
#include <vector> //para mostrar o caminho realizado pelo BFS :)


using namespace std;

//classe que armazena as jarras com suas capacidades em inteiro
class Jarras{
  
 public:

	 int jarra_3_litros;
	 int jarra_4_litros;

	 Jarras(int _3_litros, int _4_litros):
	 
	    jarra_3_litros(_3_litros),
	    jarra_4_litros(_4_litros)    

	 {}

};


//função para zerar a matriz em todo os estados possíveis, colocando eles como não visitados (0,0) ->0 (0,1)->0... e assim por diante
void zerarMatrizes(int mat[5][5]){

   for(int i=0;i<5;i++){

     for(int j=0;j<5;j++){
         mat[i][j] = 0;
     }  
       

   }


}


Jarras encherJarro3(Jarras &j,int verificaEstado[5][5]){

 if(j.jarra_3_litros < 3 && verificaEstado[3][j.jarra_4_litros] == 0){
        
          //seta que o caminho ja foi verificado
          verificaEstado[3][j.jarra_4_litros] = 1; 
          return Jarras(3,j.jarra_4_litros);
  }

  //-2 serve apenas para controle nas funções BFS e DFS, para encontrou um novo estado. Se não encontrou nada, retorna tudo (-2,-2)
  return Jarras(-2,-2);

}

Jarras encherJarro4(Jarras &j,int verificaEstado[5][5]){

  if(j.jarra_4_litros < 4 && verificaEstado[j.jarra_3_litros][4] == 0){
        
         //seta que o caminho ja foi verificado
         verificaEstado[j.jarra_3_litros][4] = 1; 
         return Jarras(j.jarra_3_litros,4);

  }
   //-2 serve apenas para controle nas funções BFS e DFS, para encontrou um novo estado. Se não encontrou nada, retorna tudo (-2,-2)
   return Jarras(-2,-2);

}
//transferir uma quantidade x do jarro 3 para o jarro 4
Jarras transferirJarro3(Jarras &j,int verificaEstado[5][5]){
    //verifica com a soma, se as quantidades em ambas as jarras passam da capacidade da jarra 4, se passar, é sinal que o que esta no jarro 3 ao ser transferido para o 4, ultrapassa o limite (que são 4 litros), e ainda sobra uma certa quantidade no jarro 3 (que é o resto da soma das duas quantidades por 4). Além disso, é verificado se esse estado já foi verificado
    if((j.jarra_4_litros + j.jarra_3_litros) >= 4 && verificaEstado[(j.jarra_4_litros + j.jarra_3_litros)%4][4] == 0){

    
          verificaEstado[(j.jarra_4_litros + j.jarra_3_litros)%4][4] = 1;
          return Jarras((j.jarra_4_litros + j.jarra_3_litros)%4,4);

    //caso isso não ocorra, então a soma não chega no limite da quantidade máxima que cabe no jarro 4, logo todo o conteúdo da jarra 3 é transferida para a jarra 4, ficando com 0 de conteúdo e a jarra de 4 litros com a soma dos dois.   
    }else if((j.jarra_4_litros + j.jarra_3_litros) < 4 && verificaEstado[0][j.jarra_4_litros + j.jarra_3_litros] == 0){
	
          verificaEstado[0][j.jarra_4_litros + j.jarra_3_litros] = 1;
          return Jarras(0,j.jarra_4_litros + j.jarra_3_litros);

         
    }    
    //-2 serve apenas para controle nas funções BFS e DFS, para encontrou um novo estado. Se não encontrou nada, retorna tudo (-2,-2)
    return Jarras(-2,-2);

}
//transferir uma quantidade x do jarro 4 para o jarro 3
Jarras transferirJarro4(Jarras &j,int verificaEstado[5][5]){

  //verifica com a soma, se as quantidades em ambas as jarras passam da capacidade da jarra 3, se passar, é sinal que o que esta no jarro 4 ao ser transferido para o 3, ultrapassa o limite (que são 3 litros), e ainda sobra uma certa quantidade no jarro 4 (que é o resto da soma das duas quantidades por 3). Além disso, é verificado se esse estado já foi verificado

  if((j.jarra_4_litros + j.jarra_3_litros) >= 3 && verificaEstado[3][(j.jarra_4_litros + j.jarra_3_litros)%3] == 0){

          verificaEstado[3][(j.jarra_4_litros + j.jarra_3_litros)%3] = 1;
          return Jarras(3,(j.jarra_4_litros + j.jarra_3_litros)%3);
        
    //caso isso não ocorra, então a soma não chega no limite da quantidade máxima que cabe no jarro 3, logo todo o conteúdo da jarra 4 é transferida para a jarra 3, ficando com 0 de conteúdo e a jarra de 3 litros com a soma dos dois. 
    }else if ((j.jarra_4_litros + j.jarra_3_litros) < 3 && verificaEstado[j.jarra_4_litros + j.jarra_3_litros][0] == 0){

          verificaEstado[j.jarra_4_litros + j.jarra_3_litros][0] = 1;
          return Jarras(j.jarra_4_litros + j.jarra_3_litros,0);

         
    }    
    //-2 serve apenas para controle nas funções BFS e DFS, para encontrou um novo estado. Se não encontrou nada, retorna tudo (-2,-2)
    return Jarras(-2,-2);


}


Jarras esvaziarJarro3(Jarras &j,int verificaEstado[5][5]){

  //se a jarra tem conteudo e o estado não foi verificado, entra na condição
  if(j.jarra_3_litros !=0 && verificaEstado[0][j.jarra_4_litros] ==0){

     verificaEstado[0][j.jarra_4_litros] = 1;
     return Jarras(0,j.jarra_4_litros); 

  }
  //-2 serve apenas para controle nas funções BFS e DFS, para encontrou um novo estado. Se não encontrou nada, retorna tudo (-2,-2)
  return Jarras(-2,-2);

}

Jarras esvaziarJarro4(Jarras &j,int verificaEstado[5][5]){
  //se a jarra tem conteudo e o estado não foi verificado, entra na condição
  if(j.jarra_4_litros !=0 && verificaEstado[j.jarra_3_litros][0] ==0){

     verificaEstado[j.jarra_3_litros][0] = 1;
     return Jarras(j.jarra_3_litros,0); 

  }
  //-2 serve apenas para controle nas funções BFS e DFS, para encontrou um novo estado. Se não encontrou nada, retorna tudo (-2,-2)
  return Jarras(-2,-2);

}


void BFS(int verificaEstado[5][5],queue<Jarras> &filaDeBusca,int &x,int &y,vector<vector<vector < Jarras> > > &caminhoBFS){
    
//vector<vector< Jarras> > &caminhoBFS serve para guarda o pai do vertice atual
      
      Jarras j = filaDeBusca.front();
      //lógica que verifica se o estado atual é o desejado (-1 serve para dizer que independe do estado de x ou y encontrado, lógica explicada na função main)
      if((j.jarra_3_litros ==x && j.jarra_4_litros == y) || (x == -1 && j.jarra_4_litros == y) || (j.jarra_3_litros == x && y == -1)){
           
           x=j.jarra_3_litros;
           y=j.jarra_4_litros;
           return;
      
      }

      else{  
          
          //verificar os próximos possíveis estados para cada uma das operações nos jarros de 3 e 4, para o BFS, se verifica vários estados adjacentes ao atual com várias verificações, por isso se utilizam vários if's sequenciais.
          Jarras j1 = encherJarro3(j,verificaEstado);
          Jarras j2 = transferirJarro3(j,verificaEstado);
          Jarras j3 = esvaziarJarro3(j,verificaEstado);
          Jarras j4 = encherJarro4(j,verificaEstado);
          Jarras j5 = transferirJarro4(j,verificaEstado);
          Jarras j6 = esvaziarJarro4(j,verificaEstado);
          if(j1.jarra_3_litros != -2){
           
             filaDeBusca.push(j1);
             caminhoBFS[j1.jarra_3_litros][j1.jarra_4_litros].push_back(Jarras(j.jarra_3_litros,j.jarra_4_litros)) ; 
          }
               
          if(j2.jarra_3_litros != -2){
           
             filaDeBusca.push(j2);
             caminhoBFS[j2.jarra_3_litros][j2.jarra_4_litros].push_back(Jarras(j.jarra_3_litros,j.jarra_4_litros)) ; 
          }

          if(j3.jarra_3_litros != -2){
           
             filaDeBusca.push(j3);
             caminhoBFS[j3.jarra_3_litros][j3.jarra_4_litros].push_back(Jarras(j.jarra_3_litros,j.jarra_4_litros)) ; 
          }

          if(j4.jarra_3_litros != -2){
           
             filaDeBusca.push(j4);
             caminhoBFS[j4.jarra_3_litros][j4.jarra_4_litros].push_back(Jarras(j.jarra_3_litros,j.jarra_4_litros)) ; 
          }
          if(j5.jarra_3_litros != -2){
           
             filaDeBusca.push(j5);
             caminhoBFS[j5.jarra_3_litros][j5.jarra_4_litros].push_back(Jarras(j.jarra_3_litros,j.jarra_4_litros)) ; 
          }
          if(j6.jarra_3_litros != -2){
           
             filaDeBusca.push(j6);
             caminhoBFS[j6.jarra_3_litros][j6.jarra_4_litros].push_back(Jarras(j.jarra_3_litros,j.jarra_4_litros)) ; 
          }
          filaDeBusca.pop();
          BFS(verificaEstado,filaDeBusca,x,y,caminhoBFS);
      }

}

void DFS(int verificaEstado[5][5],stack<Jarras> &pilhaDeBusca,int x,int y){
    
   Jarras j = pilhaDeBusca.top();

    //cout<<j.jarra_3_litros<< "----"<<j.jarra_4_litros<<endl;
    //printMatriz(verificaEstado);
     // getchar();
     if((j.jarra_3_litros ==x && j.jarra_4_litros == y) || (x == -1 && j.jarra_4_litros == y) || (j.jarra_3_litros == x && y == -1)){
           
           return;
      
      }

      else{    
          //verificar os próximos possíveis estados para cada uma das operações nos jarros de 3 e 4, como o DFS verifica em profundidade e apenas um nó filho por vez, utilizou-se if's dentro de else's
          Jarras j1 = encherJarro3(j,verificaEstado);
          if(j1.jarra_3_litros != -2){
           
             pilhaDeBusca.push(j1);
             DFS(verificaEstado,pilhaDeBusca,x,y);
          }else{

               Jarras j2 = transferirJarro3(j,verificaEstado);
               if(j2.jarra_3_litros != -2){

                 pilhaDeBusca.push(j2);
                 DFS(verificaEstado,pilhaDeBusca,x,y);

               }else{

                    Jarras j3 = esvaziarJarro3(j,verificaEstado);
                    if(j3.jarra_3_litros != -2){

                      pilhaDeBusca.push(j3);
                      DFS(verificaEstado,pilhaDeBusca,x,y);
                   
                    }else{
         
                         Jarras j4 = encherJarro4(j,verificaEstado);
                         if(j4.jarra_3_litros != -2){
           
                           pilhaDeBusca.push(j4);
                           DFS(verificaEstado,pilhaDeBusca,x,y);
               
                           }else{
 
                                Jarras j5 = transferirJarro4(j,verificaEstado);
                                if(j5.jarra_3_litros != -2){
           
                                  pilhaDeBusca.push(j5);
                                  DFS(verificaEstado,pilhaDeBusca,x,y);
          
                                  }else{

                                       Jarras j6 = esvaziarJarro4(j,verificaEstado);
                                       if(j6.jarra_3_litros != -2){
           
                                         pilhaDeBusca.push(j6);
                                         DFS(verificaEstado,pilhaDeBusca,x,y);
                            
                                        }else{
                                            pilhaDeBusca.pop();
                                        }//end else                           
                                  }//end else
                           }//end else
                    }//end else
               }//end else
          }//end else
           
      }//end else

}

void printarCaminhoBFS(vector<vector<vector < Jarras> > > &caminhoBFS, int x,int y){

  int i=x;
  int j=y;
  while(i != -10 && j != -10){

    cout<<"("<<i<<","<<j<<")"<<endl;
    Jarras aux = caminhoBFS[i][j][0];
    i = aux.jarra_3_litros;
    j = aux.jarra_4_litros;

  }

}

void printarCaminhoDFS(stack <Jarras> pilhaDeBusca){

 while(!pilhaDeBusca.empty()){
 
   Jarras aux = pilhaDeBusca.top();
   cout<<"("<<aux.jarra_3_litros<<","<<aux.jarra_4_litros<<")"<<endl;
   pilhaDeBusca.pop();
 }

}

int main(){

  //matriz para verificar os estados já visitados e os não visitados 0 - para não visitado e 1 para visitado
  int verificaEstado[5][5];
  vector<vector<vector<Jarras> > > caminhoBFS(5,vector<vector<Jarras> >(5));
  zerarMatrizes(verificaEstado);

  //----------------------------

  //variáveis de controle para a capcidade desejada para cada jarra, por padrão elas estão com os valores 0 e 2, que seria para encontrar a jarra de 3 litros com 0 litros e a jarra de 4 litros com dois litros, que seria a resposta do exercício. Caso queira encontrar 2 litros no jarro de 4 litros independente da quantidade da jarra de 3 litros, coloque -1 em capi. Para brincar com o algoritmo, pode colocar qualquer valor de entrada que desejar e que exista nos estados possíveis do problema. -1 serve para procurar uma quantidade x no outro jarro independente do valor que sobra. Se capi =-1 e capj = 1, o algoritmo vai buscar um valor mais próximo na qual o nó da arvore de estados construída durante a execução tenha o valor na jarra de 4 litros com capacidade 1 e um valor qualquer na jarra de 3 litros.

  //só serão encontrados valores possíveis e que existam no problema, valores como (1,1), (2,3) ou (4,4) e etc resultarão em erro

  //capi -> jarra de 3 litros
  //capj -> jarra de 4 litros
  int capi=0,capj=2;
  
  //

  //----------------------------

  //estrutura que armazena os próximos vértices a serem encontrados/analisados (para o BFS) 
  queue<Jarras> filaDeBusca;
  
  //colocando na fila o primeiro estado (0,0), na esquerda "(0," é a jarra de 3 litros, e na direita ",0)" a jarra de 4 litros
  filaDeBusca.push(Jarras(0,0));
  
  //dizendo que o estado (0,0) já foi verificado, pois é o estado inicial
  verificaEstado[0][0] = 1;
  
  //O pai da raiz foi setado para (-10,-10) por convenção, isso é utilizado como condição de parada para printar o caminho feito pelo BFS :)
  caminhoBFS[0][0].push_back(Jarras(-10,-10));

  //começo BFS

  /*Como esta acontecendo a lógica de busca do BFS aqui?

     Bem, para cada estado atual, muitos estados possíveis adjacentes são calculados/estimados e colocados na fila. As funções esvaziar/transferir/encher colocam mais que um valor da classe Jarras na fila, de acordo com as possibiloidades do estado.

 */
  cout<<"Caminho BFS"<<endl;

  //variáveis para pegar o ultimo estado encontrado, essas variáveis são utilizadas para buscas onde capi ou capj é negativo. Na função BFS capi e capj são subescritos. Para não perder os valores e deixar o código mais genérico possível (utilizando capi e capj no DFS também), essas variáveis foram utilizadas. Isso é importante para poder passar na função de mostrar o caminho. 
  int auxi=capi;int auxj = capj;
  //(0,2) é a resposta esperada, porém este valor pode ser trocado para outro :)
  BFS(verificaEstado,filaDeBusca,capi,capj,caminhoBFS);

  

  printarCaminhoBFS(caminhoBFS,capi,capj);
  //aqui é onde elas retornam ao seu valor original;
  capi=auxi;capj=auxj;
  //fim bfs
   
   
   zerarMatrizes(verificaEstado);
   stack<Jarras> pilhaDeBusca;

   pilhaDeBusca.push(Jarras(0,0));

   //dizendo que o estado (0,0) já foi verificado, pois é o estado inicial
   verificaEstado[0][0] = 1;
 
   //começo DFS

   /*Como esta acontecendo a lógica de busca do DFS aqui?

     Bem, para cada estado atual, eu procuro apenas o primeiro estado adjacente que eu encontro. Quando eu encontro um estado dentro das várias condições na função DFS, eu chamo de maneira recursiva a mesma função até não haver mais um estado adjacente. Eu só dou pop na pilha quando não há mais nenhum nó adjacente àquele vértice. Devido a ordem das condições e montagem dos estados durante a operação de busca, o primeiro caminho que o DFS encontra para o estado (0,2) é o mais longo kkkkk, pois como a busca é cega, deu o azar de cair justamente no caminho mais longo, nesse caso, pode se verificar que o algoritmo BFS foi melhor. 

 */

  cout<<"Caminho DFS"<<endl;
   
  //(0,2) é a resposta esperada, porém este valor pode ser trocado para outro :)
  DFS(verificaEstado,pilhaDeBusca,capi,capj);


  printarCaminhoDFS(pilhaDeBusca);

   //fim DFS

}

