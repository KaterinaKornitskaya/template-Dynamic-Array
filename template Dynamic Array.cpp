// template Dynamic Array.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

/*
	Создать шаблонный класс динамического массива (см. урок №2, с. 56). 
	Добавить в этот класс методы для добавления элемента к массиву и 
	удаления элемента из массива.
*/

template <typename T> class DynArray  // шаблонный класс Динамический Массив
{
	T* arr;    // указатель на массив
	int size;  // размер массива
public:
	DynArray() : arr{nullptr}, size{0} {}

	// конструктор с параметрами
	DynArray(T sizeP) : arr{ new T[sizeP] }, size{sizeP} {}

	DynArray(const DynArray& obj) // конструктор копирования
		: arr{ new T[obj.size] }, size{ obj.size }
	{
		for ( int i{ 0 }; i < size; ++i)
		{
			arr[i] = obj.arr[i];
		}
		std::cout << "COPY!!!";
	}	

	void fill_elements()  // метод - добавление эл-тов в массив
	{			
		T x = 0;                        // для заполнения массива пользователем
		for (int i = 0; i < size; ++i)  // до тех пор, пока < size
		{                               // (size передаем в конструкторе)			
			std::cout << "Put element: ";
			std::cin >> x;
			arr[i] = x;
		}				
	}

	void add_new(T elem, int &size)  // метод - добавление еще одного эл-та
	{
		T* temp = new T[size + 1];   // выделить новую память на размер size + 1
		for (int i = 0; i < size; i++)
		{
			temp[i] = arr[i];        // присвоили новым эл-там старые
		}
		temp[size] = elem;           // в последний эл-т - новый добавленный вписали значение
		delete[] arr;                // удаление старой памяти
		arr = temp;
		size++;                      // увеличиваем размер массива
	}

	void delete_elem(int index, int& size)  // метод - удаление определенного эл-та
	{		
		for (int i = 0; i < size; i++)
		{			
			if (i >= index)                 // если эл-т >= индексу, то приравниваем
			{                               // текущий эл-т к следующему
				arr[i] = arr[i + 1];
			}                               // если эл-т < индекса - оставляем его, как есть		
		}
		size --;                            // уменьшаем размер массива
	}

	void print_element(int &size)  // метод - вывод на экран
	{
		for (int i{ 0 }; i < size ; ++i)
		{
			std::cout << arr[i] << ' ';
		}		
	}
	
	T get_size()  // геттер для получения размера
	{
		return size;
	}

	~DynArray()
	{
		delete[] arr;  // освобождаем память
	}
};

int main()
{	
	int size = 3;
	DynArray<int> arr1(size);  // создаем конкретный объект int
		
	arr1.fill_elements();      // заполнение массива
	arr1.print_element(size);  // вывод на экран
	std::cout << std::endl;
	
	// дальше повтор ф-ий для видимости результатов
	std::cout << "\nAdd element: \n";
	arr1.add_new(7, size);      // добавление эл-та
	arr1.print_element(size);   // вывод на экран
	std::cout << std::endl;
	arr1.add_new(8, size);      // добавление эл-та
	arr1.print_element(size);   // вывод на экран
	std::cout << std::endl;
	arr1.add_new(9, size);      // добавление эл-та
	arr1.print_element(size);   // вывод на экран
	std::cout << "\nDelete element: \n";
	arr1.delete_elem(0, size);  // удаление эл-та
	arr1.print_element(size);   // вывод на экран
	std::cout << std::endl;
	arr1.delete_elem(0, size);  // удаление эл-та
	arr1.print_element(size);   // вывод на экран

	// аналогично для объекта char:
	DynArray<char> arr2(size);  // создаем конкретный объект char
	std::cout << std::endl;
	arr2.fill_elements();
	arr2.print_element(size);
	std::cout << std::endl;
	std::cout << "\nAdd element: \n";
	arr2.add_new('a', size);
	arr2.print_element(size);   
	std::cout << "\nDelete element: \n";
	arr2.delete_elem(1, size);
	arr2.print_element(size);   

	return 0;
}

