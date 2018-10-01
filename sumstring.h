#ifndef SUMSTRING_H
#define SUMSTRING_H


class SumString
{
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <iomanip>

struct int_string
{
    void reduce() { for( char& c : digits ) c -= '0' ; } // convert to integers 0-9
    void restore() { for( char& c : digits ) c += '0' ; } // convert to character '0'-'9'

    int_string( unsigned long long value ) : digits( std::to_string(value) ) {}

    int_string( std::string value ) : digits( std::move(value) )
    {
        if( digits.empty() ) digits = "0" ;
        for( char c : digits ) // sanity check
            if( !std::isdigit(c) ) throw std::invalid_argument( "badly formed number" ) ;
    }

    int_string( const char* value ) : int_string( std::string(value) ) {} // delegating constructor

    // implement the compound assignment operator += (a long inline friend)
    // friends defined inside class body are inline and are accessible
    // only via argument-dependant lookup (aka koenig look up)
    // note: a is passed as reference to non-const; the original is modified
    //       b is passed by value; the function receives a copy which it can safely trash
    friend int_string& operator+= ( int_string& a, int_string b )
    {
        // using the same logic as in the original post

        // reverse both strings
        std::reverse( a.digits.begin(), a.digits.end() ) ;
        std::reverse( b.digits.begin(), b.digits.end() ) ;

        // resize both to max size (+1 because there may be a carry at the end)
        const std::size_t max_digits = std::max( a.digits.size(), b.digits.size() ) + 1 ;
        a.digits.resize( max_digits, '0' ) ;
        b.digits.resize( max_digits, '0' ) ;

        // reduce both to hold integer digits 0-9
        a.reduce() ;
        b.reduce() ;

        // normal long hand addition
        int carry = 0 ;
        for( std::size_t i = 0 ; i < max_digits ; ++i )
        {
            a.digits[i] += b.digits[i] + carry  ;
            carry = a.digits[i] / 10 ;
            a.digits[i] %= 10 ;
        }

        // remove leading zero digits
        while( a.digits.size() > 1 && a.digits.back() == 0 ) a.digits.pop_back() ;

        // reverse the result and restore digits back to characters '0'-'9'
        std::reverse( a.digits.begin(), a.digits.end() ) ;
        a.restore() ;

        return a ;
    }

    // canonical: For every binary arithmetic operator there should exist
    // a corresponding compound assignment operator; canonical forms of binary operators
    // are implemented in terms of their compound assignments
    // note: a is passed by value; so we return the result of a+=b
    // passing lhs by value helps optimize chained a+b+c
    // for more information, see: overloading Binary arithmetic operators in
    // http://en.cppreference.com/w/cpp/language/operators
    friend int_string operator + ( int_string a, const int_string& b ){ return a += b ; }
    friend int_string operator * (int_string a, const int_string&b){return  a =a* b;}

    friend std::ostream& operator << ( std::ostream& stm, const int_string& number )
    { return stm << number.digits ; }

    private: std::string digits ;
};

int main()
{
    const int_string a = "1234567891011121314151617181920" ;
    const char* b = "5678901234567890123456789" ;
    const std::string c = "98765432101234567890123456" ;
    const unsigned int d = 2345678 ;

    std::cout << std::setw(40) << a << " +\n"
              << std::setw(40) << b << " +\n"
              << std::setw(40) << c << " +\n"
              << std::setw(40) << d << " ==\n"
              << std::setw(40) << "---------------------------" << '\n'
              << std::setw(40) << a*b << '\n' ;
}

public:
    SumString();
};

#endif // SUMSTRING_H
