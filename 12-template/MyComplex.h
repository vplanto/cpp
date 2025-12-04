/*
 * Заголовочний файл шаблону класу MyComplex (MyComplex.h)
 * Весь код шаблону зберігається в заголовочному файлі для включення в програму
 * (За основу взято та спрощено шаблон класу complex з GNU GCC.)
 */
#ifndef MY_COMPLEX_H
#define MY_COMPLEX_H

#include <iostream>

// Попереднє оголошення
template <typename T>
class MyComplex;

// Попереднє оголошення friend функцій
template <typename T>
std::ostream &operator<<(std::ostream &out, const MyComplex<T> &c);
template <typename T>
std::istream &operator>>(std::istream &in, MyComplex<T> &c);

// Оголошення шаблону класу MyComplex
template <typename T>
class MyComplex {
 private:
  T real, imag;  // Дійсна та уявна частини комплексного числа

 public:
  // Конструктор
  // explicit - забороняє неявне перетворення типів
  // Використовується для конструкторів, що можуть бути викликані з одним аргументом
  explicit MyComplex<T>(T real = 0, T imag = 0) : real(real), imag(imag) {}

  // Перевантаження оператора += для c1 += c2
  MyComplex<T> &operator+=(const MyComplex<T> &rhs) {
    real += rhs.real;
    imag += rhs.imag;
    return *this;  // Повертаємо посилання на поточний об'єкт
  }

  // Перевантаження оператора += для c1 += value
  MyComplex<T> &operator+=(T value) {
    real += value;
    return *this;
  }

  // Перевантаження оператора порівняння == для c1 == c2
  bool operator==(const MyComplex<T> &rhs) const {
    return (real == rhs.real && imag == rhs.imag);
  }

  // Перевантаження оператора порівняння != для c1 != c2
  bool operator!=(const MyComplex<T> &rhs) const { return !(*this == rhs); }

  // Перевантаження префіксного інкременту ++c
  MyComplex<T> &operator++();

  // Перевантаження постфіксного інкременту c++
  // int dummy - параметр для розрізнення префіксного та постфіксного інкременту
  const MyComplex<T> operator++(int dummy);

  /* friend функції */

  // friend функції мають доступ до private членів
  // <> - вказівка, що це шаблон функції
  friend std::ostream &operator<< <>(std::ostream &out,
                                     const MyComplex<T> &c);  // out << c
  friend std::istream &operator>>
      <>(std::istream &in, MyComplex<T> &c);  // in >> c

  // Перевантаження оператора + для c1 + c2
  // inline реалізація (в заголовочному файлі)
  friend const MyComplex<T> operator+(const MyComplex<T> &lhs,
                                      const MyComplex<T> &rhs) {
    MyComplex<T> result(lhs);
    result += rhs;  // Використовує перевантажений +=
    return result;
  }

  // Перевантаження оператора + для c + double
  friend const MyComplex<T> operator+(const MyComplex<T> &lhs, T value) {
    MyComplex<T> result(lhs);
    result += value;  // Використовує перевантажений +=
    return result;
  }

  // Перевантаження оператора + для double + c
  friend const MyComplex<T> operator+(T value, const MyComplex<T> &rhs) {
    return rhs + value;  // Обмін місцями та використання вищевказаної функції
  }
};

// Визначення префіксного інкременту
template <typename T>
MyComplex<T> &MyComplex<T>::operator++() {
  ++real;  // Інкремент тільки дійсної частини
  return *this;
}

// Визначення постфіксного інкременту
template <typename T>
const MyComplex<T> MyComplex<T>::operator++(int dummy) {
  MyComplex<T> saved(*this);  // Зберігаємо поточне значення
  ++real;  // Інкрементуємо дійсну частину
  return saved;  // Повертаємо старе значення
}

/* Визначення friend функцій */

// Перевантаження оператора виводу out << c (friend)
template <typename T>
std::ostream &operator<<(std::ostream &out, const MyComplex<T> &c) {
  out << '(' << c.real << ',' << c.imag << ')';
  return out;
}

// Перевантаження оператора вводу in >> c (friend)
template <typename T>
std::istream &operator>>(std::istream &in, MyComplex<T> &c) {
  T inReal, inImag;
  char inChar;
  bool validInput = false;
  // Ввід має бути у форматі "(real,imag)"
  in >> inChar;
  if (inChar == '(') {
    in >> inReal >> inChar;
    if (inChar == ',') {
      in >> inImag >> inChar;
      if (inChar == ')') {
        c = MyComplex<T>(inReal, inImag);
        validInput = true;
      }
    }
  }
  if (!validInput) in.setstate(std::ios_base::failbit);  // Встановлення прапорця помилки
  return in;
}

#endif
