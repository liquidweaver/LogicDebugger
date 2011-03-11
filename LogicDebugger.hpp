#ifndef LOGICDEBUGGER_H
#define LOGICDEBUGGER_H
#include <stack>
#include <iostream>
#include <sstream>

namespace LogicDebugger {
	class Debug;
	static stack<Debug*> _stack;
	static char indent[] = "* ";

	class Debug {
	protected:
		stringstream& inner() {
			return m_inner;
		}
	public:
		Debug( const char* clause )
			: first( true ) {
				for ( unsigned int i = 0; i < LogicDebugger::_stack.size(); ++i )
					m_indention << indent;
				LogicDebugger::_stack.push( this );
				m_output << m_indention.str() << clause << ": ";
				m_result_indent = string( m_output.str().length(), ' ' );
		}

		Debug( const string& clause )
			: first( true ) {
				for ( unsigned int i = 0; i < LogicDebugger::_stack.size(); ++i )
					m_indention << indent;
				LogicDebugger::_stack.push( this );
				m_output << m_indention.str() << clause << ": ";
				m_result_indent = string( m_output.str().length(), ' ' );
		}
			

		void operator()( const char* result ) {
			if ( first ) { 
				m_output << result;
				first = false;
			}
			else
				m_output << '\n' << m_result_indent << result;
		}

		void operator()( const string& result ) {
			(*this)( result.c_str() );
		}

		~Debug() {
			assert( LogicDebugger::_stack.top() == this );
			LogicDebugger::_stack.pop();
			if ( LogicDebugger::_stack.size() > 0 ) {
				Debug* parent = LogicDebugger::_stack.top();
				parent->m_inner << m_output.str();
				if ( m_inner.str().length() > 0 ) 
					parent->m_inner << '\n' << m_inner.str();
				else
					parent->m_inner << '\n' ;
			}
			else {
				cout << m_output.str();
				if ( m_inner.str().length() > 0 )
					cout << '\n' << m_inner.str();
				else
					cout << endl;
			}
		}

	protected:
		stringstream m_inner;
		stringstream m_output;
		stringstream m_indention;
		string m_result_indent;
		bool first;
	};
 
}
#endif //LOGICDEBUGGER_H
