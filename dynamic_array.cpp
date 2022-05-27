#include<iostream>
#include <stdlib.h>
using namespace std;

template <typename T>
class DynamicArray
{
private:
	int allocation_size = 20;
	T* array = nullptr;
	size_t array_capacity;
	size_t elements_num;
public:
	DynamicArray() {
		array_capacity = allocation_size;
		array = (T*)malloc(sizeof(T) * allocation_size);
		elements_num = 0;
	}
	void push_back(const T   &data) {
		if (elements_num < array_capacity) {
			*(array + elements_num) = data;
			elements_num++;
		}
		else {
			array_capacity *= 2;
			array = (T*)realloc(array,sizeof(T) * array_capacity);
			if (array) {
				*(array + elements_num) = data;
				elements_num++;
			}
		}
	}
	T& operator[](size_t pos){
		if (pos >= 0 && pos <= elements_num)
			return *(array + pos);
		else
			cout << "out of scope" << endl;
	}

	void remove_element(const T* item_pos) {
		T* first_element = array;
		T* last_element = array + elements_num-1;
		int index = last_element - item_pos;
		for (int i = 0; i < index; i++) {
			*(array + i) = *(array + i + 1);
		}
	}
	size_t get_element_num() {
		return elements_num;
	}
	template<typename F>
	size_t get_new_array_size(F& predicate) {
		int new_size = 0;
		for (int i = 0; i < elements_num; i++) {
			if (predicate(*(array + i))) {
				new_size++;
			}
		}
		return new_size;
	}
	template<typename F>
	T* remove_if(F &predicate) {
		int new_array_size =get_new_array_size(predicate);

		int new_index = 0;
		T*  new_array = (T*)malloc(sizeof(T) * elements_num-new_array_size);
		for (int i = 0; i < elements_num ;i++) {
			if (!predicate(*(array + i))) {
				*(new_array + new_index) = *(array + i);
				new_index++ ;
			}
		}
		array = (T*)realloc(new_array, sizeof(T) * (elements_num - new_array_size));
		elements_num = elements_num - new_array_size;
		return array;
	}
	~DynamicArray() {
		free(array);
	}
};

int main() {
	auto mod_by_2 = [](int element) { return element%2 == 0; };
	auto custom_1 = [](int element) { return element != 5; };
	auto custom_2 = [](int element) { return element == 5; };

	DynamicArray<int> a1;
	//push 50 element
	for (int it = 0; it < 50;it++) {
		a1.push_back(it);
	}
	//print it
	cout << "original elements: ";
	for (int i = 0; i < a1.get_element_num(); i++) {
		if(a1.get_element_num()-i==1)
			cout << a1[i] << endl;
		else
			cout << a1[i] << ",";
	}
	//remove using mod_by_2 predicate and print it
	cout << "after removing even numbers: ";
	a1.remove_if(mod_by_2);
	for (int i = 0; i < a1.get_element_num();i++) {
		if (a1.get_element_num() - i == 1)
			cout << a1[i] << endl;
		else
			cout << a1[i] << ",";
	}
	//remove all except elements has value 5
	cout << "after removing all elements except that's equal 5: ";
	a1.remove_if(custom_1);
	for (int i = 0; i < a1.get_element_num(); i++) {
		if (a1.get_element_num() - i == 1)
			cout << a1[i] << endl;
		else
			cout << a1[i] << ",";
	}

	return 0;
}