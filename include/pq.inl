#include "pq.h"

/*========================================================================================================*/
//Construtor vazio
template < typename ValueType, typename Compare>
PQ< ValueType, Compare >::PQ (const Compare & cmp) 	: m_capacity(0)
												    , m_length(0)	
												    , m_sorted (false)
												    //, m_data (nullptr)
												    , m_cmp (cmp)
{
	m_capacity = DEFAULT_SIZE;
	ValueType* p = (ValueType*) malloc(m_capacity * sizeof(ValueType));
	m_data = std::unique_ptr< ValueType[] >(p);
}
/*========================================================================================================*/