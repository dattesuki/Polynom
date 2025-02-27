#include "Translator.h"
//#include "Polynoms.h"
//#include "List.h"

using namespace std;


int main() {
    
    vector<float> c = { 1,2 };
    list<float> a(c);
    
    Polynom p1;
    p1 = TermsToPolyom(String_To_Terms("1yz + 2x"));


    Polynom p2;
    p2 = TermsToPolyom(String_To_Terms("1y"));
    
    cout << p1 << endl;
    cout << p2 << endl;
    Polynom p3;
    p3 = (p1 + p2);
    cout << p3 << endl;
    p3 = (p1 * p2);
    cout << p3 << endl;

    return 0;
}


