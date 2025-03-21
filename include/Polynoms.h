//
//  
//  Polynoms
//
//  Created by Daniil Litvyakov on 13.02.2025.
//
#pragma once
#include <iostream>
#include "List.h"

const int MAX_DEG=9;

class Monom{
private:
    int degree=0;
    double k=0;
    
public:
    Monom(int _degree = 0, double _k = 0):degree(_degree),k(_k){};

    Monom(const Monom& m): degree(m.degree), k(m.k){};
    
    int x_deg() const{
        return degree/100;
    }
    
    int y_deg() const{
        return (degree/10)%10;
    }
    
    int z_deg() const{
        return degree%10;
    }
    
    bool is_deg_correct(){
        return ((x_deg()<=MAX_DEG)&&(y_deg()<=MAX_DEG)&&(z_deg()<=MAX_DEG));
    }
    
    Monom operator+(const Monom& m){
        Monom res(*this);
        if (degree==m.degree){
            res.k = k + m.k;
        }
        else throw std::logic_error("error");
        return res;
    }
    
    Monom operator*(const double& n){
        Monom res(*this);
        res.k *= n;
        return res;
    }
    
    Monom operator*(const Monom& m){
        Monom res(degree+m.degree,k*m.k);
        if(((x_deg() + m.x_deg())>MAX_DEG)||((y_deg() + m.y_deg())>MAX_DEG)||((z_deg() + m.z_deg())>MAX_DEG)) throw std::logic_error("error");
        return res;
    }
    
    int getDegree() const { return degree; }
    double getK() const { return k; }

    Monom& operator=(const Monom& m){
        if(this!=&m){
            k=m.k;
            degree=m.degree;
        }
        return *this;
    }

    friend class Polynom;
    friend std::ostream& operator<<(std::ostream& os, Polynom& right);
};


class Polynom{
private:
    list<Monom*> List;
    
public:
    Polynom():List(){
        List.push_back(new Monom());
        List.GetFirst()->next = List.GetFirst();
        //List.MakeCycle(List.GetSize() - 1, 0);
    }
    
    void push_back(const Monom& m) {
        List.push_back(new Monom(m));
    }

    Monom& GetMonom(int index) {
        return *(List[index]);
    }
    void add(const Monom& m) {
        size_t i = 1;
        for (; i < List.GetSize(); ++i) {
            if (m.degree >= List[i]->degree) break;
        }
        if (i < List.GetSize()) {
            if (m.degree == List[i]->degree) {
                List[i]->k += m.k;
                return;
            }
        }
        List.add(new Monom(m),i);
    }

    ~Polynom(){
        while(List.GetSize()!=0){
            List.pop_front();
        }
    };
    
    Polynom(const Polynom& m) {
        List = m.List;
    }


    Polynom& operator=(const Polynom& right) {
        if (this != &right) {
            List=right.List;
        }
        return *this;
    }
   
    Polynom operator+(Polynom& p) {
        Polynom res;
        list<Monom*>::iterator it1(List.GetFirst());
        list<Monom*>::iterator it2(p.List.GetFirst());
        ++it1;
        ++it2;
        while ((it1 != List.end()) && (it2 != p.List.end())) {
            if (it1.value()->getDegree() == it2.value()->getDegree()) {
                res.add((*(it1.value()) + *(it2.value())));
                ++it1; ++it2;
            }
            else {
                if (it1.value()->getDegree() > it2.value()->getDegree()) {
                    res.add(*(it1.value()));
                    ++it1;
                }
                else {
                    res.add(*(it2.value()));
                    ++it2;
                }
            }
        }

        if (it1 == List.end()) {
            while (it2 != p.List.end()) {
                res.List.push_back(it2.value());
                ++it2;
            }
        }
        if (it2 == p.List.end()) {
            while (it1 != List.end()) {
                res.List.push_back(it1.value());
                ++it1;
            }
        }
        
        return res;
    }

    Polynom operator*(Polynom& p) {
        Polynom res;
        list<Monom*>::iterator it1(List.GetFirst());
        list<Monom*>::iterator it2(p.List.GetFirst());
        ++it1;
        ++it2;
        //naive algorithm
        for (; it1 != List.end(); ++it1) {
            it2 = list<Monom*>::iterator (p.List.GetFirst());
            ++it2;
            for (; it2 != p.List.end(); ++it2) {
                res.add(*(*it1) * *(*it2));
            }
        }
        

        return res;
    }

    
    friend std::ostream& operator<<(std::ostream& os, Polynom& right) {
        list<Monom*>::iterator it(right.List.GetFirst());
        ++it;
        while(it != right.List.end()) {
            os << it.value()->getK();
            if (it.value()->x_deg() != 0) {
                os << "*x^" << it.value()->x_deg();
            }
            if (it.value()->y_deg() != 0) {
                os << "*y^" << it.value()->y_deg();
            }
            if (it.value()->z_deg() != 0) {
                os << "*z^" << it.value()->z_deg();
            }
            if (++it != right.List.end()) os << " + ";
        }
        return os;
    }
};








