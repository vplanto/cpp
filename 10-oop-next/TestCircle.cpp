class ClassA {
  friend class ClassB;  // ClassB is a friend class of ClassA
 protected:
  int protectedVar;
};

class ClassB {
 public:
  void modifyProtectedVar(ClassA &obj) {
    obj.protectedVar = 5;  // This is fine, ClassB is a friend of ClassA
  }
};

int main() {
  ClassA objA;
  ClassB objB;
  objB.modifyProtectedVar(
      objA);  // This is fine, modifyProtectedVar is a member of ClassB
  return 0;
}
