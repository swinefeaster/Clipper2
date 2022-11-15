 
#ifndef POOL_VECTOR_H
#define POOL_VECTOR_H

#include <cstdlib>
#include <cmath>
#include <vector>
#include <memory>
#include <functional>

namespace Clipper2Lib 
{

// Wraps a std::vector and uses a shared_ptr to allocate it.
// Provides a static allocator function that can be overriden.
template <typename T>
class PoolVector
{
public:
	using size_type = typename std::vector<T>::size_type;
  using value_type = typename std::vector<T>::value_type;
  using const_iterator = typename std::vector<T>::const_iterator;
  using coord_type = typename T::coord_type;

	PoolVector()
	{
		_vector = s_allocate();
	}

  PoolVector(size_t count)
    : PoolVector()
  {
		resize(count);
  }

  PoolVector( std::initializer_list<T> init)
    : PoolVector()
  {
		for (const auto & item : init)
		{
			push_back(item);
		}
  }

	PoolVector(const PoolVector & other)
		: PoolVector()
	{
		*this = other;
	}

  PoolVector(PoolVector && other) noexcept
  {
		_vector = other._vector;
  }

	PoolVector & operator=(const PoolVector & other)
	{
		*_vector = *other._vector;
		return *this;
	}

	bool empty() const
	{
		return !_vector || _vector->empty();
	}

	size_t size() const
	{
		return _vector ? _vector->size() : 0u;
	}

	void clear()
	{
		_vector->clear();
	}

  void pop_back()
  {
    _vector->pop_back();
  }

	auto & back()
	{
		return _vector->back();
	}

  void erase(const_iterator first, const_iterator last)
  {
    _vector->erase(first, last);
  }

  void reserve(size_t count)
  {
    _vector->reserve(count);
  }

	const auto begin() const
	{
		return (*_vector).begin();
	}

	const auto end() const
  {
    return (*_vector).end();
  }

  auto cbegin() const
  {
    return (*_vector).cbegin();
  }

  auto cend() const
  {
    return (*_vector).cend();
  }

  auto begin()
  {
    return (*_vector).begin();
  }

  auto end()
  {
    return (*_vector).end();
  }

	void push_back(const T & item)
	{
		_vector->push_back(item);
	}

  void emplace_back(coord_type x, coord_type y)
  {
    _vector->emplace_back(x, y);
  }

	void resize(size_t newSize)
	{
		_vector->resize(newSize);
	}

	auto & operator[](size_t index)
	{
		return (*_vector)[index];
	}

  const auto & operator[](size_t index) const
  {
    return (*_vector)[index];
  }

	inline static std::function<std::shared_ptr<std::vector<T>>()> s_allocate = []()
	{
		return std::make_shared<std::vector<T>>();
	};

private:
	std::shared_ptr<std::vector<T>> _vector;
};

template <typename T>
const auto begin(const PoolVector<T> & x)
{
	return (*x._vector).begin();
}

template <typename T>
const auto end(const PoolVector<T> & x)
{
  return (*x._vector).end();
}

template <typename T>
auto begin(PoolVector<T> & x)
{
  return (*x._vector).begin();
}

template <typename T>
auto end(PoolVector<T> & x)
{
  return (*x._vector).end();
}

}  // namespace

#endif  // POOL_VECTOR_H
