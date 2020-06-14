//
//  Complex.h
//  Laba2final
//
//  Created by Анна Потёмкина on 10.06.2020.
//  Copyright © 2020 Анна Потёмкина. All rights reserved.
//

#ifndef Complex_h
#define Complex_h
#include <iostream>
#include<math.h>
using namespace std;

class Compl{
private:
    int re;
   int im;
public:
    Compl(): re {0}, im {0}{};
    //Compl(0);
    Compl(int base, int dop): re{base}, im{dop}{};
    ~Compl() = default;
     int Getre() const { return re; };
    int Getim() const { return im; };
    
    Compl& operator=(const Compl& numb) {
        if (this == &numb) {
            return *this;
        }
        else {
            re = numb.re;
            im= numb.im;
        }
        return *this;
    }
    
    Compl  operator +(const Compl& numb){
        Compl dub(*this);
        dub.re=numb.re+dub.re;
        dub.im = numb.im+dub.im;
        return dub;
    }
    
    Compl operator*(const Compl& numb){
        Compl dub (*this);
        dub.re=(numb.re*dub.re) -(numb.im*dub.im) ;
       dub.im=(numb.re*dub.im)+(dub.re*numb.im);
        return dub;
    }

    Compl  operator -(const Compl& numb){
          Compl dub(*this);
          dub.re=dub.re-numb.re;
          dub.im = dub.im-numb.im;
          return dub;
      }
    
    double abs() const{
        return sqrt(re*re+im*im);
    }
    
    friend bool operator >(const Compl &numb1, const Compl &numb2){
        return (numb1.abs()>numb2.abs());
    }
    
    friend bool operator <(const Compl &numb1, const Compl &numb2){
        return (numb1.abs()< numb2.abs());
    }
    
    friend bool operator >=(const Compl &numb1, const Compl &numb2){
        return (numb1.abs()>= numb2.abs());
    }
    
    friend bool operator <=(const Compl &numb1, const Compl &numb2){
        return (numb1.abs()<= numb2.abs());
    }
    
    friend bool operator ==(const Compl &numb1, const Compl &numb2){
        return ((numb1.re==numb2.re)&&(numb1.im==numb2.im));
    }
    
    friend bool operator !=(const Compl &numb1, const Compl &numb2){
        return !((numb1.re==numb2.re)&&(numb1.im==numb2.im));
    }
    
    friend std::istream& operator>>(std::istream& is, Compl& numbToInput) {
        std::cout << "введем действительную часть: ";
        (is >> numbToInput.re).get();
        std::cout << "введем мнимую часть: ";
       (is >> numbToInput.im).get();
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const Compl& numbToOutput) {
        os << numbToOutput.re << " + i*" << numbToOutput.im<< "; ";
        return os;
    }
    
friend std::string to_string(const Compl &numb) {
        return to_string(numb.re) + " + i * " + to_string(numb.im);
    }
    
};

#endif /* Complex_h */


