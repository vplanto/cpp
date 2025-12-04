// Демонстрація friend функції
class MyClass {
 private:
  int myPrivateVar;

 public:
  MyClass() : myPrivateVar(0) {}

  // Оголошення friend функції (не є методом класу, але має доступ до private членів)
  friend void modifyPrivateVar(MyClass &);
};

// Визначення friend функції
void modifyPrivateVar(MyClass &obj) {
  // Доступ до приватного члена з friend функції
  obj.myPrivateVar = 5;
}

int main() {
  MyClass obj;
  modifyPrivateVar(obj);  // Виклик friend функції
  return 0;
}
