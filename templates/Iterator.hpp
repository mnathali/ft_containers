#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include "Iterator_traits.hpp"
#include "Utility.hpp"


namespace ft
{

template<class Category, class T, class Distance = std::ptrdiff_t,
    class Pointer = T*, class Reference = T&>
struct iterator
{

	typedef Category	iterator_category;
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;

};

template <typename T>
struct BDIterator : iterator<std::bidirectional_iterator_tag, T> {};

template <typename T, typename U>
struct BDIterator<pair<pair<T*,U>, pair<void*, pair<void*, void*> > > > : iterator<std::bidirectional_iterator_tag, T>
{
	private:

	typedef pair<pair<T*, U>, pair<void*, pair<void*, void*> > > Type;

	public:

	template< class Key, class V, class Compare, class Allocator>
	friend class map;

	template< class Key, class Compare, class Allocator>
	friend class set;

	BDIterator() {}
	BDIterator(Type *p) : p_(p) {}
	BDIterator(const BDIterator &rhs) : p_(rhs.p_) {}
	~BDIterator() {}

	BDIterator &operator=(const BDIterator &rhs)
	{
		p_ = rhs.p_;
		return (*this);
	}

	BDIterator	&operator++()
	{
		p_ = tree_successor(p_);
		return (*this);
	}

	BDIterator	operator++(int)
	{
		BDIterator tmp(*this);
		++(*this);
		return (tmp);
	}

	BDIterator	&operator--()
	{
		p_ = tree_predecessor(p_);
		return (*this);
	}

	BDIterator	operator--(int)
	{
		BDIterator tmp(*this);
		--(*this);
		return (tmp);
	}

	T *operator->() const { return p_->first.first; }

	bool	operator==(const BDIterator &it) const {return it.p_ == p_ ? true : false;}
	bool	operator!=(const BDIterator &it) const {return !(it == *this);}

	T 		&operator*() { return *(p_->first.first); }
	const T &operator*() const { return *(p_->first.first); }

	operator BDIterator<pair<pair<const T*, U>, pair<void*, pair<void*, void*> > > >() const { return reinterpret_cast<pair<pair<const T*, U>, pair<void*, pair<void*, void*> > >*>(p_); }

	private:

	Type	*tree_minimum(Type *p)
	{
		while (p && p->second.second.first)
			p = static_cast<Type *>(p->second.second.first);
		return p;
	}

	Type	*tree_maximum(Type *p)
	{
		while (p && p->second.second.second)
			p = static_cast<Type *>(p->second.second.second);
		return p;
	}

	Type	*tree_successor(Type *p)
	{
		if (p->second.second.second != NULL)
			return tree_minimum(static_cast<Type *>(p->second.second.second));
		Type	*y = static_cast<Type *>(p->second.first);
		while (y != NULL && p == y->second.second.second)
		{
			p = y;
			y = static_cast<Type *>(y->second.first);
		}
		if (y == NULL)
			return p;
		return y;
	}

	Type	*tree_predecessor(Type *p)
	{
		if (p->second.second.first != NULL)
			return tree_maximum(static_cast<Type *>(p->second.second.first));
		Type	*y = static_cast<Type *>(p->second.first);
		while (y != NULL && p == y->second.second.first)
		{
			p = y;
			y = static_cast<Type *>(y->second.first);
		}
		if (y == NULL)
			return p;
		return y;
	}

	Type	*p_;

};

template <typename T>
struct RAIterator : iterator<std::random_access_iterator_tag, T>
{
	
	RAIterator() {}
	RAIterator(T *p) : p_(p) {}
	RAIterator(const RAIterator &rhs) : p_(rhs.p_) {}
	~RAIterator() {}
	RAIterator &operator=(const RAIterator &rhs)
	{
		p_ = rhs.p_;
		return (*this);
	}

	T	*base() const { return p_; }

	RAIterator	&operator++()
	{
		p_++;
		return (*this);
	}

	RAIterator	operator++(int)
	{
		RAIterator tmp(*this);
		++(*this);
		return (tmp);
	}

	RAIterator	&operator--()
	{
		p_--;
		return (*this);
	}

	RAIterator	operator--(int)
	{
		RAIterator tmp(*this);
		--(*this);
		return (tmp);
	}

	RAIterator	operator+(int i) {return (p_ + i);}

	RAIterator	operator-(int i) {return (p_ - i);}

	int	operator-(RAIterator const & rhs) {return (p_ - &(*rhs));}

	T 		&operator*() {return *p_;}
	const T &operator*() const {return *p_;}

	RAIterator	&operator+=(int i)
	{
		return (p_ = p_ + i);
	}

	RAIterator	&operator-=(int i)
	{
		return (p_ = p_ - i);
	}

	T 		&operator[](int i) {return *(p_ + i);}
	const T	&operator[](int i) const {return *(p_ + i);}
	T * operator->() const { return p_; }

	bool	operator==(const RAIterator &it) const {return it.p_ == p_ ? true : false;}
	bool	operator!=(const RAIterator &it) const {return !(it == *this);}
	bool	operator<(const RAIterator &it) const {return p_ < it.p_ ? true : false;}
	bool	operator>(const RAIterator &it) const {return (it < *this);}
	bool	operator<=(const RAIterator &it) const {return !(p_ > it.p_);}
	bool	operator>=(const RAIterator &it) const {return !(p_ < it.p_);}

	operator RAIterator<const T>() const { return p_; }

	private:

	T	*p_;
};

template< class Iter >
class reverse_iterator
{

	public:

	typedef Iter												iterator_type;
	typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
	typedef typename iterator_traits<Iter>::value_type			value_type;
	typedef typename iterator_traits<Iter>::difference_type		difference_type;
	typedef typename iterator_traits<Iter>::pointer				pointer;
	typedef typename iterator_traits<Iter>::reference			reference;

	reverse_iterator() {}

	explicit reverse_iterator( iterator_type x ) : current(x) {}

	template< class U > 
	reverse_iterator( const reverse_iterator<U>& other ) : current(other.base()) {}

	template< class U > 
	reverse_iterator& operator=( const reverse_iterator<U>& other )
	{
		current = other.base();
		return (*this);
	}

	reference operator*() const
	{
		Iter tmp = current;
		return *--tmp;
	}

	pointer operator->() const {return &operator*();}

	iterator_type base() const
	{
		return current;
	}

	value_type &operator[]( difference_type n )
	{
		return current[-n-1];
	}

	reverse_iterator& operator++()
	{
		current--;
		return *this;
	}

	reverse_iterator& operator--()
	{
		current++;
		return *this;
	}

	reverse_iterator operator++( int )
	{
		reverse_iterator tmp(*this);
		++(*this);
		return tmp;
	}

	reverse_iterator operator--( int )
	{
		reverse_iterator tmp(*this);
		--(*this);
		return tmp;
	}

	reverse_iterator operator+( difference_type n ) const
	{
		return reverse_iterator(base()-n);
	}

	reverse_iterator operator-( difference_type n ) const
	{
		return reverse_iterator(base()+n);
	}

	reverse_iterator& operator+=( difference_type n )
	{
		current -= n;
		return *this;
	}

	reverse_iterator& operator-=( difference_type n )
	{
		current += n;
		return *this;
	}

	protected:

    Iter current;
};

template< class Iterator1, class Iterator2 >
bool operator==( const reverse_iterator<Iterator1>& lhs,
                 const reverse_iterator<Iterator2>& rhs )
{
	return lhs.base() == rhs.base();
}

template< class Iterator1, class Iterator2 >
bool operator!=( const reverse_iterator<Iterator1>& lhs,
                 const reverse_iterator<Iterator2>& rhs )
{
	return lhs.base() != rhs.base();
}

template< class Iterator1, class Iterator2 >
bool operator<( const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs )
{
	return lhs.base() > rhs.base();
}

template< class Iterator1, class Iterator2 >
bool operator<=( const reverse_iterator<Iterator1>& lhs,
                 const reverse_iterator<Iterator2>& rhs )
{
	return lhs.base() >= rhs.base();
}

template< class Iterator1, class Iterator2 >
bool operator>( const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs )
{
	return lhs.base() < rhs.base();
}

template< class Iterator1, class Iterator2 >
bool operator>=( const reverse_iterator<Iterator1>& lhs,
                 const reverse_iterator<Iterator2>& rhs )
{
	return lhs.base() <= rhs.base();
}

template< class Iter > 
reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n,
               const reverse_iterator<Iter>& it )
{
	return reverse_iterator<Iter>(it.base() - n);
}

template< class Iterator >
typename reverse_iterator<Iterator>::difference_type operator-( const reverse_iterator<Iterator>& lhs,
               const reverse_iterator<Iterator>& rhs )
{
	return rhs.base() - lhs.base();
}

}

#endif