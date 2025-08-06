#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 

using namespace std;

const int alunosmaximo= 100;
const int disciplinasmaximo= 10;

string nomealunos[alunosmaximo];
string matriculas[alunosmaximo];
string turmas[alunosmaximo];
int totalAlunos= 0;

string nomedisciplinas[disciplinasmaximo];
string codigodisciplinas[disciplinasmaximo];
int totaldisci= 0;

float notas[alunosmaximo][disciplinasmaximo]= {0};

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
void carregarDisciplinas() {
    ifstream arquivo("disciplinas.txt");
    totaldisci = 0;
    while (getline(arquivo, codigodisciplinas[totaldisci], ';')) {
        getline(arquivo, nomedisciplinas[totaldisci]);
        totaldisci++;
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

void lancarNota() {
    string matricula, codigoDisciplina;
    float nota;

    cout << "Digite a matrícula do aluno: ";
    cin >> matricula;
    cout << "Digite o código da disciplina: ";
    cin >> codigoDisciplina;
    cout << "Digite a nota: ";
    cin >> nota;

    int indiceAluno = -1;
    for (int i = 0; i < totalAlunos; i++) {
        if (matriculas[i] == matricula) {
            indiceAluno = i;
            break;
        }
    }

    if (indiceAluno == -1) {
        cout << "Aluno não encontrado." << endl;
        return;
    }

    int indiceDisciplina = -1;
    for (int j = 0; j < totaldisci; j++) {
        if (codigodisciplinas[j] == codigoDisciplina) {
            indiceDisciplina = j;
            break;
        }
    }

    if (indiceDisciplina == -1) {
        cout << "Disciplina não encontrada." << endl;
        return;
    }

    notas[indiceAluno][indiceDisciplina] = nota;

    ofstream arquivo("notas.txt", ios::app);
    arquivo << matricula << ";" << codigoDisciplina << ";" << nota << endl;
    arquivo.close();

    cout << "Nota lançada com sucesso!" << endl;
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

void consultarNotasAluno() {
    string matricula;
    cout << "Digite a matrícula do aluno: ";
    cin >> matricula;

    ifstream arquivo("notas.txt");
    string linha, mat, cod;
    float nota;
    bool encontrou = false;

    while (getline(arquivo, linha)) {
        size_t pos1 = linha.find(';');
        size_t pos2 = linha.rfind(';');

        mat = linha.substr(0, pos1);
        cod = linha.substr(pos1 + 1, pos2 - pos1 - 1);
        nota = stof(linha.substr(pos2 + 1));

        if (mat == matricula) {
            encontrou = true;
            cout << "Disciplina " << cod << " - Nota: " << nota << endl;
        }
    }

    if (!encontrou) {
        cout << "Nenhuma nota encontrada para a matrícula." << endl;
    }

    arquivo.close();
}

void consultarNotasPorDisciplina() {
    string codigo;
    cout << "Digite o código da disciplina: ";
    cin >> codigo;

    ifstream arquivo("notas.txt");
    string linha, mat, cod;
    float nota;
    bool encontrou = false;

    while (getline(arquivo, linha)) {
        size_t pos1 = linha.find(';');
        size_t pos2 = linha.rfind(';');

        mat = linha.substr(0, pos1);
        cod = linha.substr(pos1 + 1, pos2 - pos1 - 1);
        nota = stof(linha.substr(pos2 + 1));

        if (cod == codigo) {
            encontrou = true;
            cout << "Aluno " << mat << " - Nota: " << nota << endl;
        }
    }

    if (!encontrou) {
        cout << "Nenhuma nota encontrada para essa disciplina." << endl;
    }

    arquivo.close();
}


void gerarRelatorio() {
    cout << fixed << setprecision(2);
    cout << "RELATÓRIO DE MÉDIAS\n" << endl;

    for (int i = 0; i < alunosmaximo; i++)
        for (int j = 0; j < disciplinasmaximo; j++)
            notas[i][j] = 0;
a
    float somaNotasDisciplina[disciplinasmaximo] = {0};
    int contNotasDisciplina[disciplinasmaximo] = {0};

    ifstream arquivo("notas.txt");
    string linha, mat, cod;
    float nota;

    while (getline(arquivo, linha)) {
        size_t pos1 = linha.find(';');
        size_t pos2 = linha.rfind(';');

        mat = linha.substr(0, pos1);
        cod = linha.substr(pos1 + 1, pos2 - pos1 - 1);
        nota = stof(linha.substr(pos2 + 1));

        int ia = -1, id = -1;
        for (int i = 0; i < totalAlunos; i++)
            if (matriculas[i] == mat) ia = i;
        for (int j = 0; j < totaldisci; j++)
            if (codigodisciplinas[j] == cod) id = j;

        if (ia != -1 && id != -1) {
            notas[ia][id] = nota;
            somaNotasDisciplina[id] += nota;
            contNotasDisciplina[id]++;
        }
    }
    arquivo.close();

    for (int i = 0; i < totalAlunos; i++) {
        cout << "Aluno: " << nomealunos[i] << " (" << matriculas[i] << ")" << endl;

        float somaNotasAluno = 0;
        int contNotasAluno = 0;

        for (int j = 0; j < totaldisci; j++) {
            cout << " - " << nomedisciplinas[j] << " (" << codigodisciplinas[j] << "): ";
            if (notas[i][j] > 0) {
                cout << notas[i][j] << endl;
                somaNotasAluno += notas[i][j];  
                contNotasAluno++;
            } else {
                cout << "Sem nota" << endl;
            }
        }

        if (contNotasAluno > 0) {
            float mediaGeral = somaNotasAluno / contNotasAluno;
            cout << "Média geral do aluno: " << mediaGeral << endl;
        } else {
            cout << "Média geral do aluno: Sem notas lançadas" << endl;
        }

        cout << endl;
    }

    cout << "MÉDIAS GERAIS POR DISCIPLINA" << endl;
    for (int j = 0; j < totaldisci; j++) {
        cout << nomedisciplinas[j] << " (" << codigodisciplinas[j] << "): ";
        if (contNotasDisciplina[j] > 0)
            cout << somaNotasDisciplina[j] / contNotasDisciplina[j] << endl;
        else
            cout << "Sem notas lançadas" << endl;
    }
}


void consultarNotas() {
    int escolha;
    cout << "1. Notas de um aluno específico"<<endl;
    cout << "2. Notas de todos os alunos em uma disciplina"<<endl;
    cout << "Escolha: ";
    cin >> escolha;

    switch (escolha) {
        case 1: consultarNotasAluno();  break;
        case 2: consultarNotasPorDisciplina(); break;
        default: cout << "Opção inválida."<<endl; break;
    }
}

void menu() {
    carregarAlunos();
    carregarDisciplinas();

    int opcao;
    do {
        cout << "MENU" << endl;
        cout << "1. Cadastrar Aluno"<<endl;
        cout << "2. Cadastrar Disciplina"<<endl;
        cout << "3. Lançar Nota"<<endl;
        cout << "4. Consultar Notas do Aluno"<<endl;
        cout << "5. Outras Consultas de Notas"<<endl;
        cout << "6. Relatórios Gerais"<<endl;
        cout << "0. Sair"<<endl;
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1: cadastrarAluno(); break;
            case 2: cadastrarDisciplina(); break;
            case 3: lancarNota(); break;
            case 4: consultarNotasAluno(); break;
            case 5: consultarNotas(); break;
            case 6: gerarRelatorio(); break;
            case 0: cout << "Encerrado."<<endl; break;
            default: cout << "Opção inválida"<<endl; break;
        }
    } while (opcao != 0);
}

int main() {
    menu();
    return 0;
}