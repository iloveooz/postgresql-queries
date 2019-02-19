
	#include <string>
	#include <vector>
	#include <iostream>
	#include <fstream>
	
	#include <pqxx/pqxx>
	
	int main(int argc, char ** argv) {
		
		std::ifstream input("login.txt"); // чтение из файла
		
		if (!input) {
			std::cout << "Не могу открыть файл!" << '\n';
			return -1;
		}
		
		std::vector <std::string> credentials;
		
		while (!input.eof()) {
			std::string line;
			getline(input, line);
			credentials.push_back(line);
		}
		
		std::cout << "User: " << credentials[0] << ", pass: " << credentials[1] << '\n';
		
		std::string connection_string("host=127.0.0.1 port=5432 dbname=example_base user=" + credentials[0] + " password=" + credentials[1]);
		
		pqxx::connection con(connection_string.c_str()); // соединение с базой
		
		pqxx::work WORK(con); // работа с базой
		
		pqxx::result res = WORK.exec("SELECT * FROM countries");
		
		if (res.size() < 1) { // res - вектор векторов
			std::cout << "Пустая таблица или ошибка просмотра таблицы" << '\n';
		}
		
		std::cout << "country\t" << "коммент\t" << '\n';
		
		for (unsigned int i = 0; i < res.size(); i++) {
			std::cout << res[i][0] << '\t' << res[i][1] << '\t' << res[i][2] << '\n';
		}
		
		return 0;
	}
