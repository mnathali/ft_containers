/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 00:20:42 by mnathali          #+#    #+#             */
/*   Updated: 2022/10/22 12:31:25 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "Utility.hpp"
#include "Iterator.hpp"
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

namespace ft
{

template< class Key, class T, class Compare = less<Key>,
    class Allocator = std::allocator<pair<const Key, T> > >
class map
{

	typedef pair<pair<pair<const Key, T>*, char>, pair<void*, pair<void*, void*> > >	Type;
	typedef typename Allocator::template rebind<Type>::other							Allocator_node;	


	public:

	typedef	Key																					key_type;
	typedef T																					mapped_type;
	typedef pair<const Key, T>																	value_type;
	typedef std::size_t																			size_type;
	typedef std::ptrdiff_t																		difference_type;
	typedef Compare																				key_compare;
	typedef Allocator																			allocator_type;
	typedef value_type&																			reference;
	typedef const value_type&																	const_reference;
	typedef typename Allocator::pointer															pointer;
	typedef typename Allocator::const_pointer													const_pointer;
	typedef BDIterator<pair<pair<value_type*, char>, pair<void*, pair<void*, void*> > > >		iterator;
	typedef BDIterator<pair<pair<const value_type*, char>, pair<void*, pair<void*, void*> > > >	const_iterator;
	typedef ft::reverse_iterator<iterator>														reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>												const_reverse_iterator;

	class value_compare : public std::binary_function<value_type, value_type, bool>
	{

		friend class map;

		public:

		bool operator()( const value_type& lhs, const value_type& rhs ) const { return comp(lhs.first, rhs.first); }

		protected:
		
		value_compare( Compare c ) : comp(c) {}

		Compare	comp;

	};

	map() : size_(0)
	{
		root.first.first = &sample;
		root.first.second = 0;
		root.second.first = NULL;
		root.second.second.second = NULL;
		root.second.second.first = NULL;
	}

	explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) : size_(0), allocator_(alloc), compare_(comp)
	{
		root.first.first = &sample;
		root.first.second = 0;
		root.second.first = NULL;
		root.second.second.second = NULL;
		root.second.second.first = NULL;
	}

	template< class InputIt >
	map( InputIt first, typename enable_if<is_iterator<InputIt>::value, InputIt>::type last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) : size_(0), allocator_(alloc), compare_(comp)
	{
		root.first.first = &sample;
		root.first.second = 0;
		root.second.first = NULL;
		root.second.second.second = NULL;
		root.second.second.first = NULL;
		try
		{
			this->insert(first, last);
		}
		catch(const std::exception& e)
		{
			throw ;
		}
	}

	map( const map& other ) : size_(other.size_), allocator_(other.allocator_), compare_(other.compare_)
	{
		Type *y = static_cast<Type*>(other.root.second.second.first);
		Type *x = &root;
		Type *p = NULL;
		root.first.first = &sample;
		root.first.second = 0;
		root.second.second.first = p;
		root.second.second.second = p;
		while (y && y != &other.root)
		{
			try
			{
				p = node_alloc.allocate(1);
				p->first.first = allocator_.allocate(1);
				allocator_.construct(p->first.first, *(y->first.first));
			}
			catch(const std::exception& e)
			{
				this->clear();
				throw;
			}
			p->first.second = y->first.second;
			p->second.first = x;
			p->second.second.first = NULL;
			p->second.second.second = NULL;
			if (static_cast<Type*>(y->second.first)->second.second.first == y)
				x->second.second.first = p;
			else
				x->second.second.second = p;
			x = p;
			if (y->second.second.first)
				y = static_cast<Type*>(y->second.second.first);
			else if (y->second.second.second)
				y = static_cast<Type*>(y->second.second.second);
			else
			{
				while (y != &other.root && ((y->second.second.second == NULL && x->second.second.second == NULL) || (y->second.second.second && x->second.second.second)))
				{
					y = static_cast<Type*>(y->second.first);
					x = static_cast<Type*>(x->second.first);
				}
				if (y != &other.root)
					y = static_cast<Type*>(y->second.second.second);
			}
		}
	}

	~map()
	{
		if (!size_)
			return ;
		Type	*y = static_cast<Type*>(root.second.second.first);
		Type	*x = NULL;
		while (y != &root)
		{
			if (y->second.second.first)
				y = static_cast<Type*>(y->second.second.first);
			else if (y->second.second.second)
				y = static_cast<Type*>(y->second.second.second);
			else
			{
				x = y;
				y = static_cast<Type*>(y->second.first);
				if (y && y->second.second.first == x)
					y->second.second.first = NULL;
				else if (y != &root)
					y->second.second.second = NULL;
				allocator_.destroy(x->first.first);
				allocator_.deallocate(x->first.first, 1);
				node_alloc.deallocate(x, 1);
			}
		}
	}

	map& operator=( const map& other )
	{
		Type *y = static_cast<Type*>(other.root.second.second.first);
		Type *x = &root;
		Type *p = NULL;
		
		if (this != &other)
		{
			this->clear();
			while (y && y != &other.root)
			{
				try
				{
					p = node_alloc.allocate(1);
					p->first.first = allocator_.allocate(1);
					allocator_.construct(p->first.first, *(y->first.first));
				}
				catch(const std::exception& e)
				{
					this->clear();
					throw;
				}
				p->first.second = y->first.second;
				p->second.first = x;
				p->second.second.first = NULL;
				p->second.second.second = NULL;
				if (static_cast<Type*>(y->second.first)->second.second.first == y)
					x->second.second.first = p;
				else
					x->second.second.second = p;
				x = p;
				if (y->second.second.first)
					y = static_cast<Type*>(y->second.second.first);
				else if (y->second.second.second)
					y = static_cast<Type*>(y->second.second.second);
				else
				{
					while (y != &other.root && ((y->second.second.second == NULL && x->second.second.second == NULL) || (y->second.second.second && x->second.second.second)))
					{
						y = static_cast<Type*>(y->second.first);
						x = static_cast<Type*>(x->second.first);
					}
					if (y != &other.root)
						y = static_cast<Type*>(y->second.second.second);
				}
			}
			size_ = other.size_;
			allocator_ = other.allocator_;
			compare_ = other.compare_;
		}
		return (*this);
	}

	allocator_type get_allocator() const { return allocator_; }

//Element access

	T& at( const Key& key )
	{
		Type *x = static_cast<Type*>(root.second.second.first);

		while (x != NULL)
		{
			if (compare_(key, x->first.first->first))
				x = static_cast<Type *>(x->second.second.first);
			else if (!compare_(x->first.first->first, key))
				return x->first.first->second;
			else
				x = static_cast<Type *>(x->second.second.second);
		}
		throw std::out_of_range("map");
	}

	const T& at( const Key& key ) const
	{
		Type *x = static_cast<Type*>(root.second.second.first);

		while (x != NULL)
		{
			if (compare_(key, x->first.first->first))
				x = static_cast<Type *>(x->second.second.first);
			else if (!compare_(x->first.first->first, key))
				return x->first.first->second;
			else
				x = static_cast<Type *>(x->second.second.second);
		}
		throw std::out_of_range("map");
	}

	T& operator[]( const Key& key ) { return insert(pair<Key, T>(key, T())).first->second; }
	
//iterator

	iterator				begin() { return tree_minimum(&root); }
	const_iterator			begin() const { return iterator(tree_minimum(const_cast<Type *>(&root))); }
	iterator				end() { return &root; }
	const_iterator			end() const { return iterator(const_cast<Type *>(&root)); }
	reverse_iterator		rbegin() { return reverse_iterator(iterator(&root)); }
	const_reverse_iterator	rbegin() const { return reverse_iterator(iterator(const_cast<Type *>(&root))); }
	reverse_iterator		rend() { return reverse_iterator(iterator(tree_minimum(&root))); }
	const_reverse_iterator	rend() const { return reverse_iterator(iterator(tree_minimum(const_cast<Type *>(&root)))); }
	
//Capacity

	size_type size() const { return size_; }
	bool empty() const { return size_ ? false : true; }
	size_type max_size() const { return std::numeric_limits<size_type>::max() / (sizeof(pair<value_type*, pair<void*, pair<void*, void*> > >) + sizeof(value_type)); }

//Modifiers

	void clear()
	{
		if (!size_)
			return ;
		Type	*y = static_cast<Type*>(root.second.second.first);
		Type	*x = NULL;
		while (y && y != &root)
		{
			if (y->second.second.first)
				y = static_cast<Type*>(y->second.second.first);
			else if (y->second.second.second)
				y = static_cast<Type*>(y->second.second.second);
			else
			{
				x = y;
				y = static_cast<Type*>(y->second.first);
				if (y && y->second.second.first == x)
					y->second.second.first = NULL;
				else if (y != &root)
					y->second.second.second = NULL;
				allocator_.destroy(x->first.first);
				allocator_.deallocate(x->first.first, 1);
				node_alloc.deallocate(x, 1);
			}
		}
		root.second.second.first = NULL;
		root.second.second.second = NULL;
		size_ = 0;
	}

	pair<iterator, bool> insert( const value_type& value )
	{
		Type *y = NULL;
		Type *x = static_cast<Type*>(root.second.second.first);
		Type *z = NULL;

		while (x != NULL)
		{
			y = x;
			if (compare_(value.first, x->first.first->first))
				x = static_cast<Type *>(x->second.second.first);
			else if (!compare_(x->first.first->first, value.first))
				return pair<iterator, bool>(x, 0);
			else
				x = static_cast<Type *>(x->second.second.second);
		}
		try
		{
			z = node_alloc.allocate(1);
			z->first.first = allocator_.allocate(1);
			allocator_.construct(z->first.first, value);
			z->first.second = 1;
			z->second.first = NULL;
			z->second.second.first = NULL;
			z->second.second.second = NULL;
		}
		catch(const std::exception& e)
		{
			throw;
		}
		if (!size_)
		{
			root.second.second.first = z;
			root.second.second.second = z;
			z->second.first = &root;
			size_++;
			return pair<iterator, bool>(z, 1);
		}
		z->second.first = y;
		if (compare_(value.first, y->first.first->first))
			y->second.second.first = z;
		else
			y->second.second.second = z;
		balance_tree(z);
		size_++;
		return pair<iterator, bool>(z, 1);
	}

	iterator insert( iterator hint, const value_type& value )
	{	
		iterator it;
		Type *y = NULL;
		Type *z = NULL;
		Type *x;
	
		if (compare_(hint->first, value.first))
		{
			while (compare_(hint->first, value.first) && hint != this->end())
				hint++;
		}
		else
		{
			while (compare_(value.first, hint->first) && hint != this->end())
				hint--;
		}
		try
		{
			x = hint.p_;
			if (hint == this->end())
				it = insert(value).first;
			else
			{
				while (x != NULL)
				{
					y = x;
					if (compare_(value.first, x->first.first->first))
						x = static_cast<Type *>(x->second.second.first);
					else if (!compare_(x->first.first->first, value.first))
						return x;
					else
						x = static_cast<Type *>(x->second.second.second);
				}
				z = node_alloc.allocate(1);
				z->first.first = allocator_.allocate(1);
				allocator_.construct(z->first.first, value);
				z->second.first = NULL;
				z->second.second.first = NULL;
				z->second.second.second = NULL;
				z->second.first = y;
				if (compare_(value.first, y->first.first->first))
					y->second.second.first = z;
				else
					y->second.second.second = z;
				balance_tree(z);
				size_++;
				it = z;
			}
		}
		catch(const std::exception& e)
		{
			if (z && z->first.first)
				allocator_.deallocate(z->first.first, 1);
			if (z)
				node_alloc.deallocate(z, 1);
			throw;
		}	
		return it;
	}

	template< class InputIt >
	void insert( InputIt first, typename enable_if<is_iterator<InputIt>::value, InputIt>::type last )
	{
		iterator it = this->end();

		try
		{
			for (; first != last; ++first)
				it = this->insert(it, *first);
		}
		catch(const std::exception& e)
		{
			throw;
		}
	}

	iterator erase( iterator pos )
	{
		Type	*z = pos.p_;
		Type	*b = NULL;
		
		pos++;
		if (z->second.second.first == NULL)
		{
			b = static_cast<Type*>(z->second.first);
			transplant(z, static_cast<Type*>(z->second.second.second));
		}
		else if (z->second.second.second == NULL)
		{
			b = static_cast<Type*>(z->second.first);
			transplant(z, static_cast<Type*>(z->second.second.first));
		}
		else
		{
			Type *y = tree_minimum(static_cast<Type*>(z->second.second.second));
			if (y->second.first != z)
			{
				b = static_cast<Type*>(y->second.first);
				transplant(y, static_cast<Type*>(y->second.second.second));
				y->second.second.second = z->second.second.second;
				static_cast<Type*>(y->second.second.second)->second.first = y;
			}
			else
				b = y;
			transplant(z, y);
			y->second.second.first = z->second.second.first;
			static_cast<Type*>(y->second.second.first)->second.first = y;
		}
		if (b->second.second.first)
			b = static_cast<Type*>(b->second.second.first);
		else if (b->second.second.second)
			b = static_cast<Type*>(b->second.second.second);
		balance_tree(b);
		allocator_.destroy(z->first.first);
		allocator_.deallocate(z->first.first, 1);
		node_alloc.deallocate(z, 1);
		size_--;
		return (pos);
	}
	
	iterator erase( iterator first, iterator last )
	{
		iterator it = first;
		while (first != last)
		{
			first++;
			this->erase(it);
			it = first;
		}
		return last;
	}

	size_type erase( const Key& key )
	{
		Type *x = static_cast<Type*>(root.second.second.first);

		while (x != NULL)
		{
			if (compare_(key, x->first.first->first))
				x = static_cast<Type *>(x->second.second.first);
			else if (!compare_(x->first.first->first, key))
			{
				this->erase(iterator(x));
				return 1;
			}
			else
				x = static_cast<Type *>(x->second.second.second);
		}
		return 0;
	}

	void swap( map& other )
	{
		size_type							sz = size_;
		pair<void*, pair<void*, void*> >	pointers = root.second;
		allocator_type						alloc = allocator_;
		key_compare							comp = compare_;

		size_ 		= other.size_;
		root.second = other.root.second;
		allocator_ 	= other.allocator_;
		compare_ 	= other.compare_;

		other.size_ 		= sz;
		other.root.second 	= pointers;
		other.allocator_ 	= alloc;
		other.compare_ 		= comp;

		static_cast<Type*>(root.second.second.first)->second.first = &root;
		static_cast<Type*>(other.root.second.second.first)->second.first = &other.root;
	}

//Loockup

	size_type count( const Key& key ) const
	{
		Type *x = static_cast<Type*>(root.second.second.first);

		while (x != NULL)
		{
			if (compare_(key, x->first.first->first))
				x = static_cast<Type *>(x->second.second.first);
			else if (!compare_(x->first.first->first, key))
				return 1;
			else
				x = static_cast<Type *>(x->second.second.second);
		}
		return 0;
	}

	iterator find( const Key& key )
	{
		Type *x = static_cast<Type*>(root.second.second.first);

		while (x != NULL)
		{
			if (compare_(key, x->first.first->first))
				x = static_cast<Type *>(x->second.second.first);
			else if (!compare_(x->first.first->first, key))
				return x;
			else
				x = static_cast<Type *>(x->second.second.second);
		}
		return this->end();
	}

	const_iterator find( const Key& key ) const
	{
		Type *x = static_cast<Type*>(root.second.second.first);

		while (x != NULL)
		{
			if (compare_(key, x->first.first->first))
				x = static_cast<Type *>(x->second.second.first);
			else if (!compare_(x->first.first->first, key))
				return iterator(x);
			else
				x = static_cast<Type *>(x->second.second.second);
		}
		return this->end();
	}

	pair<iterator,iterator> equal_range( const Key& key )
	{
		Type *y = 0;
		Type *x = static_cast<Type*>(root.second.second.first);

		while (x != NULL)
		{
			y = x;
			if (compare_(key, x->first.first->first))
				x = static_cast<Type *>(x->second.second.first);
			else if (key == x->first.first->first)
				return pair<iterator, iterator>(x, tree_successor(x));
			else
				x = static_cast<Type *>(x->second.second.second);
		}
		if (compare_(key, y->first.first->first))
			return pair<iterator, iterator>(y, y);
		x = tree_successor(y);
		return pair<iterator, iterator>(x, x);
	}
	
	pair<const_iterator,const_iterator> equal_range( const Key& key ) const
	{
		Type *y = 0;
		Type *x = static_cast<Type*>(root.second.second.first);

		while (x != NULL)
		{
			y = x;
			if (compare_(key, x->first.first->first))
				x = static_cast<Type *>(x->second.second.first);
			else if (!compare_(x->first.first->first, key))
				return pair<iterator, iterator>(x, tree_successor(x));
			else
				x = static_cast<Type *>(x->second.second.second);
		}
		if (compare_(key, y->first.first->first))
			return pair<iterator, iterator>(y, y);
		x = tree_successor(y);
		return pair<iterator, iterator>(x, x);
	}
	
	iterator lower_bound( const Key& key ) { return equal_range(key).first; }
	const_iterator lower_bound( const Key& key ) const { return equal_range(key).first; }
	iterator upper_bound( const Key& key ) { return equal_range(key).second; }
	const_iterator upper_bound( const Key& key ) const { return equal_range(key).second; }

//Observers
	
	key_compare key_comp() const { return compare_; }
	map::value_compare value_comp() const { return compare_; }
	
	private:
	
	Type	*tree_minimum(Type *p) const
	{
		while (p && p->second.second.first)
			p = static_cast<Type *>(p->second.second.first);
		return p;
	}

	Type	*tree_maximum(Type *p) const
	{
		while (p && p->second.second.second)
			p = static_cast<Type *>(p->second.second.second);
		return p;
	}

	Type	*tree_successor(Type *p) const
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

	void	transplant(Type *u, Type *v)
	{
		if (u->second.first == &root)
		{
			root.second.second.first = v;
			root.second.second.second = v;
		}
		else if (u == static_cast<Type*>(u->second.first)->second.second.first)
			static_cast<Type*>(u->second.first)->second.second.first = v;
		else
			static_cast<Type*>(u->second.first)->second.second.second = v;
		if (v != NULL)
			v->second.first = u->second.first;
	}

		void	left_rotate(Type *x)
	{
		Type *y = static_cast<Type*>(x->second.second.second);
		x->second.second.second = y->second.second.first;
		if (y->second.second.first != NULL)
			static_cast<Type*>(y->second.second.first)->second.first = x;
		y->second.first = x->second.first;
		if (x->second.first == &root)
		{
			root.second.second.first = y;
			root.second.second.second = y;
		}
		else if (x == static_cast<Type*>(x->second.first)->second.second.first)
			static_cast<Type*>(x->second.first)->second.second.first = y;
		else
			static_cast<Type*>(x->second.first)->second.second.second = y;
		y->second.second.first = x;
		x->second.first = y;
	}

	void	right_rotate(Type *x)
	{
		Type *y = static_cast<Type*>(x->second.second.first);
		x->second.second.first = y->second.second.second;
		if (y->second.second.second != NULL)
			static_cast<Type*>(y->second.second.second)->second.first = x;
		y->second.first = x->second.first;
		if (x->second.first == &root)
		{
			root.second.second.first = y;
			root.second.second.second = y;
		}
		else if (x == static_cast<Type*>(x->second.first)->second.second.first)
			static_cast<Type*>(x->second.first)->second.second.first = y;
		else
			static_cast<Type*>(x->second.first)->second.second.second = y;
		y->second.second.second = x;
		x->second.first = y;
	}

	int	calculate_balance(Type *x)
	{
		if (x->second.second.first && x->second.second.second)
			return static_cast<Type*>(x->second.second.second)->first.second - static_cast<Type*>(x->second.second.first)->first.second;
		else if (x->second.second.first)
			return -static_cast<Type*>(x->second.second.first)->first.second;
		else if (x->second.second.second)
			return static_cast<Type*>(x->second.second.second)->first.second;
		return 0;
	}

	int	calculate_height(Type *x)
	{
		if (x->second.second.first && x->second.second.second)
			return MAX(static_cast<Type*>(x->second.second.second)->first.second, static_cast<Type*>(x->second.second.first)->first.second) + 1;
		else if (x->second.second.first)
			return static_cast<Type*>(x->second.second.first)->first.second + 1;
		else if (x->second.second.second)
			return static_cast<Type*>(x->second.second.second)->first.second + 1;
		return 1;
	}

	void balance_tree(Type *z)
	{
		Type *x = static_cast<Type*>(z->second.first);

		while (x != &root)
		{
			int balance_z = calculate_balance(z);
			int balance_x = calculate_balance(x);

			if (balance_x == 2 || balance_x == -2)
			{
				if (balance_x == 2 && balance_z == 1)
					left_rotate(x);
				else if (balance_x == -2 && balance_z == -1)
					right_rotate(x);
				else if (balance_x == 2 && balance_z == -1)
				{
					right_rotate(z);
					left_rotate(x);
				}
				else if (balance_x == -2 && balance_z == 1)
				{
					left_rotate(z);
					right_rotate(x);
				}
				x->first.second = calculate_height(x);
				z->first.second = calculate_height(z);
			}
			else
				x->first.second = calculate_height(x);

			z = x;
			x = static_cast<Type*>(x->second.first);
		}
	}

	size_type				size_;
	value_type				sample;
	Type					root;
	allocator_type			allocator_;
	Allocator_node			node_alloc;
	key_compare				compare_;
	
};

template< class Key, class T, class Compare, class Alloc >
bool operator==( const map<Key,T,Compare,Alloc>& lhs,
                 const map<Key,T,Compare,Alloc>& rhs )
{
	if (lhs.size() != rhs.size())
		return false;
	for (typename map<Key,T,Compare,Alloc>::const_iterator it = lhs.begin(), ite = rhs.begin(); it != lhs.end(); ++it, ++ite)
	{
		if (*it != *ite)
			return false;
	}
	return true;
}

template< class Key, class T, class Compare, class Alloc >
bool operator!=( const map<Key,T,Compare,Alloc>& lhs,
                 const map<Key,T,Compare,Alloc>& rhs )
{
	return !(lhs == rhs);
}

template< class Key, class T, class Compare, class Alloc >
bool operator<( const map<Key,T,Compare,Alloc>& lhs,
                const map<Key,T,Compare,Alloc>& rhs )
{
	typename map<Key,T,Compare,Alloc>::const_iterator it = lhs.begin(), ite = rhs.begin();
	for (; it != lhs.end() && ite != rhs.end(); ++it, ++ite)
	{
		if (*it != *ite)
			return *it < *ite;
	}
	if (ite != rhs.end())
		return (true);
	return (false);
}

template< class Key, class T, class Compare, class Alloc >
bool operator<=( const map<Key,T,Compare,Alloc>& lhs,
                 const map<Key,T,Compare,Alloc>& rhs )
{
	return !(rhs < lhs);
}

template< class Key, class T, class Compare, class Alloc >
bool operator>( const map<Key,T,Compare,Alloc>& lhs,
                const map<Key,T,Compare,Alloc>& rhs )
{
	return rhs < lhs;
}

template< class Key, class T, class Compare, class Alloc >
bool operator>=( const map<Key,T,Compare,Alloc>& lhs,
                 const map<Key,T,Compare,Alloc>& rhs )
{
	return !(lhs < rhs);
}

template< class Key, class T, class Compare, class Alloc >
void swap( map<Key,T,Compare,Alloc>& lhs, 
           map<Key,T,Compare,Alloc>& rhs )
{
	lhs.swap(rhs);
}

}

#endif