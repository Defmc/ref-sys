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

#if AUTO_INCLUDE == ON
#include "ref.cpp"
#endif

#endif // REF_HEADER