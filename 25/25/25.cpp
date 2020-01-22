#include <iostream>
#include <vector>

struct student
{
	char name[100];
	int group;
	int sec[5] = { 0 };
};

int main() {
	setlocale(LC_ALL, "russian");

	student stud[10] = { "Ivanov I.V.",1,{5,3,5,3,3},
		"Petrov P.P.",1,{3,5,4,3,2},
		"Fedorov A.I.",2,{3,4,5,2,2},
		"Sidorov V.R.",2,{5,0,0,3,0},
		"Alexandrov P.W.",3,{5,5,4,3,3}, 
		"Sergeev V.A.",1,{5,0,3,2,0},
		"Valerin V.L.",1,{4,0,1,0,5},
		"Nikitin N.A.",2,{2,2,0,5,1},
		"Artemov S.R.",2,{0,0,1,0,2},
		"Dmitrow A.H.",3,{5,2,0,4,0}
	};
	bool flag = true;
	std::vector<student> assessment;

	for (int i = 0; i < 10; i++) // Проверка на оценки ниже 3
	{
		if (stud[i].sec[0] < 3 || stud[i].sec[1] < 3 || stud[i].sec[2] < 3 || stud[i].sec[3] < 3 || stud[i].sec[4] < 3) {
			assessment.push_back(stud[i]);
			flag = false;
		}
	}
	for (int i = 0; i < assessment.size(); i++) // Как метод пузырька, сравниваются буквы в ascii
		for (int k = 0; k < assessment.size() - i - 1; k++) // Так как последний элемент можно не трогать, метод пузырька
			if (strcmp(assessment[k].name, assessment[k + 1].name) > 0)
			{
				student temp = assessment[k];
				assessment[k] = assessment[k + 1];
				assessment[k + 1] = temp;
			}

	if (flag)std::cout << "Нет студентов с оценками < 3" << std::endl;
	else for (int i = 0; i < assessment.size(); i++)	std::cout << assessment[i].name << ' ' << assessment[i].group << std::endl;
}

