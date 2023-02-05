// template Dynamic Array.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

/*
	Создать шаблонный класс динамического массива (см. урок №2, с. 56). 
	Добавить в этот класс методы для добавления элемента к массиву и 
	удаления элемента из массива.
*/

/*
	В ранее созданный шаблонный класс динамического массива добавить 
	метод для расчета суммы элементов этого массива. Создать объекты 
	этого класса, инкаспулирующие массивы типа int, double, char и Point.
	Point - это класс, содержащий 2 поля (координаты точки): int x и int y.
*/

class Point
{
	int x;
	int y;
public:
	Point() : x{0}, y{0} 
	{
		std::cout << "Default constructor for class Point\n";
	}

	// если я ввожу здесь два параметра - у меня тогда не работает ф-ия fill_randome
	Point(float a) : x{ (int)a }, y{ (int)a+1 } 
	{
		std::cout << "Constructor with paramaters for class Point\n";
	}
	
	int get_x() const { return x; }  // геттер для получения поля х
	int get_y() const { return y; }  // геттер для получения поля у
	void set_x(int xP) { x = xP; }   // сеттер для утсановки поля х
	void set_y(int yP) { y = yP; }   // сеттер для утсановки поля у

	~Point()
	{
		std::cout << "Destructor for class point\n";
	}
};

template <typename T> class DynArray  // шаблонный класс Динамический Массив
{
	T* arr;    // указатель на массив
	int size;  // размер массива
public:
	DynArray() : arr{nullptr}, size{0}
	{
		std::cout << "Constructor by defoult for class DynArray\n";
	}

	DynArray(int sizeP) : arr{ new T[sizeP] }, size{sizeP}  // конструктор с параметрами
	{
		std::cout << "Constructor with parameters for class DynArray\n";
	}

	DynArray(const DynArray& obj)  // конструктор копирования
		: arr{ new T[obj.size] }, size{ obj.size }
	{
		std::cout << "COPY CONSTRUCTOR";
		for ( int i{ 0 }; i < size; ++i)
		{
			arr[i] = obj.arr[i];
		}
	}	

	void print_element();            // метод - вывод на экран
	void fill_random();              // метод для заполнения массива рандомными числами
	float sum_arr();                 // метод для суммирования элементов массива
	void add_element(T element);     // метод - добавление еще одного эл-та
	void delete_element(int index);  // метод - удаление определенного эл-та
	void fill_by_user();             // метод для заполнения массива пользователем
	
	~DynArray()
	{
		std::cout << "Destructor for class DynArray\n";
		delete[] arr;  // освобождаем память
	}
};

template <typename T> void DynArray<T>::fill_random()   // метод для заполнения массива рандомными числами
{
	T x;
	for (int i{ 0 }; i < size; ++i)
	{
		x = rand() % 10; 
		arr[i] = x;
	}
}

template <typename T> void DynArray<T>::print_element()  // метод для вывода на экран
{
	for (int i{ 0 }; i < size; ++i)
	{
		std::cout << arr[i] << ' ';
	}
}

template <class T> float DynArray<T>::sum_arr()  // метод для суммирования эл-тов массива
{
	float sum = 0;
	for (int i{ 0 }; i < size; ++i)
	{
		sum += arr[i];
	}
	return sum;
}

template <typename T> void DynArray<T>::add_element(T el)  // метод - добавление еще одного элементата
{
	T* temp = new T[size + 1];      // выделить новую память на размер size + 1
	for (int i = 0; i < size; i++)
	{
		temp[i] = arr[i];           // присвоили новым элементам старые
	}
	temp[size] = el;                // в последний элемент - новый добавленный вписали значение
	delete[] arr;                   // удаление старой памяти
	arr = temp;
	size++;                         // увеличиваем размер массива
}

template <typename T> void DynArray<T>::delete_element(int index)  // метод - удаление определенного элемента
{
	for (int i = 0; i < size; i++)
	{
		if (i >= index)                 // если эллемент >= индексу, то приравниваем
		{                               // текущий эллемент к следующему
			arr[i] = arr[i + 1];
		}                               // если элемент < индекса - оставляем его, как есть		
	}
	size--;                             // уменьшаем размер массива
}

// методы для заполнения массивов путем ввода пользователем
// здесь у меня не получается сделать один универсальный метод для числовых/символьных
// массивов и для массива точек Point - получается два перегруженных

template <typename T> 
void DynArray<T>::fill_by_user()    // метод для заполнения массива (числового или символьного)
{
	T x = 0;
	for (int i = 0; i < size; ++i) 
	{
		std::cout << "Put element: ";
		std::cin >> x;
		arr[i] = x;
	}	
}

template <> 
void DynArray<Point>::fill_by_user()   // метод для заполнения массива с элементами из класса Point
{
	int x, y;
	for (int i = 0; i < size; ++i)
	{
		std::cout << "Enter x and y: ";
		std::cin >> x;
		arr[i].set_x(x);
		std::cin >> y;
		arr[i].set_y(y);
	}
}

std::ostream& operator<<(std::ostream& out, Point& obj)  // перегруженный оператор <<
{
	out << "x: " << obj.get_x() << " y: " << obj.get_y() << std::endl;
	return out;
}

float operator+=(float& x, Point& obj)  // метод перегрузки += (для суммирования всех точек Point)
{                                       
	x = x + obj.get_x() + obj.get_y();  
	return x;
}

int main()
{	
	int size = 4;
	srand(time(0));

	DynArray<int> arr1{ size };       // создаем объект типа int		
	arr1.fill_random();               // заполнение массива случайными числами
	arr1.print_element();             // вывод на экран
	std::cout << "\nAdd element: \n";
	arr1.add_element(7);              // добавление эл-та "7"
	arr1.add_element(8);              // добавление эл-та "8"
	arr1.print_element();             // вывод на экран
	std::cout << "\nSum = "           // вывод на экран суммы элементов
		<< arr1.sum_arr() << '\n';  
	
	DynArray<char> arr2(size);        // создаем объект типа char
	arr2.fill_random();               // заполнение массива случайными числами
	arr2.print_element();             // вывод на экран
	std::cout << "\nAdd element: \n";
	arr2.add_element('a');            // добавление эл-та "а"
	arr2.print_element();             // вывод на экран
	std::cout << "\nSum = " << arr2.sum_arr() << '\n';
	
	DynArray<Point> arr4{ size };     // массив из 3-ех элементов типа Point
	arr4.fill_random();               // заполнение массива случайными числами
	arr4.print_element();             // вывод на экран
	std::cout << "\nSum = " << arr4.sum_arr() << '\n';

	// для ввода пользователем:
	std::cout << "------------------------------------------------";
	DynArray<int> arr5{ 3 };
	arr5.fill_by_user();
	arr5.print_element();
	std::cout << "\nSum = " << arr5.sum_arr() << std::endl;
	std::cout << "------------------------------------------------";
	DynArray<char> arr7{ 3 };
	arr7.fill_by_user();
	arr7.print_element();
	std::cout << "\nSum = " << arr7.sum_arr() << std::endl;
	std::cout << "------------------------------------------------";
	DynArray<Point> arr6{ 3 };
	arr6.fill_by_user();
	arr6.print_element();
	std::cout << "\nSum = " << arr6.sum_arr() << std::endl;


	return 0;
}

