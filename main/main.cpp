#include "Translator.h"
//#include "Polynoms.h"
//#include "List.h"

using namespace std;


int main() {
    
    vector<float> c = { 1,2 };
    list<float> a(c);
    

    std::vector<Term*> terms1 = String_To_Terms("x^2 + y^2 + z^2");
    Polynom p1 = TermsToPolyom(terms1);

    std::vector<Term*> terms2 = String_To_Terms("x^2 + y^2 + z^2");
    Polynom p2 = TermsToPolyom(terms2);

    Polynom p3 = p1 + p2;

    p3 = (p1 + p2);
    cout << p3 << endl;
    p3 = (p1 * p2);
    cout << p3 << endl;

    return 0;
}


