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
	T* arr;  // указатель на массив
	T size;  // размер массива
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
		T x = 0;  // для заполнения массива пользователем
		for (int i = 0; i < size; ++i)  // до тех пор, пока < size
		{                               // (size передаем в конструкторе)			
			std::cout << "Put element: ";
			std::cin >> x;
			arr[i] = x;
		}				
	}

	void add_new(int elem)  // метод - добавление еще одного эл-та
	{
		T* temp = new T[size + 1];  // выделить новую память на размер size + 1
		for (int i = 0; i < size; i++)
		{
			temp[i] = arr[i];  // присвоили "новому" массивы "старый"
		}
		temp[size] = elem;
		delete[] arr;  // удаление старой памяти
		arr = temp;
		for (int i = 0; i < size+1; i++)
		{
			std::cout << arr[i] << ' ';  // вывод нового массива
		}
		size++;
	}

	void delete_elem(int index)  // // метод - удаление одного эл-та
	{		
		for (int i = 0; i < size; i++)
		{			
			if (i != index)
			{				
				std::cout << arr[i] << ' ';
			}			
		}
		size -= 1;
	}

	void print_element()  // метод - вывод на экран
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
		delete[] arr;
	}
};

int main()
{	
	int size = 3;
	DynArray<int> arr1(size++);  // создаем конкретный объект int
		
	arr1.fill_elements();  // заполнение массива
	arr1.print_element();  // вывод на экран
	std::cout << std::endl;
	
	std::cout << "\nAdd element: \n";
	arr1.add_new(2);  // добавление эл-та
	std::cout << "\nDelete element: \n";
	arr1.delete_elem(0);  // удаление эл-та

	/*
		Здесь у меня проблема. Если я хочу прописала ф-ию добавления и 
		удаления по одному разу - все ок.
		А если я хочу добавить несколько раз подряд - просто каждый раз
		добавляет другой элемент.
		Я не пойму, как сдела так, что бы после 3 введенный можно
		было дальше добалять еще много.
	*/
	
	std::cout << std::endl;
	DynArray<char> arr2(size++);  // создаем конкретный объект char

	arr2.fill_elements();
	arr2.print_element();
	std::cout << std::endl;
	std::cout << "\nAdd element: \n";
	arr2.add_new(4);
	std::cout << "\nDelete element: \n";
	arr2.delete_elem(1);

	return 0;
}



