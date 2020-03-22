/**
    ���d�\�[�g�̂��߂̑��d��r�p�֐��I�u�W�F�N�g
    Ver.1.0.0
    2014.7.27 designed by a.oinoue

    Q1) ��r�֐����֐��I�u�W�F�N�g�ɂ��Ή��������B
    �����̃I�u�W�F�N�g�̊Ǘ��e�[�u���̃f�[�^�^���ǂ̂悤��
    ��`����Ηǂ��̂��H

    Q2�j�\�[�g�Ώۂ̃f�[�^�^��ėp�I�Ɉ�������
    ����ł͍\���̂�O��Ƃ��Ă���B
    string��int�^�̂Q�����z��Ȃǂ���������

*/
#ifndef MULTICOMPARE_H
#define MULTICOMPARE_H
#include <iostream>
#include <exception>
#include <string>
#include <map>
#include <functional>
#define _LESS_THAN (-1)
#define _GREATER_THAN (1)
#define _EQUAL (0)
#define _SAME _EQUAL

namespace locallib {
    using namespace std;
    namespace Mcomp
    {
        /** ��r�֐��̖߂�l�p�̃e���v���[�g
        */
        template <typename _T_LHS, typename _T_RHS>
        int comp_temp(_T_LHS lhs, _T_RHS rhs)
        {
            int retv;
            if (lhs == rhs)
            {
                retv = _SAME;
            }
            else if (lhs < rhs)
            {
                retv = _LESS_THAN;
            }
            else
            {
                retv = _GREATER_THAN;
            }
            return retv;
        }

        /**
            ��O�N���X
        */
        class Exception:
            public exception
        {
        public:
            Exception(){}
            Exception( const string& msg );
            virtual ~Exception() throw();
            virtual const char* what() const throw();
        private:
            const string message;
        };
    }
    /**
        T1:�f�[�^�\���^
    */
    template< typename T1, typename _T_FpComp = int (*)( T1, T1 ) >
    class multiCompare:
        public unary_function<T1, bool>,
        public Mcomp::Exception
    {
    public:
        typedef T1 argument_type;
        typedef bool result_type;
        /**��r�֐����e�[�u��
        */
        typedef map< string, _T_FpComp >    _T_Name_Table;
        /** ��r���s�p�I�[�_�[�e�[�u�� */
        typedef struct _strct {
            /** �J������ */
            string m_col_name;
            /** �\�[�g���[�h true:�����Afalse:�~�� */
            bool m_mode;
            /** ���d��r�֐��|�C���^�A�֐��I�u�W�F�N�g */
            _T_FpComp m_comp_func;
        } _T_FpComp_Strct;
        typedef map< int, _T_FpComp_Strct >   _T_Comp_Table;
        /** �Ăяo���p�I�[�_�[�e�[�u�� */
        typedef struct _order_tbl {
            /** �J������ */
            string m_col_name;
            /** �\�[�g���[�h true:�����Afalse:�~�� */
            bool m_mode;
        } _T_Order_Tbl;
        typedef map< int, _T_Order_Tbl >    _T_Order_Map;

    public:
        /** Default constructor */
        multiCompare()
        {
            this->m_counter = 0;
        }
        /** Default destructor */
        virtual ~multiCompare() throw()
        {
            this->clear();
        }
    public:
        /**
            �\�[�g�I�[�_�[�ݒ�
            must be 'int _comp_func( DataType lhs, DataType rhs );'
            return case of lhs == rhs is 0, lhs < rhs is -1, lhs > rhs is 1
        */
        multiCompare<T1,_T_FpComp>& operator()( const string col_name, bool val = true )
        {
            this->m_comp_table[ m_counter ].m_col_name = col_name;
            this->m_comp_table[ m_counter ].m_comp_func = this->get( col_name );
            this->m_comp_table[ m_counter ].m_mode = val;
            ++m_counter;
            return *this;
        }
        multiCompare<T1,_T_FpComp>& operator()( int key, const string col_name, bool val = true )
        {
            this->m_comp_table[ key ].m_col_name = col_name;
            this->m_comp_table[ key ].m_comp_func = this->get( col_name );
            this->m_comp_table[ key ].m_mode = val;
            return *this;
        }
        multiCompare<T1,_T_FpComp>& operator()( _T_FpComp _comp_func, bool val = true )
        {
            this->m_comp_table[ m_counter ].m_col_name = "none";
            this->m_comp_table[ m_counter ].m_comp_func = _comp_func;
            this->m_comp_table[ m_counter ].m_mode = val;
            ++m_counter;
            return *this;
        }
        /**
            ��r�֐����e�[�u���o�^
        */
        multiCompare<T1,_T_FpComp>& operator()( const string col_name, _T_FpComp _comp_func )
        {
            this->set( col_name, _comp_func );
            return *this;
        }
        /** ���d��r�֐��|�C���^�e�[�u���N���A
        */
        void clear()
        {
            m_comp_table.clear();
            m_name_table.clear();
        }
        /** ��r�֐��R�[��
        */
        result_type operator()( argument_type lhs, argument_type rhs )
        {
            register int retv = 0;

            for (const auto var : m_comp_table)
            {
                /** ��r�������ʓ����������玟�̍��ڂ��r
                */
                retv = var.second.m_comp_func( lhs, rhs );
                if ( retv != _SAME )
                {
                    retv =  var.second.m_mode? retv: retv*(-1);
                    break;
                }
            }
            return retv < 0;
        }
        /** �\�[�g�I�[�_�[���\��
        *   ���ږ��̏����E�~����\��
        */
        void disp_info() const
        {
            int ii = 1;
            for (const auto var : m_comp_table)
            {
                /** �\�[�g�I�[�_�[���\��
                */
                cout << ii << ".";
                cout << var.second.m_col_name << ",";
                cout << (var.second.m_mode ? "����": "�~��") << endl;
                ii++;
            }
        }
    private:
        /**
            ��r�J�������e�[�u���ݒ�
        */
        void set( string col_name, _T_FpComp _comp_func )
        {
            m_name_table[ col_name ] = _comp_func;
        }
        /**
            ��r�֐��|�C���^�擾
        */
        _T_FpComp get( const string& col_name )
        {
            _T_FpComp   retv;
            typename _T_Name_Table::iterator   it_retv;
            it_retv = m_name_table.find( col_name );
            /* �G���[�`�F�b�N */
            if ( it_retv == m_name_table.end() )
            {
                throw Mcomp::Exception( col_name );
            }
            else
            {
                /* �I�u�W�F�N�g�̖߂� */
                retv = m_name_table[ col_name ];
            }
            return retv;
        }

    private:
        /** ���d��r�֐��|�C���^�̃J�E���^�[
        */
        int m_counter;
        /** ���d��r�֐��|�C���^�e�[�u��
        */
        _T_Comp_Table   m_comp_table;
        /** �֐����e�[�u��
        */
        _T_Name_Table   m_name_table;

    public:
    };
}
#endif // MULTICOMPARE_H
















