// Final assignment for the course "Fundamentals of C++: White Belt"
// Done by Liubov Piliagina

#include <cstdint>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <stdexcept>
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
        if (new_month.month_value > 12 || new_month.month_value < 1) {
            throw logic_error("Month value is invalid: " + to_string(new_month.month_value));
        }
        month = new_month.month_value;
        if (new_day.day_value > 31 || new_day.day_value < 1) {
            throw logic_error("Day value is invalid: " + to_string(new_day.day_value));
        }
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

bool operator < (const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        }
        return lhs.GetMonth() < rhs.GetMonth();
    }
    return lhs.GetYear() < rhs.GetYear();
};

ostream& operator << (ostream& out, const Date& date) {
    out << setw(4) << setfill('0') << date.GetYear() << "-" <<
        setw(2) << setfill('0') << date.GetMonth() << "-" <<
        setw(2) << setfill('0') << date.GetDay();
    return out;
}

class Database {
public:
    Database() {}
    Database(Date& date, string& event) {
        AddEvent(date, event);  //this constructor can be removed
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
    //function can return set
    void Find(const Date& date) const {
        if (database.count(date) == 1) {
            for (const auto& event : database.at(date)) {
                cout << event << endl;   //return database.at(date); return {};
            }
        }
    }

    void Print() const {
        for (const auto& date_events : database){
            for (const auto& event : date_events.second) {
                cout << date_events.first << ": " << event << endl;
            }
        }
    }
private:
    map<Date, set<string>> database;
};

void DetermineNextSymbolAndSkip(stringstream& ss, const string& date_str) {
    if (ss.peek() != '-') {
        throw logic_error("Invalid date format!" + date_str);
    }
    ss.ignore(1);
}
Date ParseDate(const string& date_str) {
    int year = 0, month = 0, day = 0;

    stringstream ss(date_str);
    ss >> year;
    DetermineNextSymbolAndSkip(ss, date_str);

    ss >> month;
    DetermineNextSymbolAndSkip(ss, date_str);

    ss >> day;
    if (!ss.eof()) {
        throw logic_error("Invalid date format!" + date_str);
    }

    return { Year{year}, Month{month}, Day{day} };
}

int main()
{
    try {
        Database db;

        string command_line;
        while (getline(cin, command_line)) {
            stringstream ss(command_line);
        
            string command;
            ss >> command;
            if (command == "Add") {
                string date_str, event;
                ss >> date_str >> event;

                const Date date = ParseDate(date_str);

                db.AddEvent(date, event);
            }
            else if (command == "Del") {
                string date_str, event;
                ss >> date_str;

                if (!ss.eof()) {
                    ss >> event;
                }

                const Date date = ParseDate(date_str);

                if (!event.empty()) {
                    db.DeleteEvent(date, event);
                }
                else {
                    db.DeleteDate(date);
                }
            }
            else if ( command == "Find") {
                string date_str;
                ss >> date_str;

                const Date date = ParseDate(date_str);

                db.Find(date);
            }
            else if (command == "Print") {
                db.Print();
            }
            else if (command.empty()) {
                break;
            }
            else {
                throw logic_error("Unknown command: " + command);
            }
        }
    }
    catch (const exception& error) {
        cout << error.what() << endl;
    }
    return 0;
}
