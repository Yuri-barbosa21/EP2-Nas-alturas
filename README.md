# EP2-Nas-Alturas

**Teste de eficiência entre Arvores de Estruturas de Dados (AVL e BST)**

## Principais estruturas:
  - O programa foi feito em um único arquivo.

## BST
  > Função **int altura_BST(BST raiz)** que recebe a raiz de uma BST e retorna a altura da arvore.
  > 
  > Função **void mostra_in_ordem_BST(BST raiz)** que recebe a raiz de uma BST e mostra na tela todo as chaves no formato *In Ordem*, usada para muitos testes.
  >
  > Função **void libera_BST(BST raiz)** que recebe a raiz de uma BST e libera toda memória alocada.

## AVL
  > Funções **unsigned altura_AVL(AVL no) e unsigned calcula_altura(AVL no)**, que recebem a raiz de uma AVL e retorna a altura da arvore
  > 
  > Função **void mostra_in_ordem_AVL(AVL raiz)** que recebe a raiz de uma AVL e mostra na tela todo as chaves no formato *In Ordem*, usada para muitos testes.
  > 
  > Função **int fb(AVL no)** que recebe um nó e retorna o fator de balaceamento.
  > 
  > Funções **AVL rotL(AVL r) e AVL rotR(AVL r)** que receberm um nó e fazem as rotações necessárias, direcionando os ponteiros para manter a arvore um AVL.

## Geração de Números Alertórios
  > Foi utilizado as seguintes bibliotecas: **time.h e stdlib.h**. Através desses recursos foi criada uma *matriz* **v[amostra][elementos]** que recebe os valores aleatórios  de 1 a 99, criados pela função **rand()** que útiliza como semente a função **srand(time(NULL))** como semente.
  >
  > Os números aleatórios são gerados fora do *loop* de inserção nas arvores, para que não haja interferência no tempo de execução das mesmas.
  >  
  >![image](https://user-images.githubusercontent.com/62626768/169922810-838821f2-9a48-445e-ac4b-bc1b7a70354e.png)

## Medição das Criação das Árvores
   > Foi usado exatamento o mesmo método para as duas árvores.
   > 
   > Para ser mais exato, o tempo foi medido através dos *clocks* do processador.
   >
   > Através das variaveis abaixo dos tipos clock_t e double (para medir o tempo com mais exatidão de pontos flutuantes)  
   > ![image](https://user-images.githubusercontent.com/62626768/169924200-39f5aa73-3cf4-43e7-97b5-dab66b2e8dda.png)
   >
   > O tempo é medido da seguinte forma...
   > Antes de iniciar a tarefa é iniciado o *clock()*, depois da realização da tarefa ele é medido novamente. É feita uma subtração do tempo final menos o tempo inicial para obter o tempo gasto, esse tempo é dividido por **CLOCKS_PER_SEC** que retornará o número de segundos usados pela CPU;
   > ![image](https://user-images.githubusercontent.com/62626768/169924040-1d59a4c8-23d1-42a0-9769-e5fb4c2fce60.png)


## Interpretação

- O sistema roda em um loop simples através de um *do while*, ao qual tem duas opçãos - (1 - Novo teste) e (2 - Sair); 
- O usuario pode fazer diversos testes, digitando o número de amostra e o número de elementos aleatórios que cada amostra vai ter:
### Foi observado que:
  - De forma geral, o tempo de criação de uma árvore **AVL** é quase sempre maior do que de uma árvore **BST**, dado que em uma inserção na AVL é feito alguns teste para ajustes na forma em que os nós são dispostos, para que a altura total da árvore se mantenha a mais baixa possível.
  
  - Na arvore **BST** as regras de inserção são mais simples, não tendo ajustes em nós já dispostos. Com isso o tempo de criação de uma **BST** é mais curto.
   
  - Em contra partida, a árvore **AVL** tem a vantagem de manter o menor tempo em uma busca, sendo O($log{_a}{n}$).
-![image](https://user-images.githubusercontent.com/62626768/169925409-894aeafb-48da-4c80-807f-15ee60ecefc2.png)
