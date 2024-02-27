#include <iostream> 
#include <fstream> 
#include <cstring>

class MyString {

private:
	char* data;

public:

	// Конструкторы 
	MyString();
	MyString(const char* str);
	MyString(const MyString& other);

	// Деструктор 
	~MyString();

	// Метод ввода исходной строки 
	void set();

	// Метод изменения исходной строки и записи в файл 
	void update();

	// Метод вывода на экран 
	void print() const;

	// Метод удаления точек, если длина строки больше пяти символов 
	void removeDotsIfLong();
};

// Реализация методов класса 

MyString::MyString() {
	data = nullptr;
	std::cout << "Вызывается конструктор по умолчанию." << std::endl;
}

MyString::MyString(const char* str) {
	data = new char[strlen(str) + 1];
	strcpy(data, str);
	std::cout << "Вызван параметризованный конструктор." << std::endl;
}

MyString::MyString(const MyString& other) {
	data = new char[strlen(other.data) + 1];
	strcpy(data, other.data);
	std::cout << "Вызван конструктор копирования." << std::endl;
}

MyString::~MyString() {
	delete[] data;
	std::cout << "Вызван деструктор." << std::endl;
}

void MyString::set() {
	char buffer[100];
	std::cout << "Введите строку: ";
	std::cin.getline(buffer, 100);
	data = new char[strlen(buffer) + 1];
	strcpy(data, buffer);
}

void MyString::update() {
	std::ofstream outFile("output.txt");
	if (strlen(data) > 5) {
		outFile << data << std::endl;
		for (size_t i = 0; i < strlen(data); ++i) {
			if (data[i] == '.') {
				for (size_t j = i; j < strlen(data); ++j) {
					data[j] = data[j + 1];
				}
				--i;
			}
		}
	}
	outFile << data << std::endl;
	outFile.close();

	std::cout << "Строка обновлена. Изменения сохранены в файл." << std::endl;
}

void MyString::print() const {
	std::cout << "Строка: " << data << std::endl;
}

void MyString::removeDotsIfLong() {
	if (strlen(data) > 5) {
		for (size_t i = 0; i < strlen(data); ++i) {
			if (data[i] == '.') {
				for (size_t j = i; j < strlen(data); ++j) {
					data[j] = data[j + 1];
				}
				--i;
			}
		}
		std::cout << "Точки удалены из строки." << std::endl;
	}
	else {
		std::cout << "Длина строки не должна превышать пяти символов. Точки не удаляются." << std::endl;
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	// Демонстрационная программа 
	MyString str1;
	str1.set();
	str1.print();

	MyString str2("hi my name is Kira . . . . .... . . .. ");
	str2.print();

	MyString str3 = str2;
	str3.print();

	str2.update();
	str2.print();

	return 0;
}
