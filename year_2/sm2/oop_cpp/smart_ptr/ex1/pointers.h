
#pragma once

/*********************************************************************************/
/*****************************<UNIQUE POINTER>************************************/
template <class T>
class UniquePointer
{
public:
	UniquePointer(T* p) : _ptr(p) {}
	~UniquePointer() { delete _ptr; }
	UniquePointer(const UniquePointer<T>& p) = delete;//Disable copy constructor
	const UniquePointer<T>& operator = (const UniquePointer<T>& p) = delete;//disable = operator
	UniquePointer(UniquePointer<T> &&p) //Create move semantics for rvalue referance
	{
		_ptr = p._ptr;
		p._ptr=nullptr;
	}


	const T& operator *() const
	{
		if (nullptr != _ptr)
			return *_ptr;
		return NULL;
	}

	T* operator -> () const
	{
		if (nullptr != _ptr)
			return _ptr;

		return NULL;
	}

private:
	T *_ptr;
};

/*********************************************************************************/
/*****************************<SHARED POINTER>************************************/
class Counter
{
public:
	Counter() : _useCount(0), _weakCount(0) {}
	Counter(int use, int weak) : _useCount(use), _weakCount(weak) {}

public:
	void incUse() { ++_useCount; }
	void incWeak() { ++_weakCount; }
	void decUse() { --_useCount; }
	void decWeak() { --_weakCount; }
	int getUse() const { return _useCount; }
	int getWeak() const { return _weakCount; }

private:
	int _useCount;
	int _weakCount;
};


template <class T>
class SharedPointer
{
public:
	SharedPointer(T* p) : _ptr(p), _counter(new Counter(1, 0)) {}
		

	~SharedPointer()
	{
		decrementRef();
	}

	SharedPointer(const SharedPointer<T>& p)
	{
		_counter = nullptr;
		*this = p; //Call = operator
	}

	const SharedPointer<T>& operator = (const SharedPointer<T>& p)
	{
		
		_counter = nullptr;
		_ptr = p._ptr;
		p._counter->incUse();
		_counter = p._counter;
		return *this;
	}

	const T& get() { return *_ptr; }

	template<class U>
	friend class WeakPointer;

private:
	void decrementRef()
	{
		if (_counter == nullptr)
			return;

		_counter->decUse();//Decrement the reference counter

		if (_counter->getUse() == 0 &&_counter->getWeak() == 0)
			delete _ptr;
	}

	const T& operator *() const { return *_ptr; }

	T* operator -> () const {
		if (nullptr == _ptr)
			NULL;

			return _ptr; }

private:
	T* _ptr;
	Counter* _counter;


};

/*********************************************************************************/
/******************************<WEAK POINTER>************************************/

template <class T>
class WeakPointer
{
public:
	WeakPointer() : _shared(nullptr), _counter(_shared->_counter) {}

	WeakPointer(SharedPointer<T>& p) :_shared(&p), _counter(p._counter) {
		_counter->incWeak();
	}

	~WeakPointer()
	{
		decrementRef();
	}

	WeakPointer(const WeakPointer<T>& wp)
	{
		_counter = nullptr;
		*this = wp;
	}

	const WeakPointer<T>& operator = (const WeakPointer<T>& WeakPointer)
	{
		decrementRef();
		_counter = WeakPointer._counter;
		_shared = WeakPointer._shared;
		_counter->incWeak();
		return *this;
	}

	bool expired() const { return _counter->getUse() == 0; }

	T* operator -> () const
	{
		if (_counter->getUse()==0)
			throw "Pointer is not longer valid.";
		return _shared->get();
	}

	const T& operator * () const
	{
		if (_counter->getUse() == 0)
			throw "Pointer is not longer valid.";
		return _shared->get();
	}

private:
	void decrementRef(void)
	{
		if (_counter == nullptr)
			return;

		_counter->decWeak();
		if (_counter->getUse() == 0 && _counter->getWeak() == 0)
			delete _shared;
	}

private:
	SharedPointer<T>* _shared;
	Counter* _counter;
};