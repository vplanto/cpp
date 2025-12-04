/* Тестування структури Person (TestStructPerson.cpp) */
#include <iostream>
#include <string>
using namespace std;
 
// Структура може містити поля різних типів, включно з об'єктами класів
struct Person {
   string name;    // Поле типу string
   int age;        // Поле типу int
   double height;  // Поле типу double
   double weight;  // Поле типу double
};
 
int main() {
   // Ініціалізація структури списком значень (порядок відповідає порядку оголошення полів)
   Person peter = {"Peter Jone", 18, 180.5, 70.5};
   // Доступ до полів через оператор . (крапка)
   cout << "Name: " << peter.name << endl;
   cout << "Age: " << peter.age << endl;
   cout << "Height: " << peter.height << endl;
   cout << "weight: " << peter.weight << endl;
   return 0;
}
