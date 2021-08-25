#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class PhoneBook {
public:
    string* name;
    string* lines;

    PhoneBook() {};
    PhoneBook(string nm, string ln) {
        this->name = name;
        this->lines = lines;
    }

    void InputData(string name, string phone)
    {
        fstream _name;
        cout << "Enter Surname, Name and Phone  (ex. Ivanov Ivan 123456): ";
        getline(cin, name);
        _name.open("names.txt", ios::app);
        if (!_name.is_open()) perror("Error: ");
        else _name << "\n" << name;
        _name.close();
    }

    int FindByName(string text) {
        ifstream _name;
        string word, line;
        _name.open("names.txt");
        if (!_name.is_open()) exit(EXIT_FAILURE);
        cout << "Enter a surname or phone: (to Find || Change || Delete)"; cin >> word;
        int number_of_lines = 0;
        while (getline(_name, line))
        {
            number_of_lines += 1;
            if ((line.find(word) != string::npos) && (line.find(word) != (-1)))
            {
                cout << "Surname and phone -> " << line <<  endl;
                cout << "Data in line " << number_of_lines << endl;
                return number_of_lines;
            }
        }
        cout << "No surnames finded " << word << endl;
        _name.close();
        return number_of_lines;
    }

    void ShowData(string text) {
        string getcontent;
        ifstream openfile("names.txt");
        if (openfile.is_open())
        {
            while (getline(openfile, getcontent))
            {
                cout << getcontent << endl;
            }
        }
        cout << endl;
    }

    int ShowAbonents(string filename)    {
        lines = new string[20];
        ifstream F(filename, ios::in);
        if (!F) return -1;
        int count = 0;
        char buffer[1000];
        while (!F.eof())
        {
            F.getline(buffer, 1000);
            int len;
            for (len = 0; buffer[len] != '\0'; len++);
            lines[count].assign(buffer, len);
            count++;
        }
        F.close();

        for (int i = 0; i <= count; i++) cout <<i << " "<< lines[i] << endl;
        
        return count;
    }
      
    int ChangeAbonentData(string filename)    {
        int count, position; 
        string text, str;
        count = ShowAbonents(filename);
        position = FindByName(text);
        ofstream F(filename); 
        if (!F.is_open()) return -1;
        for (int i = 0; i < position - 1; i++) F << lines[i] << endl; 
        cout << "Enter NEW Surname, Name and Phone  (ex. Ivanov Ivan 123456): \n" << endl;
        cin.ignore();
        getline(cin, str);
        F << str << endl; 
        for (int i = position; i < count - 1; i++) F << lines[i] << endl;
        F << lines[count - 1];
        F.close();
        delete[] lines;
        return 0;
    }

    int DeleteAbonent(string filename)    {
        int count, position;
        string text, str;
        count = ShowAbonents(filename);
        position = FindByName(text);
        ofstream F(filename);
        if (!F.is_open()) return -1;
        for (int i = 0; i < position - 1; i++) F << lines[i] << endl;
        for (int i = position; i < count - 1; i++) F << lines[i] << endl;
        F << lines[count - 1];
        F.close();
        delete[] lines;
        return 0;
    }

    int sortAbonents(string filename)
    {
        int count, position;
        string text, str;
        count = ShowAbonents(filename);
        //position = FindByName(text);
        ofstream F(filename);
        if (!F.is_open()) return -1;
        for (int i = 0; i < count - 1; i++)
            for (int j = i; j >= 0; j--)
                if (lines[j] > lines[j + 1])
                {
                    str = lines[j];
                    lines[j] = lines[j + 1];
                    lines[j + 1] = str;
                }
        for (int i = 0; i < count - 1; i++) F << lines[i] << endl;
        F << lines[count - 1];
        F.close();
        cout << "Данные отсортированы. Нажмите 3, чтоб проверить )\n\n";
    }
};

int main()
{
    string name, phone, line;
    setlocale(LC_ALL, "");
    int key;
    PhoneBook abonent;

    for (;;)
    {
        cout << "Выберите пункт меню\n\n";
        cout << "##################################\n";
        cout << "1. Добавление абонента в базу\n";
        cout << "2. Поиск абонента\n";
        cout << "3. Показать всех абонентов\n";
        cout << "4. Изменение данных абонента\n";
        cout << "5. Удаление данных абонента\n";
        cout << "6. Сортировка данных\n";
        cout << "7. Выход из программы\n";
        cout << "##################################\n";

        (cin >> key).get();
        if (key < 7 && key > 0)
        {
            switch (key)
            {
            case 1:
                abonent.InputData(name, phone);
                break;
            case 2:
                abonent.FindByName(name);
                break;
            case 3:
                abonent.ShowAbonents("names.txt");
                break;
            case 4:
                abonent.ChangeAbonentData("names.txt");
                break;
            case 5:
                abonent.DeleteAbonent("names.txt");
                break;
            case 6:
                abonent.sortAbonents("names.txt");
                break;
            case 7:
                exit;
            }
        }
        else if (key <= 0 || key > 7) cout << "Ошибка ввода\n\n";
        else break;
    }
    return 0;
}


//void ChangingAbonent()
//{
//    size_t fwrite(const void* buffer, size_t size, size_t count, FILE * stream);  //записывает массив данных в файл.
//}
//
//void DeleteAbonent()
//{
//    size_t fread(void* buffer, size_t size, size_t count, FILE * stream);    //считывает данные из файла в буфер
//    FILE* fopen(const char* filename, const char* mode); //Функция открывает файл.
//    int fclose(FILE * stream); //Функция закрывает файл.
//    char* fgets(char* string, int n, FILE * stream);  //Считывает строку начиная с текущей позиции
//    int fputs(const char* string, FILE * stream);  //Записывает строку в файл, начиная с текущей позиции.
//}


