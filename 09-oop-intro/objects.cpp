#include <iostream>
#include <sstream>
#include <string>

// Демонстрація перевантаження конструкторів та композиції
class Date {
 private:
  int day;
  int month;
  int year;

 public:
  // Конструктор з параметрами за замовчуванням
  Date(int d = 01, int m = 01, int y = 1970) : day(d), month(m), year(y) {}

  // Конструктор з рядком формату "dd/mm/yyyy" (nonce - параметр для розрізнення)
  Date(const std::string &date, bool nonce) {
    std::stringstream ss(date);  // stringstream для парсингу
    char delim;
    ss >> day >> delim >> month >> delim >> year;
  }

  // Конструктор з трьома окремими рядками
  Date(const std::string &d, const std::string &m, const std::string &y) {
    day = std::stoi(d);    // stoi - перетворення string в int
    month = std::stoi(m);
    year = std::stoi(y);
  }

  // Конструктор з одним рядком формату "ddmmyyyy"
  Date(const std::string &date) {
    if (date.length() == 8) {
      day = std::stoi(date.substr(0, 2));      // substr(0, 2) - перші 2 символи
      month = std::stoi(date.substr(2, 2));     // substr(2, 2) - символи 2-3
      year = std::stoi(date.substr(4, 4));      // substr(4, 4) - символи 4-7
    }
  }

  ~Date() { std::cout << "Destructor called!" << std::endl; }
};

// Композиція: Person містить об'єкт Date як член
class Person {
 private:
  std::string name;
  Date birthdate;  // Композиція - об'єкт Date як частина Person

 public:
  // Список ініціалізації: name(n), birthdate(bd) - виклик конструктора Date
  Person(std::string n, Date bd) : name(n), birthdate(bd) {}
};

int main() {
  // Різні способи створення об'єктів Date через перевантаження конструкторів
  Date birthdate0(1, 1, 2000);           // Конструктор з int параметрами
  Date birthdate1(4, 5);                 // Використання значень за замовчуванням
  Date birthdate2("01/01/2000");          // Конструктор з одним рядком
  Date birthdate3("01", "01", "2000");    // Конструктор з трьома рядками
  Date birthdate4("01012000");            // Конструктор з форматом "ddmmyyyy"

  Person person1("John Doe", birthdate1);
  Person person2("Jane Doe", birthdate2);
  Person person3("Jim Doe", birthdate3);
  Person person4("Jill Doe", birthdate4);

  // Примітка: деструктори викликаються автоматично при виході з області видимості
  // (для автоматичних об'єктів, не для динамічно виділених)
}
