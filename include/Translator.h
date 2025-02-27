//
//  Translator
//
//  Created by Daniil Litvyakov on 13.02.2025.
//
#pragma once
#include <iostream>
#include "Polynoms.h"
#include <vector>
#include <string>
#include <map>
#include <algorithm>
enum types { number, degree, sign };

class Term {
protected:
    types type;
    char sign; 
public:
    types GetType() { return type; }
};

class Number : public Term {
private:
    double Value;
public:
    double GetNumber() { return Value; }
    Number(double _Value = 0.0) : Value(_Value) {
        type = number;
    }
};

class Degree : public Term {
private:
    int Value;
    char letter;
public:
    int GetDegree() { return Value; }
    char GetLetter() { return letter; }
    Degree(int _Value = 0, char let = 'x') : Value(_Value), letter(let) {
        type = degree;
    }
};
/*
class Sign :public Term {
private:
    bool si;
public:
    Sign(char _sign){
        type = sign;
        if (_sign =='+') si = false;
        else si = true;
    }
    int GetSign(){
        if (si == true) return -1;
        else 1;
    }
};
*/
bool IsNumeral(char t) {
    return (t >= '0' && t <= '9');
}

bool IsDeg(char t) {
    return (t == 'x' || t == 'y' || t == 'z' || t == 'X' || t == 'Y' || t == 'Z');
}

bool CheckString(std::string input_string) {
    input_string.erase(std::remove(input_string.begin(), input_string.end(), '*'), input_string.end());
    input_string.erase(std::remove(input_string.begin(), input_string.end(), ' '), input_string.end());
    for (size_t i = 0; i < input_string.size() - 1; ++i) {
        if ((input_string[i] == '+') || (input_string[i] == '-')) {
            if ((input_string[i + 1] == '+') || (input_string[i + 1] == '-') || (input_string[i + 1] == '^') || (input_string[i + 1] == '*')) return false;
        }
        if (input_string[i] == '^') {
            if ((input_string[i + 1] == '+') || (input_string[i + 1] == '-') || (input_string[i + 1] == '^') || (input_string[i + 1] == '*') || (IsDeg(input_string[i + 1]))) return false;
        }
        if (IsDeg(input_string[i])) {
            // It's ok
        }
        if (IsNumeral(input_string[i])) {
            if ((input_string[i + 1] == '^') || (input_string[i + 1] == '*')) return false;
        }
        if (input_string[i] == '*') {
            if ((input_string[i + 1] == '+') || (input_string[i + 1] == '-') || (input_string[i + 1] == '^') || (input_string[i + 1] == '*') || (IsNumeral(input_string[i]))) return false;
        }
    }
    if ((input_string[0]=='*')||(input_string[0]=='^')) return false;
    if ((input_string[input_string.size()-1]=='*')||(input_string[input_string.size()-1]=='^')) return false;
    return true;
}


/*
struct FlagDeg {
public:
    unsigned short Bit : 3;
    FlagDeg(int i) :Bit(i) {}
};*/

std::vector<Term*> String_To_Terms(std::string input_string) {
    //FlagDeg Bit(0);
    input_string.erase(std::remove(input_string.begin(), input_string.end(), '*'), input_string.end());
    input_string.erase(std::remove(input_string.begin(), input_string.end(), ' '), input_string.end());
    std::vector<Term*> terms;
    bool sign = false;
    std::string str_Number = "";
    double temp_num = 1.0;
    std::string temp_str;
    char letter;
    size_t shift;
    for (size_t i = 0; i < input_string.size(); ++i) {
        if (input_string[i] == '-') {
            sign = true;
            /*
            if (Bit.Bit != 7) {
                if (!(Bit.Bit & (1 << 2))) terms.push_back(new Degree(0, 'x'));
                if (!(Bit.Bit & (1 << 1))) terms.push_back(new Degree(0, 'y'));
                if (!(Bit.Bit & 1)) terms.push_back(new Degree(0, 'z'));
                Bit.Bit = 0;
            }*/
        }
        else if (input_string[i] == '+') {
            sign = false;
            /*
            if (Bit.Bit != 7) {
                if (!(Bit.Bit & (1 << 2))) terms.push_back(new Degree(0, 'x'));
                if (!(Bit.Bit & (1 << 1))) terms.push_back(new Degree(0, 'y'));
                if (!(Bit.Bit & 1)) terms.push_back(new Degree(0, 'z'));
                Bit.Bit = 0;
            }
             */
        }


        if ((IsNumeral(input_string[i])) || (input_string[i] == '.')) {
            while ((i < input_string.size()) && (IsNumeral(input_string[i]) || (input_string[i] == '.'))) {
                str_Number += input_string[i++];
            }
            temp_num = std::stod(str_Number);
            str_Number = "";
            if (sign) temp_num *= -1;
            sign = false;
            terms.push_back(new Number(temp_num));
            i--;
        }


        if (IsDeg(input_string[i])) {
            letter = input_string[i];
            int degree = 1;
            if (i < input_string.size()) i++;

            if (i < input_string.size() && input_string[i] == '^') {
                if (input_string[i] == '^') i++;
                temp_str = "";
                if (i < input_string.size() && IsNumeral(input_string[i])) {
                    temp_str += input_string[i++];
                }
                degree = std::stoi(temp_str);
            }

            terms.push_back(new Degree(degree, letter));
            /*if (letter == 'x') shift = 1 << 2;
            if (letter == 'y') shift = 1 << 1;
            if (letter == 'z') shift = 1;
            Bit.Bit |= shift;*/
            i--;
        }
    }


    return terms;
}



























Polynom TermsToPolyom(std::vector<Term*> terms) {
    Polynom polynom;
    double temp = 0;
    int x_deg = 0, y_deg = 0, z_deg = 0;
    int flag = 0;
    for (size_t i = 0; i < terms.size(); ++i) {
        if (terms[i]->GetType() == number) {
            temp = static_cast<Number*>(terms[i])->GetNumber();
            x_deg = y_deg = z_deg = 0; 
            i++; 
        }

        while (i < terms.size() && terms[i]->GetType() == degree && flag<3) {
            Degree* degreeTerm = static_cast<Degree*>(terms[i]);
            if (degreeTerm->GetLetter() == 'x') {
                x_deg = degreeTerm->GetDegree();
            }
            else if (degreeTerm->GetLetter() == 'y') {
                y_deg = degreeTerm->GetDegree();
            }
            else if (degreeTerm->GetLetter() == 'z') {
                z_deg = degreeTerm->GetDegree();
            }
            i++;
            flag++;
        }
        flag = 0;
        int deg = x_deg * 100 + y_deg * 10 + z_deg;
        polynom.add(Monom(deg, temp));
        i--; 
    }
    return polynom;
}







