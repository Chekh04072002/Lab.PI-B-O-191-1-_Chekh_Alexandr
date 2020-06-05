МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ  
Федеральное государственное автономное образовательное учреждение высшего образования  
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  
Кафедра компьютерной инженерии и моделирования
<br/><br/>

### Отчёт по лабораторной работе № 6<br/> по дисциплине "Программирование"
<br/>

студента 1 курса группы ПИ-б-о-191(1)  
Чех Александр Семенович 
направления подготовки 09.03.04 "Программная инженерия"  
<br/>

<table>
<tr><td>Научный руководитель<br/> старший преподаватель кафедры<br/> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br/><br/>

Симферополь, 2020
 
 **Цель работы:**
 - **Закрепить навыки разработки многофайловыx приложений;**
 - **Изучить способы работы с API web-сервиса;**
 -  **Изучить процесс сериализации/десериализации данных.**
#### Ход работы:

Вот мой _API_ ключ от _openweathermap.org_
![Изображение№1](https://sun9-11.userapi.com/c854016/v854016279/23e41f/S805BdiLtEs.jpg "Рис.1")

Код программы:
```c++
#include <iostream>
#include <httplib/httplib.h>
#include <nlohmann/json.hpp>


char host[] = "api.openweathermap.org";
char simf_weather[] = "/data/2.5/forecast?q=Simferopol&appid=2f3d38711cb544e16f85c33b6b22a9c7&units=metric";

struct Forecast {
	std::string date;
	std::string weather;
	int temp;
};

void replace(std::string& html, std::string init, std::string final) {
	int init_index = html.find(init);
	html.erase(init_index, init.size());
	html.insert(init_index, final);
}

void replace(std::string& html, std::string init, int final) {
	std::string final_str = std::to_string(final);
	int init_index = html.find(init);
	html.erase(init_index, init.size());
	html.insert(init_index, final_str);
}

void gen_response(const httplib::Request& req, httplib::Response& res) {
	httplib::Client cli(host, 80);
	std::string w_temp;
	std::fstream fin;
	std::vector<Forecast> parsedData;
	fin.open("informer_template.html");
	if (!fin.is_open()) {
		std::cout << "Error" << std::endl;
	}
	else {
		char ch;
		while (fin.get(ch)) {
			w_temp += ch;
		}
	}
	auto result = cli.Get(simf_weather);
	nlohmann::json json_weather = nlohmann::json::parse(result->body);
	for (int i = 0; i < 30; i++) {
		std::string temp_date = json_weather.at("list")[i].at("dt_txt");
		std::string date = temp_date.substr(0, 11);
		bool flag = false;
		for (size_t j = 0; j < parsedData.size(); j++) {
			if (parsedData[j].date == date) {
				flag = true;
				break;
			}
		}
		if (flag) {
			continue;
		}
		else if (parsedData.size() < 5) {
			Forecast element;
			element.date = date;
			element.weather = json_weather.at("list")[i].at("weather")[0].at("icon");
			element.temp = json_weather.at("list")[i].at("main").at("temp");
			parsedData.push_back(element);
		}
	}
	std::string city = json_weather.at("city").at("name");
	replace(w_temp, "{city.name}", city);
	for (size_t i = 0; i < parsedData.size(); i++) {
		replace(w_temp, "{list.dt}", parsedData[i].date);
		replace(w_temp, "{list.weather.icon}", parsedData[i].weather);
		replace(w_temp, "{list.main.temp}", parsedData[i].temp);
	}
	res.set_content(w_temp, "text/html");
	fin.close();
}

int main() {
	httplib::Server svr;
	svr.Get("/", gen_response);
	svr.listen("localhost", 3000);
}
```
Скриншот экрана с демонстрацией работы программы:
![Изображение№1](https://sun9-9.userapi.com/c853420/v853420849/2360b4/l326XHxVAos.jpg "Рис.2")

#### Вывод: Я закрепил навыки разработки многофайловыx приложений. Изучил способы работы с API web-сервиса. Изучил процесс сериализации/десериализации данных.