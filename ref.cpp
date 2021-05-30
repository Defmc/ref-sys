#include "ref.hpp"

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