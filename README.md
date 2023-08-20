# Trabalho Aquecimento

## Introdução

No problema conhecido como "Top K Itens" o objetivo é desenvolver um algoritmo que possa listar as palavras mais valiosas em um texto, por exemplo, escolhendo as mais ou menos frequentes. Utilizando das estruturas hash e heap é possível desenvolver uma solução com com custo computacional $O(n \cdot \log k)$, onde n é número total de palavras e k é a quantidade palavras escolhidas.

Esse trabalho tem como objetivo principal desenvolver um algoritmo que consiga listar os K termos mais frequentes em uma coleção de arquivos de texto. Além disso, também serão implementadas estruturas de hash e de heap. E por enfim, comparar a função de hashing "Meio dos quadrados" com a estrutura unordered_map.

**Palavras-chave:** heap, min-heap, hash, unorderep_map, meio dos quadrados.

**Observação:** O programa irá considerar todos os arquivos dentro da pasta dataset como entrada, independente do nome. Com excessão do arquivo "stopwords.data", que contém termos que serem ignorados na listagem, esse arquivo não deve ser seu nome alterado.

## Solução 

Inicialmente buscamos todos os termos dentro do arquivo de stopwords. Estes serão ignorados durante a contagem, não aparecendo na listagem final.

Após essa etapa são extraídas as palavras dos arquivos de entrada. Cada dessas, que não for uma *stopword*, é inserida na estrutura de hash. Sendo a palavra a chave e a sua frequencia o valor, este é incrementado a cada ocorrencia. Ao fim desse processo temos uma lista com todas as palavras e a quantidade de aparicoes no texto.

As estruturas de hash são uma alternativa interresante nessa etapa devido à sua complexidade constante.

Em seguida, implementaremos uma min-heap. Isso facilitará a remoção de valores, já que sempre removeremos o menor valor, a fim de manter os maiores valores dentro da estrutura.

As estruturas de heap, sejam min ou max, tem complexidade logarítmica no número de itens armazenados para cada inserção e um custo constante para recuperar ou retirar o topo. No pior caso da nossa solução, onde sempre será necessário remover uma palavra e inserir outra teremos complexidade $O(n \cdot \log k)$.

Nessa situação esse pior caso seria testar as palavras em ordem crescente, da menos comum até a mais que aparece nos texto.

Os primeiros K elementos da tabela hash serão inseridos na heap. Em seguida, para o restante dos elementos é verificado se seu valor é maior que o menor valor dentro da heap. Se isso acontecer, o item da heap será removido e o item da iteração será inserido.

É possível que perceber que caso um valor não seja maior que topo da min-heap ele consequentemente não será maior que nenhum outro elemento. Isso garante que nossa heap sempre terá os maiores elementos e pra isso é necessário fazer comparações apenas como o menor elemento.

Para recuperar os K termos em ordem crescente de aparição, basta ir buscando o topo da heap e imprimi-lo enquanto houver elementos na heap. Como buscar o topo tem complexidade constante, recuperar os K elementos terá complexidade $O(k)$.

Portanto, a complexidade total da solução pode ser descrita como

$O(n)$ → para percorrer as palavras do texto

$O(k \cdot \log k)$ → para inserir os $k$ primeiro itens

$O((n-k) \cdot \log k)$ → para tentar inserir o restante dos elementos na heap

$O(k)$ → para exibir os $k$ itens

Simplificando, a complexidade do algoritmo pode ser descrita como $O(n \cdot \log k)$.

## Implementação

### Lendo os arquivos

Durante o programa são realizadas duas leituras, uma para buscar os textos de entrada e outra para as stopwords, ambas usando a bliblioteca fstream do C++.

As stopwords estão em um arquivo formatado de uma maneira especifica tendo cada palavra em uma linha. Assim, em nosso código é feita a leitura linha por linha e aplicando a palavra em umas das estruturas de hash.

Já o texto de entrada, por ser um texto comum, é lido de caracter em caracter, a fim de ir fazendo as validações e categorizações necessárias. Caso o char da iteração seja válido, ou seja pode aparecer em uma palavra, ele é concatenado a palavra. Os caracteres são lidos até se encontrar um separador válido, esses são: ' ' (espaço em branco), ',' (vírgula), '.' (ponto final), '!' (ponto de exclamação), '?' (ponto de interrogação) ou '\n' (fim de paragráfo).

Existem alguns caracteres especiais que são ignorados. Por exemplo na palavra “faça-se” o caracter “-” é ignorado e a palavra é contabilizada como “façase”.

### Hash

Iremos comparar a estrutura unodered_map com uma implementação de hash utilzando a função "Meio do quadrado". 

#### unordered_map

A estrutura `unordered_map` é parte da biblioteca padrão do C++ e é definida na biblioteca `<map>`. Essa estrutura é uma implementação de hash, com a caracteristica de não ordenar os itens salvos.  Para utilizá-la, é necessário definir o tipo de dado da chave e do valor entre os sinais de maior e menor, seguindo a sintaxe `unordered_map<tipo_chave, tipo_valor>`.

Na nossa implementação o tipo da chave será string e o tipo do valor será um inteiro. Para salvar a palavra e sua frequencia, respectivamente.

### Meio dos quadrados

Dentro das atributos e métodos privados temos: O vetor onde são armazendos os elementos, o tamanho desse vetor (bucketsNumber) e as métodos de `hash` e `rehash`.

O método de hash dado uma chave retonar um valor. Essa chave será uma palavra e o valor correspondente é o indice do vetor onde o elemento pode ser armazenado.

Os valores ASCII de cada caracter são somados, transformando a palavra em um valor númerico. Esse valor é elevado ao quadrado. É retirado desse o valor o meio, sendo esse caracterizado pelos N elementos centrais. O valor de N é o número de digitos do tamanho do vetor menos um. Por exemplo, se o vetor tem tamanho 100 e temos o número 44333112 o resultado será 33.

Todas as operações feitas são constantes ou lineares. Porém o custo linear está atrelado ao número de digitos e não ao valor em si. Visto que é necessário contar o número de digitos e descolar digitos para retirar o meio do quadrado.

```cpp
size_t Hash::hash(string key) {
    size_t keySum = sumDigits(key);
    size_t square = keySum * keySum;

    size_t digitsInArraySize = getDigitsInArraySize(this->array.size());

    size_t squareDigits = getDigitsInSquare(square);

    size_t middle = getSquareMiddle(squareDigits, digitsInArraySize, square);

    return middle;
};
```

O método de rehash aumenta o tamanho de vetor e reposiciona todos os elementos que já estavam. Essa função é chamada sempre que atingimos um fator de carga de 50%. O fator de carga é valor dado pela divisão do tamanho do vetor pelo número de elementos inseridos, ou seja, representa a ocupação do vetor. Aumentando o tamanho do vetor o número de colisões diminuem.


```cpp
class Hash {
   private:
    vector<pair<string, int>> array;
    size_t bucketsNumber;
    size_t hash(string key);
    void rehash();

   public:
    Hash();
    virtual ~Hash();
    vector<string> keys;
    void insert(string key);
    void insert(string key, int value);
    bool find(string key);
    pair<string, int> at(string key);
};
```


### Heap

Para nossa solução foi mais conveniente implementar a heap ao invés de utilizar alguma estrutura pronta. As principais justificadas estão relacionadas, além de compreender melhor o algoritmo, a dificuldade de analisar os detalhes de implementação das estruturas.

```cpp
class Heap {
   private:
    vector<pair<string, int>> array;
    void heapify_up(int index);
    void heapify_down(int index);

   public:
    int size();
    bool empty();
    void push(pair<string, int> item);
    pair<string, int> top();
    void pop();
};
```

O método `int size` retorna o número de elementos dentro da heap, e o método `bool empty` retorna se a heap está vázia, baseando no número de elementos.

O método `pair<string, int> top()` retorna o primeiro elemento da heap. Como optamos por implementar uma min-heap o topo da heap é o elemento com menor frequencia.

O método `void push(pair<string, int> item)` insere dentro da heap. O elemento é inserido na última posição do vetor, garantido que está em um dos nós da heap. Sempre que é um elemento é inserido é executado o método `heapify_up`.

O método `void heapify_up(int index)`  chamada durante a inserção dentro da heap coloca o item inserido na posição correta. Enquanto o valor for menor que seu pai eles são trocados, assim o item vai “subindo” na heap até a posição correta. Ou seja, quando se localizar um item de valor menor ou chegar ao topo da heap.

```cpp
void Heap::heapify_up(int index) {
    int parent = (index - 1) / 2;

    if (parent < 0) return;

    int parentFreq = array[parent].second;
    int indexFreq = array[index].second;

    if (parent != index && parentFreq > indexFreq) {
        swap(array[parent], array[index]);
        heapify_up(parent);
    }
}
```

O método `void pop()`  remove o item que está no topo da heap. O elemento que queremos remover está na posição 0 do vetor. Assim pegamos o último elemento do vetor e colocamos do lugar do primeiro, isso elimina o valor. Depois removemos a última posição do vetor, visto que esse elemento foi transferido para a primeira posição. Sempre que é um elemento é inserido é executado o método `heapify_down`

```cpp
void Heap::pop() {
    this->array[0] = this->array.back();
    this->array.pop_back();

    heapify_down(0);
}
```

O método `void heapify_down(int index)` chamado durante as remoções coloca o valor, que foi trazido da última posição, para seu lugar correto. É verificado se algum dos filhos do elemento é menor que ele, e caso de for, é feito a troca. No caso dos dois filhos serem menores, é escolhido o menor entre eles.

```cpp
void Heap::heapify_down(int index) {
    int left = (2 * index) + 1;
    int right = (2 * index) + 2;

    int smaller = index;
	
    int childLeft = this->array[left].second;
    int childRight = this->array[right].second;

    int indexFreq = this->array[index].second;

    if (left < size() && childLeft < indexFreq) {
        smaller = left;
    }

    if (right < size() && childRight < childLeft) {
        smaller = right;
    }

    if (smaller != index) {
        swap(this->array[smaller], this->array[index]);
        heapify_down(smaller);
    }
}
```
## Resultados

A saída do program tem o seguinte formato vai exibir duas listas com as K palavras mais frequentes, uma mostrando a heap e a outra mostrando as palavras em ordem crescente. Sendo essas listas mostradas tanto para as duas implementações de hash.

Exibir os elementos em ordem crescente é importante para validar o funcionamento correta da heap. Como podemos buscar os elementos de menor valor, para se mostrar em ordem crescente a saída basta ir buscando e mostrando os elementos na heap.

Para os arquivos dentro da pasta dataset, temos a seguinte saída:

```

unordered_map

Elementos na Heap: 
menos 408
tão 426
nada 452
dia 475
dias 443
agora 476
outro 582
vez 500
todos 526
bem 451
grande 472
aqui 507
pode 604
assim 610
outros 495
tudo 750
outra 575
ainda 768
homem 537
tempo 494

Elemetos ordenados:
menos 408
tão 426
dias 443
bem 451
nada 452
grande 472
dia 475
agora 476
tempo 494
vez 500
aqui 507
outros 495
todos 526
homem 537
outra 575
outro 582
pode 604
assim 610
tudo 750
ainda 768

Time taken to execute in seconds : 0.407632

---------------

Meio dos quadrados

Elementos na Heap: 
menos 408
bem 451
tão 426
nada 452
tempo 494
grande 472
dias 443
agora 476
aqui 507
outros 495
outra 575
vez 500
dia 475
tudo 750
outro 582
todos 526
assim 610
ainda 768
homem 537
pode 604

Elemetos ordenados:
menos 408
tão 426
dias 443
bem 451
nada 452
grande 472
dia 475
agora 476
tempo 494
outros 495
vez 500
aqui 507
todos 526
homem 537
outra 575
outro 582
pode 604
assim 610
tudo 750
ainda 768

Time taken to execute in seconds : 0.542150
```

Para comparar as implementações de hash iremos fazer um teste com 3 entradas, e calcular a média do tempo de execução para cada uma.
Entrada 1: "DomCasmurro.txt"
Entrada 2: "Semana_Machado_Assis.txt"
Entrada 3: "DomCasmurro.txt" + "Semana_Machado_Assis.txt"

|           | unordered_map | meio dos quadrados |
|-----------|---------------|--------------------|
| Entrada 1 | 0,075500      | 0,134379           |
| Entrada 2 | 0,272346      | 0,374359           |
| Entrada 3 | 0,322327      | 0,472777           |

Os resultados mostram uma melhor performace utilizando o unordered_map. Entretanto essa diferença é bem menor que o esperado visto que o método "meio do quadrado" é uma função de hash muito simples, quando comparada a outros métodos.

Além disso a implementação da biblioteca utiliza várias otimizações que não foram igualmente aplicar a hash feita no trabalho. Um exemplo são operações bitwise, que melhoram o custo ao realizar manipulações com a chave.

## Conclusão

Nessa trabalho conseguimos analisar a eficiencia de estruturas para resolução de problemas. Conseguindo extrair as palavras mais frequentes, de textos relativamente grandes, em questão de segundos. Nessa situação ao se optar por métodos quadráticos ou até mesmo a métodos de ordenação, teriámos um tempo muito pior. Podendo o programa até mesmo não terminar sua execução em um tempo hábil.

Foi também possível compreender melhor as estruras de heap e hash. Para realizar o trabalho foram feitas várias pesquisas sobre o funcionamento desses algoritmos. E a opção de implementar, ao invés de buscar soluções prontas, contribuiu ainda mais para o entendimento

Por fim, foi possível comparar duas implementações de hash. Tivemos como resultado que mesmo um método de hash simples pode ser muito eficiente e até mesmo comparavel com as implementações usadas na bibliotaca padrão.

## COMPILAÇÃO E EXECUÇÃO

A algorítmo disponibilizado possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:

| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |
