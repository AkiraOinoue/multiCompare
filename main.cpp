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
    ��r�֐��A�֐��I�u�W�F�N�g�̓o�^
*/
    typedef Strct_comp_func<_T_Strct_Country>    _FuncObj;
    locallib::multiCompare< _T_Strct_Country, _FuncObj >   mcomp;
    /*
        �֐��I�u�W�F�N�g�̏ꍇ
        ���ږ��̔�r�֐���ݒ�
    */
    mcomp
        ( "name", _FuncObj(_FuncObj::_NAME) )
        ( "int", _FuncObj(_FuncObj::_INT) )
        ( "float", _FuncObj(_FuncObj::_FLOAT) )
        ( "char", _FuncObj(_FuncObj::_CHAR) )
        ;
    try
    {
        /* �\�[�g�w�� by col name */
        // true:�����i�ȗ��j�Afalse:�~��
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

    // �Y���f�[�^�\���z��̍��ږ��̃\�[�g�����{
    sort( vdata.begin(), vdata.end(), mcomp );

    // �\�[�g��̃f�[�^��\��
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




















