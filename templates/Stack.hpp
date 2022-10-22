/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 00:13:35 by mnathali          #+#    #+#             */
/*   Updated: 2022/10/16 17:19:58 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "Vector.hpp"

namespace ft
{

template< class T, class Container = vector<T> >
class stack
{
	public:

	typedef Container							container_type;
	typedef typename Container::value_type		value_type;
	typedef typename Container::size_type		size_type;
	typedef typename Container::reference		reference;
	typedef typename Container::const_reference	const_reference;

	explicit stack( const Container& cont = Container() ) try : c(cont) {}
	catch(const std::exception& e)
	{
		throw;
	}

	~stack() {}
	
	stack& operator=( const stack& other )
	{
		if (this != &other)
			c = other.c;
		return (*this);
	}

	reference top()
	{
		return c.back();
	}

	const_reference top() const
	{
		return c.back();
	}

	bool empty() const
	{
		return c.empty();
	}

	size_type size() const
	{
		return c.size();
	}

	void push( const value_type& value )
	{
		c.push_back(value);
	}

	void pop()
	{
		c.pop_back();
	}

	protected:

	Container c;
};


template< class T, class Container >
bool operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return lhs == rhs; }

template< class T, class Container >
bool operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return lhs != rhs; }

template< class T, class Container >
bool operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return lhs < rhs; }

template< class T, class Container >
bool operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return lhs <= rhs; }

template< class T, class Container >
bool operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return lhs > rhs; }

template< class T, class Container >
bool operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return lhs >= rhs; }


}

#endif