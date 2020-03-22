/**
    多重ソートのための多重比較用関数オブジェクト
    Ver.1.0.0
    2014.7.27 designed by a.oinoue

    Q1) 比較関数を関数オブジェクトにも対応したい。
    →そのオブジェクトの管理テーブルのデータ型をどのように
    定義すれば良いのか？

    Q2）ソート対象のデータ型を汎用的に扱いたい
    現状では構造体を前提としている。
    stringやint型の２次元配列などを扱いたい

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
        /** 比較関数の戻り値用のテンプレート
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
            例外クラス
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
        T1:データ構造型
    */
    template< typename T1, typename _T_FpComp = int (*)( T1, T1 ) >
    class multiCompare:
        public unary_function<T1, bool>,
        public Mcomp::Exception
    {
    public:
        typedef T1 argument_type;
        typedef bool result_type;
        /**比較関数名テーブル
        */
        typedef map< string, _T_FpComp >    _T_Name_Table;
        /** 比較実行用オーダーテーブル */
        typedef struct _strct {
            /** カラム名 */
            string m_col_name;
            /** ソートモード true:昇順、false:降順 */
            bool m_mode;
            /** 多重比較関数ポインタ、関数オブジェクト */
            _T_FpComp m_comp_func;
        } _T_FpComp_Strct;
        typedef map< int, _T_FpComp_Strct >   _T_Comp_Table;
        /** 呼び出し用オーダーテーブル */
        typedef struct _order_tbl {
            /** カラム名 */
            string m_col_name;
            /** ソートモード true:昇順、false:降順 */
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
            ソートオーダー設定
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
            比較関数名テーブル登録
        */
        multiCompare<T1,_T_FpComp>& operator()( const string col_name, _T_FpComp _comp_func )
        {
            this->set( col_name, _comp_func );
            return *this;
        }
        /** 多重比較関数ポインタテーブルクリア
        */
        void clear()
        {
            m_comp_table.clear();
            m_name_table.clear();
        }
        /** 比較関数コール
        */
        result_type operator()( argument_type lhs, argument_type rhs )
        {
            register int retv = 0;

            for (const auto var : m_comp_table)
            {
                /** 比較した結果等しかったら次の項目を比較
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
        /** ソートオーダー情報表示
        *   項目毎の昇順・降順を表示
        */
        void disp_info() const
        {
            int ii = 1;
            for (const auto var : m_comp_table)
            {
                /** ソートオーダー情報表示
                */
                cout << ii << ".";
                cout << var.second.m_col_name << ",";
                cout << (var.second.m_mode ? "昇順": "降順") << endl;
                ii++;
            }
        }
    private:
        /**
            比較カラム名テーブル設定
        */
        void set( string col_name, _T_FpComp _comp_func )
        {
            m_name_table[ col_name ] = _comp_func;
        }
        /**
            比較関数ポインタ取得
        */
        _T_FpComp get( const string& col_name )
        {
            _T_FpComp   retv;
            typename _T_Name_Table::iterator   it_retv;
            it_retv = m_name_table.find( col_name );
            /* エラーチェック */
            if ( it_retv == m_name_table.end() )
            {
                throw Mcomp::Exception( col_name );
            }
            else
            {
                /* オブジェクトの戻り */
                retv = m_name_table[ col_name ];
            }
            return retv;
        }

    private:
        /** 多重比較関数ポインタのカウンター
        */
        int m_counter;
        /** 多重比較関数ポインタテーブル
        */
        _T_Comp_Table   m_comp_table;
        /** 関数名テーブル
        */
        _T_Name_Table   m_name_table;

    public:
    };
}
#endif // MULTICOMPARE_H
















