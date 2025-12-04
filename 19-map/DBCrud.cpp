#include <iostream>
#include <map>      // std::map - асоціативний контейнер
#include <string>

struct Student {
  std::string name;   // Ім'я студента
  int age;            // Вік студента
  std::string course; // Курс студента
};

// map для імітації бази даних з цілочисельними ключами (ID) та значеннями Student
// std::map автоматично сортує ключі за зростанням
std::map<int, Student> DB;

// Функція перевірки існування студента з заданим ID
// find() повертає ітератор до елемента або end(), якщо не знайдено
// Складність: O(log n)
bool exists(int id) {
  return DB.find(id) != DB.end();
}

// Функція створення нового студента в БД
int create(
    const std::string &name, int age,
    const std::string &course) {
  int id = DB.size() + 1; // Генерація ID на основі поточного розміру БД
  DB[id] = {name, age, course}; // Додавання нового студента в БД
  return id;                    // Повернення ID новоствореного запису
}

// Функція читання та виведення деталей студента з БД
void read(int id) {
  if (exists(id)) {
    std::cout << "ID: " << id << ", Name: " << DB[id].name
              << ", Age: " << DB[id].age << ", Course: " << DB[id].course
              << std::endl;
  } else {
    std::cout << "Student with ID: " << id << " not found." << std::endl;
  }
}

// Функція оновлення деталей студента в БД
void update(int id, const std::string &name, int age,
            const std::string &course) {
  if (exists(id)) {
    DB[id] = {name, age, course}; // Оновлення деталей студента в БД
  } else {
    std::cout << "Student with ID: " << id << " not found." << std::endl;
  }
}

// Функція видалення студента з БД
// erase() видаляє елемент за ключем
// Складність: O(log n)
void remove(int id) {
  if (exists(id)) {
    DB.erase(id);     // Видалення студента з БД
  } else {
    std::cout << "Student with ID: " << id << " not found." << std::endl;
  }
}

// Функція пошуку студента за ім'ям та повернення його ID
// НЕЕФЕКТИВНО: O(n) - лінійний пошук по всіх елементах
// Краще використовувати додатковий map<string, int> для інвертованого індексу
int find(const std::string &name) {
  for (const auto &pair : DB) { // Прохід по всіх елементах БД
    if (pair.second.name == name) { // Якщо ім'я поточного студента співпадає
      return pair.first; // Повернення ID студента
    }
  }
  return -1; // Якщо студент з заданим ім'ям не знайдено, повертаємо -1
}

int main() { // Main function
  int id1 =
      create("John Doe", 20, "Computer Science"); // Add a new student to the DB
  int id2 =
      create("Jane Doe", 22,
             "Electrical Engineering"); // Add another new student to the DB

  read(id1); // Retrieve and display the first student's details
  read(id2); // Retrieve and display the second student's details

  update(id1, "John Doe", 21,
         "Computer Science"); // Update the first student's details

  remove(id2); // Remove the second student from the DB

  int foundId = find("John Doe"); // Find a student by name and get their ID
  if (foundId != -1) {            // If the student was found
    std::cout << "Found student with ID: " << foundId << std::endl;
  } else { // If the student was not found
    std::cout << "Student not found." << std::endl;
  }

  return 0; // End the program
}
