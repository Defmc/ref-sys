#ifndef REF_HEADER
#define REF_HEADER

#ifndef DEBUG_MODE
#define DEBUG_MODE ON
#endif

#ifndef SAFE_CLASS
#define SAFE_CLASS ON
#endif

#ifndef DEFINE_GENERIC_REFS
#define DEFINE_GENERIC_REFS ON
#endif

#if DEBUG_MODE == ON
#include <iostream>
#endif

template<class ValType, class CounterType = unsigned int>
class Ref{
private:

	ValType* ptr;
	CounterType* count;

public:

	Ref();
	Ref(const Ref<ValType, CounterType>& ref);
	Ref(ValType* val);

	Ref<ValType, CounterType>& operator=(const Ref<ValType, CounterType>& ref);
	Ref<ValType, CounterType>& operator=(const ValType* val);

	void ref();
	void unref();

	ValType* operator->();

	~Ref();
};

#if DEFINE_GENERIC_REFS == ON

template<class ValType>
using TinyRef = Ref<ValType, unsigned char>;

template<class ValType>
using ShortRef = Ref<ValType, unsigned short>;

template<class ValType>
using NormalRef = Ref<ValType, unsigned int>;

template<class ValType>
using BigRef = Ref<ValType, unsigned long>;

template<class ValType>
using MaxRef = Ref<ValType, unsigned long long>;

#endif

template<class ValType, class CounterType>
Ref<ValType, CounterType>::Ref() : ptr(nullptr), count(nullptr){

}

template<class ValType, class CounterType>
Ref<ValType, CounterType>::Ref(const Ref<ValType, CounterType>& ref) : ptr(ref.ptr), count(ref.count){
	this->ref();
}

template<class ValType, class CounterType>
Ref<ValType, CounterType>::Ref(ValType* val) : ptr(val), count(new CounterType(1)){
#if DEBUG_MODE == ON
	std::cout << "Created reference to " << ptr << " (" << static_cast<unsigned long long>(*count) << " references in total)" << std::endl;
#endif
}

template<class ValType, class CounterType>
Ref<ValType, CounterType>& Ref<ValType, CounterType>::operator=(const Ref<ValType, CounterType>& ref){
	if (ptr != nullptr)
		this->unref();

	ptr = ref.ptr;
	count = ref.count;
	this->ref();
	return this;
}

template<class ValType, class CounterType>
Ref<ValType, CounterType>& Ref<ValType, CounterType>::operator=(const ValType* val){
	if (ptr != nullptr)
		this->unref();
	ptr = val;
	count = new CounterType(1);

#if DEBUG_MODE == ON
	std::cout << "Created reference to " << ptr << " (" << static_cast<unsigned long long>(*count) << " references in total)" << std::endl;
#endif

}

template<class ValType, class CounterType>
ValType* Ref<ValType, CounterType>::operator->(){
	return ptr;
}

template<class ValType, class CounterType>
void Ref<ValType, CounterType>::ref(){
#if SAFE_CLASS == ON
	if (count != nullptr)
#endif
		(*count)++;

#if DEBUG_MODE == ON
	std::cout << "Added   reference to " << ptr << " (" << static_cast<unsigned long long>(*count) << " references in total)" << std::endl;
#endif
}

template<class ValType, class CounterType>
void Ref<ValType, CounterType>::unref(){
#if SAFE_CLASS == ON
	if (count != nullptr)
		(*count)--;
	else
		return;
#else
		(*count)--;
#endif

#if DEBUG_MODE == ON
	std::cout << "Removed reference to " << ptr << " (" << static_cast<unsigned long long>(*count) << " references in total)" << std::endl;
#endif

	if (*count <= 0){
#if DEBUG_MODE == ON
	std::cout << "Freeing reference to " << ptr << " (" << static_cast<unsigned long long>(*count) << " references in total)" << std::endl;
#endif

#if SAFE_CLASS == ON
		if (ptr != nullptr)
#endif
			delete ptr;
		delete count;
	}
}

template<class ValType, class CounterType>
Ref<ValType, CounterType>::~Ref(){
	this->unref();
}

#endif // REF_HEADER