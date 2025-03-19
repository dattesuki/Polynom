#include "Translator.h"
//#include "Polynoms.h"
//#include "List.h"
#include "string"

using namespace std;


int main() {
    
    cout << "Input Polynom #1: ";
    string st;
    getline(cin, st);
    std::vector<Term*> terms1 = String_To_Terms(st);
    Polynom p1 = TermsToPolyom(terms1);

    cout << "Input Polynom #2: ";

    getline(cin, st);
    std::vector<Term*> terms2 = String_To_Terms(st);
    Polynom p2 = TermsToPolyom(terms2);



    Polynom p3 = p1 + p2;
    cout << "Polynom #1 + Polynom #2 = " << p3 << endl;

    p3 = p1 * p2;

    cout << "Polynom #1 * Polynom #2 = " << p3 << endl;

    return 0;
}


