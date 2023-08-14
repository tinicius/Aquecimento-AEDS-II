# Trabalho Aquecimento

## Introdução

Um exemplo clássico de problema que pode ser solucionado utilizando hash e heap é o "TOP k itens". Nesse problema, é necessário encontrar os k itens mais valiosos de uma coleção de dados. Utilizando um hash para contar a frequência de todos os itens, enquanto o heap é utilizado para manter uma lista dos k itens de maior valor

Nesse trabalho iremos trabalhar com o map (da biblioteca padrão do C++) para hash e iremos, manualmente, implementar uma estrutura de heap, mais especificamente uma min-heap.

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

### Lendo o arquivo

Durante o programa são realizadas duas leituras, uma para buscar o texto de entrada e outra para as stopwords, ambas usando a bliblioteca fstream do C++.

As stopwords estão em um arquivo formatado de uma maneira especifica tendo cada palavra em uma linha. Assim, em nosso código é feita a leitura linha por linha e aplicando a palavra em umas das estruturas de hash.

```cpp
void loadStopWords(unordered_map<string, int>& stopWordsTable) {
    ifstream file("../dataset/stopwords.data");

    if (!file.is_open()) {
        cerr << "Erro ao abrir um dos arquivos de entrada!" << std::endl;
        exit(1);
    }

    string line;

    while (getline(file, line)) {
        stopWordsTable[line]++;
    }

    file.close();
}
```

O texto de entrada, por ser um texto comum, é lido de caracter em caracter, a fim de ir fazendo as validações e categorizações necessárias. Caso o char da iteração seja válido, ou seja pode aparecer em uma palavra, ele é concatenado a palavra. 

Existem alguns caracteres especiais que são ignorados. Por exemplo na palavra “faça-se” o caracter “-” é ignorado e a palavra é contabilizada como “façase”.

```cpp
void countWords(unordered_map<string, int>& freqWordsTable) {
    ifstream file("../dataset/input.data");

    if (!file.is_open()) {
        cerr << "Erro ao abrir um dos arquivos de entrada!" << std::endl;
        exit(1);
    }

    char aux;
    string word;

    while (file) {
				file.get(aux); // Lendo do arquivo

        if (isValidChar(aux)) { // Caracteres que podem fazer parte da palavra
            word += tolower(aux);
        } else {
						//Caracteres que são ignorados
            if (aux == '-' || aux == '/' || aux == '_') continue;

            if (!word.empty()) {
                freqWordsTable[word]++; // Inserindo a palavra na hash
            };

            word = ""; // Limpando a variável auxiliar
        }
    }

    file.close();
}
```

### Hash

A estrutura `unordered_map` é parte da biblioteca padrão do C++ e é definida na biblioteca `<map>`. Essa estrutura é uma implementação de hash, com a caracteristica de não ordenar os itens salvos.  Para utilizá-la, é necessário definir o tipo de dado da chave e do valor entre os sinais de maior e menor, seguindo a sintaxe `unordered_map<tipo_chave, tipo_valor>`.

Na nossa implementação o tipo da chave será string e o tipo do valor será um inteiro. Para salvar a palavra e sua frequencia, respectivamente.

A complexidade dessa estrutura dessa estrutura é constante, porém devido a implementação da função de hash essa constante é alta. Assim, existem cenários onde essa estrutura pode ter um desempenho abaixo do esperado. Mas, no geral, a estrutura apresentara o comportamento esperado.

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

O método `int size` retorna o número de elementos dentro da heap, e o método `bool empty` retorna se o heap está vazio, baseando no número de elementos.

```cpp
int Heap::size() { 
	return this->array.size(); 
}

bool Heap::empty() {
	return this->size() == 0; 
}
```

O método `pair<string, int> top()` retorna o primeiro elemento da heap. Como optamos por implementar uma min-heap o topo da heap é o elemento com menor frequencia.

```cpp
pair<string, int> Heap::top() { 
	return this->array[0]; 
}
```

O método `void push(pair<string, int> item)` insere dentro da heap. O elemento é inserido na última posição do vetor, garantido que está em um dos nós da heap. 

```cpp
void Heap::push(pair<string, int> item) {
    this->array.push_back(item);

    this->heapify_up(size() - 1);
}
```

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

O método `void pop()`  remove o item que está no topo da heap. O elemento que queremos remover está na posição 0 do vetor. Assim pegamos o último elemento do vetor e colocamos do lugar do primeiro, isso elimina o valor. Depois removemos a última posição do vetor, visto que esse elemento foi transferido para a primeira posição.

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
		int childRight = ;

		int indexFreq = this->array[index].second

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