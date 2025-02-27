#include "Translator.h"
#include <gtest.h>

TEST(MonomTest, DefaultConstructor) {
    Monom m;
    EXPECT_EQ(m.getDegree(), 0);
    EXPECT_EQ(m.getK(), 0);
}

TEST(MonomTest, ParameterizedConstructor) {
    Monom m(123, 2.5);
    EXPECT_EQ(m.getDegree(), 123);
    EXPECT_EQ(m.getK(), 2.5);
}

TEST(MonomTest, CopyConstructor) {
    Monom m1(123, 2.5);
    Monom m2(m1);
    EXPECT_EQ(m2.getDegree(), 123);
    EXPECT_EQ(m2.getK(), 2.5);
}

TEST(MonomTest, AssignmentOperator) {
    Monom m1(123, 2.5);
    Monom m2;
    m2 = m1;
    EXPECT_EQ(m2.getDegree(), 123);
    EXPECT_EQ(m2.getK(), 2.5);
}



TEST(MonomTest, MultiplicationOperatorWithScalar) {
    Monom m1(123, 2.5);
    Monom m2 = m1 * 2.0;
    EXPECT_EQ(m2.getDegree(), 123);
    EXPECT_EQ(m2.getK(), 5.0);
}

TEST(MonomTest, MultiplicationOperatorWithMonom) {
    Monom m1(111, 2.0);
    Monom m2(222, 3.0);
    Monom m3 = m1 * m2;
    EXPECT_EQ(m3.getDegree(), 333);
    EXPECT_EQ(m3.getK(), 6.0);
}

TEST(MonomTest, DegreeComponents) {
    Monom m(123);
    EXPECT_EQ(m.x_deg(), 1);
    EXPECT_EQ(m.y_deg(), 2);
    EXPECT_EQ(m.z_deg(), 3);
}

TEST(MonomTest, DegreeValidation) {
    Monom m1(999);
    EXPECT_TRUE(m1.is_deg_correct());

    Monom m2(1000);
    EXPECT_FALSE(m2.is_deg_correct());
}

TEST(PolynomTest, DefaultConstructor) {
    Polynom p;
    EXPECT_EQ(p.GetMonom(0).getDegree(), 0);
    EXPECT_EQ(p.GetMonom(0).getK(), 0);
}

TEST(PolynomTest, PushBack) {
    Polynom p;
    p.push_back(Monom(123, 2.5));
    EXPECT_EQ(p.GetMonom(1).getDegree(), 123);
    EXPECT_EQ(p.GetMonom(1).getK(), 2.5);
}

TEST(PolynomTest, AddMonom) {
    Polynom p;
    p.add(Monom(123, 2.5));
    p.add(Monom(123, 1.5));
    EXPECT_EQ(p.GetMonom(1).getDegree(), 123);
    EXPECT_EQ(p.GetMonom(1).getK(), 4.0);
}



TEST(PolynomTest, MultiplicationOperator) {
    Polynom p1;
    p1.add(Monom(222, 2.0));
    p1.add(Monom(111, 1.0));


    Polynom p2;
    p2.add(Monom(222, 2.0));
    p2.add(Monom(111, 1.0));

    Polynom p3 = p1 * p2;
    EXPECT_EQ(p3.GetMonom(1).getDegree(), 444);
    EXPECT_EQ(p3.GetMonom(1).getK(), 4.0);
    EXPECT_EQ(p3.GetMonom(2).getDegree(), 333);
    EXPECT_EQ(p3.GetMonom(2).getK(), 4.0);
}

TEST(PolynomTest, OutputOperator) {
    Polynom p;
    p.add(Monom(123, 2.5));
    p.add(Monom(111, 1.5));

    std::ostringstream os;
    os << p;

    EXPECT_EQ(os.str(), "2.5*x^1*y^2*z^3 + 1.5*x^1*y^1*z^1");
}

TEST(PolynomTest, CopyConstructor) {
    Polynom p1;
    p1.add(Monom(123, 2.5));
    p1.add(Monom(111, 1.5));

    Polynom p2(p1);

    EXPECT_EQ(p2.GetMonom(1).getDegree(), 123);
    EXPECT_EQ(p2.GetMonom(1).getK(), 2.5);
    EXPECT_EQ(p2.GetMonom(2).getDegree(), 111);
    EXPECT_EQ(p2.GetMonom(2).getK(), 1.5);
}

TEST(PolynomTest, AssignmentOperator) {
    Polynom p1;
    p1.add(Monom(123, 2.5));
    p1.add(Monom(111, 1.5));

    Polynom p2;
    p2 = p1;

    EXPECT_EQ(p2.GetMonom(1).getDegree(), 123);
    EXPECT_EQ(p2.GetMonom(1).getK(), 2.5);
    EXPECT_EQ(p2.GetMonom(2).getDegree(), 111);
    EXPECT_EQ(p2.GetMonom(2).getK(), 1.5);
}

TEST(TranslatorTest, CheckStringValid) {
    EXPECT_TRUE(CheckString("2.5*x^1*y^2*z^3 + 1.5*x^1*y^1*z^1"));
    EXPECT_TRUE(CheckString("3*x^2 + 4*y^3 - 5*z^4"));
    EXPECT_TRUE(CheckString("x^2 + y^2 + z^2"));
}

TEST(TranslatorTest, CheckStringInvalid) {
    EXPECT_FALSE(CheckString("2.5*x^1*y^2*z^3 + + 1.5*x^1*y^1*z^1"));
    EXPECT_FALSE(CheckString("x^2 + y^2 + z^2^"));
}


TEST(TranslatorTest, TermsToPolynom) {
    std::vector<Term*> terms = String_To_Terms("2.5*x^1*y^2*z^3 + 1.5*x^1*y^1*z^1");
    Polynom p = TermsToPolyom(terms);

    EXPECT_EQ(p.GetMonom(1).getDegree(), 123);
    EXPECT_EQ(p.GetMonom(1).getK(), 2.5);

    EXPECT_EQ(p.GetMonom(2).getDegree(), 111);
    EXPECT_EQ(p.GetMonom(2).getK(), 1.5);
}

TEST(TranslatorTest, ComplexExpression) {
    std::vector<Term*> terms = String_To_Terms("3*x^2 + 4*y^3 - 5*z^4");
    Polynom p = TermsToPolyom(terms);

    EXPECT_EQ(p.GetMonom(1).getDegree(), 200);
    EXPECT_EQ(p.GetMonom(1).getK(), 3.0);

    EXPECT_EQ(p.GetMonom(2).getDegree(), 30);
    EXPECT_EQ(p.GetMonom(2).getK(), 4.0);

    EXPECT_EQ(p.GetMonom(3).getDegree(), 4);
    EXPECT_EQ(p.GetMonom(3).getK(), -5.0);
}

TEST(TranslatorTest, SingleTerm) {
    std::vector<Term*> terms = String_To_Terms("7*x^3");
    Polynom p = TermsToPolyom(terms);

    EXPECT_EQ(p.GetMonom(1).getDegree(), 300);
    EXPECT_EQ(p.GetMonom(1).getK(), 7.0);
}

TEST(TranslatorTest, NoDegree) {
    std::vector<Term*> terms = String_To_Terms("5");
    Polynom p = TermsToPolyom(terms);

    EXPECT_EQ(p.GetMonom(1).getDegree(), 0);
    EXPECT_EQ(p.GetMonom(1).getK(), 5.0);
}

TEST(TranslatorTest, NegativeCoefficient) {
    std::vector<Term*> terms = String_To_Terms("-3*x^2");
    Polynom p = TermsToPolyom(terms);

    EXPECT_EQ(p.GetMonom(1).getDegree(), 200);
    EXPECT_EQ(p.GetMonom(1).getK(), -3.0);
}

TEST(TranslatorTest, MultipleTermsSameDegree) {
    std::vector<Term*> terms = String_To_Terms("2*x^2 + 3*x^2");
    Polynom p = TermsToPolyom(terms);

    EXPECT_EQ(p.GetMonom(1).getDegree(), 200);
    EXPECT_EQ(p.GetMonom(1).getK(), 5.0);
}

TEST(TranslatorTest, MixedTerms) {
    std::vector<Term*> terms = String_To_Terms("2*x^2 + 3*y^3 - 4*z^4");
    Polynom p = TermsToPolyom(terms);

    EXPECT_EQ(p.GetMonom(1).getDegree(), 200);
    EXPECT_EQ(p.GetMonom(1).getK(), 2.0);

    EXPECT_EQ(p.GetMonom(2).getDegree(), 30);
    EXPECT_EQ(p.GetMonom(2).getK(), 3.0);

    EXPECT_EQ(p.GetMonom(3).getDegree(), 4);
    EXPECT_EQ(p.GetMonom(3).getK(), -4.0);
}

