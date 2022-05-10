#define N 100
template <typename T> (template <typename data_T = int> - in case for int only!)
class CVector
{
	data_T* data;
	int size;
public:
	CVector (int vector_size)
	{
		data = new data_T[N];
		size = vector_size;
	}
};

int main ()
{
	CVector <int> vector1;
	CVector <double> vector2;
	CVector <CVector<int>> vector3;
}

template <typename data_T>
data_T& CVector <data_T> :: operator[] (int n)
{
	return data_[n];
}

#include <iostream>

class CVector
{
		int* data;
		int count;
public:
	CVector (int Count)
	{
			data = new int[Count]; 
			count = Count;
	}
	~CVector ()
	{
		delete data;
	}
	int& operator[] (int n)
	{
		try
		{
			if ((n >= 0) && (n < count))
				return data[n];
			throw n;
		}
		catch (int n)
		{
			std::cout << "Error index = " << n << "; size = " << count << "\n";
			throw n;
		}
	}
};

int main ()
{
	try
	{	
		CVector vector (10);
		vector[100] = 0;
		std::cout << vector[1] << "\n";
	}
	catch (int n)
	{
		std::cout << "\n";
	}

	return 0;
}

class CVector
{
private:
	static int count;
public:
	CVector () {};
	~CVector () {};
	void* operator[] (int n) {};
	int get_count () {return count}
};

class CVector_int : CVector
{
private:
	int* data;
public:
	CVector_int ()
	{
		CVector;
		data = new int[10];
	}
	CVector_int (int Count)
	{
		CVector;
		data = new int[count];
	}
	void* operator[] (int i)
	{
		return (void*)(&data[i]);
	}
	~CVector_int ()
	{
		delete data;
	}
};

class CVector_float : CVector
{
private:
	float* data;
public:
	CVector_float ()
	{
		CVector;
		data = new float[10];
	}
	CVector_float (int Count)
	{
		CVector;
		data = new float[count];
	}
	void* operator[] (int i)
	{
		return (void*)(&data[i]);
	}
	~CVector_float ()
	{
		delete data;
	}
};

int main()
{
	CVector_int INT(15);
	CVector_float FLOAT(15);
	std::cout << *(int*)(INT[10]) << *(int*)(FLOAT[10]) << "\n";
	
	return 0;
}