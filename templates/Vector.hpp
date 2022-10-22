#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "Iterator.hpp"
#include "Iterator_traits.hpp"
#include "Type_traits.hpp"

namespace ft
{

template<class T, class Allocator = std::allocator<T> >
class vector
{

	public:

//member types//
	typedef T															value_type;
	typedef Allocator													allocator_type;
	typedef std::size_t													size_type;
	typedef std::ptrdiff_t												difference_type;
	typedef value_type&													reference;
	typedef const value_type&											const_reference;
	typedef typename Allocator::pointer									pointer;
	typedef typename Allocator::const_pointer							const_pointer;
	typedef RAIterator<value_type>										iterator;//iterator<std::random_access_iterator_tag, value_type>
	typedef	RAIterator<const value_type>								const_iterator;//iterator<std::random_access_iterator_tag, const value_type>
	typedef ft::reverse_iterator<iterator>								reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

//constructor//
	explicit vector (const allocator_type& alloc = allocator_type()) : size_(0), capacity_(0),  allocator_(alloc), data_(NULL) {}

	explicit vector (size_type n, const value_type& val = value_type(),
        const allocator_type& alloc = allocator_type()) try : size_(n), capacity_(n), allocator_(alloc), data_(allocator_.allocate(n))
	{
		for (size_type i = 0; i < size_; i++)
			allocator_.construct(data_ + i, val);
	}
	catch(const std::exception& e)
	{
		throw;
	}

	template <class InputIterator>
    vector (typename enable_if<is_iterator<InputIterator>::value, InputIterator>::type first, InputIterator last, const allocator_type& alloc = allocator_type())
	{
		size_t	sz = 0;
		for (InputIterator tmp = first; tmp != last; ++tmp)
			sz++;
		try
		{
			size_ = sz;
			capacity_ = sz;
			allocator_ = alloc;
			data_ = allocator_.allocate(capacity_);
			for (size_type i = 0; i < size_; i++, first++)
				allocator_.construct(data_ + i, *first);
		}
		catch(const std::exception& e)
		{
			throw ;
		}
	}

	vector (const vector& x) try : size_(x.size_), capacity_(x.capacity_), allocator_(x.allocator_), data_(allocator_.allocate(capacity_))
	{
		for (size_type i = 0; i < size_; i++)
			allocator_.construct(data_ + i, x[i]);
	}
	catch(const std::exception& e)
	{
		throw;
	}

//destructor//
	~vector()
	{
		for (size_type i = 0; i < size_; i++)
			allocator_.destroy(data_ + i);
		allocator_.deallocate(data_, capacity_);
	}

//Member function//
	vector<T, Allocator> &operator=(const vector<T, Allocator> &other)
	{
		value_type *tmp = 0;

		if (this != &other)
		{
			try
			{
				if (capacity_ < other.size())
					tmp = other.get_allocator().allocate(other.size());
				for (size_type i = 0; i < size_; i++)
					allocator_.destroy(data_ + i);
				if (tmp)
				{
					allocator_.deallocate(data_, capacity_);
					data_ = tmp;
					capacity_ = other.capacity();
				}
				size_ = other.size();
				for (size_type i = 0; i < size_; i++)
					allocator_.construct(data_ + i, other[i]);
			}
			catch(const std::exception& e)
			{
				throw;
			}
		}
		return (*this);
	}
	
	void assign( size_type count, const T& value )
	{
		value_type *tmp = 0;

		try
		{
			if (capacity_ < count)
				tmp = allocator_.allocate(count);
			for (size_type i = 0; i < size_; i++)
				allocator_.destroy(data_ + i);
			if (tmp)
			{
				allocator_.deallocate(data_, capacity_);
				data_ = tmp;
				capacity_ = count;
			}
			for (size_type i = 0; i < count; i++)
				allocator_.construct(data_ + i, value);
			size_ = count;
		}
		catch(const std::exception& e)
		{
			throw;
		}
	}

	template< class InputIt >
	void assign(typename enable_if<is_iterator<InputIt>::value, InputIt>::type first, InputIt last)
	{
		size_t	sz = 0;
		value_type *tmp = 0;

		for (InputIt tmp = first; tmp != last; ++tmp)
			sz++;
		try
		{
			if (capacity_ < sz)
				tmp = allocator_.allocate(sz);
			for (size_type i = 0; i < size_; i++)
				allocator_.destroy(data_ + i);
			if (tmp)
			{
				allocator_.deallocate(data_, capacity_);
				data_ = tmp;
				capacity_ = sz;
			}
			for (size_t i = 0; i < sz; i++, ++first)
				allocator_.construct(data_ + i, *first);
			size_ = sz;
		}
		catch(const std::exception& e)
		{
			throw;
		}
	}

	allocator_type get_allocator() const {return (allocator_);}

//Element access//

	value_type &at( size_type pos )
	{
		if (pos > size_)
			throw std::out_of_range("vector");
		return *(data_ + pos);
	}

	const value_type at( size_type pos ) const
	{
		if (pos > size_)
			throw std::out_of_range("vector");
		return *(data_ + pos);
	}

	value_type &operator[](int i) {return *(data_ + i);}
	const value_type &operator[](int i) const {return *(data_ + i);}

	value_type &front()
	{
		if (data_)
			return *(data_);
		throw std::out_of_range("vector");
	}

	const value_type &front() const
	{
		if (data_)
			return *(data_);
		throw std::out_of_range("vector");
	}

	value_type &back()
	{
		if (data_ && size_)
			return *(data_ + size_ - 1);
		throw std::out_of_range("vector");
	}

	const value_type &back() const
	{
		if (data_ && size_)
			return *(data_ + size_ - 1);
		throw std::out_of_range("vector");
	}

	pointer data() {return data_;}
	const pointer data() const {return data_;}


//Iterators//
	iterator begin() {return (data_);}
	const_iterator begin() const {return (data_);}

	iterator end() {return (data_ + size_);}
	const_iterator end() const {return (data_ + size_);}

	reverse_iterator rbegin() { return reverse_iterator(this->end());}
	const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end());}

	reverse_iterator rend() { return reverse_iterator(this->begin());}
	const_reverse_iterator rend() const { return const_reverse_iterator(this->begin());}
//capacity//

	bool empty() const {return size_ == 0 ? true : false;}
	size_type	size() const {return (size_);}
	size_type	capacity() const {return (capacity_);}
	size_type	max_size() const {return std::numeric_limits<size_type>::max() / sizeof(value_type);}

	void reserve( size_type new_cap )
	{
		if (!(new_cap > capacity_))
			return ;
		try
		{
			pointer p = allocator_.allocate(new_cap);
			for (size_type i = 0; i < size_; ++i)
				allocator_.construct(p + i, (*this)[i]);
			for (size_type i = 0; i < size_; ++i)
				allocator_.destroy(data_ + i);
			allocator_.deallocate(data_, capacity_);
			capacity_ = new_cap;
			data_ = p;
		}
		catch(const std::exception& e)
		{
			throw;
		}
	}

//modifiers//

	void clear()
	{
		for (size_type i = 0; !(i > size_) && data_; i++)
			allocator_.destroy(data_ + i);
		size_ = 0;
	}

	iterator insert( iterator pos, const T& value )
	{
		size_type sz = 0;

		if (pos > this->end() || pos < this->begin())
			throw std::out_of_range("vector");
		try
		{
			if (size_ < capacity_)
			{
				for (iterator it = this->end(); pos < it; it--)
				{
					if (it == this->end())
						allocator_.construct(&(*it), it[-1]);
					else
						it[0] = it[-1];
				}
				pos[0] = value;
				size_++;
				return pos;
			}
			pointer p = 0;
			size_type new_cap;
			iterator it = this->begin();

			if (size_)
				new_cap = 2 * capacity_;
			else
				new_cap = 1;
			p = allocator_.allocate(new_cap);
			for (; it != pos && sz < size_; ++it, ++sz)
				allocator_.construct(p + sz, (*this)[sz]);
			allocator_.construct(p + sz, value);
			for (size_type i = sz; i < size_; ++i)
				allocator_.construct(p + i + 1, (*this)[i]);
			for (size_type i = 0; i < size_; ++i)
				allocator_.destroy(data_ + i);
			allocator_.deallocate(data_, capacity_);
			capacity_ = new_cap;
			size_ += 1;
			data_ = p;
		}
		catch(const std::exception& e)
		{
			throw;
		}
		return ((*this).begin() + sz);
	}

	void insert( iterator pos, size_type count, const T& value )
	{
		size_type sz = 0;

		if (!count)
			return ;
		if (pos > this->end() || pos < this->begin())
			throw std::out_of_range("vector");
		try
		{
			if (!(size_ + count > capacity_))
			{
				for (iterator it = this->end() + count - 1; !(pos > it); it--)
				{
					if (it >= this->end())
						allocator_.construct(&(*it), it[-count]);
					else if (pos + count - 1 < it)
						it[0] = it[-count];
					else
						it[0] = value;
				}
				size_ += count;
				return ;
			}
			pointer p = 0;
			size_type new_cap;
			iterator it = this->begin();

			if (size_ && 2 * capacity_ > size_ + count)
				new_cap = 2 * capacity_;
			else if (size_)
				new_cap = size_ + count;
			else
				new_cap = count;
			p = allocator_.allocate(new_cap);
			for (; it != pos && sz < size_; ++it, ++sz)
				allocator_.construct(p + sz, (*this)[sz]);
			for (size_type i = 0; i < count; ++i)
				allocator_.construct(p + sz + i, value);
			for (size_type i = sz; i < size_; ++i)
				allocator_.construct(p + i + count, (*this)[i]);
			for (size_type i = 0; i < size_; ++i)
				allocator_.destroy(data_ + i);
			allocator_.deallocate(data_, capacity_);
			capacity_ = new_cap;
			size_ += count;
			data_ = p;
		}
		catch(const std::exception& e)
		{
			throw;
		}
		return ;
	}

	template< class InputIt >
	void insert( iterator pos, typename enable_if<is_iterator<InputIt>::value, InputIt>::type first, InputIt last )
	{
		size_type sz = 0;
		size_type count = 0;

		if (pos > this->end() || pos < this->begin())
			throw std::out_of_range("vector");
		for (InputIt tmp = first; tmp != last; tmp++)
			count++;
		if (!count)
			return ;
		try
		{
			if (!(size_ + count > capacity_))
			{
				for (iterator it = this->end() + count - 1; pos < it; it--)
				{
					if (it >= this->end())
						allocator_.construct(&(*it), it[-count]);
					else if (pos + count - 1 < it)
						it[0] = it[-count];
				}
				for (iterator it = pos; first != last; it++, first++)
					it[0] = *first;
				size_ += count;
				return ;
			}
			pointer p = 0;
			size_type new_cap;
			iterator it = this->begin();

			if (size_ && 2 * capacity_ > size_ + count)
				new_cap = 2 * capacity_;
			else if (size_)
				new_cap = size_ + count;
			else
				new_cap = count;
			p = allocator_.allocate(new_cap);
			for (; it != pos && sz < size_; ++it, ++sz)
				allocator_.construct(p + sz, (*this)[sz]);
			for (size_type i = 0; i < count; ++i, ++first)
				allocator_.construct(p + sz + i, *first);
			for (size_type i = sz; i < size_; ++i)
				allocator_.construct(p + i + count, (*this)[i]);
			for (size_type i = 0; i < size_; ++i)
				allocator_.destroy(data_ + i);
			allocator_.deallocate(data_, capacity_);
			capacity_ = new_cap;
			size_ += count;
			data_ = p;
		}
		catch(const std::exception& e)
		{
			throw;
		}
		return ;
	}

	iterator erase( iterator pos )
	{
		if (pos < this->begin() || pos >= this->end())
			throw std::out_of_range("vector");
		for (iterator it = pos; it < this->end(); it++)
		{
			if (it + 1 != this->end())
				it[0] = it[1];
			else
				allocator_.destroy(&(*it));
		}
		size_--;
		return pos;
	}

	iterator erase( iterator first, iterator last )
	{
		if (first < this->begin() || last > this->end() || first > last)
			throw std::out_of_range("vector");
		size_type sz = last - first;
		for (iterator it = last; first < this->end() && sz; it++, first++)
		{
			if (it < this->end())
				first[0] = it[0];
			else
				allocator_.destroy(&(*first));
		}
		size_-= sz;
		return last;
	}

	void push_back( const T& value )
	{
		try
		{
			this->insert(this->end(), value);
		}
		catch(const std::exception& e)
		{
			throw ;
		}
	}

	void pop_back()
	{
		try
		{
			if (size_)
				this->erase(this->end() - 1);
		}
		catch(const std::exception& e)
		{
			throw;
		}
	}

	void resize( size_type count, T value = T() )
	{
		try
		{
			if (count > size_)
				this->insert(this->end(), count - size_, value);
			else
				this->erase(this->begin() + count, this->end());
		}
		catch(const std::exception& e)
		{
			throw;
		}
	}

	void swap( vector &other )
	{
		if (this == &other)
			return ;
		size_type sz = size_;
		size_type cap = capacity_;
		value_type *p = data_;
		allocator_type all = allocator_;
		
		data_ = other.data_;
		size_ = other.size_;
		capacity_ = other.capacity_;
		allocator_ = other.allocator_;

		other.data_ = p;
		other.size_ = sz;
		other.capacity_ = cap;
		other.allocator_ = all;
	}

//casts//

	private:

	size_type		size_;
	size_type		capacity_;
	allocator_type	allocator_;
	value_type		*data_;

};

//non-member functions
template< class T, class Alloc >
void swap( vector<T,Alloc>& lhs, vector<T,Alloc>& rhs )
{
	lhs.swap(rhs);
}

template< class T, class Alloc >
bool operator==( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
{
	typename vector<T,Alloc>::const_iterator it = lhs.begin(), ite = rhs.begin();

	for (; it < lhs.end() && ite < rhs.end(); it++, ite++)
		if (*it != *ite)
			return false;
	if (it != lhs.end() || ite != rhs.end())
		return false;
	return true;
}

template< class T, class Alloc >
bool operator!=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
{
	return !(lhs == rhs);
}

template< class T, class Alloc >
bool operator<( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
{
	typename vector<T,Alloc>::const_iterator it = lhs.begin(), ite = rhs.begin();

	for (; it < lhs.end() && ite < rhs.end() && *it == *ite; it++, ite++)
		;
	if (it != lhs.end() && ite != rhs.end())
		return (*it < *ite);
	else if (it == lhs.end())
		return (true);
	return (false);
}

template< class T, class Alloc >
bool operator<=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
{
	return !(lhs > rhs);
}

template< class T, class Alloc >
bool operator>( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
{
	return (rhs < lhs);
}

template< class T, class Alloc >
bool operator>=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
{
	return !(lhs < rhs);
}

}


#endif