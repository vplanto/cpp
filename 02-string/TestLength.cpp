#include <iostream>
#include <string>

// Цей файл .cpp має бути збережено у кодуванні UTF-8
// (це стандарт для більшості сучасних редакторів коду)

int main() {
    // Використовуємо std::, щоб не писати "using namespace std;"
    
    // 6 символів кирилиці
    std::string str = "Привіт"; 

    std::cout << "Рядок: " << str << std::endl;

    // --- Перевірка ---
    // У кодуванні UTF-8 кожен символ кирилиці займає 2 байти.
    // 6 символів * 2 байти/символ = 12 байт.
    // 
    // std::string::length() та std::string::size() 
    // повертають кількість байт (кількість об'єктів char),
    // а не кількість "людських" символів.

    std::cout << "str.length(): " << str.length() << std::endl;
    std::cout << "str.size():   " << str.size() << std::endl;

    // Для порівняння, рядок з 6 символів ASCII
    std::string str_ascii = "Hello";
    std::cout << "\nРядок ASCII: " << str_ascii << std::endl;
    std::cout << "str_ascii.length(): " << str_ascii.length() << std::endl; // Виведе 5
    
    str[0] = 'h';
    std::cout << "Змінений рядок: ";
    std::cout << str << std::endl;

    return 0;
}
