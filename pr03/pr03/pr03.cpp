#include <iostream>


int main()
{
	setlocale(LC_ALL, "russian");
	int a, b;
	std::cout << "Введите a и b " << std::endl;
	std::cin >> a >> b;
	std::cout << "a+b=" << a + b << std::endl << "a-b=" << a - b << std::endl << "a*b=" << a * b << std::endl << "a/b=" << a / b << std::endl << std::endl;
	double c, d;
	std::cout << "Введите c и d " << std::endl;
	std::cin >> c >> d;
	std::cout << "c+d=" << c + d << std::endl << "c-d=" << c - d << std::endl << "c*d=" << c * d << std::endl << "c/d=" << c / d << std::endl << std::endl;
	int e;
	double i;
	std::cout << "Введите e и i " << std::endl;
	std::cin >> e >> i;
	std::cout << "e+i=" << e + i << std::endl << "e-i=" << e - i << std::endl << "e*i=" << e * i << std::endl << "e/i=" << e / i << std::endl << std::endl;
	double q;
	int w;
	std::cout << "Введите q и w " << std::endl;
	std::cin >> q >> w;
	std::cout << "q+w=" << q + w << std::endl << "q-w=" << q - w << std::endl << "q*w=" << q * w << std::endl << "q/w=" << q / w << std::endl << std::endl;
}
