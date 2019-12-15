#include <iostream>
double BMI(double weight, double height) {
	return weight / (height * height);
}
void printBMI(double BMI) {
	if (BMI < 18.5) {
		std::cout << "Underweight";
	}
	else if ( BMI >= 18.5  && BMI < 25.0) {
		std::cout << "Normal";
	}
	else if ( BMI >= 25.0 && BMI < 30.0) {
		std::cout << "Overweight";
	}
	else if(BMI >= 30.0) {
		std::cout << "Obesity";
	}
}
int main() {
	setlocale(LC_ALL, "russian");
		double v, r;
		std::cout << "Введите вес" << std::endl;
		std::cin >> v;
		std::cout << "Введите рост" << std::endl;
		std::cin >> r;
		r = r / 100;
		double bmi = BMI(v, r);
	printBMI(bmi);
}