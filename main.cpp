#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "multiCompare.h"
#include "sub.h"

int main()
{
    using namespace std;
    extern int m_size;
    vector< _T_Strct_Country >  vdata( ele, ele + m_size );

/**
    比較関数、関数オブジェクトの登録
*/
    typedef Strct_comp_func<_T_Strct_Country>    _FuncObj;
    locallib::multiCompare< _T_Strct_Country, _FuncObj >   mcomp;
    /*
        関数オブジェクトの場合
        項目毎の比較関数を設定
    */
    mcomp
        ( "name", _FuncObj(_FuncObj::_NAME) )
        ( "int", _FuncObj(_FuncObj::_INT) )
        ( "float", _FuncObj(_FuncObj::_FLOAT) )
        ( "char", _FuncObj(_FuncObj::_CHAR) )
        ;
    try
    {
        /* ソート指定 by col name */
        // true:昇順（省略）、false:降順
        mcomp
            ("name")
            ("int", false)
            ("float", true)
            ("char", false)
            ;
        // 
        mcomp.disp_info();
    }
    catch ( const lMcomp::Exception& ex )
    {
        cout << "not found function name:" << ex.what() << endl;
        return EXIT_FAILURE;
    }

    // 該当データ構造配列の項目毎のソートを実施
    sort( vdata.begin(), vdata.end(), mcomp );

    // ソート後のデータを表示
    for (const auto var : vdata)
    {
        cout << var.name << ", "
         << var.int_a << ", "
         << var.float_a << ", "
         << var.char_a <<
         endl;
    }

    return EXIT_SUCCESS;
}




















