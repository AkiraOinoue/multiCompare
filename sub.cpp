#include "multiCompare.h"
#include "sub.h"

_T_Strct_Country    ele[] = {
    /*name,int_a,float_a,char_a*/
    {"aaa",5,35.1,'A'},
    {"aaa",5,35.1,'B'},
    {"aaa",5,35.1,'C'},
    {"aaa",5,35.1,'D'},
    {"aaa",5,40.5,'A'},
    {"aaa",5,40.5,'B'},
    {"aaa",5,40.5,'C'},
    {"aaa",5,40.5,'D'},
    {"zzz",5,35.1,'A'},
    {"zzz",5,35.1,'B'},
    {"zzz",5,35.1,'C'},
    {"zzz",5,35.1,'D'},
    {"zzz",5,40.5,'A'},
    {"zzz",5,40.5,'B'},
    {"zzz",5,40.5,'C'},
    {"zzz",5,40.5,'D'},
    {"aaa",10,35.1,'A'},
    {"aaa",10,35.1,'B'},
    {"aaa",10,35.1,'C'},
    {"aaa",10,35.1,'D'},
    {"aaa",10,40.5,'A'},
    {"aaa",10,40.5,'B'},
    {"aaa",10,40.5,'C'},
    {"aaa",10,40.5,'D'},
    {"zzz",10,35.1,'A'},
    {"zzz",10,35.1,'B'},
    {"zzz",10,35.1,'C'},
    {"zzz",10,35.1,'D'},
    {"zzz",10,40.5,'A'},
    {"zzz",10,40.5,'B'},
    {"zzz",10,40.5,'C'},
    {"zzz",10,40.5,'D'}
};

int m_size = sizeof( ele ) / sizeof(ele[0]);

int comp_name( _T_Strct_Country lhs, _T_Strct_Country rhs )
{
    return lMcomp::comp_temp( lhs.name, rhs.name );
}

int comp_int( _T_Strct_Country lhs, _T_Strct_Country rhs )
{
    return lMcomp::comp_temp( lhs.int_a, rhs.int_a );
}

int comp_float( _T_Strct_Country lhs, _T_Strct_Country rhs )
{
    return lMcomp::comp_temp( lhs.float_a, rhs.float_a );
}
int comp_char( _T_Strct_Country lhs, _T_Strct_Country rhs )
{
    return lMcomp::comp_temp( lhs.char_a, rhs.char_a );
}
