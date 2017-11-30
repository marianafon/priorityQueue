#include "pq.h"

/*========================================================================================================*/
//Construtor vazio === Working!
template < typename ValueType, typename Compare>
PQ< ValueType, Compare >::PQ (const Compare & cmp) 	: m_length(0)	
												    , m_sorted (false)
												    , m_cmp (cmp)
{
	m_capacity = DEFAULT_SIZE;
	//Alocar:
	//ValueType* p = (ValueType*) malloc(m_capacity * sizeof(ValueType));
	//m_data = std::unique_ptr< ValueType[] >(p);

	//Assim também dá certo:
	//Alocar:
		ValueType* p = new ValueType[m_capacity];
		m_data = std::unique_ptr< ValueType[] >(p);	
	//Alocar:
		//std::unique_ptr< ValueType[] > p(new ValueType[m_capacity]);
		//m_data = std::move(p);
}
/*========================================================================================================*/
//Push === Working!
template < typename ValueType, typename Compare >
void PQ< ValueType, Compare >::push( const_reference x )
{
	//Verificar se pode ser inserido
		//Se não poder, dobrar o tamanho da heap mantendo os elementos atuais intáctos
	if(m_capacity <= m_length + 1)
	{		
		reserve(m_capacity * 2);
	}

	//Inserir x na última posição
	m_data[m_length + 1] = x;
	//atualizar m_length
	m_length++;

	//Verificar sort order
		//Caso não seja a posição correta, fazer operação de move_up até obedecer à regra
	if(m_sorted == false)
	{
		move_up(m_length);
	}
	
	//fix_heap();
}
/*========================================================================================================*/
//Move Up === Working!
template<typename ValueType , typename Compare >
void PQ< ValueType, Compare >::move_up(size_type item_idx) 	
{
	if((item_idx) > 1 && (item_idx) <= m_length)
	{
		if(m_cmp(m_data[(item_idx)], m_data[(item_idx)/2]))
		{
			std::swap(m_data[(item_idx)], m_data[(item_idx)/2]);		
			move_up((item_idx)/2);
		}
	}
}
/*========================================================================================================*/
//Move Down === Working!
template<typename ValueType , typename Compare >
void PQ< ValueType, Compare >::move_down(size_type item_idx) 	
{
	if((item_idx) > 0 && (item_idx) < (m_length/2))
	{
		if(! m_cmp(m_data[(item_idx)], m_data[(item_idx)*2]))
		{
			std::swap(m_data[(item_idx)], m_data[(item_idx)*2]);		
			move_down((item_idx)*2);
		}

		if(! m_cmp(m_data[(item_idx)], m_data[(item_idx*2) + 1]))
		{
			std::swap(m_data[(item_idx)], m_data[(item_idx*2) + 1]);		
			move_down((item_idx*2) + 1);
		}
	}
}
/*========================================================================================================*/
//reserve === Working!
template<typename ValueType , typename Compare >
void PQ< ValueType, Compare >::reserve(size_type new_cap)
{
	ValueType* p = (ValueType*) malloc(new_cap * sizeof(ValueType));
	
	for(size_type i = 0; i < new_cap; i++)
		p[i] = m_data[i];
	
	m_data.reset(p);

	m_capacity = new_cap;
}
/*========================================================================================================*/
//Fix Heap
template<typename ValueType , typename Compare >
void PQ< ValueType, Compare >::fix_heap() 	
{
	size_type startIndex = (m_length+1)/2;

	for(size_type i = startIndex; i > 0; i --)
	{
		move_down(i);
	}

	m_sorted = true;
}
/*========================================================================================================*/
//Pop === Working!
template<typename ValueType , typename Compare >
void PQ< ValueType, Compare >::pop()
{
	//m_data[m_length + 1] = null;
	std::swap(m_data[m_length], m_data[1]);
	m_data[m_length] = 0;
	move_down(1);
	//fix_heap();
	m_length--;
}
/*========================================================================================================*/
//Top === Working!
template<typename ValueType , typename Compare >
typename PQ< ValueType, Compare >::const_reference PQ< ValueType, Compare >::top(void) 	
{
	return m_data[1];
}
/*========================================================================================================*/
//Initializer list constructor ==Working!
template<typename ValueType, typename Compare>
PQ< ValueType, Compare >::PQ(const std::initializer_list< ValueType > & ilist, const Compare & cmp) : m_length(0)	
												    												, m_sorted (false)
												    												, m_cmp (cmp)
{
	m_capacity = DEFAULT_SIZE;
	
	ValueType* p = new ValueType[m_capacity];
	m_data = std::unique_ptr< ValueType[] >(p);	

	//typename std::initializer_list<ValueType>::iterator it;
	for (auto it=ilist.begin(); it!=ilist.end(); it++) 
		this->push((ValueType)*it);
}
/*========================================================================================================*/
//Range constructor
template<typename ValueType , typename Compare>
template<typename InputIt >
PQ< ValueType, Compare >::PQ(InputIt first,	InputIt	last, const Compare & cmp): m_length(0)	
																			  , m_sorted (false)
												    						  , m_cmp (cmp)
{
	m_capacity = DEFAULT_SIZE;
	
	ValueType* p = new ValueType[m_capacity];
	m_data = std::unique_ptr< ValueType[] >(p);	
	
	for (auto it=first; it!=last; it++) 
		this->push(*it);
} 	
/*========================================================================================================*/
//Range constructor
template<typename ValueType, typename Compare >
void PQ< ValueType, Compare >::toss(const ValueType & x) 	
{
	//Verificar se pode ser inserido
		//Se não poder, dobrar o tamanho da heap mantendo os elementos atuais intáctos
	if(m_capacity <= m_length + 1)
	{		
		reserve(m_capacity * 2);
	}

	//Inserir x na última posição
	m_data[m_length + 1] = x;
	//atualizar m_length
	m_length++;

	//Verificar sort order
		//Caso não seja a posição correta, fazer operação de move_up até obedecer à regra
	//if(m_sorted == false)
	//{
	//	move_up(m_length);
	//}
	
	fix_heap();	
}








































