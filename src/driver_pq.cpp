#include <iostream>// cout, endl
#include <sstream>
#include <cassert> // assert()
#include <algorithm> // copy, sort
#include <iterator> // begin(), end().
#include <vector>

#include "../include/pq.h"

//#define USE_FUNCTOR
#ifdef USE_FUNCTOR
struct CompareItems {
    bool operator()( const size_t & a, const size_t & b )
    {
        return a > b ;
    }
} compare;

#else // Use lambda
auto compare = []( int a, int b ) { return a > b; };
#endif

int main( )
{
    auto n_unit{0}; // unit test count.

    // First array for the tests.
    int A[]       = { 65, 26, 13, 14, 31, 19, 68, 16, 32, 21 };
    auto A_length = sizeof(A)/sizeof(A[0]) ;
    int A_sorted[ A_length ];
    // Sort reference array (expected output).
    std::copy( std::begin(A), std::end(A), A_sorted );
    std::sort( A_sorted, A_sorted+A_length, compare );

    // Second array for the tests
    int B[]       = { 92, 47, 21, 20, 12, 45, 63, 61, 17, 55, 37, 25, 64, 83, 73 };
    auto B_length = sizeof(B)/sizeof(B[0]) ;
    int B_sorted[ B_length ];
    // Sort reference array (expected output).
    std::copy( std::begin(B), std::end(B), B_sorted );
    std::sort( B_sorted, B_sorted+B_length, compare );

    //=== Unit tests start here
    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": empty.\n";

        // Create a empty PQ.
        PQ<int, decltype(compare) > h( compare );

        assert( h.size() == 0 );
        assert( h.empty() == true );
        h.push(1);
        assert( h.empty() == false );

        std::cout << ">>> Passed!\n\n";
    }
    
    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": size.\n";

        // Create a empty PQ.
        PQ<int, decltype(compare) > h( compare );

        auto expected_len(0u);
        for( const auto &e : A )
        {
            assert( expected_len == h.size() );
            h.push( e );
            h.print();
            assert( ++expected_len == h.size() );
        }

        std::cout << ">>> Passed!\n\n";
    }
    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": insertion.\n";

        // Create a empty PQ.
        PQ<int, decltype(compare) > h( compare );

        // Store elements in the PQ.
        for( const auto e : A )
        {
            std::cout << ">>> Inserting " << e << std::endl;
            h.push( e );
            h.print();
        }

        assert( h.size() == A_length );

        // Check whether the elements come out of the PQ in the correct sorted order.
        auto i(0);
        while( not h.empty() )
        {
            auto x = h.top();
            assert( x == A_sorted[i++] );
            h.pop();
        }
        assert( h.empty() == true );

        std::cout << ">>> Passed!\n\n";
    }
    /*
    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": deletion.\n";

        // Create a empty PQ.
        PQ<int, decltype(compare) > h( compare );

        // Store elements in the PQ.
        for( const auto e : B )
            h.push( e );

        assert( h.size() == B_length );

        // Check whether the elements come out of the PQ in the correct sorted order.
        auto i(0);
        while( not h.empty() )
        {
            auto x = h.top();
            assert( x == B_sorted[i++] );
            h.pop();
        }

        assert( h.size() == 0 );

        std::cout << ">>> Passed!\n\n";
    }
    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": constructor from initilize list.\n";


        // Create a empty PQ.
        PQ<int, decltype(compare) > h{ { 92, 47, 21, 20, 12, 45, 63, 61, 17, 55, 37, 25, 64, 83, 73 }, compare };

        assert( h.size() == B_length );

        // Check whether the elements come out of the PQ in the correct sorted order.
        auto i(0);
        while( not h.empty() )
        {
            auto x = h.top();
            assert( x == B_sorted[i++] );
            h.pop();
        }

        assert( h.size() == 0 );

        std::cout << ">>> Passed!\n\n";
    }
    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": constructor from range.\n";

        // Create a empty PQ.
        PQ<int, decltype(compare) > h{ std::begin(B), std::end(B), compare };

        assert( h.size() == B_length );

        // Check whether the elements come out of the PQ in the correct sorted order.
        auto i(0);
        while( not h.empty() )
        {
            auto x = h.top();
            assert( x == B_sorted[i++] );
            h.pop();
        }

        assert( h.size() == 0 );

        std::cout << ">>> Passed!\n\n";
    }
    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": toss.\n";

        // Create a empty PQ.
        PQ<int, decltype(compare) > h( compare );

        // Insert elements with toss
        auto expected_len(0u);
        for( const auto & e : B )
        {
            assert( expected_len == h.size() );
            h.toss( e );
            assert( ++expected_len == h.size() );
            //h.print();
        }
        //std::cout << std::endl;

        assert( h.size() == B_length );

        // Check whether the elements come out of the PQ in the correct sorted order.
        auto i(0);
        while( not h.empty() )
        {
            auto x = h.top();
            //h.print();
            assert( x == B_sorted[i++] );
            h.pop();
        }

        assert( h.size() == 0 );

        std::cout << ">>> Passed!\n\n";
    }

    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": insertion/deletion mixed.\n";

        // Create a empty PQ.
        PQ<int, decltype(compare) > h( compare );

        // Store elements in the PQ.
        for( const auto e : A )
        {
            //std::cout << ">>> Inserting " << e << std::endl;
            h.push( e );
            //h.print();
        }

        assert( h.size() == A_length );


        // Remove half the elements.
        std::vector<int> dump;
        for( auto i(0u) ; i < A_length/2 ; ++i )
        {
            auto x = h.top();
            dump.push_back( x );
            assert( x == A_sorted[i] );
            h.pop();
        }
        // Insert back the elements.
        for( const auto& e : dump )
            h.push( e );

        auto i(0);
        while( not h.empty() )
        {
            auto x = h.top();
            //h.print();
            assert( x == A_sorted[i++] );
            h.pop();
        }

        assert( h.empty() == true );

        std::cout << ">>> Passed!\n\n";
    }

    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": Copy constructor.\n";

        // Create a empty PQ.
        PQ<int, decltype(compare) > h( compare );

        // Insert elements with toss
        auto expected_len(0u);
        for( const auto & e : B )
        {
            assert( expected_len == h.size() );
            h.toss( e );
            assert( ++expected_len == h.size() );
            //h.print();
        }
        assert( h.size() == B_length );

        auto h2(h); // Calling copy constructor.

        // Check whether the elements come out of the PQ in the correct sorted order.
        auto i(0);
        while( not h2.empty() )
        {
            auto x = h2.top();
            assert( x == B_sorted[i++] );
            h2.pop();
        }
        assert( h2.size() == 0 );
        assert( h2.empty() == true );
        assert( h.empty() == false );

        // Let us test if the original PQ has retained its elements.
        // Check whether the elements come out of the PQ in the correct sorted order.
        i = 0;
        while( not h.empty() )
        {
            auto x = h.top();
            assert( x == B_sorted[i++] );
            h.pop();
        }

        std::cout << ">>> Passed!\n\n";
    }
    */
    return 0;
}


