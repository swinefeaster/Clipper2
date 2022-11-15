
#ifndef RECYCLED_VECTOR_H
#define RECYCLED_VECTOR_H

#include <cstdlib>
#include <cmath>
#include <vector>

namespace Clipper2Lib 
{

template <typename T>
class RecycledVector
{
public:
	RecycledVector()
	{
	}

	~RecycledVector()
	{
		for (auto item : _items)
		{
			delete item;
		}
	}

	RecycledVector(const RecycledVector &) = delete;
	RecycledVector(RecycledVector &&) = delete;
	RecycledVector & operator = (const RecycledVector &) = delete;

	T * GrabNew()
	{
		if (_items.empty())
		{
			return new T;
		}
		else
		{
			T * item = _items.back();
			_items.pop_back();
			return item;
		}
	}

	void Recycle(T * item)
	{
		_items.push_back(item);
	}

private:
	std::vector<T *> _items;
};

}  // namespace

#endif  // RECYCLED_VECTOR_H
