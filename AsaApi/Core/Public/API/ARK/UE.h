#pragma once
#include "Actor.h"
//struct UObject;
struct FWeakObjectPtr
{
	int ObjectIndex;
	int ObjectSerialNumber;

	void operator=(UObject const* __that) { return NativeCall<void, UObject const*>(this, "FWeakObjectPtr.operator=", __that); }
	UObject* Get(bool bEvenIfPendingKill = false) { return NativeCall<UObject*, bool>(this, "FWeakObjectPtr.Get", bEvenIfPendingKill); }
	//	bool IsValid() { return NativeCall<bool>(this, "FWeakObjectPtr.IsValid"); }
};

template <typename T>
struct TWeakObjectPtr
{
	int ObjectIndex;
	int ObjectSerialNumber;

	FORCEINLINE T& operator*()
	{
		return *Get();
	}

	FORCEINLINE T* operator->()
	{
		return Get();
	}

	T* Get(bool bEvenIfPendingKill = false)
	{
		return NativeCall<T*, bool>(this, "FWeakObjectPtr.Get", bEvenIfPendingKill);
	}

	FORCEINLINE operator bool()
	{
		return Get() != nullptr;
	}

	FORCEINLINE operator T* ()
	{
		return Get();
	}

	FORCEINLINE bool operator==(const TWeakObjectPtr<T>& __that) const
	{
		return this->ObjectIndex == __that.ObjectIndex
			&& this->ObjectSerialNumber == __that.ObjectSerialNumber;
	}

	TWeakObjectPtr()
	{}

	TWeakObjectPtr(int index, int serialnumber)
		:ObjectIndex(index),
		ObjectSerialNumber(serialnumber)
	{}
};


struct FObjectHandlePrivate
{
	//Stores either FPackedObjectRef or a UObject*
	UPTRINT PointerOrRef;

	explicit inline operator bool() const
	{
		return PointerOrRef != 0;
	}

};

template <typename T>
struct TObjectPtr
{
private:
	FORCEINLINE UObject* RealGet() const { return reinterpret_cast<UObject*>(Handle.PointerOrRef); }
	FObjectHandlePrivate Handle;
public:

	FORCEINLINE T* Get() const { return (T*)(RealGet()); }
	FORCEINLINE T* operator->() const { return Get(); }
	FORCEINLINE T& operator*() const { return *Get(); }
};

struct UTexture : UObject
{
	static UClass* StaticClass() { return NativeCall<UClass*>(nullptr, "UTexture.StaticClass"); }
};

struct UTexture2D : UTexture
{
};