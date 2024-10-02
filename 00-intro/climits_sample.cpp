/* Test integer limits in <climits> header */
#include <iostream>
#include <climits>   // integer limits
using namespace std;
 
int main() {
   cout << "int max = " << INT_MAX << endl;
   cout << "int min = " << INT_MIN << endl;
   cout << "unsigned int max = " << UINT_MAX << endl;
   cout << "long long max = " << LLONG_MAX << endl;
   cout << "long long min = " << LLONG_MIN << endl;
   cout << "unsigned long long max = " << ULLONG_MAX << endl;
   cout << "Bits in char = " << CHAR_BIT << endl;
   cout << "char max = " << CHAR_MAX << endl;
   cout << "char min = " << CHAR_MIN << endl;
   cout << "signed char max = " << SCHAR_MAX << endl;
   cout << "signed char min = " << SCHAR_MIN << endl;
   cout << "unsigned char max = " << UCHAR_MAX << endl;
   return 0;
}
