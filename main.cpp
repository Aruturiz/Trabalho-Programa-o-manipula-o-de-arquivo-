#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 

using namespace std;

const int alunosmaximo = 100;
const int disciplinasmaximo = 10;

string nomealunos[alunosmaximo];
string matriculas[alunosmaximo];
string turmas[alunosmaximo];
int totalAlunos = 0;

string nomedisciplinas[disciplinasmaximo];
string codigodisciplinas[disciplinasmaximo];
int totaldisci = 0;

float notas[alunosmaximo][disciplinasmaximo] = {0};

void carregarAlunos() {
    ifstream arquivo("alunos.txt");
    totalAlunos = 0;
    while (arquivo >> matriculas[totalAlunos]) {
        arquivo.ignore();
        getline(arquivo, nomealunos[totalAlunos], ';');
        getline(arquivo, turmas[totalAlunos]);
        totalAlunos++;
    }
    arquivo.close();
}

void cadastrarAluno() {
    string nome, matricula, turma;
    cout << "Nome: ";
    cin.ignore();
    getline(cin, nome);
    cout << "Matrícula: ";
    cin >> matricula;
    cout << "Turma: ";
    cin >> turma;

    ofstream arquivo("alunos.txt", ios::app);
    arquivo << matricula << " " << nome << ";" << turma << endl;
    arquivo.close();

    cout << "Aluno cadastrado com sucesso!" << endl;
}
void carregarDisciplinas() {
    ifstream arquivo("disciplinas.txt");
    totaldisci = 0;
    while (getline(arquivo, codigodisciplinas[totaldisci], ';')) {
        getline(arquivo, nomedisciplinas[totaldisci]);
        totaldisci++;
    }
    arquivo.close();
}

void cadastrarDisciplina() {
    string codigo, nome;
    cout << "Código da disciplina: ";
    cin >> codigo;
    cout << "Nome da disciplina: ";
    cin.ignore();
    getline(cin, nome);

    ofstream arquivo("disciplinas.txt", ios::app);
    arquivo << codigo << ";" << nome << endl;
    arquivo.close();

    cout << "Disciplina cadastrada com sucesso!" << endl;
}

void menu() {
    carregarAlunos();
    carregarDisciplinas();

    int opcao;
    do {
        cout << "MENU" << endl;
        cout << "1. Cadastrar Aluno\n";
        cout << "2. Cadastrar Disciplina\n";
        cout << "3. Lançar Nota\n";
        cout << "4. Consultar Notas do Aluno\n";
        cout << "5. Outras Consultas de Notas\n";
        cout << "6. Relatórios Gerais\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1: cadastrarAluno(); break;
            case 2: cadastrarDisciplina(); break;
            case 3: lancarNota(); break;
            case 4: consultarNotasAluno(); break;
            case 5: consultarNotas(); break;
            case 6: gerarRelatorio(); break;
            case 0: cout << "Encerrando...\n"; break;
            default: cout << "Opção inválida!\n"; break;
        }
    } while (opcao != 0);
}

int main() {
    menu();
    return 0;
}