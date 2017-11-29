#include "pq.h"

/*========================================================================================================*/
//Construtor vazio
template < typename ValueType, typename Compare>
PQ< ValueType, Compare >::PQ (const Compare & cmp) 	: m_capacity(0)
												    , m_length(0)	
												    , m_sorted (true)
												    //, m_data (nullptr)
												    , m_cmp (cmp)
{
	m_capacity = DEFAULT_SIZE;
	//Assim também dá certo:
	ValueType* p = (ValueType*) malloc(m_capacity * sizeof(ValueType));
	m_data = std::unique_ptr< ValueType[] >(p);

	//std::unique_ptr< ValueType[] > p( new foo(42) );
	//std::unique_ptr< ValueType[] > p(new ValueType[m_capacity]);
	//m_data = std::move(p);
}
/*========================================================================================================*/
//Push
template < typename ValueType, typename Compare >
void PQ< ValueType, Compare >::push( const_reference x )
{
	//Verificar se pode ser inserido
		//Se não poder, dobrar o tamanho da heap mantendo os elementos atuais intáctos
	if(m_capacity <= m_length + 1)
	{
		m_capacity *= 2;			
	}

	//Inserir x na última posição e atualizar m_length
	m_data[m_length + 1] = x;
	m_length++;
	
	//Verificar sort order
		//Caso não seja a posição correta, fazer operação de move_up até obedecer à regra
	if(m_sorted == false)
	{
		move_up(m_length);
	}
}

//Move Up
template<typename ValueType , typename Compare >
void PQ< ValueType, Compare >::move_up(size_type item_idx) 	
{
	if(item_idx > 0)
	{
		if(m_cmp(m_data[item_idx + 1], m_data[(item_idx + 1)/2]))
		{
			std::swap(m_data[(item_idx + 1)/2], m_data[item_idx + 1]);		
			move_up((item_idx + 1)/2);
		}
	}
}

template<typename ValueType , typename Compare >
void PQ< ValueType, Compare >::reserve(size_type new_cap)
{
	//ValueType* p = (ValueType*) malloc(m_capacity * sizeof(ValueType));
	//m_data = std::unique_ptr< ValueType[] >(p);

	//void reset( pointer ptr = pointer() )
}