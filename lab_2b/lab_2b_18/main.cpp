#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>

#include "polynomial.h"

using std::string;

template <class T>
T Read(bool interactive, std::ifstream& in, T& t) {
    if (interactive) {
        std::cin >> t;
        return t;
    }
    in >> t;
    return t;
}

Polynomial ReadPol(bool interactive, std::ifstream& in) {
    //std::cout << "STaRT" << std::endl;
    Polynomial res;
    int length = Read(interactive, in, length);
    for (int i = 0; i < length; ++i) {
        int degree = Read(interactive, in, degree);
        double coef = Read(interactive, in, coef);
        res.Add(degree, coef);
    }
    //std::cout << "FINISH" << std::endl;
    return res;
}


int main() {
   string operation, type;
   bool interactive = true;
   std::ifstream in(".../lab_2b_18.txt");

   std::cin >> type;
   if (type == "Demo") {
       interactive = false;
   }

   while (true) {
       Polynomial lhs = ReadPol(interactive, in);
       char c = Read(interactive, in, c);
       Polynomial rhs = ReadPol(interactive, in);

       Polynomial res1, res2;
       if (c == '+') {
           res1 = lhs + rhs;
           res1.Print();
           std::cout << std::endl;
       }
       if (c == '-') {
           res1 = lhs - rhs;
           res1.Print();
           std::cout << std::endl;
       }
       if (c == '*') {
           res1 = lhs * rhs;
           res1.Print();
           std::cout << std::endl;
       }
       if (c == '/') {
           std::pair<Polynomial, Polynomial> res = lhs / rhs;
           res.first.Print();
           std::cout << std::endl;
           res.second.Print();
           std::cout << std::endl;
       }

        std::cout << "Continue?" << std::endl;
        operation = Read(interactive, in, operation);

        if (operation == "No") {
            return 0;
        }
   }
}
