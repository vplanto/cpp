#include <iostream>
#include <sstream>
#include <string>

class Date {
 private:
  int day;
  int month;
  int year;

 public:
  // Constructor accepting day, month, and year as integers
  Date(int d = 01, int m = 01, int y = 1970) : day(d), month(m), year(y) {}

  // Constructor accepting date as a string in the format "dd/mm/yyyy"
  Date(const std::string &date, bool nonce) {
    std::stringstream ss(date);
    char delim;
    ss >> day >> delim >> month >> delim >> year;
  }

  // Constructor accepting date as three separate strings
  Date(const std::string &d, const std::string &m, const std::string &y) {
    day = std::stoi(d);
    month = std::stoi(m);
    year = std::stoi(y);
  }

  // Constructor accepting date as a single string in the format "ddmmyyyy"
  Date(const std::string &date) {
    if (date.length() == 8) {
      day = std::stoi(date.substr(0, 2));
      month = std::stoi(date.substr(2, 2));
      year = std::stoi(date.substr(4, 4));
    }
  }

  ~Date() { std::cout << "Destructor called!" << std::endl; }
};

class Person {
 private:
  std::string name;
  Date birthdate;

 public:
  Person(std::string n, Date bd) : name(n), birthdate(bd) {}
};

int main() {
  Date birthdate0(1, 1, 2000);
  Date birthdate1(4, 5);
  Date birthdate2("01/01/2000");
  Date birthdate3("01", "01", "2000");
  Date birthdate4("01012000");

  Person person1("John Doe", birthdate1);
  Person person2("Jane Doe", birthdate2);
  Person person3("Jim Doe", birthdate3);
  Person person4("Jill Doe", birthdate4);

  // Forgot to call delete, so the destructor is never called and memory is
  // leaked.
}
