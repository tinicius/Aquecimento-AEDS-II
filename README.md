# Trabalho de aquecimento - Top K Itens

## Introdução

Um exemplo clássico de problema que pode ser solucionado utilizando-se hash e heap é o
chamado top k itens. Neste problema, é preciso encontrar os k itens mais valiosos de uma
coleção de dados. Logo, utiliza-se o hash para contar a frequência de todos os itens, enquanto
o heap se aplica na manutenção de uma lista dos k itens de maior valor.

Nesse trabalho, iremos trabalhar com duas estruturar do STL do C++: map (para o hash) e priority_queue (para o heap);

## Solução
    
Inicialmente será criada nossa hash. Para isso iremos considerar cada palavra uma chave e a frequência será valor armazenado. Então, a cada colisão o valor salvo é incrementado.

Iremos percorrer todo o texto, extraindo cada palavra, e aplicando a nossa hash. Ao fim desse processo teremos a frequência de todas palavras do texto. Nessa parte é importante tratar o texto, considerando acentuações e caracteres maiúsculos e minúsculos.

A hash nessa etapa será uma boa alternativa, devido sua complexidade aproximadamente constante.

Foi escolhido utilizar uma min-heap. Isso irá facilitar na hora de fazer as remoções, visto que sempre iremos remover o menor valor, a fim de manter sempre os maiores valores.

A estrutura de heap tem complexidade O(log k) para cada inserção e O(1) para recuperar o topo. No pior caso da nosso solução, onde sempre será necessáro inserir a palavra na heap, teremos complexidade n * log k. Sendo essa a etada mais de maior custo da implementação.

Os primeiros K elementos da hash serão inseridos na heap. Após isso, o restando dos elementos será percorrido e verificado se seu valor é maior que o menor valor dentro da heap. Caso isso aconteça, o item da heap é removido e o item da iteração é inserido.

Para recuperar os elementos é necessário apenas ir buscando o topo da heap e imprimindo ele, enquando tiver elementos na heap. Como buscar o topo tem complexidade constante, recuperar os K elementos terá complexidade O(k).

Então, a complexidade total da solução pode ser descrita como:
O(n + k * log k + (n - k) * log k + k) podendo ser simplificada para O(n * log k).

## Implementação

### Lendo o arquivo

### Hash

Para implementar a hash, será utilizada a estrutura map. Tendo como paramêtro uma string e um inteiro para armazenar a palavra e a frequência.

### Heap

Já o heap, será implementado usando a estrutura prioriry_queue. Temo paramêtro um pair de string e inteiro. 

Para essa priority_queue poder ser utlizada como uma min-heap, é necessário alterar a função de comparação padrão, já que essa utiliza o primeiro valor do pair para considerar na ordenação.

# Exemplos de entrada e saída


# Conclusão


# Compilação e Execução

A estrutura árvore disponibilizada possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:

| Comando | Função |
| --- | --- |
| make clean | Apaga a última compilação realizada contida na pasta build |
| make | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build |
| make run | Executa o programa da pasta build após a realização da compilação |

# Contatos

<div style="display: inline-block;">
<a href="https://t.me/vini_apereira">
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white"/> 
</a>

<a href="https://www.linkedin.com/in/vinicius-alves-pereira-913254236/">
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white"/>
</a>

</div>

<p> </p>


<a style="color:black" href="mailto:vinicius.apereira04@gmail.com?subject=[GitHub]%20Source%20Dynamic%20Lists">
✉️ <i>vinicius.apereira04@gmail.com</i>
</a>