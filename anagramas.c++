#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

const int TAM = 28;

void imprimir(char letras[5][4], char BancoAcertos[TAM][8], int &acertos, int &erros, int &tentativas) {
    cout << "\n============================================================";
    cout << "\n" << setw(32) << "ANAGRAMAS";
    cout << "\n============================================================" << endl;
    cout << "\nQuadro de letras: " << endl;

    for (int a = 0; a < 5; ++a) {
        cout << endl;

        for (int g = 0; g < 4; ++g) {
            cout << setw(7) << letras[a][g];
        }
    }

    cout << endl << "\nQuadros de acertos: " << endl << "\n";

    if (acertos > 0) {
        for (int b = 0; b < acertos; ++b) {
            cout << BancoAcertos[b] << endl;
        }
    }

    cout << "\nNumero de Acertos: " << acertos << endl;
    cout << "Numero de Erros: " << erros << endl;
    cout << "Numero de Tentativas: " << tentativas << endl;
}

int validarBanco(char BancoPalavras[TAM][8], char BancoAcertos[TAM][8], char palavra[8], int &acertos, int &erros, int &tentativas) {
    ++tentativas;

    for (int k = 0; k < TAM; ++k) {
        if (strcmp(BancoPalavras[k], palavra) == 0) {
            int palavraEncontrada = 0;

            for (int p = 0; p < acertos; ++p) {
                if (strcmp(palavra, BancoAcertos[p]) == 0) {
                    cout << "\nA palavra já foi encontrada!" << endl;
                    palavraEncontrada = 1;
                    break;
                }
            }

            if (!palavraEncontrada) {
                strcpy(BancoAcertos[acertos], palavra);
                cout << "\nNova Palavra Encontrada! Adicionando no Banco de Acertos." << endl;
                ++acertos;
            }

            return 1;
        }
    }

    cout << "\nA palavra não é valida." << endl;
    ++erros;

    return -1;
}

int validarPalavra(char letras[5][4], char palavra[8], int &erros, int &tentativas, int TamDificuldade) {
    if (strlen(palavra) <= TamDificuldade) {
        char validarLetras[5][4];

        for (int a = 0; a < 5; a++) {
            for (int b = 0; b < 4; b++) {
                validarLetras[a][b] = letras[a][b];
            }
        }

        int tamanhoPalavra = strlen(palavra);

        for (int c = 0; c < tamanhoPalavra; ++c) {
            char letra = palavra[c];
            int encontrou = 0;

            for (int d = 0; d < 5; ++d) {
                for (int e = 0; e < 4; ++e) {
                    if (validarLetras[d][e] == letra) {
                        validarLetras[d][e] = ' ';
                        encontrou = 1;
                        break;
                    }
                }

                if (encontrou == 1) {
                    break;
                }
            }

            if (encontrou == 0) {
                cout << "\nPalavra Inválida no Banco de Letras" << endl;
                ++tentativas;
                ++erros;
                return -1;
            }
        }
        return 1; // Retorna 1 se a palavra for válida
    } else {
        cout << "\nA palavra é inválida para a dificuldade atual" << endl;
        return -1; // Retorna -1 se a palavra for inválida
    }
}


void menu(char BancoPalavras[TAM][8], char BancoAcertos[TAM][8], char palavra[8], int &acertos, int &erros, int &tentativas, char letras[5][4], int TamDificuldade) {
    int sair = 0;

    while (sair == 0) {
        imprimir(letras, BancoAcertos, acertos, erros, tentativas);

        cout << "\nDigite a palavra que você encontrou no anagrama: ";
        cin.getline(palavra, 8);

        int resultadoValidacao = validarPalavra(letras, palavra, erros, tentativas, TamDificuldade);

        if (resultadoValidacao == 1) {
            validarBanco(BancoPalavras, BancoAcertos, palavra, acertos, erros, tentativas);
        }

        if (erros == 5) {
            cout << "\nNúmero máximo de erros atingido.";
            sair = 1;
            break;
        }

        do {
            cout << "\nDeseja sair [1 = Sim / 0 = Não]: ";
            cin >> sair;
            cin.ignore();
        } while (sair != 0 && sair != 1);
    }

    imprimir(letras, BancoAcertos, acertos, erros, tentativas);

    cout << "\nFechando o Programa.";
}


int main() {
    char BancoPalavras[TAM][8] = {
        "bar", "boa", "cabo", "cara", "caro", "cor",
        "rabo", "barca", "barra", "raro", "boda", "roda",
        "arco", "broa", "caçar", "cada", "abra", "baro",
        "cobra", "roça", "arab", "arar", "caro"
    };

    char letras[5][4] = {
        'a', 'b', 'c', 'd', 'e',
        'f', 'g', 'h', 'i', 'j',
        'k', 'l', 'm', 'n', 'o',
        'p', 'r', 's', 't', 'u'
    };

    char BancoAcertos[TAM][8];

    int acertos = 0, erros = 0, tentativas = 0, sair = 0, TamDificuldade = 0;

    char palavra[8];
    char dificuldade[8];

    cout << "\nDigite a dificuldade que deseja jogar: ";
    cin.getline(dificuldade, 8);

    if (strcmp(dificuldade, "facil") == 0) {
        TamDificuldade = 8;
        menu(BancoPalavras, BancoAcertos, palavra, acertos, erros, tentativas, letras, TamDificuldade);
    } else if (strcmp(dificuldade, "medio") == 0) {
        TamDificuldade = 6;
        menu(BancoPalavras, BancoAcertos, palavra, acertos, erros, tentativas, letras, TamDificuldade);
    } else if (strcmp(dificuldade, "dificil") == 0) {
        TamDificuldade = 4;
        menu(BancoPalavras, BancoAcertos, palavra, acertos, erros, tentativas, letras, TamDificuldade);
    } else {
        cout << "\nOpção invalida";
    }

    return 0;
}
