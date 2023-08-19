# Trabalho Aquecimento

## Introdução

Um exemplo clássico de problema que pode ser solucionado utilizando hash e heap é o "TOP k itens". Nesse problema, é necessário encontrar os k itens mais valiosos de uma coleção de dados. Utilizando um hash para contar a frequência de todos os itens, enquanto o heap é utilizado para manter uma lista dos k itens de maior valor

Este trabalho tem com objetivo implementar uma estrutura de min-heap, implementar uma estrutura de hash e, por fim, comparar a hash desenvolvida com a implementação de hash disponínel na biblioteca do C++.

Palavras-chave: heap, min-heap, hash, unorderep_map, meio dos quadrados.

**Observação:** Esse trabalho irá considerar todos os arquivos dentro da pasta *dataset* como entrada. Com excessão do arquivo "stopwords.data".

## Solução 

Inicialmente, criaremos uma tabela hash. Para isso, consideraremos cada palavra como uma chave e a frequência como o valor armazenado. Em cada colisão, o valor armazenado será incrementado.

Em seguida, percorreremos todo o texto, extraindo cada palavra e aplicando-a em nossa tabela hash. Ao final desse processo, teremos a frequência de todas as palavras do texto. Nessa etapa, é importante tratar o texto considerando acentuações e caracteres maiúsculos e minúsculos.

A tabela hash será uma boa alternativa nessa etapa, devido à sua complexidade aproximadamente constante.

Para a heap, implementaremos uma min-heap. Isso facilitará a remoção de valores, já que sempre removeremos o menor valor, a fim de manter os maiores valores dentro da estrutura.

A estrutura de heap tem complexidade logarítmica no número de itens armazenados para cada inserção e um custo constante para recuperar o topo. No pior caso da nossa solução, onde sempre será necessário inserir a palavra na heap, teremos complexidade O(n * log k).

Os primeiros K elementos da tabela hash serão inseridos na heap. Em seguida, percorreremos o restante dos elementos e verificaremos se seu valor é maior que o menor valor dentro da heap. Se isso acontecer, o item da heap será removido e o item da iteração será inserido.

Para recuperar os elementos, basta ir buscando o topo da heap e imprimi-lo enquanto houver elementos na heap. Como buscar o topo tem complexidade constante, recuperar os K elementos terá complexidade O(k).

Portanto, a complexidade total da solução pode ser descrita como 

- O(n) → para percorrer as palavras do texto
- O(k * log k) → para inserir os k primeiro itens
- O( (n-k) * log k) → para tentar inserir o restante dos elementos na heap
- O(k) → para exibir os K itens

Simplificando, a complexidade do algoritmo pode ser descrita como O(n * log k).

## Implementação

### Lendo os arquivos

Durante o programa são realizadas duas leituras, uma para buscar o texto de entrada e outra para as stopwords, ambas usando a bliblioteca fstream do C++.

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