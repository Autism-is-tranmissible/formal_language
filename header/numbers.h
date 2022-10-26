#pragma once

#include <ostream>
#include <istream>
#include <numeric>
#include <cassert>

namespace numbers{
    using namespace std;

    using ll = long long;
    using ld = long double;

    class real{
    public:
        real(){
            Zvalue = 0;
            normalize_integer();
        }
        real(ll val){
            Zvalue = val;
            normalize_integer();
        }
        real(ll nume, ll deno){
            Qvalue = fraction(nume, deno);
            normalize_rational();
        }
        real(ld val){
            Ivalue = val;
            normalize_irrational();
        }

        bool is_integer() const{
            return (((int)type & 0b001) == 0b001);
        }
        bool is_rational() const{
            return (((int)type & 0b010) == 0b010);
        }
        bool is_irrational() const{
            return (((int)type & 0b100) == 0b100);
        }
        bool is_real() const{
            return true;
        }

        real& ucast_integer(){
            assert(is_integer());
            return *this;
        }
        friend real to_integer(real num){ return num.ucast_integer(); }
        real& ucast_rational(){
            assert(is_integer() or is_rational());
            if (is_integer()){
                *this = real(Zvalue, 1);
            }
            return *this;
        }
        friend real to_rational(real num){ return num.ucast_rational(); }
        real& ucast_irrational(){
            if (is_integer()){
                *this = real((ld)Zvalue);
            }
            else if (is_rational()){
                *this = real((ld)Qvalue);
            }
            return *this;
        }
        friend real to_irrational(real num){ return num.ucast_irrational(); }

        friend void ucast_sametype(real& lhs, real& rhs){
            types t = max(lhs.get_type(), rhs.get_type());
            lhs.cast(t); rhs.cast(t);
        }
        friend pair <real, real> to_sametype(real lhs, real rhs){
            ucast_sametype(lhs, rhs);
            return make_pair(lhs, rhs);
        }

        real& operator+=(real rhs){
            ucast_sametype(*this, rhs);
            switch (type){
                case types::integer: Zvalue += rhs.Zvalue; break;
                case types::rational: Qvalue += rhs.Qvalue; break;
                case types::irrational: Ivalue += rhs.Ivalue; break;
            }
            return *this;
        }
        friend real operator+(real lhs, const real& rhs){ lhs += rhs; return lhs; }
        real& operator-=(real rhs){
            ucast_sametype(*this, rhs);
            switch (type){
                case types::integer: Zvalue -= rhs.Zvalue; break;
                case types::rational: Qvalue -= rhs.Qvalue; break;
                case types::irrational: Ivalue -= rhs.Ivalue; break;
            }
            return *this;
        }
        friend real operator-(real lhs, const real& rhs){ lhs -= rhs; return lhs; }
        real& operator*=(real rhs){
            ucast_sametype(*this, rhs);
            switch (type){
                case types::integer: Zvalue *= rhs.Zvalue; break;
                case types::rational: Qvalue *= rhs.Qvalue; break;
                case types::irrational: Ivalue *= rhs.Ivalue; break;
            }
            return *this;
        }
        friend real operator*(real lhs, const real& rhs){ lhs *= rhs; return lhs; }
        real& operator/=(real rhs){
            ucast_sametype(*this, rhs);
            switch (type){
                case types::integer: Zvalue -= rhs.Zvalue; break;
                case types::rational: Qvalue -= rhs.Qvalue; break;
                case types::irrational: Ivalue -= rhs.Ivalue; break;
            }
            return *this;
        }
        friend real operator/(real lhs, const real& rhs){ lhs /= rhs; return lhs; }

        friend bool operator<(real lhs, real rhs){
            ucast_sametype(lhs, rhs);
            switch (lhs.type){
                case types::integer: return lhs.Zvalue < rhs.Zvalue;
                case types::rational: return lhs.Qvalue < rhs.Qvalue;
                case types::irrational: return lhs.Ivalue < rhs.Ivalue;
            }
        }
        friend bool operator>(const real& lhs, const real& rhs){ return rhs < lhs; }
        friend bool operator<=(const real& lhs, const real& rhs){ return !(lhs > rhs); }
        friend bool operator>=(const real& lhs, const real& rhs){ return !(lhs < rhs); }
        friend bool operator==(real lhs, real rhs){
            ucast_sametype(lhs, rhs);
            switch (lhs.type){
                case types::integer: return lhs.Zvalue == rhs.Zvalue;
                case types::rational: return lhs.Qvalue == rhs.Qvalue;
                case types::irrational: return lhs.Ivalue == rhs.Ivalue;
            }
        }
        friend bool operator!=(const real& lhs, const real& rhs){ return !(lhs == rhs); }

        friend ostream& operator<<(ostream& os, const real& rhs){
            switch (rhs.type){
                case types::integer: os << rhs.Zvalue; break;
                case types::rational: os << rhs.Qvalue; break;
                case types::irrational: os << rhs.Ivalue; break;
            }
            return os;
        }
        friend istream& operator>>(istream& is, real& rhs){
            switch (rhs.type){
                case types::integer: is >> rhs.Zvalue; break;
                case types::rational: is >> rhs.Qvalue; break;
                case types::irrational: is >> rhs.Ivalue; break;
            }
            return is;
        }
    private:
        class fraction{
        public:
            fraction(){
                nume = 0; deno = 1;
            }
            fraction(ll val){
                nume = val; deno = 1;
            }
            fraction(ll tnume, ll tdeno){
                assert(tdeno != 0);
                nume = tnume; deno = tdeno;
                normalize();
            }

            ll numerator(){
                return nume;
            }
            ll denominator(){
                return deno;
            }
            explicit operator ld() const{
                return (ld)nume / deno;
            }

            fraction& operator+=(const fraction& rhs){
                nume = nume * rhs.deno + rhs.nume * deno;
                deno *= rhs.deno;
                normalize();
                return *this;
            }
            friend fraction operator+(fraction lhs, const fraction& rhs){ lhs += rhs; return lhs; }
            fraction& operator-=(const fraction& rhs){
                nume = nume * rhs.deno - rhs.nume * deno;
                deno *= rhs.deno;
                normalize();
                return *this;
            }
            friend fraction operator-(fraction lhs, const fraction& rhs){ lhs -= rhs; return lhs; }
            fraction& operator*=(const fraction& rhs){
                nume *= rhs.nume;
                deno *= rhs.deno;
                normalize();
                return *this;
            }
            friend fraction operator*(fraction lhs, const fraction& rhs){ lhs *= rhs; return lhs; }
            fraction& operator/=(const fraction& rhs){
                nume *= rhs.deno;
                deno *= rhs.nume;
                normalize();
                return *this;
            }
            friend fraction operator/(fraction lhs, const fraction& rhs){ lhs /= rhs; return lhs; }
            
            friend bool operator<(const fraction& lhs, const fraction& rhs){
                return (__int128_t)lhs.nume * rhs.deno < (__int128_t)rhs.nume * lhs.deno;
            }
            friend bool operator>(const fraction& lhs, const fraction& rhs){ return rhs < lhs; }
            friend bool operator<=(const fraction& lhs, const fraction& rhs){ return !(lhs > rhs); }
            friend bool operator>=(const fraction& lhs, const fraction& rhs){ return !(lhs < rhs); }
            friend bool operator==(const fraction& lhs, const fraction& rhs){
                return (__int128_t)lhs.nume * rhs.deno == (__int128_t)rhs.nume * lhs.deno;
            }
            friend bool operator!=(const fraction& lhs, const fraction& rhs){ return !(lhs == rhs); }
            
            friend ostream& operator<<(ostream& os, const fraction& rhs){
                os << rhs.nume << '/' << rhs.deno;
                return os;
            }
            friend istream& operator>>(istream& is, fraction& rhs){
                is >> rhs.nume;
                if (is.peek() == '/'){
                    is.get();
                }
                is >> rhs.deno;
                return is;
            }
        private: 
            ll nume, deno;

            void normalize(){
                assert(deno != 0);
                ll g = gcd(nume, deno);
                nume /= g; deno /= g;
                if (deno < 0){
                    nume = -nume; deno = -deno;
                }
            }
        };

        // 0b001 = is integer, 0b010 = is rational, 0b100 = is irrational
        enum class types{
            integer = 0b011, rational = 0b010, irrational = 0b100
        };
        
        ll Zvalue;
        fraction Qvalue;
        ld Ivalue;
        types type;

        void normalize_integer(){
            type = types::integer;
        }

        void normalize_rational(){
            type = types::rational;
        }

        void normalize_irrational(){
            type = types::irrational;
        }

        types get_type(){
            return type;
        }

        friend bool operator<(types lhs, types rhs){
            if (lhs == rhs){
                return false;
            }
            if (lhs == types::integer or rhs == types::integer){
                return (lhs == types::integer);
            }
            if (lhs == types::rational or rhs == types::rational){
                return (lhs == types::rational);
            }
            return (lhs == types::irrational);
        }
        friend bool operator>(types lhs, types rhs){ return rhs < lhs; }
        friend bool operator<=(types lhs, types rhs){ return !(lhs > rhs); }
        friend bool operator>=(types lhs, types rhs){ return !(lhs < rhs); }

        real& cast(const types& t){
            assert(type <= t);
            switch (t){
                case types::integer: return ucast_integer();
                case types::rational: return ucast_rational();
                case types::irrational: return ucast_irrational();
            }
            return *this;
        }
    };
}