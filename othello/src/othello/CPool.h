
/**
 **************************************************************************************************************************************************************
 * Objects pool.
 * The simplest memory pool ever made :)
 **************************************************************************************************************************************************************
 * @file   CPool.h
 * @author Antoine Villepreux
 * @date   01/06/2003
 **************************************************************************************************************************************************************/

#ifndef CPOOL_H
#define CPOOL_H

/**************************************************************************************************************************************************************
 * Classes
 **************************************************************************************************************************************************************/

template<class T, int SIZE> class CPool
{
public:

	CPool() : m_size(0)
	{
	}

	~CPool()
	{
		while(m_size>0)
		{
			delete m_pool[m_size-1];
			--m_size;
		}
	}

	T* New()
	{
		if (m_size > 0)
		{
			T* pObject = m_pool[m_size-1];

			m_pool[m_size-1] = 0;
			--m_size;

			return pObject;
		}

		return new T;
	}

	void Delete(T* pObject)
	{
		if (m_size < SIZE)
		{
			m_pool[m_size++] = pObject;
		}
		else
		{
			delete pObject;
		}
	}

private:

	T*  m_pool[SIZE];
	int m_size;
};


/**************************************************************************************************************************************************************/

#endif
