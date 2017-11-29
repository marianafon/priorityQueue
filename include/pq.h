#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <stdexcept>  // std::runtime_error or std::out_of_range
#include <functional> // std::less<>().
#include <cassert>    // assert().
#include <memory>     // std::unique_ptr<>.
#include <initializer_list> // std::initializer_list<>.
#include <iostream> // cout, endl
#include <algorithm> // copy.


template < typename ValueType, typename Compare = std::less<ValueType>() >
class PQ
{
public:
    //=== Aliases
    typedef size_t size_type; 
    typedef ValueType value_type; 
    typedef const value_type& const_reference; 

private:
    //=== Members
    size_type m_capacity;  
    size_type m_length;    
    bool m_sorted;         
    std::unique_ptr< ValueType [] > m_data; 
    Compare m_cmp;         

    enum { DEFAULT_SIZE = 2 }; 


    void fix_heap( );


    void move_down( size_type item_idx );


    void move_up( size_type item_idx );


    void reserve( size_type new_cap );

    bool full( void ) const { return m_length == m_capacity; }

public:
    //=== The public interface.

    //=== Constructors and destructor.

    explicit PQ( const Compare& cmp = Compare() );


    PQ( const std::initializer_list< ValueType >& ilist, const Compare& cmp = Compare() );

    template< typename InputIt >
    PQ( InputIt first, InputIt last, const Compare& cmp = Compare() );
    PQ( const PQ & );


    PQ & operator= ( const PQ& rhs );

    virtual ~PQ(){};

    //=== Element access methods
    const_reference  top( void );

    //=== Capacity methods

    bool empty( void ) const { return m_length==0; }


    size_type size( void ) const { return m_length; }

    //=== Modifier methods.

    void clear( );
    void push( const_reference x );
    void pop( );
    void toss( const ValueType & x );


    void print() const
    {
     std::cout << "BH: [ ";
     std::copy( m_data.get()+1, m_data.get()+m_length+1, std::ostream_iterator<ValueType>(std::cout, " ") );
     std::cout << "| ";
     std::copy( m_data.get()+m_length+1, m_data.get()+m_capacity+1, std::ostream_iterator<ValueType>(std::cout, " ") );
     std::cout << "],";
     std::cout << "len = " << m_length << ", cap = " << m_capacity << " \n";
    }
};

#include "pq.inl"
#endif