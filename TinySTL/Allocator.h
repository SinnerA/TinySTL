#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include <cassert>
#include <new>

#include "Alloc.h"
#include "Construct.h"

namespace TinySTL{

	//�ռ�������-----------------------------------------------------------------
	template <class T>
	class allocator{
	public:
		typedef T            value_type;
		typedef T*           pointer;
		typedef const T*     const_pointer;
		typedef T&           reference;
		typedef const T&     const_reference;
		typedef size_t       size_type;
		typedef ptrdiff_t    difference_type;
	public:
		static T* allocate();
		static T* allocate(size_t n);
		static void deallocate(T* ptr);
		static void deallocate(T* ptr, size_t n);
	
		static void construct(T* ptr);
		static void construct(T* ptr, const T& value);
		static void destory(T* ptr);
		static void destory(T* first, T* last);
	};

	template<class T>
	T* allocator<T>::allocate(){
		return static_cast<T*>(alloc::allocate(sizeof(T)));
	}

	template<class T>
	T* allocator<T>::allocate(size_t n){
		return static_cast<T*>(alloc::allocate(n * sizeof(T)));
	}

	template<class T>
	void allocator<T>::deallocate(T* ptr){
		alloc::deallocate(static_cast<void*>(ptr), sizeof(T));
	}

	template<class T>
	void allocator<T>::deallocate(T* ptr, size_t n){
		alloc::deallocate(static_cast<void*>(ptr), sizeof(T) * n);
	}

	template<class T>
	void allocator<T>::construct(T* ptr){
		new(ptr) T();
	}

	template<class T>
	void allocator<T>::construct(T* ptr, const T& value){
		new(ptr) T(value);
	}

	template<class T>
	void allocator<T>::destory(T* ptr){
		ptr->~T();
	}

	template<class T>
	void allocator<T>::destory(T* first, T* last){
		for(; first != last; ++first){
			first->~T();
		}
	}
}

#endif