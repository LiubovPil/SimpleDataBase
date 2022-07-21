// Final assignment for the course "Fundamentals of C++: White Belt"
// Done by Liubov Piliagina

#include <iomanip>
#include <iostream>
#include <cstdio>
#include <string>
#include <set>
#include <map>

using namespace std;

struct Year {
public:
    int year_value;
    explicit Year(int new_year_value) {
        year_value = new_year_value;
    }
};

struct Month {
public:
    int month_value;
    explicit Month(int new_month_value) {
        month_value = new_month_value;
    }
};

struct Day {
public:
    int day_value;
    explicit Day(int new_day_value) {
        day_value = new_day_value;
    }
};

class Date {
public:
    Date(Year new_year, Month new_month, Day new_day) {
        year = new_year.year_value;
        month = new_month.month_value;
        day = new_day.day_value;
    }
    int GetYear() const {
        return year;
    };
    int GetMonth() const {
        return month;
    };
    int GetDay() const {
        return day;
    };

private:
    int year;
    int month;
    int day;
};

class Database {
public:
    Database() {}
    Database(Date& date, string& event) {
        AddEvent(date, event);
    }

    void AddEvent(const Date& date, const string& event) {
        if (!event.empty())
            database[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event) {
        if (database.count(date) == 1 && database.at(date).count(event) == 1 ) {
            if (database.at(date).size() > 1) {
                database.at(date).erase(event);
            }
            else {
                database.erase(date);
            }
            cout << "Deleted successfully" << endl;
            return true;
        }
        cout << "Event not found" << endl;
        return false;
    }
    int  DeleteDate(const Date& date) {
        int num_events = 0;
        if (database.count(date) > 0) {
            num_events = database.at(date).size();
            database.erase(date);
        }
        cout << "Delete " << num_events << " events" << endl;
        return num_events;
    }
    //redo - function find must return set
    void Find(const Date& date) const {
        if (database.count(date) == 1) {
            for (const auto& event : database.at(date)) {
                cout << event << endl;
            }
        }
    }

    void Print() const {
        cout << setfill('0');
        for (const auto& db : database){
            // next line, after GetDay it is necessary to print ostream from Find
            for (const auto& event : db.second) {
                cout << setw(4) << db.first.GetYear() << "-" << setw(2)
                    << db.first.GetMonth() << "-" << setw(2)
                    << db.first.GetDay() << "-" << event << endl;
            }
        }
    }
private:
    map<Date, set<string>> database;
};

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        }
        return lhs.GetMonth() < rhs.GetMonth();
    }
    return lhs.GetYear() < rhs.GetYear();
};

/*bool operator>(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() > rhs.GetDay();
        }
        return lhs.GetMonth() > rhs.GetMonth();
    }
    return lhs.GetYear() > rhs.GetYear();
}*/
ostream& operator<<(ostream& out, Database& db) {
    return out;
};

int main()
{
    Database db;

    string command;
    while (getline(cin, command)) {
        //Считайте команды с потока ввода и обработайте каждую
    }

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
