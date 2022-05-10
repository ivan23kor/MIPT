#pragma once
#include <iostream>

struct Vector2
{
private:
	float get_angle ();
public:
	float x, y;

	Vector2 ();										// creates a vector (1, 1)
	Vector2 (float _x, float _y);					// creates a vector (x, y)
	
	/*
		Если вы не напишете конструктор копирования, деструктор и оператор присваивания для этого класса,
		то компилятор сгенерируется для них точно такой же код сам.
		
		... в данном случае можно было бы их не реализовывать
	*/
	Vector2 (const Vector2& v);						// creates a vector v
	~Vector2 ();									// deletes the vector

	float operator[] (int index) const;				// returns index-th coordinate of the vector
	Vector2& operator= (const Vector2& other);
	Vector2& operator+= (const Vector2& other);
	Vector2& operator-= (const Vector2& other);
	Vector2 operator+ (const Vector2& other) const;
	Vector2 operator- (const Vector2& other) const;
	float operator* (const Vector2& other) const;	// dot product
	float operator^ (const Vector2& other) const;	// cross product
	Vector2 operator* (float mul) const;			// the vector gets multiplied by the constant mul
	Vector2 operator/ (float div) const;			// the vector gets divided by the constant div
	Vector2 operator-() const;						// returns -v

	/*
		fixit:
		norm , len , squared_len , get_rotate_one должны быть константными
		
		rotate_itself должен возвращать ссылку на измененного себя
	*/
	Vector2 normal () const;
	Vector2 norm () const;
	float len () const;
	float squared_len () const;
	Vector2& rotate_itself (float angle);
	Vector2 get_rotated_one (float angle) const;
};

std::ostream& operator<< (std::ostream& stream, const Vector2& v);
std::istream& operator>> (std::istream& stream, Vector2& v);

Vector2 operator* (float mul, const Vector2& v);
