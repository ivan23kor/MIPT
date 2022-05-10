#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define N 3
#define EPSILON 0.0000001

class Exception
{
protected:
	std::string where;
	std::string what;
	int line;
private:
	Exception (const std::string where_happened, const std::string what_happened, int line_happened)
	{
		where = where_happened;
		what = what_happened;
		line = line_happened;
	}
};

template <typename data_T>
class CVector
{
private:
	int dimension;
	data_T * data;
public:
	CVector ();
	CVector (int dim);
	CVector (const CVector & v);
	~CVector ();

	data_T &operator[] (int i);
	void operator= (const CVector <data_T> & v);
	void operator+= (const CVector <data_T> & v);
	void operator-= (const CVector <data_T> & v);
	
	int operator* (const CVector <data_T> & v);
	double veclen ();
	double operator^ (CVector <data_T> & v);

	CVector <data_T> operator+ (const CVector <data_T> & v);
	CVector <data_T> operator- (const CVector <data_T> & v);
	CVector <data_T> & operator* (int mul);
	CVector <data_T> & operator/ (int div);
	
	template <typename data_X>
	friend std::ostream & operator<< (std::ostream & stream, const CVector <data_X> & v);
	template <typename data_X>
	friend std::istream & operator>> (std::istream & stream, const CVector <data_X> & v);
	
	void norm ();
};

template <typename data_T>
CVector <data_T>::CVector ()
{
	dimension = N;
	assert (data = new data_T [N]);
}

template <typename data_T>
CVector <data_T>::CVector (int dim)
{
	dimension = dim;
	assert (data = new data_T [dim]);
}

template <typename data_T>
CVector <data_T>::CVector (const CVector <data_T>& v)
{
	dimension = v.dimension;
	assert (data = new data_T [dimension]);
	for (int i = 0; i < dimension; i++)
		data[i] = v.data[i];
}

template <typename data_T>
CVector <data_T>::~CVector ()
{
	delete[] data;
	data = NULL;
}

template <typename data_T>
data_T& CVector <data_T>::operator[] (int i)
{
	assert ((i < dimension) && (i >= 0));
	return data[i];
}

template <typename data_T>
void CVector <data_T>::operator= (const CVector <data_T>& v)
{
	assert ((dimension == v.dimension) && (dimension));
	for (int i = 0; i < dimension; i++)
	{
		data[i] = v.data[i];
	}
}

template <typename data_T>
void CVector <data_T>::operator+= (const CVector <data_T>& v)
{
	dimension = v.dimension;
	for (int i = 0; i < dimension; i++)
	{
		data[i] += v.data[i];
	}
}

template <typename data_T>
void CVector <data_T>::operator-= (const CVector <data_T>& v)
{
	dimension = v.dimension;
	for (int i = 0; i < dimension; i++)
	{
		data[i] -= v.data[i];
	}
}

template <typename data_T>
int CVector <data_T>::operator* (const CVector <data_T> & v)
{
	int scalar = 0;

	for (int i = 0; i < dimension; i++)
	{
		scalar += this->data[i] * v.data[i];
	}

	return scalar;
}

template <typename data_T>
double CVector <data_T>::veclen ()
{
	double square = 0.0;

	for (int i = 0; i < dimension; i++)
		square += this->data[i] * this->data[i];

	return sqrt (square);
}

template <typename data_T>
double CVector <data_T>::operator^ (CVector <data_T> & v)
{
	return ((*this) * v)/(this->veclen ()) / (v.veclen ()); 	
}

template <typename data_T>
CVector <data_T> CVector <data_T>::operator+ (const CVector <data_T>& v)
{
	CVector <data_T> temp(dimension);

	for (int i = 0; i < dimension; i++)
		temp.data[i] = this->data[i] + v.data[i];

	return temp;
}

template <typename data_T>
CVector <data_T> CVector <data_T>::operator- (const CVector <data_T>& v)
{
	CVector <data_T> temp(dimension);

	for (int i = 0; i < dimension; i++)
		temp.data[i] = this->data[i] - v.data[i];

	return temp;
}

template <typename data_T>
CVector <data_T>& CVector <data_T>::operator* (int mul)
{
	for (int i = 0; i < dimension; i++)
		this->data[i] *= mul;

	return *this;
}

template <typename data_T>
CVector <data_T>& CVector <data_T>::operator/ (int div)
{
	for (int i = 0; i < dimension; i++)
		this->data[i] /= div;

	return *this;
}

template <typename data_X>
std::ostream & operator<< (std::ostream & stream, const CVector <data_X> & v)
{
	stream << "(";

	for (int i = 0; i < v.dimension - 1; i++)
		stream << v.data[i] << ", ";
	stream << v.data[i] << ")\n";

	return stream;
}

template <typename data_X>
std::istream & operator>> (std::istream & stream, const CVector <data_X> & v)
{
	for (int i = 0; i < v.dimension - 1; i++)
		stream >> v.data[i];

	return stream;
}

template <typename data_T>
void CVector <data_T>::norm ()
{
	double length_sqr = 0.0;
	double length = 0.0;

	for (int i = 0; i < dimension; i++)
		length_sqr += (this->data[i]) * (this->data[i]);

	if ((length_sqr - 1.0 > EPSILON) || (1.0 - length_sqr > EPSILON))
	{
		length = sqrt ((double)length_sqr);
		for (int i = 0; i < dimension; i++)
			this->data[i] = (data_T)((double)this->data[i]/length);
	}
} 