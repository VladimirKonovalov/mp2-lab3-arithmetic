#include <iostream>

using namespace std;

const int MAX_STACK_SIZE = 100000000;

// ������ �������
template <class ValType>
class TStack {
protected:
	ValType *pVector;
	int Size;       // ������ �������
	int StartIndex; // ������ ������� �������� �������
	ValType& operator[](int pos) const;
public:
	TStack(int s = 10, int si = 0);
	TStack(const TStack &v);                // ����������� �����������
	virtual ~TStack();
	int GetSize() const { return Size; } // ������ �������
	int GetStartIndex() const { return StartIndex; } // ������ ������� ��������
	void IncStartIndex() { StartIndex += 1; }
	void DecStartIndex() { if (StartIndex != 0) StartIndex -= 1; else throw invalid_argument("Stack is empty"); }
	bool IsEmpty(void);
	bool IsFull(void);
	void SetElem(ValType n);
	ValType GetElem(void);
	/*
	bool operator==(const TStack &v) const;  // ���������
	bool operator!=(const TStack &v) const;  // ���������
	TStack& operator=(const TStack &v);     // ������������

	// ��������� ��������
	TStack  operator+(const ValType &val);   // ��������� ������
	TStack  operator-(const ValType &val);   // ������� ������
	TStack  operator*(const ValType &val);   // �������� �� ������
	
	// ��������� ��������
	TStack  operator+(const TStack &v);     // ��������
	TStack  operator-(const TStack &v);     // ���������
	ValType  operator*(const TStack &v);     // ��������� ������������

	// ����-�����
	template <class ValType>
	friend istream& operator>>(istream &in, TStack &v) 
	{
		for (int i = 0; i < v.Size; i++)
			in >> v.pVector[i];
		return in;
	}
	*/
	template <class ValType>
	friend ostream& operator<<(ostream &out, const TStack &v) 
	{
		for (int i = 0; i < v.Size + v.StartIndex; i++)
			out << v[i] << ' ';
		return out;
	}
};

template <class ValType>
TStack<ValType>::TStack(int s, int si = 0) 
{
	if (s > MAX_STACK_SIZE) 
		throw invalid_argument("CONSTRUCTOR: MAX_STACK_SIZE < SIZE");
	
	if (s < 0) 
		throw invalid_argument("CONSTRUCTOR: SIZE < 0");
	
	if (si < 0) 
		throw invalid_argument("CONSTRUCTOR: START INDEX < 0");

	if (!(si < s)) 
		throw invalid_argument("CONSTRUCTOR: START INDEX >= SIZE");
	
	pVector = new ValType[s];
	Size = s;
	StartIndex = si;

	for (int i = 0; i < Size; i++) 
		pVector[i] = ValType();
	
} /*-------------------------------------------------------------------------*/

template <class ValType> //����������� �����������
TStack<ValType>::TStack(const TStack<ValType> &v) 
{
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size];

	for (int i = 0; i < StartIndex; i++) 
		pVector[i] = ValType();

	for (int i = StartIndex; i < Size; i++) 
		pVector[i] = v.pVector[i];
} /*-------------------------------------------------------------------------*/

template <class ValType>
TStack<ValType>::~TStack() 
{
	delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������
ValType& TStack<ValType>::operator[](int pos) const 
{
	if (pos < 0) 
		throw invalid_argument("[] ARGUMENT < 0");
	
	if (!(pos < Size)) 
		throw invalid_argument("[] ARGUMENT > SIZE");
	
	return pVector[pos];
} /*-------------------------------------------------------------------------*/

template <class ValType>
bool TStack<ValType>::IsEmpty(void)
{
	if (GetStartIndex()==NULL)
		return true;
	else
		return false;
} /*-------------------------------------------------------------------------*/

template <class ValType>
bool TStack<ValType>::IsFull(void)
{
	if (GetStartIndex() + 1 == GetSize())
		return true;
	else
		return false;
} /*-------------------------------------------------------------------------*/

template <class ValType>
void TStack<ValType>::SetElem(ValType n)
{
	if (IsFull())
		throw invalid_argument("Stackowerflow");
	if (IsEmpty())
	{
		(*this)[GetStartIndex()] = n;
		IncStartIndex();
	}
	else
		throw invalid_argument("Crash actual index");
} /*-------------------------------------------------------------------------*/

template <class ValType>
ValType TStack<ValType>::GetElem(void)
{
	if (IsEmpty())
		throw invalid_argument("Stack is empty");

	ValType temp;
	DecStartIndex();
	temp = (*this)[GetStartIndex()];
	(*this)[GetStartIndex()] = ValType();

	return temp;
} /*-------------------------------------------------------------------------*/


/*
template <class ValType> // ���������
bool TStack<ValType>::operator==(const TStack &v) const 
{
	if (Size != v.GetSize()) 
	{
		return false;
	}
	if (StartIndex != v.GetStartIndex())
	{
		return false;
	}

	for (int i = StartIndex; i < Size; i++) 
	{
		if (pVector[i] != v.pVector[i]) 
		{
			return false;
		}
	}
	return true;
} /*-------------------------------------------------------------------------*/
/*
template <class ValType> // ���������
bool TStack<ValType>::operator!=(const TStack &v) const 
{
	return !(*this == v);
} /*-------------------------------------------------------------------------*/
/*
template <class ValType> // ������������
TStack<ValType>& TStack<ValType>::operator=(const TStack &v) 
{
	if (this != &v) 
	{
		if (Size != v.GetSize())
		{
			delete[]pVector;
			pVector = new ValType[v.Size];
		}
		Size = v.GetSize();
		StartIndex = v.GetStartIndex();
		for (int i = StartIndex; i < Size; i++) 
		{
			pVector[i] = v.pVector[i];
		}
	}
	return *this;
} /*-------------------------------------------------------------------------*/
/*
template <class ValType> // ��������� ������
TStack<ValType> TStack<ValType>::operator+(const ValType &val) 
{
	for (int i = StartIndex; i < Size; i++) 
		pVector[i] = pVector[i] + val;
	
	return *this;
} /*-------------------------------------------------------------------------*/
/*
template <class ValType> // ������� ������
TStack<ValType> TStack<ValType>::operator-(const ValType &val) 
{
	for (int i = StartIndex; i < Size; i++) 
		pVector[i] = pVector[i] - val;
	
	return *this;
} /*-------------------------------------------------------------------------*/
/*
template <class ValType> // �������� �� ������
TStack<ValType> TStack<ValType>::operator*(const ValType &val) 
{
	for (int i = StartIndex; i < Size; i++) 
		pVector[i] = pVector[i] * val;
	
	return *this;
} /*-------------------------------------------------------------------------*/
/*
template <class ValType> // ��������
TStack<ValType> TStack<ValType>::operator+(const TStack<ValType> &v) 
{
	if ((GetSize() != v.GetSize()) || (GetStartIndex() != v.GetStartIndex())) 
		throw invalid_argument("ADDITION OF VECTORS OF DIFFERENT LENGTH");

	TStack<ValType> result(GetSize(), GetStartIndex());

	for (int i = StartIndex; i < Size; i++) 
		result[i] = pVector[i] + v.pVector[i];
	
	return result;
} /*-------------------------------------------------------------------------*/
/*
template <class ValType> // ���������
TStack<ValType> TStack<ValType>::operator-(const TStack<ValType> &v) 
{
	if ((GetSize() != v.GetSize()) || (GetStartIndex() != v.GetStartIndex())) 
		throw invalid_argument("SUBTRACTION OF VECTORS OF DIFFERENT LENGTH");

	TStack<ValType> result(GetSize(), GetStartIndex());

	for (int i = StartIndex; i < Size; i++)
		result[i] = pVector[i] - v.pVector[i];
	
	return result;
} /*-------------------------------------------------------------------------*/
/*
template <class ValType> // ��������� ������������
ValType TStack<ValType>::operator*(const TStack<ValType> &v) 
{
	if ((GetSize() != v.GetSize()) || (GetStartIndex() != v.GetStartIndex())) 
		throw invalid_argument("MULTIPLICATION OF VECTORS OF DIFFERENT LENGTH");

	ValType result = 0;
	
	for (int i = StartIndex; i < Size; i++) 
		result = result + pVector[i] * v.pVector[i];
		
	return result;
} /*-------------------------------------------------------------------------*/