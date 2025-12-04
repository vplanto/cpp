// Демонстрація friend класу
class ClassA {
  friend class ClassB;  // ClassB - friend клас ClassA (має доступ до private/protected членів)
 protected:
  int protectedVar;  // protected член доступний friend класу
};

class ClassB {
 public:
  void modifyProtectedVar(ClassA &obj) {
    // ClassB має доступ до protected членів ClassA, бо є friend класом
    obj.protectedVar = 5;
  }
};

int main() {
  ClassA objA;
  ClassB objB;
  objB.modifyProtectedVar(objA);  // Виклик методу friend класу
  return 0;
}
