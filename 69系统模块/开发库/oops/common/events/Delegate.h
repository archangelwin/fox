#ifndef _Delegate_H_
#define _Delegate_H_

/**
 * Example

 class Test1
 {
 public:
	unsigned int Print(unsigned int data)
	{
		cout << "Test1::Print "<< data << endl;
		return 0;
	}
 }; // Test1

 unsigned int Print(unsigned int data)
 {
	cout << "Print " << data << endl;
	return 0;
 }

 int main(int argc, char* argv[])
 {
	Test1 t;
	CDelegate<Test1> d1(&t, &Test1::Print);
	CDelegate<void> d2(&Print);

	d1.Invoke(1);
	d2.Invoke(2);
	return 0;
 }

 */

/**
 * ί�нӿ�
 */
class IDelegate
{
public:
	virtual ~IDelegate() {}
	/** ί��ִ�� */
	virtual unsigned int invoke(unsigned int data) = 0;
	/** �ж��Ƿ���� */
	virtual bool operator== (const IDelegate &rhs) = 0;
	/** �ж��Ƿ���� */
	bool operator== (const IDelegate *rhs)
	{
		return (*this == *rhs);
	} // operator==
}; // IDelegate

/**
 * ���Ա����ί��
 */
template<typename T>
class CDelegate 
	: public IDelegate
{
public:
	CDelegate(T *pT, unsigned int (T::*pFunc)(unsigned int))
		: m_pT(pT), m_pFunc(pFunc)
	{};

	CDelegate()
		: m_pT(0), m_pFunc(0)
	{};
	
	unsigned int invoke(unsigned int data)
	{
		return (m_pT->*m_pFunc)(data);
	} // invoke

	void bind(T *pT, unsigned int (T::*pFunc)(unsigned int))
	{
		m_pT    = pT;
		m_pFunc = pFunc;
	} // bind

	bool operator== (const IDelegate &rhs)
	{
		if (this == &rhs)
		{
			return true;
		}

		CDelegate<T>* pRhs = (CDelegate<T>*)&rhs;

		if (pRhs == 0)
		{
			return false;
		}

		return pRhs->m_pT == m_pT && pRhs->m_pFunc == m_pFunc;
	} // operator==

	bool operator== (const CDelegate<T> &rhs)
	{
		if (this == &rhs)
		{
			return true;
		}

		return rhs.m_pT == m_pT && rhs.m_pFunc == m_pFunc;
	} // operator==
private:
	T*           m_pT;
	unsigned int (T::*m_pFunc)(unsigned int);
}; // CDelegate

/**
* һ�㺯��ί��
*/
template<>
class CDelegate<void> 
	: public IDelegate
{
public:
	CDelegate(unsigned int (*pFunc)(unsigned int))
		: m_pFunc(pFunc)
	{};

	CDelegate()
		: m_pFunc(0)
	{};

	unsigned int invoke(unsigned int data)
	{
		return (*m_pFunc)(data);
	} // invoke

	void bind(unsigned int (*pFunc)(unsigned int))
	{
		m_pFunc = pFunc;
	} // bind

	bool operator== (const IDelegate &rhs)
	{
		if (this == &rhs)
		{
			return true;
		}

		CDelegate<void>* pRhs = (CDelegate<void>*)&rhs;

		if (pRhs == 0)
		{
			return false;
		}

		return pRhs->m_pFunc == m_pFunc;
	} // operator==

	bool operator== (const CDelegate<void> &rhs)
	{
		if (this == &rhs)
		{
			return true;
		}

		return rhs.m_pFunc == m_pFunc;
	} // operator==
private:
	unsigned int (*m_pFunc)(unsigned int);
}; // CDelegate

#endif // _Delegate_H_