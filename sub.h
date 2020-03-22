#ifndef SUB_H_INCLUDED
#define SUB_H_INCLUDED
#include <string>
#include <functional>

// 構造体型宣言
typedef struct _t {
    std::string  name;
    int     int_a;
    double  float_a;
    char    char_a;
} _T_Strct_Country;

extern _T_Strct_Country    ele[];

// 比較関数
int comp_name( _T_Strct_Country lhs, _T_Strct_Country rhs );
int comp_int( _T_Strct_Country lhs, _T_Strct_Country rhs );
int comp_float( _T_Strct_Country lhs, _T_Strct_Country rhs );
int comp_char( _T_Strct_Country lhs, _T_Strct_Country rhs );

namespace lMcomp=locallib::Mcomp;

// 関数オブジェクト
template <typename T1>
struct Strct_comp_func :
    public std::unary_function< T1, int >
{
    typedef T1 argument_type;
    typedef int result_type;

    typedef enum
    {
        _NAME,
        _INT,
        _FLOAT,
        _CHAR
    } COLNAME;
    int mode;
    Strct_comp_func(const int val):
        mode(val)
        {}
    Strct_comp_func(){;}

    result_type operator()( argument_type lhs, argument_type rhs ) const
    {
        switch ( this->mode )
        {
        case    _NAME:
                return lMcomp::comp_temp( lhs.name, rhs.name );
                break;
        case    _INT:
                return lMcomp::comp_temp( lhs.int_a, rhs.int_a );
                break;
        case    _FLOAT:
                return lMcomp::comp_temp( lhs.float_a, rhs.float_a );
                break;
        case    _CHAR:
                return lMcomp::comp_temp( lhs.char_a, rhs.char_a );
                break;
        default:
                return -1;
                break;
        }
    }
};

#endif // SUB_H_INCLUDED
