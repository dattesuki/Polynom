//
//  main.cpp
//  List
//
//  Created by Daniil Litvyakov on 13.02.2025.
//
#pragma once
#include <iostream>
#include <vector>

//declaring a list for friendliness
template <typename type>
class list;

class Polynom;

template <typename type>
struct node {
public:
    node* next = NULL;
    type value = type();

    type& GetValue() { return value; }

    node(const type& _value = type(), node* _next = NULL) :value(_value), next(_next) {}

    node* GetNext() {
        if (next == NULL) throw std::logic_error("no next");
        return next;
    };

    node<type>& operator=(const node<type>& right) {
        if (this != &right) {
            value = right.value;
            next = right.next;
        }
        return *this;
    }

    friend class list<type>;
};


template <typename type>
class list {
protected:
    node<type>* first;
    size_t sz = 0;

    //It's nice that someone can't get a pointer outside of the class.
    node<type>* GetLast() {
        node<type>* temp = first;
        for (size_t i = 0; i < (sz - 1); ++i) temp = temp->next;
        return temp;
    }

public:
    list() {
        first = NULL;
    }
    list(type value) {
        first = new node<type>(value);
        ++sz;
    }

    list(std::vector<type> v) {
        if (v.size() == 0) throw std::logic_error("vector is empty");
        first = new node<type>(v[0]);
        sz = v.size();
        node<type>* temp = first;

        for (size_t i = 1; i < sz; ++i) {
            temp = temp->next = new node<type>(v[i]);
        }

    }
    ~list() {
        while (sz != 0) pop_front();
    }
    size_t GetSize() const { return sz; }

    void push_front(const type& value) {
        node<type>* temp = new node<type>(value);
        temp->next = first;
        first = temp;
        ++sz;
    }

    void push_back(const type& value) {
        if (sz != 0) {
            node<type>* temp = new node<type>(value);
            GetLast()->next = temp;
            ++sz;
        }
        else {
            push_front(value);
        }
    }


    //
    void insert(const type& value, size_t num) {
        if ((num > sz) || (num < 0)) throw std::logic_error("error");

        if (num == sz) push_back(value);
        else {
            if (num != 0) {
                node<type>* temp = first;
                node<type>* temp2;
                for (int i = 0; i < (num - 1); ++i) {
                    temp = temp->next;
                }
                temp2 = temp->next;
                temp->next = new node<type>(value);
                temp->next->next = temp2;
                ++sz;
            }
            else {
                node<type>* temp = new node<type>(value);
                temp->next = first;
                first = temp;
                ++sz;
            }
        }
    }


    void pop_back() {
        node<type>* temp = first;
        for (size_t i = 0; i < (sz - 1); ++i) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = NULL;
        --sz;
    }

    void pop_front() {
        if (first == NULL) throw std::logic_error("error");
        node<type>* temp = first->next;
        delete first;
        first = temp;
        --sz;
    }


    type& remove(size_t num) {
        type temp_val;

        if (num == 0) {
            temp_val = first->value;
            pop_front();
        }
        else {
            --sz;
            node<type>* temp = first;
            node<type>* temp2;
            for (size_t i = 0; i < (num - 1); ++i) {
                temp = temp->next;
            }
            temp2 = temp->next->next;
            temp_val = temp->next->value;
            delete temp->next;
            temp->next = temp2;
        }
        return temp_val;
    }

    type& operator[](size_t num) {
        if ((num >= sz)&&(CheckCycles()==false)) throw std::logic_error("error");
        node<type>* temp = first;
        for (size_t i = 0; i < num; ++i) {
            temp = temp->next;
        }
        return temp->value;
    }

    void MakeCycle(size_t from, size_t to) {
        if (from < to) throw std::logic_error("something wrong with cycle");
        node<type>* temp = first;
        node<type>* temp2 = first;
        for (size_t i = 0; i < to; ++i) temp = temp->next;
        for (size_t i = 0; i < from; ++i) temp2 = temp2->next;
        temp2->next = temp;

    }

    bool CheckCycles() const{
        node<type>* slow = first;
        node<type>* fast = first;

        while (fast != NULL) {
            fast = fast->next;
            slow = slow->next;
            if (fast == NULL) return false;
            fast = fast->next;
            if (fast == slow) return true;
        }
        return false;
    }

    size_t FindCycles() {
        node<type>* slow = first;
        node<type>* fast = first;
        size_t num;
        fast = fast->next->next;
        slow = slow->next;
        while (fast != slow) {
            fast = fast->next->next;
            slow = slow->next;
        }
        fast = first;
        for (num = 0;; ++num) {
            slow = slow->next;
            fast = fast->next;
            if (fast == slow) break;
        }
        
        return num;
    }


    size_t LenCycle() {
        if (CheckCycles() == false) throw std::logic_error("error");
        node<type>* slow = first;
        node<type>* fast = first;
        size_t num;
        fast = fast->next->next;
        slow = slow->next;
        while (fast != slow) {
            fast = fast->next->next;
            slow = slow->next;
        }
        fast = first;
        for (num = 0;; ++num) {
            slow = slow->next;
            fast = fast->next;
            if (fast == slow) break;
        }
        size_t len = 1;
        fast = fast->next;
        while (fast != slow) {
            ++len;
            fast = fast->next;
        }
        return len;
    }
    /*
    list<type>& operator = (const list<type>& l) {
        if (this != &l) {
            while (this->sz != 0) this->pop_back();
            for (size_t i = 0; i < l.sz; ++i) this->push_back(l[i]);
        }
        return *this;
    }
    */

    friend std::ostream& operator<<(std::ostream& os, list<type>& l) {
        if (l.CheckCycles() == false) {
            //it was written before iterators
            os << "size = " << size(l) << "; ";
            for (size_t i = 0; i < size(l); ++i) {
                os << l[i];
                if (i != (size(l) - 1)) os << "->";
            }
            return os;
        }
        else {
            node<type>* now = l.first;
            os << "size = Cycle;\t";
            
            //if()
            for (size_t i = 0; i <= l.FindCycles(); ++i) {
                os << now->GetValue() << "->";
                now = now->next;
            }
            os << "(";
            for (size_t i = 0; i < l.LenCycle(); ++i) {
                os << now->GetValue();
                now = now->next;
                if(i!=(l.LenCycle()-1)) os << "->";
            }
            os << ")";
            return os;
        }
    }
    
    list<type>& operator=(const list<type>& right) {
        if (this != &right) {
            while (sz != 0) {
                this->pop_back();
            }
            node<type>* temp = right.first;
            for (size_t i = 0; i < right.GetSize(); ++i) {
                this->push_back(temp->value);
                temp = temp->next;
            }
        }
        return *this;
    }


    class iterator {
    protected:
        list<type>* List;
        node<type>* now;
        size_t n;
    public:
        iterator(list<type>& l, size_t num = 0):List(&l),now(l.first), n(num) {
            if ((List->CheckCycles()==false) && (num>List->GetSize())) throw std::logic_error("error");
            for (size_t i = 0; i < num; ++i) now = now->next;
        }
        
        list<type>::iterator& operator=(const list<type>::iterator& right) {
            if (this != (&right)) {
                List = right.List;
                now = right.now;
                n = right.n;
            }
            return *this;
        }

        operator node<type>*() const { return now; }
        node<type>* now_ptr() const { return now; }

        node<type>* begin() { return first; }
        node<type>* pt_now() { return now; }
        node<type>* end() {
            if (List->CheckCycles() == true) return List->GoBack();
            return NULL;
        }

        node<type>* next() { return now->next; }

        type& value() const
        {
            return now->value;
        }

        type& operator*() const
        {
            return now->value;
        }

        list<type>::iterator& operator++() {
            if (now == NULL) throw std::logic_error("error");
            now = now->next;
            n++;
            return *this;
        }

        list<type>::iterator& operator++(int) {
            list<type>::iterator temp = *this;
            ++*this;
            return temp;
        }
        
        list<type>::iterator& operator--() {
            if ((now==List->first)&&(List->CheckCycles() == false)) throw std::logic_error("error");
            node<type>* temp = now;
            now = List->first;
            while (now->next != temp) {
                now = now->next;
            }
            n--;
            return *this;
        }

        list<type>::iterator& operator--(int) {
            list<type>::iterator temp = *this;
            --*this;
            return temp;
        }
        
        bool operator==(const list<type>::iterator& right) {
            if ((now == right.now)&&(List==right.List)) return true;
            else return false;
        }

        bool operator!=(const list<type>::iterator& right) {
            return !(*this == right);
        }
        
    };

    void clear() {
        while (sz != 0) pop_front();
    }

    using Iterator = list<type>::iterator;
    node<type>* GoBack() {
        Iterator it(*this);
        if (CheckCycles() == false) {
            while (it.next() != it.end()) {
                ++it;
            }
            return it.now_ptr();
        }
        else {
            for (size_t i = 0; i < this->FindCycles(); ++it, ++i);
            node<type>* flag = (++it);
            while (it.now_ptr()->next != flag) {
                //if is needed in order to return a non-first element in same a situation (when the loop starts with the zero element)
                //
                //size = Cycle; 1->(2->3->7->1)
                //  Goback() :1
                if (it.now_ptr()->next == first) break;
                ++it;
            }
            return it.now_ptr();
        }
    }
    //Слияние упорядоченных массивов
    friend list<type> merge(list& a, list& b, list& c) {
        while (c.GetSize() != 0) c.pop_front();
        size_t na = a.sz;
        size_t nb = b.sz;
        size_t i;
        size_t j;
        for (i = 0, j = 0; ((i < na) && (j < nb));) {
            if (a[i] < b[j]) c.push_back(a[i++]);
            else c.push_back(b[j++]);
        }
        for (; i < na; i++) c.push_back(a[i]);
        for (; j < nb; j++) c.push_back(b[j]);
        c.pop_front();
        return c;
    }
    
    
};



template <typename type>
size_t size(const list<type>& A) {
    return A.GetSize();
}
























