#!/bin/bash


# Verifica se o nome do arquivo .c foi fornecido
if [ -z "$1" ]; then
    echo "Erro: Forneça o nome do arquivo .c a ser testado."
    echo "Uso: ./test.sh seu_programa.c"
    exit 1
fi

SOURCE_FILE=$1
# Extrai o nome base do arquivo (ex: '51-meteoros' de '51-meteoros.c')
BASE_NAME=${SOURCE_FILE%.c}
EXECUTABLE_NAME=$BASE_NAME
TEST_DIR="${BASE_NAME}_casos-de-teste"

# Verifica se o diretório de testes existe
if [ ! -d "$TEST_DIR" ]; then
    echo "Erro: Diretório de testes '${TEST_DIR}' não encontrado."
    exit 1
fi

# Compila o programa. O -lm é útil para problemas que usam a biblioteca de matemática.
gcc -o $EXECUTABLE_NAME $SOURCE_FILE -lm
if [ $? -ne 0 ]; then
    echo "Falha na compilação!"
    exit 1
fi

echo "Compilação bem-sucedida. Iniciando testes..."

# Procura por todos os arquivos .in na pasta de testes especificada
for test_in in "$TEST_DIR"/*.in; do
    # Esta verificação previne erros caso a pasta de testes esteja vazia.
    [ -e "$test_in" ] || continue

    # Extrai o nome do caso de teste (ex: 'caso1' de '.../caso1.in')
    test_case_name=$(basename "$test_in" .in)
    test_out="${TEST_DIR}/${test_case_name}.out"
    my_out="${TEST_DIR}/${test_case_name}.myout" # Arquivo temporário para a sua saída

    echo -n "Testando o caso '${test_case_name}'... "

    # Verifica se o arquivo de gabarito .out existe
    if [ ! -f "$test_out" ]; then
        echo "AVISO: Arquivo de gabarito '${test_out}' não encontrado."
        continue
    fi

    # Executa seu programa, passando o .in como entrada e salvando a saída em .myout
    ./$EXECUTABLE_NAME < "$test_in" > "$my_out"

    # Compara a sua saída com o gabarito.
    if diff -w "$my_out" "$test_out" > /dev/null; then
        echo "Aceito"
    else
        echo "Resposta Errada"
        echo "--- Sua Saída (${my_out}) ---"
        cat "$my_out"
        echo "--- Saída Esperada (${test_out}) ---"
        cat "$test_out"
    
    fi

    # Remove o arquivo de saída temporário
    rm "$my_out"
done

echo "Testes finalizados."
# Remove o arquivo executável compilado
rm $EXECUTABLE_NAME