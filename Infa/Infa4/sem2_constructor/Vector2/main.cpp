#include "vector2.h"
#include <iostream>

const float PI = 3.14159f;

int main(int argc, char const *argv[])
{
	// default_constructor
	Vector2 default_constructor;
	std::cout << "Constructed a vector (1, 1) " << default_constructor;

	// constructor_3_4
	Vector2 constructor_3_4 (3, 4);
	std::cout << "Constructed a vector (3, 4) " << constructor_3_4;

	// constructor_with_another_vector
	Vector2 constructor_with_another_vector (constructor_3_4);
	std::cout << "Constructed a vector (3, 4) using already existing one "  << constructor_with_another_vector;

	// index_and_cin_check
	std::cout << "Input a vector to check the index operator.\n";
	Vector2 index_and_cin_check;
	std::cin >> index_and_cin_check;
	std::cout << "vector[0] = " << index_and_cin_check[0] << ", vector[1] = " << index_and_cin_check[1] << ".\n";

	// equal_check
	Vector2 equal_check;
	equal_check = constructor_3_4;
	std::cout << "v = (1, 1) v2 = (3, 4), v = v2, v - ?" << equal_check;

	// equal_plus_check
	Vector2 equal_plus_check;
	equal_plus_check += equal_check;
	std::cout << "v = (1, 1), v2 = (3, 4), v += v2, v - ?" << equal_plus_check;

	// equal_minus_check
	Vector2 equal_minus_check;
	equal_minus_check -= equal_check;
	std::cout << "v = (1, 1), v2 = (3, 4), v -= v2, v - ?" << equal_minus_check;

	// +, -, *, / check
	Vector2 v1(1, 2);
	Vector2 v2(-1, -2);
	Vector2 v3(7, 8.7);
	Vector2 v4;
	v4 = 2 * v1 / 2 + .5 * v2 * 2 - v3 * 7.1;
	std::cout << "2 * (1, 2) / 2 + .5 * (-1, -2) * 2 - (7, 8.7) * 7.1 = " << v4;

	// dot product check
	Vector2 scalar1(1, 1);
	Vector2 scalar2(2, 2);
	std::cout << "((1, 1), (2, 2)) = " << scalar1 * scalar2 << "\n";

	// cross product check
	Vector2 vector1(1, 0);
	Vector2 vector2(0, 2);
	std::cout << "((1, 0) x (0, 2)) = " << (vector1 ^ vector2) << "\n";

	// operator- (which returns -v) check
	Vector2 minus_check(7.3, -11);
	std::cout << "v = (7.3, -11), -v = " << -minus_check;

	// normal and norm check
	Vector2 norm_check;
	std::cout << "v = (1, 1), v2 is normal to n, n2 = " << norm_check.normal();
	std::cout << "v = (1, 1), v.norm() = " << norm_check.norm();

	// len and squared_len check
	Vector2 len_check(5, 12);
	std::cout << "v = (5, 12), v.len() = " << len_check.len()
	<< "\nv = (5, 12), v.squared_len() = " << len_check.squared_len() << "\n";

	// rotate check
	Vector2 rotate_check(1, 1);
	std::cout << "v = (1, 1), rotate 90 degrees, v' after such rotation (rotate_itself): " << rotate_check.rotate_itself(PI / 2) << "\n";
	std::cout << "v' = (-1, 1), rotate 90 degrees, v'' after such rotation (get_rotated_one): " << rotate_check.get_rotated_one(PI / 2) << "\n";

	return 0;
}
