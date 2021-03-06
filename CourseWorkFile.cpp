#define _CRT_SECURE_NO_WARNINGS

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
using namespace std;

char ent;
char str[20];
int eint;
int sS, sF;
int counter = 0;
char fPath[100] = "Temp";
char newPath[100];
char months[12][10] = { "январе", "феврале", "марте",
"апреле", "мае", "июне", "июле", "августе",
"сентябре", "октябре", "ноябре", "декабре" };

struct name {
    char fam[30];
    char imya[30];
    char otch[30];
};

struct date {
    unsigned short dd;
    unsigned short mm;
    unsigned short yyyy;
};

struct mark {
    char subject[30] = "none\0";
    int ball;
    int isFilled = 0;
};

struct Stud {
    name fio;
    date birth;
    int year;
    char fak[30];
    char kaf[30];
    char group[15];
    char zach[15];
    char gender;
    mark grades[9][10];
    int isOK = 0;
};

int CharToInt(char c[]) {
    int a = 0;
    for (int i = strlen(c) - 1; i >= 0; i--) {
        int power = 1;
        for (int j = 0; j < strlen(c) - i - 1; j++) power *= 10;
        if ((c[i] >= '0') && (c[i] <= '9')) a += (c[i] - 48) * power;
    };
    return a;
}

int IntToChar(int c) {
    int length = 0;
    while (c > 0) {
        length++;
        c /= 10;
    }
    return length;
}

void Enter(char& c) {
    char dataline[30];
    char trash;
    dataline[0] = '\0';
    cin.get(dataline, 30);
    if (dataline[0] == '\0') {
        cin.clear();
    };
    c = dataline[0];
    do {
        trash = getchar();
    } while (trash != '\n');
}

void Enter(char c[], int len) {
    char dataline[100];
    char trash;
    dataline[0] = '\0';
    cin.get(dataline, len);
    for (int i = 0; i < len - 1; i++)
        if (dataline[i] != ';') c[i] = dataline[i];
        else c[i] = ' ';
    if (dataline[0] == '\0') {
        cin.clear();
    };
    do {
        trash = getchar();
    } while (trash != '\n');
}

int Enter(unsigned short& en, unsigned  short& em, unsigned  short& ey) {
    char dataline[30] = { "" };
    char tdate[3][30] = { "", "", "" };
    char trash;
    dataline[0] = '\0';
    cin.get(dataline, 30);
    if (dataline[0] == '\0') {
        cin.clear();
    };
    do {
        trash = getchar();
    } while (trash != '\n');
    int j = 0, k = 0;
    en = 0; em = 0; ey = 0;
    for (int i = 0; i < 30; i++) {
        if ((dataline[i] == ';') || (dataline[i] == '.') || (dataline[i] == ' ') || (dataline[i] == '/') || (dataline[i] == '\0')) {
            j = 0;
            if (++k > 2) break;
        }
        else { tdate[k][j] = dataline[i]; j++; }
    }
    if ((CharToInt(tdate[0]) > 0) && (CharToInt(tdate[0]) < 1000)) {
        if ((CharToInt(tdate[1]) > 0) && (CharToInt(tdate[1]) < 13)) {
            if (CharToInt(tdate[2]) > 999) {
                en = CharToInt(tdate[0]);
                em = CharToInt(tdate[1]);
                ey = CharToInt(tdate[2]);
            }
            else {
                cout << "Дата не распознана. Попробуйте ввести в формате ЧЧ.ММ.ГГГГ\n> ";
                return 1;
            }
        }
        else {
            cout << "Дата не распознана. Попробуйте ввести в формате ЧЧ.ММ.ГГГГ\n> ";
            return 1;
        }
    }
    else if (CharToInt(tdate[0]) > 999) {
        if ((CharToInt(tdate[1]) > 0) && (CharToInt(tdate[1]) < 13)) {
            if ((CharToInt(tdate[2]) > 0) && (CharToInt(tdate[2]) < 1000)) {
                en = CharToInt(tdate[2]);
                em = CharToInt(tdate[1]);
                ey = CharToInt(tdate[0]);
            }
            else {
                cout << "Дата не распознана. Попробуйте ввести в формате ЧЧ.ММ.ГГГГ\n> ";
                return 1;
            }
        }
        else {
            cout << "Дата не распознана. Попробуйте ввести в формате ЧЧ.ММ.ГГГГ\n> ";
            return 1;
        }
    }
    else {
        cout << "Дата не распознана. Попробуйте ввести в формате ЧЧ.ММ.ГГГГ\n> ";
        return 1;
    }
    switch (em) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        if (en > 31) {
            cout << "ОШИБКА\nВ " << months[em - 1] << " только 31 день, а вы ввели " << en << endl;
            cout << "\nПовторите ввод > ";
            em = en = ey = 0;
            return 1;
        }
        break;
    case 4: case 6: case 9: case 11:
        if (en > 30) {
            cout << "ОШИБКА\nВ " << months[em - 1] << " только 30 дней, а вы ввели " << en << endl;
            cout << "\nПовторите ввод > ";
            em = en = ey = 0;
            return 1;
        }
        break;
    case 2:
        if (!(ey % 4) && (((ey % 100) && (ey % 400)) || (!(ey % 100) && !(ey % 400)))) {
            if (en > 29) {
                cout << "ОШИБКА\nВ феврале " << ey << "-го года 29 дней, а вы ввели " << en << endl;
                cout << "\nПовторите ввод > ";
                em = en = ey = 0;
                return 1;
            }
        }
        else if (en > 28) {
            cout << "ОШИБКА\nВ феврале " << ey << "-го года 28 дней, а вы ввели " << en << endl;
            cout << "\nПовторите ввод > ";
            em = en = ey = 0;
            return 1;
        } break;
    default: cout << "Месяц должен быть числом от 1 до 12, а вы ввели " << em;
        cout << "\nПовторите ввод > "; return 1;
    }
    return 0;
}

int Enter(int& c) {
    char dataline[30];
    char numberline[30] = { "" };
    char trash;
    int flag = 0;
    dataline[0] = '\0';
    cin.get(dataline, 30);
    if (dataline[0] == '\0') {
        cin.clear();
    };
    c = CharToInt(dataline);
    do {
        trash = getchar();
    } while (trash != '\n');
    return c;
}

void Enter(int& a, int& b) {
    char dataline[10];
    char trash;
    char yfrom[10], yto[10];
    int flag = 0;
    for (int k = 0; k < 10; k++) {
        dataline[k] = '\0';
        yfrom[k] = '\0';
        yto[k] = '\0';
    }
    cin.get(dataline, 100);
    if (dataline[0] == '\0') {
        cin.clear();
    };
    if (dataline[0] != '\0') {
        int qe = 0, j = 0;
        while ((dataline[qe] != '-') && (qe < 10)) {
            yfrom[qe] = dataline[qe];
            qe++;
        }
        qe++;
        while ((dataline[qe] != '\0') && (qe < 10)) {
            yto[j] = dataline[qe];
            qe++;
            j++;
            flag = 1;
        }
    }
    if (CharToInt(yfrom) > CharToInt(yto)) {
        cout << "Ваш интервал бы интерпретирован как " << yto << "-" << yfrom << endl;
        swap(yto, yfrom);
    }
    a = CharToInt(yfrom);
    b = CharToInt(yto);
    do {
        trash = getchar();
    } while (trash != '\n');
}

int EnterFile(char c[], int deter) {
    char dataline[100];
    char trash;
    dataline[0] = '\0';
    cin.get(dataline, 100);
    if (dataline[0] == '\0') {
        cin.clear();
    };
    do {
        trash = getchar();
    } while (trash != '\n');
    fstream T;
    switch (deter) {
    case 0:
        T.open(dataline, ios_base::in | ios_base::binary);
        if (!T.is_open()) {
            cout << "\n| ОШИБКА\n| Файл не найден, либо нельзя получить к нему доступ\n| Проверьте, что путь к файлу указан без ошибок\n";
            return 0;
        }
        else if (dataline[0] != '\0') {
            for (int i = 0; i < 100; i++) c[i] = dataline[i];
            return 1;
        }
        else return 0;
        T.close();
        break;
    case 1:
        T.open(dataline, ios_base::app | ios_base::binary);
        if (dataline[0] != '\0') {
            for (int i = 0; i < 100; i++) c[i] = dataline[i];
            return 1;
        }
        else return 0;
        T.close();
        break;
    }
}

int Which(char b, char c) {
    char a;
    do {
        Enter(a);
        if ((a == b) || (a == (b + 32))) return 1;
        if ((a == c) || (a == (c + 32))) return 0; else
            cout << "Ошибка, повторите выбор > ";;
    } while (1);
}

void Which(char* a, char b, char c) {
    do {
        Enter(*a);
        if ((*a == b) || (*a == (b + 32))) {
            *a = b; break;
        }
        else if ((*a == c) || (*a == (c + 32))) {
            *a = c; break;
        }
        else cout << "Ошибка, повторите выбор > ";;
    } while (1);
}

void addZero(int c) {
    if (c > 9) cout << c; else cout << "0" << c;
}

void Teleport(char left[], char right[]) {
    ifstream fileFrom;
    ofstream fileTo;
    char f;
    fileFrom.open(left, ios_base::in | ios_base::binary);
    fileTo.open(right, ios_base::trunc | ios_base::binary);
    while (fileFrom.get(f)) {
        fileTo << f;
    }
}

void Teleport(const char left[], char right[]) {
    char L[100];
    strcpy_s(L, left);
    Teleport(L, right);
}

void Teleport(char left[], const char right[]) {
    char R[100];
    strcpy_s(R, right);
    Teleport(left, R);
}

void LoadSess(fstream& left, Stud& right) {
    char c[30] = {};
    char k = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 10; j++) {
            k = 0;
            while (!(left.eof()) && (k < 29)) {
                ent = '\0';
                (left.get(ent));
                if ((ent == ';')) break; else {
                    c[k++] = ent;
                }
                c[k] = '\0';
            }
            while (k > 28) {
                if (!(left.get(ent))) break; else if (ent == ';') break;
            }
            if (!strcmp(c, "")) {
                left.get(ent);
                if (ent == ';') {
                    left.get(ent);
                    if (ent == ';') {
                        i = 11;
                    }
                    break;
                }
                break;
            }
            strcpy_s(right.grades[i][j].subject, c);
            strcpy_s(c, "");
            left.get(ent);
            k = 0;
            while (!(left.eof()) && (k < 4)) {
                ent = '\0';
                (left.get(ent));
                if ((ent == ';')) break; else {
                    c[k++] = ent;
                }
                c[k] = '\0';
            }
            while (k > 3) {
                if (!(left.get(ent))) break; else if (ent == ';') break;
            }
            right.grades[i][j].ball = CharToInt(c);
            right.grades[i][j].isFilled = 1;
            strcpy_s(c, "");
            left.get(ent);
            if (ent == ';') {
                left.get(ent);
                if (ent == ';') {
                    i = 11;
                }
                break;
            }
        }
    }
}

void operator<<(fstream& left, Stud right) {
    left << right.fio.fam << "; " << right.fio.imya << "; " <<
        right.fio.otch << "; " << right.birth.dd << "." <<
        right.birth.mm << "." << right.birth.yyyy << "; " << right.year << "; " <<
        right.fak << "; " << right.kaf << "; " <<
        right.group << "; " << right.zach << "; " <<
        right.gender << ";";
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 10; j++) {
            if (right.grades[i][j].isFilled)
                left << " " << right.grades[i][j].subject << "; "
                << right.grades[i][j].ball << ";";
            else {
                if (j == 0) left << " ;";
                break;
            }
        }
        left << ";";
    }
    left << ";";
}

void operator>>(fstream& left, Stud& right) {
    char c[30] = {};
    char k = 0;
    while (!(left.eof()) && (k < 29)) {
        ent = '\0';
        (left.get(ent));
        if ((ent == ';')) break; else {
            c[k++] = ent;
        }
        c[k] = '\0';
    }
    while (k > 28) {
        if (!(left.get(ent))) break; else if (ent == ';') break;
    }
    strcpy_s(right.fio.fam, c);
    strcpy_s(c, "");
    left.get(ent);
    k = 0;
    while (!(left.eof()) && (k < 29)) {
        ent = '\0';
        (left.get(ent));
        if ((ent == ';')) break; else {
            c[k++] = ent;
        }
        c[k] = '\0';
    }
    while (k > 28) {
        if (!(left.get(ent))) break; else if (ent == ';') break;
    }
    strcpy_s(right.fio.imya, c);
    strcpy_s(c, "");
    left.get(ent);
    k = 0;
    while (!(left.eof()) && (k < 29)) {
        ent = '\0';
        (left.get(ent));
        if ((ent == ';')) break; else {
            c[k++] = ent;
        }
        c[k] = '\0';
    }
    while (k > 28) {
        if (!(left.get(ent))) break; else if (ent == ';') break;
    }
    strcpy_s(right.fio.otch, c);
    strcpy_s(c, "");
    left.get(ent);
    k = 0;
    while (!(left.eof()) && (k < 2)) {
        ent = '\0';
        (left.get(ent));
        if ((ent == '.')) break; else {
            c[k++] = ent;
        }
        c[k] = '\0';
    }
    while (k > 1) {
        if (!(left.get(ent))) break; else if (ent == '.') break;
    }
    right.birth.dd = CharToInt(c);
    strcpy_s(c, "");
    k = 0;
    while (!(left.eof()) && (k < 2)) {
        ent = '\0';
        (left.get(ent));
        if ((ent == '.')) break; else {
            c[k++] = ent;
        }
        c[k] = '\0';
    }
    while (k > 1) {
        if (!(left.get(ent))) break; else if (ent == '.') break;
    }
    right.birth.mm = CharToInt(c);
    strcpy_s(c, "");
    k = 0;
    while (!(left.eof()) && (k < 4)) {
        ent = '\0';
        (left.get(ent));
        if ((ent == ';')) break; else {
            c[k++] = ent;
        }
        c[k] = '\0';
    }
    while (k > 3) {
        if (!(left.get(ent))) break; else if (ent == ';') break;
    }
    right.birth.yyyy = CharToInt(c);
    strcpy_s(c, "");
    left.get(ent);
    k = 0;
    while (!(left.eof()) && (k < 4)) {
        ent = '\0';
        (left.get(ent));
        if ((ent == ';')) break; else {
            c[k++] = ent;
        }
        c[k] = '\0';
    }
    while (k > 3) {
        if (!(left.get(ent))) break; else if (ent == ';') break;
    }
    right.year = CharToInt(c);
    strcpy_s(c, "");
    left.get(ent);
    k = 0;
    while (!(left.eof()) && (k < 29)) {
        ent = '\0';
        (left.get(ent));
        if ((ent == ';')) break; else {
            c[k++] = ent;
        }
        c[k] = '\0';
    }
    while (k > 28) {
        if (!(left.get(ent))) break; else if (ent == ';') break;
    }
    strcpy_s(right.fak, c);
    strcpy_s(c, "");
    left.get(ent);
    k = 0;
    while (!(left.eof()) && (k < 29)) {
        ent = '\0';
        (left.get(ent));
        if ((ent == ';')) break; else {
            c[k++] = ent;
        }
        c[k] = '\0';
    }
    while (k > 28) {
        if (!(left.get(ent))) break; else if (ent == ';') break;
    }
    strcpy_s(right.kaf, c);
    strcpy_s(c, "");
    left.get(ent);
    k = 0;
    while (!(left.eof()) && (k < 14)) {
        ent = '\0';
        (left.get(ent));
        if ((ent == ';')) break; else {
            c[k++] = ent;
        }
        c[k] = '\0';
    }
    while (k > 13) {
        if (!(left.get(ent))) break; else if (ent == ';') break;
    }
    strcpy_s(right.group, c);
    strcpy_s(c, "");
    left.get(ent);
    k = 0;
    while (!(left.eof()) && (k < 14)) {
        ent = '\0';
        (left.get(ent));
        if ((ent == ';')) break; else {
            c[k++] = ent;
        }
        c[k] = '\0';
    }
    while (k > 13) {
        if (!(left.get(ent))) break; else if (ent == ';') break;
    }
    strcpy_s(right.zach, c);
    strcpy_s(c, "");
    left.get(ent);
    k = 0;
    while (!(left.eof()) && (k < 1)) {
        ent = '\0';
        (left.get(ent));
        if ((ent == ';')) break; else {
            c[k++] = ent;
        }
        c[k] = '\0';
    }
    while (k > 0) {
        if (!(left.get(ent))) break; else if (ent == ';') break;
    }
    right.gender = c[0];
    strcpy_s(c, "");
    left.get(ent);

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 10; j++)
            right.grades[i][j].isFilled = 0;

    if (right.year - right.birth.yyyy < 14) {
        right.year = 0;
    }

    switch (right.birth.mm) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        if ((right.birth.dd > 31) || (right.birth.dd < 0)) {
            right.birth.yyyy = right.birth.mm = right.birth.dd = 0;
        }
        break;
    case 4: case 6: case 9: case 11:
        if ((right.birth.dd > 30) || (right.birth.dd < 0)) {
            right.birth.yyyy = right.birth.mm = right.birth.dd = 0;
        }
        break;
    case 2:
        if (!(right.birth.yyyy % 4) && (((right.birth.yyyy % 100) && (right.birth.yyyy % 400)) || (!(right.birth.yyyy % 100) && !(right.birth.yyyy % 400)))) {
            if (right.birth.dd > 29) {
                right.birth.yyyy = right.birth.mm = right.birth.dd = 0;
            }
        }
        else if (right.birth.dd > 28) {
            right.birth.yyyy = right.birth.mm = right.birth.dd = 0;
        } break;
    default: right.birth.yyyy = right.birth.mm = right.birth.dd = 0;
    }

    LoadSess(left, right);
    right.isOK = !left.eof();
}

bool operator>(Stud& left, Stud& right) {
    return (left.year > right.year);
}
bool operator<(Stud& left, Stud& right) {
    return (left.year < right.year);
}
bool operator>=(Stud& left, int right) {
    return left.birth.yyyy >= right;
}
bool operator<=(Stud& left, int right) {
    return left.birth.yyyy <= right;
}

void SumFile(const char f1[], const char f2[], char sum[]) {
    ifstream File1;
    ifstream File2;
    ofstream FileSum;
    char s;
    File1.open(f1, ios_base::in | ios_base::binary);
    File2.open(f2, ios_base::in | ios_base::binary);
    FileSum.open(sum, ios_base::app | ios_base::binary);
    while (File1.get(s)) if (s == ':') break;
    while (File1.get(s)) {
        FileSum << s;
    }
    while (File2.get(s)) {
        FileSum << s;
    }
    File1.close();
    File2.close();
    FileSum.close();
}

class Data {
protected:
    int det = 0;
    Stud about;
public:
    virtual void Set() = 0;
    virtual void Edit() = 0;
    virtual void Load() = 0;
};

class Student : public Data {
    friend class Control;
    friend int Recovery(void);
public:
    Student(int a) {
        det = a;
    }
    void Set() override {
        ofstream isCr;
        isCr.open("isCrash", ios_base::trunc | ios_base::binary);
        isCr << 1;
        isCr.close();
        switch (det) {
        case 1:
            int N, u;
            cout << "\nВвод студента № " << counter + 1 << ".\nВведите фамилию > ";
            Enter(about.fio.fam, 30);
            Save(1);
        case 2:
            cout << "Введите имя > ";
            Enter(about.fio.imya, 30);
            Save(2);
        case 3:
            cout << "Введите отчество > ";
            Enter(about.fio.otch, 30);
            Save(3);
        case 4:
            cout << "Введите дату рождения (число, месяц и год) > ";
            while (Enter(about.birth.dd, about.birth.mm, about.birth.yyyy));
            Save(4);
        case 5:
            cout << "Введите год поступления в институт > ";
            Enter(about.year);
            while (about.year < 14 + about.birth.yyyy) {
                cout << "ОШИБКА\nЧеловек " << about.birth.yyyy << "-го года рождения не мог поступить в "
                    << about.year << " году.\nB - редактировать дату рождения    R - повтор ввода года поступл-ия\n> ";
                if (Which('B', 'R')) {
                    cout << "Введите дату рождения полностью > ";
                    while (Enter(about.birth.dd, about.birth.mm, about.birth.yyyy));
                }
                else {
                    cout << "Введите год поступления в институт > ";
                    Enter(about.year);
                }
            };
            Save(5);
        case 6:
            cout << "Введите факультет > ";
            Enter(about.fak, 30);
            Save(6);
        case 7:
            cout << "Введите кафедру > ";
            Enter(about.kaf, 30);
            Save(7);
        case 8:
            cout << "Введите группу > ";
            Enter(about.group, 15);
            Save(8);
        case 9:
            cout << "Введите номер зачетной книжки > ";
            do { Enter(about.zach, 15); } while (CheckZach());
            Save(9);
        case 10:
            cout << "Введите пол (м - мужской, ж - женский) > ";
            if (Which('М', 'Ж')) about.gender = 'М'; else about.gender = 'Ж';
            Save(10);
        case 11:
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 10; j++) {
                    about.grades[i][j].isFilled = 0;
                }
            }
        }
    };
    void Edit() override {
        fstream OldFile;
        fstream NewFile;
        OldFile.open(fPath, ios_base::in | ios_base::binary);
        NewFile.open("Tmp", ios_base::trunc | ios_base::out | ios_base::binary);
        for (int i = 0; i < det; i++) {
            OldFile >> about;
        }
        switch (eint) {
        case 1:
            cout << about.fio.fam << endl;
            cout << "Введите новое значение > ";
            Enter(about.fio.fam, 30);
            break;
        case 2:
            cout << about.fio.imya << endl;
            cout << "Введите новое значение > ";
            Enter(about.fio.imya, 30);
            break;
        case 3:
            cout << about.fio.otch << endl;
            cout << "Введите новое значение > ";
            Enter(about.fio.otch, 30);
            break;
        case 4:
            addZero(about.birth.dd);
            cout << ".";
            addZero(about.birth.mm);
            cout << "." << about.birth.yyyy << endl;
            cout << "Введите новое значение > ";
            while (Enter(about.birth.dd, about.birth.mm, about.birth.yyyy));
            while (1) {
                if (about.year < 14 + about.birth.yyyy) {
                    cout << "ОШИБКА\nЧеловек " << about.birth.yyyy << "-го года рождения не мог поступить в "
                        << about.year << " году.\nB - редактировать дату рождения    R - редактировать год поступления\n> ";
                    if (Which('B', 'R')) {
                        cout << "Введите новую дату рождения > ";
                        while (Enter(about.birth.dd, about.birth.mm, about.birth.yyyy));
                    }
                    else {
                        cout << "Введите год поступления в институт > ";
                        Enter(about.year);
                    }
                }
                else break;
            }
            break;
        case 5:
            cout << about.year << endl;
            cout << "Введите новое значение > ";
            Enter(about.year);
            while (1) {
                if (about.year < 14 + about.birth.yyyy) {
                    cout << "ОШИБКА\nЧеловек " << about.birth.yyyy << "-го года рождения не мог поступить в "
                        << about.year << " году.\nB - редактировать дату рождения    R - редактировать год поступления\n> ";
                    if (Which('B', 'R')) {
                        cout << "Введите новую дату рождения > ";
                        while (Enter(about.birth.dd, about.birth.mm, about.birth.yyyy));
                    }
                    else {
                        cout << "Введите год поступления в институт > ";
                        Enter(about.year);
                    }
                }
                else break;
            }
            break;
        case 6:
            cout << about.fak << endl;
            cout << "Введите новое значение > ";
            Enter(about.fak, 30);
            break;
        case 7:
            cout << about.kaf << endl;
            cout << "Введите новое значение > ";
            Enter(about.kaf, 30);
            break;
        case 8:
            cout << about.group << endl;
            cout << "Введите новое значение > ";
            Enter(about.group, 15);
            break;
        case 9:
            cout << about.zach << endl;
            cout << "Введите новое значение > ";
            do { Enter(about.zach, 15); } while (CheckZach());
            break;
        case 10:
            cout << about.gender << endl;
            cout << "Введите новое значение > ";
            if (Which('М', 'Ж')) about.gender = 'М'; else about.gender = 'Ж';
            break;
        }
        OldFile.close();
        OldFile.open(fPath, ios_base::in | ios_base::binary);
        OldFile.seekg(0, ios::beg);
        Stud A;
        for (int i = 1; i < det; i++) {
            OldFile >> A;
            NewFile << A;
        }
        NewFile << about;
        OldFile >> A;
        for (int i = det + 1; i <= counter; i++) {
            OldFile >> A;
            NewFile << A;
        }
        OldFile.close();
        NewFile.close();
        Teleport("Tmp", fPath);
    };
    void Load() override {
        fstream T;
        char e;
        T.open("RecoveryStudent", ios_base::in | ios_base::binary);
        while (T.get(e)) if (e == ':') break;
        T >> about;
        T.close();
    }
protected:
    void Save(int a) {
        ofstream R;
        R.open("RecoveryStudent", ios_base::trunc | ios_base::binary);
        R << fPath << ":";
        R << about.fio.fam << "; ";
        if (a == 1) { R.close(); return; }
        R << about.fio.imya << "; ";
        if (a == 2) { R.close(); return; }
        R << about.fio.otch << "; ";
        if (a == 3) { R.close(); return; }
        R << about.birth.dd << "." << about.birth.mm << "." << about.birth.yyyy << "; ";
        if (a == 4) { R.close(); return; }
        R << about.year << "; ";
        if (a == 5) { R.close(); return; }
        R << about.fak << "; ";
        if (a == 6) { R.close(); return; }
        R << about.kaf << "; ";
        if (a == 7) { R.close(); return; }
        R << about.group << "; ";
        if (a == 8) { R.close(); return; }
        R << about.zach << "; ";
        if (a == 9) { R.close(); return; }
        R << about.gender << ";";
        if (a == 10) { R.close(); return; }
        R.close();
    }
    void Print() {
        if (det) {
            fstream Read;
            Read.open(fPath, ios_base::in | ios_base::binary);
            Read.seekg(0, ios::beg);
            for (int i = 0; i < det; i++) Read >> about;
            if ((det > 0) && (det <= counter)) {
                cout << "1. Фамилия > " << about.fio.fam << endl;
                cout << "2. Имя > " << about.fio.imya << endl;
                cout << "3. Отчество > " << about.fio.otch << endl;
                cout << "4. Дата рождения > ";
                addZero(about.birth.dd);
                cout << ".";
                addZero(about.birth.mm);
                cout << "." << about.birth.yyyy << endl;
                cout << "5. Год поступления > " << about.year << endl;
                cout << "6. Факультет > " << about.fak << endl;
                cout << "7. Кафедра > " << about.kaf << endl;
                cout << "8. Группа > " << about.group << endl;
                cout << "9. Номер зачётной книжки > " << about.zach << endl;
                cout << "10.Пол > " << about.gender << endl;
                cout << "\n11. СЕССИИ\n";
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 10; j++) {
                        if (about.grades[i][j].isFilled != 0) {
                            if (j == 0) cout << "     Сессия №" << i + 1 << endl;
                            cout << "   " << about.grades[i][j].subject << " - " << about.grades[i][j].ball << endl;
                        }
                        else break;
                    }
                }
            }
            else cout << "";
            Read.close();
        }
        else {
            int cf = 7, ci = 3, co = 8, cfak = 9, ckaf = 7, cgr = 6, cz = 9;
            fstream Read;
            Read.open(fPath, ios_base::in | ios_base::binary);
            Read.seekg(0, ios::beg);
            counter = 0;
            while (!Read.eof()) {
                Read >> about;
                if (about.isOK) {
                    if (strlen(about.fio.fam) > cf) cf = strlen(about.fio.fam);
                    if (strlen(about.fio.imya) > ci) ci = strlen(about.fio.imya);
                    if (strlen(about.fio.otch) > co) co = strlen(about.fio.otch);
                    if (strlen(about.fak) > cfak) cfak = strlen(about.fak);
                    if (strlen(about.kaf) > ckaf) ckaf = strlen(about.kaf);
                    if (strlen(about.group) > cgr) cgr = strlen(about.group);
                    if (strlen(about.zach) > cz) cz = strlen(about.zach);
                    counter++;
                }
            }
            cout << endl << "№";
            int ll = IntToChar(counter);
            for (int i = 0; i <= ll; i++) cout << " ";
            if (cf > 7) {
                cout << "Фамилия";
                for (int i = 7; i <= cf; i++) cout << " ";
            }
            else cout << "Фамилия ";
            cout << " ";
            if (ci > 3) {
                cout << "Имя";
                for (int i = 3; i <= ci; i++) cout << " ";
            }
            else cout << "Имя ";
            cout << " ";
            if (co > 8) {
                cout << "Отчество";
                for (int i = 8; i <= co; i++) cout << " ";
            }
            else cout << "Отчество ";
            cout << " Дата рожд.  Год поступ.  ";
            if (cfak > 9) {
                cout << "Факультет";
                for (int i = 9; i <= cfak; i++) cout << " ";
            }
            else cout << "Факультет ";
            cout << " ";
            if (ckaf > 7) {
                cout << "Кафедра";
                for (int i = 7; i <= ckaf; i++) cout << " ";
            }
            else cout << "Кафедра ";
            cout << " ";
            if (cgr > 6) {
                cout << "Группа";
                for (int i = 6; i <= cgr; i++) cout << " ";
            }
            else cout << "Группа ";
            cout << " ";
            if (cz > 9) {
                cout << "№ зач. кн";
                for (int i = 9; i <= cz; i++) cout << " ";
            }
            else cout << "№ зач. кн ";
            cout << " Пол ";
            int j = 1;
            Read.close();
            Read.open(fPath, ios_base::in | ios_base::binary);
            Read.seekg(0, ios::beg);
            for (int i = 0; i < counter; i++) {
                Read >> about;
                cout << endl;
                cout << j << ".";
                for (int i = IntToChar(j++); i <= ll; i++) cout << " ";
                if (cf > strlen(about.fio.fam)) {
                    cout << about.fio.fam;
                    for (int i = strlen(about.fio.fam); i <= cf; i++) cout << " ";
                }
                else cout << about.fio.fam << " ";
                cout << " ";
                if (ci > strlen(about.fio.imya)) {
                    cout << about.fio.imya;
                    for (int i = strlen(about.fio.imya); i <= ci; i++) cout << " ";
                }
                else cout << about.fio.imya << " ";
                cout << " ";
                if (co > strlen(about.fio.otch)) {
                    cout << about.fio.otch;
                    for (int i = strlen(about.fio.otch); i <= co; i++) cout << " ";
                }
                else cout << about.fio.otch << " ";
                cout << " ";
                addZero(about.birth.dd);
                cout << ".";
                addZero(about.birth.mm);
                cout << "." << about.birth.yyyy << "  " << about.year <<
                    "         ";
                if (cfak > strlen(about.fak)) {
                    cout << about.fak;
                    for (int i = strlen(about.fak); i <= cfak; i++) cout << " ";
                }
                else cout << about.fak << " ";
                cout << " ";
                if (ckaf > strlen(about.kaf)) {
                    cout << about.kaf;
                    for (int i = strlen(about.kaf); i <= ckaf; i++) cout << " ";
                }
                else cout << about.kaf << " ";
                cout << " ";
                if (cgr > strlen(about.group)) {
                    cout << about.group;
                    for (int i = strlen(about.group); i <= cgr; i++) cout << " ";
                }
                else cout << about.group << " ";
                cout << " ";
                if (cz > strlen(about.zach)) {
                    cout << about.zach;
                    for (int i = strlen(about.zach); i <= cz; i++) cout << " ";
                }
                else cout << about.zach << " ";
                cout << " " << about.gender;
            }
            Read.close();
        }
    };
    int CheckZach() {
        Stud Test;
        fstream Read;
        Read.open(fPath, ios_base::in | ios_base::binary);
        while (!Read.eof()) {
            Read >> Test;
            if (Test.isOK) {
                if (!strcmp(Test.zach, about.zach)) {
                    cout << "Этот номер зачетной книжки принадлежит студенту " <<
                        Test.fio.fam << " " << Test.fio.imya << " " <<
                        Test.fio.otch << "\nПовторите ввод > ";
                    return 1;
                }
            }
            else break;
        }
        Read.close();
        return 0;
    }
    void Erase() {
        int p1 = 0, p2;
        fstream File1;
        File1.open(fPath, ios_base::in | ios_base::binary);
        fstream File2;
        File2.open("Tmp", ios_base::trunc | ios_base::out | ios_base::binary);
        for (int i = 1; i < det; i++) {
            File1 >> about;
            File2 << about;
        }
        File1 >> about;
        cout << about.fio.fam << " " <<
            about.fio.imya << " " <<
            about.fio.otch << " удал";
        (about.gender == 'М') ? cout << "ён" : cout << "ена";
        for (int i = det; i < counter; i++) {
            File1 >> about;
            File2 << about;
        }
        File1.close();
        File2.close();
        Teleport("Tmp", fPath);
    }
};

class Sessions : public Data {
    friend class Control;
public:
    Sessions(int a) {
        det = a;
    }
    void Load() override {
        fstream T;
        T.open("RecoverySessions", ios_base::in | ios_base::binary);
        T.get(ent);
        LoadSess(T, about);
        T.close();
    }
    void Save() {
        ofstream R;
        R.open("RecoverySessions", ios_base::trunc | ios_base::binary);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 10; j++) {
                if (about.grades[i][j].isFilled)
                    R << " " << about.grades[i][j].subject << "; "
                    << about.grades[i][j].ball << ";";
                else {
                    if (j == 0) R << " ;";
                    break;
                }
            }
            R << ";";
        }
        R << ";";
        R.close();
    }
    int CheckSubject(int k, int m) {
        for (int i = 0; i < 10; i++)
            if ((m != i) && (about.grades[k][i].isFilled))
                if (!strcmp(about.grades[k][m].subject, about.grades[k][i].subject)) {
                    cout << "Такой предмет уже есть\n";
                    return 1;
                }
        return 0;
    }
    void Set() override {
        char NSess[3] = "";
        int count;
        int numb;
        Save();
        cout << "\nВвод оценок\n";
        do {
            cout << "\n  Введите число 1-9 для редактирования сессии или N для выхода\n  > ";
            Enter(NSess, 3);
            NSess[2] = '\0';
            if ((CharToInt(NSess) > 0) && (CharToInt(NSess) < 10)) {
                numb = CharToInt(NSess) - 1;
                cout << "\n  Сессия № " << numb + 1 << "\n  В этой сессии ";
                count = 0;
                for (int i = 0; i < 10; i++) {
                    if (about.grades[numb][i].isFilled != 0) {
                        count++;
                    }
                }
                (count == 0) ? cout << "нет" : cout << count;
                cout << " предмет";
                if ((count == 0) || (count > 4)) cout << "ов";
                if ((count > 1) && (count < 5)) cout << "а";
                do {
                    for (int i = 0; i < count; i++) {
                        cout << "\n  " << i + 1 << ". " << about.grades[numb][i].subject << " - " << about.grades[numb][i].ball;
                    }
                    if (count == 0) {
                        cout << "\n\n  Выберите действие\n  A - добавить   S - выбрать другую сессию\n  > ";
                    }
                    else if (count == 10) {
                        cout << "\n\n  Выберите действие\n  E - редактировать  D - удалить предмет\n  C - удалить все  S - выбрать другую сессию\n  > ";
                    }
                    else cout << "\n\n  Выберите действие\n  E - редактировать  D - удалить предмет\n  C - удалить все    A - добавить\n  S - выбрать другую сессию\n  > ";
                    do {
                        Enter(ent);
                        switch (ent) {
                        case 'E': case 'e':
                            if (count != 0) {
                                cout << "\n  Редактирование.\n  Выберите номер предмета для редактирования\n  > ";
                                Enter(eint);
                                if (about.grades[numb][eint - 1].isFilled) {
                                    do {
                                        cout << "\n  Введите новое название для предмета " << about.grades[numb][eint - 1].subject << "\n > ";
                                        Enter(about.grades[numb][eint - 1].subject, 30);
                                    } while (CheckSubject(numb, eint - 1));
                                    cout << "\n  Введите оценку для предмета " << about.grades[numb][eint - 1].subject << " > ";
                                    EnterBall(numb, eint - 1);
                                    about.grades[numb][eint - 1].isFilled = 1;
                                    Save();
                                }
                                else
                                {
                                    cout << "Предмет не отредактирован\n";
                                    ent = 'N';
                                }
                            }
                            else cout << "Ошибка, повторите ввод > ";
                            break;
                        case 'D': case 'd':
                            if (count != 0) {
                                cout << "\n  Удаление.\n  Выберите номер предмета для удаления\n  > ";
                                Enter(eint);
                                if (about.grades[numb][eint - 1].isFilled == 1) {
                                    cout << "\n  Вы действительно хотите удалить " << about.grades[numb][eint - 1].subject << " - " << about.grades[numb][eint - 1].ball << "?\n  Y - да\tN - нет\n  > ";
                                    if (Which('Y', 'N')) {
                                        for (int i = (eint - 1); i < 9; i++) {
                                            strcpy_s(about.grades[numb][i].subject, about.grades[numb][i + 1].subject);
                                            about.grades[numb][i].ball = about.grades[numb][i + 1].ball;
                                            about.grades[numb][i].isFilled = about.grades[numb][i + 1].isFilled;

                                        }
                                        about.grades[numb][9].isFilled = 0;
                                        Save();
                                        count--;
                                    }
                                    else {
                                        cout << "Предмет не удалён\n";
                                        ent = 'N';
                                    }
                                }
                                else
                                {
                                    cout << "Предмет не удалён\n";
                                    ent = 'N';
                                }
                            }
                            else cout << "Ошибка, повторите ввод > ";
                            break;
                        case 'C': case 'c':
                            if (count != 0) {
                                cout << "\n  Вы действительно хотите удалить все предметы в этой сессии\n  Y - да\tN - нет\n  > ";
                                if (Which('Y', 'N')) {
                                    for (int i = 0; i < 10; i++) {
                                        strcpy_s(about.grades[numb][i].subject, "none");
                                        about.grades[numb][i].isFilled = 0;
                                    }
                                    count = 0;
                                    Save();
                                }
                                else {
                                    cout << "Хорошо.\n";
                                    ent = 'N';
                                }
                            }
                            else cout << "Ошибка, повторите ввод > ";
                            break;
                        case 'A': case 'a':
                            if (count != 10) {
                                cout << "\n  Добавление.";
                                do {
                                    do {
                                        cout << "\n  Введите название предмета > ";
                                        Enter(about.grades[numb][count].subject, 30);
                                    } while (CheckSubject(numb, count));
                                    cout << "\n  Введите оценку за предмет " << about.grades[numb][count].subject << " > ";
                                    EnterBall(numb, count);
                                    about.grades[numb][count].isFilled = 1;
                                    Save();
                                    if (count != 9) {
                                        cout << "\n  Предмет добавлен. Ещё один?\n  Y - да\tN - нет, вернуться в меню\n  > ";
                                        Which(&ent, 'Y', 'N');
                                    }
                                    else {
                                        cout << "\n  Предмет добавлен.\n";
                                        ent = 'N';
                                    }
                                    (count)++;
                                } while (ent == 'Y' || ent == 'y');
                            }
                            break;
                        case 'S': case 's':
                            break;
                        default: ent = 'W'; cout << "Ошибка, повторите выбор > ";
                        }
                    } while (ent == 'W');
                } while (ent != 'S' && ent != 's');
            }
        } while (NSess[0] != 'N' && NSess[0] != 'n');
    };
    void Edit() override {
        cout << "Сессии\n";
        fstream OldFile;
        fstream NewFile;
        OldFile.open(fPath, ios_base::in | ios_base::binary);
        NewFile.open("Tmp", ios_base::trunc | ios_base::out | ios_base::binary);
        for (int i = 0; i < det; i++) {
            OldFile >> about;
        }
        Set();
        OldFile.close();
        OldFile.open(fPath, ios_base::in | ios_base::binary);
        OldFile.seekg(0, ios::beg);
        Stud A;
        for (int i = 1; i < det; i++) {
            OldFile >> A;
            NewFile << A;
        }
        NewFile << about;
        OldFile >> A;
        for (int i = det + 1; i <= counter; i++) {
            OldFile >> A;
            NewFile << A;
        }
        OldFile.close();
        NewFile.close();
        Teleport("Tmp", fPath);
    };
    void EnterBall(int a, int b) {
        int c;
        do {
            Enter(c);
            if ((c < 1) || (c > 5)) {
                cout << "Оценкой должно быть число от 1 до 5\nПовторите ввод > ";
            }
        } while ((c < 1) || (c > 5));
        about.grades[a][b].ball = c;
    }
};

void Set(Data* temp) {
    temp->Set();
}

void Edit(Data* temp) {
    temp->Edit();
}

void Load(Data* temp) {
    temp->Load();
}

int Recovery() {
    fstream T;
    T.open("RecoveryStudent", ios_base::in | ios_base::binary);
    for (int i = 0; i < 100; i++) fPath[i] = '\0';
    for (int i = 0; i < 99; i++) {
        T.get(fPath[i]);
        if (fPath[i] == ':') {
            fPath[i] = '\0';
            break;
        }
    }
    Stud R;
    Student P(0);
    P.Print();
    cout << "\n\n";
    T >> R;
    if (strcmp(R.fio.fam, "")) {
        cout << "Фамилия > " << R.fio.fam << endl;
        if (strcmp(R.fio.imya, "")) {
            cout << "Имя > " << R.fio.imya << endl;
            if (strcmp(R.fio.otch, "")) {
                cout << "Отчество > " << R.fio.otch << endl;
                if (R.birth.dd != 0) {
                    cout << "Дата рождения > ";
                    addZero(R.birth.dd);
                    cout << ".";
                    addZero(R.birth.mm);
                    cout << "." << R.birth.yyyy << endl;
                    if (R.year != 0) {
                        cout << "Год поступления в институт > " << R.year << endl;
                        if (strcmp(R.fak, "")) {
                            cout << "Факультет > " << R.fak << endl;
                            if (strcmp(R.kaf, "")) {
                                cout << "Кафедра > " << R.kaf << endl;
                                if (strcmp(R.group, "")) {
                                    cout << "Группа > " << R.group << endl;
                                    if (strcmp(R.zach, "")) {
                                        cout << "Номер зачетной книжки > " << R.zach << endl;
                                        if ((R.gender == 'М') || (R.gender == 'Ж')) {
                                            cout << "Пол > " << R.gender << endl;
                                            return 11;
                                        }
                                        else {
                                            return 10;
                                        }
                                    }
                                    else {
                                        return 9;
                                    }
                                }
                                else {
                                    return 8;
                                }
                            }
                            else {
                                return 7;
                            }
                        }
                        else {
                            return 6;
                        }
                    }
                    else {
                        return 5;
                    }
                }
                else {
                    return 4;
                }
            }
            else {
                return 3;
            }
        }
        else {
            return 2;
        }
    }
    else {
        return 0;
    }
    T.close();
}

class Crypto {
    friend class Control;
    char* cryptostring = new char[40];
    CHAR Password[30];
    BYTE* data = NULL;
protected:
    int Encrypt() {
        if (cryptostring == nullptr) {
            cout << "Ошибка при шифровании файла\n";
            return 1;
        }
        ifstream OldFile;
        ifstream Enc;
        ofstream NewFile;
        cout << "Введите пароль для шифрования\n| ВАЖНО!\n| Забытый пароль невозможно восстановить\n> ";
        Enter(Password, 30);
        OldFile.open(fPath, ios_base::in | ios_base::binary);
        NewFile.open("Tmp", ios_base::trunc | ios_base::binary);
        int j = 0;
        while (!OldFile.eof()) {
            if (j < 8) {
                OldFile.get(ent);
                cryptostring[j++] = ent;
            }
            else {
                j = 0;
                cryptostring[8] = '\0';
                if (InPass(cryptostring, strlen(cryptostring))) return 1;
                for (int i = 0; i < 16; i++)
                    NewFile << data[i];
                for (int i = 0; i < 29; i++) cryptostring[i] = ' ';
                cryptostring[29] = '\0';
            }
        }
        if (j != 0) {
            cryptostring[8] = '\0';
            if (InPass(cryptostring, strlen(cryptostring))) return 1;
            for (int i = 0; i < 16; i++)
                NewFile << data[i];
        }
        OldFile.close();
        NewFile.close();
        OldFile.open("Tmp", ios_base::in | ios_base::binary);
        int sl = strlen(fPath);
        if (remove(fPath)) {
            cout << "Кажется, вы ограничили доступ к вашему файлу. Данные зашифрованы, но они могут быть не в безопасности\n";
        };
        if (sl >= 95) sl = 94;
        fPath[sl] = '.';
        fPath[sl + 1] = 'e';
        fPath[sl + 2] = 'n';
        fPath[sl + 3] = 'c';
        fPath[sl + 4] = '\0';
        NewFile.open(fPath, ios_base::trunc | ios_base::binary);
        while (OldFile.get(ent)) NewFile << ent;
        OldFile.close();
        NewFile.close();
        return 0;
    }
    int Decrypt() {
        ifstream OldFile;
        ofstream Enc;
        ofstream NewFile;
        HCRYPTKEY hSessionKey;

        OldFile.open(fPath, ios_base::in | ios_base::binary);
        NewFile.open("Tmp", ios_base::trunc | ios_base::binary);

        cout << "Документ зашифрован\nВведите пароль > ";
        Enter(Password, 30);

        int j = 0, r = 0, flag = 1;
        while (!OldFile.eof()) {
            if (j < 16) {
                OldFile.get(ent);
                cryptostring[j++] = ent;
            }
            else {
                j = 0;
                data = (BYTE*)cryptostring;
                if (flag) {
                    if (FromPass(cryptostring, 8))
                        flag = 0;
                }
                else if (FromPass(cryptostring, 8)) return 1; else flag = 1;
                cryptostring[8] = '\0';
                for (int i = 0; i < 8; i++)
                    NewFile << data[i];
                for (int i = 0; i < 30; i++) cryptostring[i] = '\0';
            }
        }
        cryptostring[j] = '\0';
        OldFile.close();
        NewFile.close();
        int sl = strlen(fPath);
        if (remove(fPath)) {
            cout << "Пожалуйста, вручную удалите файл " << fPath << " - программа не может получить к ней доступ\n";
        };
        for (int i = sl - 4; i < 99; i++) fPath[i] = '\0';
        OldFile.open("Tmp", ios_base::in | ios_base::binary);
        NewFile.open(fPath, ios_base::trunc | ios_base::binary);
        while (OldFile.get(ent)) NewFile << ent;
        return 0;
    }
    int InPass(char str[], int slen) {
        DWORD count = slen;

        HCRYPTPROV hProv = 0;
        HCRYPTKEY hKey = 0;
        HCRYPTHASH hHash = 0;

        DWORD dwLength;
        dwLength = (DWORD)strlen(Password);

        CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_DELETEKEYSET);

        if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_NEWKEYSET))
        {
            cout << "Возникла ошибка при шифровании\n";
            return 1;
        }

        if (!CryptCreateHash(hProv, CALG_SHA1, 0, 0, &hHash))
        {
            return 1;
        }

        if (!CryptHashData(hHash, (BYTE*)Password, dwLength, 0))
        {
            return 1;
        }

        if (!CryptDeriveKey(hProv, CALG_RC2, hHash, CRYPT_EXPORTABLE, &hKey))
        {
            return 1;
        }

        DWORD const str_len = (DWORD)slen;
        DWORD len = str_len;
        DWORD buf_len = 0;

        CryptEncrypt(hKey, NULL, TRUE, 0, data, &len, buf_len);

        buf_len = len;
        len = str_len;
        data = (BYTE*)malloc(buf_len);
        memcpy(data, str, str_len);

        CryptEncrypt(hKey, NULL, TRUE, 0, data, &len, buf_len);
        return 0;
    }
    int FromPass(char to[], int slen) {
        DWORD count = 16;

        HCRYPTPROV hProv = 0;
        HCRYPTKEY hKey = 0;
        HCRYPTHASH hHash = 0;

        DWORD dwLength;
        dwLength = (DWORD)strlen(Password);

        CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_DELETEKEYSET);

        if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_NEWKEYSET))
        {
            return 1;
        }

        if (!CryptCreateHash(hProv, CALG_SHA1, 0, 0, &hHash))
        {
            return 1;
        }

        if (!CryptHashData(hHash, (BYTE*)Password, dwLength, 0))
        {
            return 1;
        }

        if (!CryptDeriveKey(hProv, CALG_RC2, hHash, CRYPT_EXPORTABLE, &hKey))
        {
            return 1;
        }

        DWORD const str_len = (DWORD)16;
        DWORD len = str_len;
        DWORD buf_len = 0;
        char string[16];
        memcpy(string, data, 16);

        if (!CryptDecrypt(hKey, NULL, TRUE, 0, (BYTE*)string, &len)) {
            return 1;
        }
        strcpy(to, string);
        return 0;
    }

    int Check() {
        return ((fPath[strlen(fPath) - 1] == 'c') &&
            (fPath[strlen(fPath) - 2] == 'n') &&
            (fPath[strlen(fPath) - 3] == 'e') &&
            (fPath[strlen(fPath) - 4] == '.'));
    }
};


class Control {
public:
    Control() {
        int choo = 1;
        do {
            if (choo == 1) choo = Hub();
            else if (choo == 2) choo = WhatToDo();
        } while (choo != 0);
    }
    ~Control() {
        if (strcmp(fPath, "Temp")) {
            Trash(1);
            ifstream C;
            C.open("RecoveryStudent", ios_base::in | ios_base::binary);
            if (C.is_open()) {
                C.close();
                remove("RecoveryStudent");
            }
            else C.close();
            C.open("RecoverySessions", ios_base::in | ios_base::binary);
            if (C.is_open()) {
                C.close();
                remove("RecoverySessions");
            }
            else C.close();
            C.open("Tmp", ios_base::in | ios_base::binary);
            if (C.is_open()) {
                C.close();
                remove("Tmp");
            }
            else C.close();
        }
        cout << "База данных студентов была сохранена в файле " << fPath;
    }
private:
    void Trash(int det) {
        fstream isCrash;
        isCrash.open("RecoveryStudent", ios_base::trunc | ios_base::out | ios_base::binary);
        isCrash.close();
        if (det) {
            isCrash.open("isCrash", ios_base::trunc | ios_base::out | ios_base::binary);
            isCrash << 0;
            isCrash.close();
            isCrash.open("Temp", ios_base::trunc | ios_base::out | ios_base::binary);
            isCrash.close();
            isCrash.open("RecoverySessions", ios_base::trunc | ios_base::out | ios_base::binary);
            isCrash.close();
        }
        else {
            isCrash.open("RecoveryStudent", ios_base::out | ios_base::app | ios_base::binary);
            isCrash << "Temp:";
            isCrash.close();
        }
    }
    int Crash() {
        fstream isCrash;
        int iC;
        isCrash.open("isCrash", ios_base::app | ios_base::binary);
        isCrash << 0;
        isCrash.close();
        isCrash.open("isCrash", ios_base::in | ios_base::binary);
        isCrash >> iC;
        isCrash.close();
        if (iC) {
            cout << "В ходе предыдущего сеанса работа произошла ошибка. Восстановить данные?\nY - да\tN - нет\n> ";
            if (Which('Y', 'N')) {
                cout << "Восстановление...\n\n";
                cout << endl << endl;
                Scan();
            }
            else {
                Trash(1); iC = 0;
            }
        }
        else Trash(1);
        return iC;
    }
    void Encrypt() {
        Crypto* EN = new Crypto;
        if (EN == nullptr) {
            cout << "Ошибка при шифровании файла\n";
            return;
        }
        if (EN->Encrypt()) {
            cout << "В процессе шифрования произошла ошибка\n";
        }
        else
        {
            cout << "Документ зашифрован. Не забудьте при следующем открытии указать документ " <<
                fPath << ", чтобы расшифровать файл" << endl;
            strcpy_s(fPath, "Temp\0");
        }
        delete EN;
    }
    int Decrypt() {
        Crypto* DN = new Crypto;
        if (DN == nullptr) {
            cout << "Ошибка при дешифровании файла\n";
            return 1;
        }
        if (DN->Check()) {
            if (DN->Decrypt()) {
                cout << "Пароль неверен\n";
                delete DN;
                return 1;
            }
            else {
                Stud* T = new Stud;
                fstream N, NewFile;
                N.open("Tmp", ios_base::trunc | ios_base::out | ios_base::binary);
                NewFile.open(fPath, ios_base::in | ios_base::binary);
                while (!NewFile.eof()) {
                    NewFile >> *T;
                    if (T->isOK) N << *T; else break;
                }
                N.close();
                NewFile.close();
                Teleport("Tmp", fPath);
                delete T;
            }
        }
        delete DN;
        return 2;
    }
    void Update() {
        if (!strcmp(newPath, "Tmp") ||
            !strcmp(newPath, "RecoveryStudent") ||
            !strcmp(newPath, "RecoverySessions")) {
            cout << "Это имя файла недопустимо\n";
            return;
        }
        ofstream NewFile;
        Teleport(fPath, newPath);
        strcpy_s(fPath, newPath);
        NewFile.open("isCrash", ios_base::trunc | ios_base::binary);
        NewFile << 0;
        NewFile.close();

    }
    void addStud() {
        Data* I = new Student(1);
        if (I == nullptr) {
            cout << "Ошибка при добавлении студента\n";
            return;
        }
        Set(I);
        delete I;
        I = new Sessions(1);
        if (I == nullptr) {
            cout << "Ошибка при добавлении студента\n";
            return;
        }
        Set(I);
        delete I;
        SumFile("RecoveryStudent", "RecoverySessions", fPath);
        Trash(strcmp(fPath, "Temp"));
    }
    void delStud(int c) {
        if ((c > 0) && (c <= counter)) {
            Student* D = new Student(c);
            if (D == nullptr) {
                cout << "Ошибка при удалении студента\n";
                return;
            }
            D->Erase();
            delete D;
        }
        else cout << "Нет студента с номером " << c << endl;
    };
    void Scan() {
        Data* S;
        int q = Recovery();
        if (q == 11) S = new Sessions(q); else S = new Student(q);
        if (S == nullptr) {
            cout << "Ошибка при добавлении студента\n";
            return;
        }
        Load(S);
        Set(S);
        if ((q != 11) && (q)) {
            delete S;
            S = new Sessions(0);
            if (S == nullptr) {
                cout << "Произошла ошибка\n";
                return;
            }
            Set(S);
        }
        delete S;
        SumFile("RecoveryStudent", "RecoverySessions", fPath);
        Trash(strcmp(fPath, "Temp"));
    };
    void printStud(int a) {
        Student* P = new Student(a);
        if (P == nullptr) {
            cout << "Ошибка при выводе студента\n";
            return;
        }
        P->Print();
        delete P;
    };
    void BubbleSort(int a, int b) {
        int cntSor = 0;
        fstream Read;
        fstream Sort;
        Stud* A = new Stud;
        Stud* B = new Stud;
        if ((A == nullptr) || (B == nullptr)) {
            cout << "Ошибка при сортировке студентов\n";
            return;
        }
        Read.open(fPath, ios_base::in | ios_base::binary);
        Sort.open("Sort", ios_base::trunc | ios_base::out | ios_base::binary);
        Read.seekg(0, ios::beg);
        while (!Read.eof()) {
            Read >> *A;
            if (A->isOK) {
                if ((*A >= a) && (*A <= b)) { Sort << *A; cntSor++; }
            }
        }
        Read.close();
        Sort.close();
        Read.open("Sort", ios_base::in | ios_base::out | ios_base::binary);
        int rSt = 0, flag = 1;
        while (flag) {
            Read.seekg(0, ios::beg);
            flag = 0;
            for (int i = 1; i < cntSor; i++) {
                rSt = Read.tellg();
                Read >> *A;
                Read >> *B;
                if (*A > * B) { swap(*A, *B); flag = 1; }
                Read.seekg(rSt, ios::beg);
                Read << *A;
                rSt = Read.tellg();
                Read << *B;
                Read.seekg(rSt, ios::beg);
            }
        }
        Read.close();
        strcpy_s(newPath, fPath);
        strcpy_s(fPath, "Sort");
        Student* P = new Student(0);
        P->Print();
        strcpy_s(fPath, newPath);
        delete A;
        delete B;
    }
    void Sum() {
        if (strcmp(fPath, "Temp")) {
            fstream OldFile;
            fstream NewFile;
            NewFile.open(newPath, ios_base::in | ios_base::binary);
            OldFile.open(fPath, ios_base::app | ios_base::binary);
            Stud A;
            int j = 1;
            while (!NewFile.eof()) {
                NewFile >> A;
                if (A.isOK) {
                    OldFile << A;
                }
            }
            OldFile.close();
            NewFile.close();
        }
        else Update();
    }
    int Find(char c[]) {
        Stud Test;
        fstream Read;
        int flag = 1;
        Read.open(fPath, ios_base::in | ios_base::binary);
        while (!Read.eof()) {
            Read >> Test;
            if (Test.isOK) {
                if (!strcmp(Test.zach, c)) { Read.close(); return flag; }
            }
            else break;
            flag++;
        }
        Read.close();
        return 0;
    }
    void EditStud(int a) {
        Data* E;
        cout << "Какой пункт вы хотите отредактировать?\n> ";
        Enter(eint);
        if (eint == 11) E = new Sessions(a); else E = new Student(a);
        if (E == nullptr) {
            cout << "Ошибка при редактировании студента\n";
            return;
        }
        cout << "Пункт " << eint << " > ";
        Edit(E);
    }
    int Hub() {
        if (!Crash()) {
            cout << "\nДля работы программы нужна база данных студентов. Откуда её взять?\nF - из файла\tI - ввести\n> ";
            if (Which('I', 'F')) {
                do {
                    addStud();
                    cout << "\nA - добавить ещё\tS - закончить ввод студентов\n> ";
                } while (Which('A', 'S'));
                return 2;
            }
            else {
                cout << "Введите путь к файлу (или название, если он в папке с проектом)\n > ";
                if (EnterFile(fPath, 0)) {
                    return Decrypt();
                }
                else return 1;
            }
        }
        else return 2;
    }
    int WhatToDo() {
        printStud(0);
        if (strcmp(fPath, "Temp"))
            cout << "\nТаблица сохраняется в файл " << fPath << endl << endl;
        cout << endl;
        cout << "\nЧто вы хотите делать далее?\n\nВведите число от 1 до " << counter << " или номер зач. книжки, чтобы просмотреть информацию о студенте\n";
        cout << "A - добавить       E - редактировать\nD - удалить        F - сохранить в файл\nS - сортировать    U - объединить с...\nC - зашифровать    Q - выйти\n > ";
        Enter(str, 19);
        ent = str[0];
        cout << endl;
        switch (ent) {
        case 'd': case 'D':
            cout << "Введите номер студента, которого необходимо удалить.\n| ВНИМАНИЕ\n| Это действие невозможно будет отменить!\n > ";
            Enter(eint);
            delStud(eint);
            break;
        case 'e': case 'E':
            cout << "Введите номер студента, данные о котором необходимо отредактировать.\n > ";
            Enter(eint);
            if ((eint > 0) && ((eint <= counter))) {
                printStud(eint);
                EditStud(eint);
            }
            else cout << "Студента с таким номером нет";
            break;
        case 'f': case 'F':
            cout << "Введите путь (или название, если сохранить в папке с проектом)\n > ";
            if (EnterFile(newPath, 1)) {
                Update();
            }
            break;
        case 's': case 'S':
            cout << "Введите интервал года рождения, в пределах которого сортировать\nПишите в формате 1990-2005\n > ";
            Enter(sS, sF);
            cout << "Сортируем на " << sS << "-" << sF << endl;;
            BubbleSort(sS, sF);
            break;
        case 'u': case 'U':
            cout << "Введите название/путь файла, с которым нужно объединить текущую базу\n > ";
            if (EnterFile(newPath, 0)) {
                Sum();
            }
            break;
        case 'c': case 'C':
            Encrypt();
            return 1;
            break;
        case 'a': case 'A':
            addStud();
            break;
        case 'q': case 'Q': return 0; break;
        default:
            if (Find(str)) {
                printStud(Find(str));
            }
            else if ((CharToInt(str) > 0) && ((CharToInt(str) <= counter))) {
                printStud(CharToInt(str));
            }
            else cout << "Студента с таким номером/зачётной книжкой нет";
        }
        cout << "\n_______________________________________________\n";
        return 2;
    }
};


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "Курсовая работа. Вариант 79.\nСортировка студентов по увеличению года поступления в вуз\n\n";
    Control* TheMain = new Control;
    if (TheMain == nullptr) {
        cout << "Невозможно выделить память для работы программы\n";
        return 1;
    }
    delete TheMain;
    return 0;
}