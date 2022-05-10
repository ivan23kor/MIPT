#include "vector2.h"
#include <math.h>

/*
	fixit:
	Используйте константы вместо define:
	
	const float EPSILON = 1e-5f;
*/
const float EPSILON = 1e-5f;
const float PI = 3.14159f;

float Vector2::get_angle ()
{
	float length = this->len();
	float sign = 1;
	Vector2 temp(this->norm());

	if (y < -EPSILON)
		sign = -1.0;

	if (length > EPSILON)
		return sign * acos (temp.x);
	else
		return sign * PI / 2;
}

Vector2::Vector2 ()
{
	/*
		обычно инициализируют нулями
	*/
	x = 1;
	y = 1;
}

Vector2::Vector2 (float _x, float _y)
{
	x = _x;
	y = _y;
}

Vector2::Vector2 (const Vector2& v)
{
	x = v.x;
	y = v.y;
}

Vector2::~Vector2 () {}

float Vector2::operator[] (int index) const
{
	if (index == 0)
		return x;
	else if (index == 1)
		return y;
	else
	{
		/*
			как выриант написать что-то в консоль.
			можно ещё бросить исключение ... про которое не говорили пока на семинаре.
			либо можно не делать проверки в пользу быстродействия.
			
			ещё можно было бы написать так:
			return &x[index];
			
			работает, т.к. x и y последовательно в памяти лежат
		*/
		std::cout << "Invalid index (" << index << ")!\n";
		return 0.0;
	}
}

Vector2& Vector2::operator= (const Vector2& other)
{
	x = other.x;
	y = other.y;

	return *this;
}

Vector2& Vector2::operator+= (const Vector2& other)
{
	x += other.x;
	y += other.y;

	return *this;
}

Vector2& Vector2::operator-= (const Vector2& other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}

Vector2 Vector2::operator+ (const Vector2& other) const
{
	/* fixit:
	Лучше написать в одну строчку:
	return Vector2(x + other.x, y + other.y);
	
	То же самое поправьте дальше по тексту для всех бинарных константных методов
	*/
	return Vector2 (x + other.x, y + other.y);
}

Vector2 Vector2::operator- (const Vector2& other) const
{
	return Vector2 (x - other.x, y - other.y);
}

float Vector2::operator* (const Vector2& other) const
{
	return x * other.x + y * other.y;
}

float Vector2::operator^ (const Vector2& other) const
{
	return x * other.y - y * other. x;
}

Vector2 Vector2::operator* (float mul) const
{
	return Vector2 (x * mul, y * mul);
}

Vector2 Vector2::operator/ (float div) const
{
	if (div > EPSILON)
		return Vector2 (x / div, y / div);
	else
	{
		std::cout << "Can not divide by zero!\n";
		return *this;
	}
}

Vector2 Vector2::operator-() const
{
	/*
		return Vector2(-x, -y);
	*/
	return Vector2(-x, -y);
}

Vector2 Vector2::normal() const
{
	return Vector2 (-y, x);
}

Vector2 Vector2::norm () const
{
	/*
	Обычно делает два метода:
	один константный norm(), который не меняет переменные структуры, а второй модифицирующий
	makeNorm() , например.
	
	Ещё называют их unit() и makeUnit()
	*/
	float length = this->len();
	Vector2 temp(*this);

	if (length > EPSILON)
	{
		temp.x /= length;
		temp.y /= length;
	}
	else
		std::cout << "The vector is a null vector!\n";

	return temp;
}

float Vector2::len () const
{
	return sqrt(x * x + y * y);
}

float Vector2::squared_len () const
{
	/*
		Не круто так делать. Операцию нахождения корня дорогая + 
		здесь у вас ошибки вычисления ненужные.
		
		Лучше написать squared как x * x + y * y,
		а len уже как sqrt(squared_len())
	*/
	return x * x + y * y;
}

Vector2& Vector2::rotate_itself (float angle)
{
	/*
	Забыли ф-лу для поворота? :)
	https://ru.wikipedia.org/wiki/%D0%9C%D0%B0%D1%82%D1%80%D0%B8%D1%86%D0%B0_%D0%BF%D0%BE%D0%B2%D0%BE%D1%80%D0%BE%D1%82%D0%B0
	
	Вычисление арккосинуса и корня - дорогие.
	Умножение - дешевое.
	*/
	float resulting_angle = this->get_angle() + angle;
	float length = this->len();

	this->x = cos (resulting_angle) * length;
	this->y = sin (resulting_angle) * length;

	return *this;
}

Vector2 Vector2::get_rotated_one (float angle) const
{
	/*
		Можно не копировать почти тот же самый код, а написать
		return Vector2(x, y).rotate_itself(angle);
		
		Хотя на мой взгляд название слишком длинное: из правильной сигнатуры метода итак ясно,
		что Vector2& rotate(float angle) поворачивает себя на угол, а
		
		Vector2 getRotated(float angle) const 
		себя не меняет, а возвращает повернутый угол
	*/
	/*Vector2 temp(*this);
	float resulting_angle = this->get_angle() + angle;
	float length = this->len();

	temp.x = cos (resulting_angle) * length;
	temp.y = sin (resulting_angle) * length;

	return temp;*/
	return Vector2 (x, y).rotate_itself(angle);
}

std::ostream& operator<< (std::ostream& stream, const Vector2& v)
{
	stream << "( " << v.x << ", " << v.y << " )\n";
	return stream;
}

std::istream& operator>> (std::istream& stream, Vector2& v)
{
	stream >> v.x;
	stream >> v.y;

	return stream;
}

Vector2 operator* (float mul, const Vector2& v)
{
	return Vector2 (v.x * mul, v.y * mul);
}
