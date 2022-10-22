/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:24:59 by mnathali          #+#    #+#             */
/*   Updated: 2022/10/22 12:45:38 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP

#include <iostream>
#include "Utility.hpp"
#include "Iterator.hpp"
#define RED		true
#define BLACK	false

namespace ft
{

template<class Key, class Compare = less<Key>,
	class Allocator = std::allocator<Key> >
class set
{

	typedef pair<pair<Key*, bool>, pair<void*, pair<void*, void*> > >	Type;
	typedef typename Allocator::template rebind<Type>::other			Allocator_node;	

	public:
	
	typedef	Key																				key_type;
	typedef Key																				value_type;
	typedef std::size_t																		size_type;
	typedef std::ptrdiff_t																	difference_type;
	typedef Compare																			key_compare;
	typedef Compare																			value_compare;
	typedef Allocator																		allocator_type;
	typedef value_type&																		reference;
	typedef const value_type&																const_reference;
	typedef typename Allocator::pointer														pointer;
	typedef typename Allocator::const_pointer												const_pointer;
	typedef BDIterator<pair<pair<Key*, bool>, pair<void*, pair<void*, void*> > > >			iterator;
	typedef BDIterator<pair<pair<const Key*, bool>, pair<void*, pair<void*, void*> > > >	const_iterator;
	typedef ft::reverse_iterator<iterator>													reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>											const_reverse_iterator;

	set() : size_(0)
	{
		root.first.first = &sample;
		root.first.second = BLACK;
		root.second.first = NULL;
		root.second.second.second = NULL;
		root.second.second.first = NULL;
	}
	
	explicit set( const Compare& comp, 
              const Allocator& alloc = Allocator() ) : size_(0), allocator_(alloc), compare_(comp)
	{
		root.first.first = &sample;
		root.first.second = BLACK;
		root.second.first = NULL;
		root.second.second.second = NULL;
		root.second.second.first = NULL;

	}

	template< class InputIt >
	set( InputIt first, typename enable_if<is_iterator<InputIt>::value, InputIt>::type last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) : size_(0), allocator_(alloc), compare_(comp)
	{
		root.first.first = &sample;
		root.first.second = BLACK;
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
	
	set( const set& other ) : size_(other.size_), allocator_(other.allocator_), compare_(other.compare_)
	{
		Type *y = static_cast<Type*>(other.root.second.second.first);
		Type *x = &root;
		Type *p = NULL;
		root.second.second.first = NULL;
		root.second.second.second = NULL;
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
			p->second.first = x;
			p->second.second.first = NULL;
			p->second.second.second = NULL;
			if (static_cast<Type*>(y->second.first)->second.second.first == y)
				x->second.second.first = p;
			else
				x->second.second.second = p;
			x = p;
			if (y->second.second.first != NULL)
				y = static_cast<Type*>(y->second.second.first);
			else if (y->second.second.second != NULL)
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
	
	~set()
	{
		if (size_ == 0)
			return ;

		Type	*y = static_cast<Type*>(root.second.second.first);
		Type	*x = 0;
		
		while (y != &root)
		{
			if (y->second.second.first != NULL)
				y = static_cast<Type*>(y->second.second.first);
			else if (y->second.second.second != NULL)
				y = static_cast<Type*>(y->second.second.second);
			else
			{
				x = y;
				y = static_cast<Type*>(y->second.first);
				if (y->second.second.first == x)
					y->second.second.first = NULL;
				if (y->second.second.second == x)
					y->second.second.second = NULL;
				allocator_.destroy(x->first.first);
				allocator_.deallocate(x->first.first, 1);
				node_alloc.deallocate(x, 1);
			}
		}
	}

	set& operator=( const set& other )
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
				p->second.first = x;
				p->second.second.first = NULL;
				p->second.second.second = NULL;
				if (static_cast<Type*>(y->second.first)->second.second.first == y)
					x->second.second.first = p;
				else
					x->second.second.second = p;
				x = p;
				if (y->second.second.first != NULL)
					y = static_cast<Type*>(y->second.second.first);
				else if (y->second.second.second != NULL)
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

//iterators

	iterator				begin() { return tree_minimum(&root); }
	const_iterator			begin() const { return iterator(tree_minimum(const_cast<Type *>(&root))); }
	iterator				end() { return &root; }
	const_iterator			end() const { return iterator(const_cast<Type *>(&root)); }
	reverse_iterator		rbegin() { return reverse_iterator(iterator(&root)); }
	const_reverse_iterator	rbegin() const { return reverse_iterator(iterator(const_cast<Type *>(&root))); }
	reverse_iterator		rend() { return reverse_iterator(iterator(tree_minimum(&root))); }
	const_reverse_iterator	rend() const { return reverse_iterator(iterator(tree_minimum(const_cast<Type *>(&root)))); }

//Capacity

	size_type	size() const { return size_; }
	bool		empty() const { return size_ ? false : true; }
	size_type	max_size() const { return std::numeric_limits<size_type>::max() / (sizeof(pair<Key*, pair<void*, pair<void*, void*> > >)); }

//modifiers
	void clear()
	{
		Type	*y = static_cast<Type*>(root.second.second.first);
		Type	*x = NULL;
		while (y && y != &root)
		{
			if (y->second.second.first != NULL)
				y = static_cast<Type*>(y->second.second.first);
			else if (y->second.second.second != NULL)
				y = static_cast<Type*>(y->second.second.second);
			else
			{
				x = y;
				y = static_cast<Type*>(y->second.first);
				if (y->second.second.first == x)
					y->second.second.first = NULL;
				if (y->second.second.second == x)
					y->second.second.second = NULL;
				allocator_.destroy(x->first.first);
				allocator_.deallocate(x->first.first, 1);
				node_alloc.deallocate(x, 1);
			}
		}
		size_ = 0;
	}


	pair<iterator,bool> insert( const value_type& value )
	{
		Type *z = 0;
		Type *y;

		try
		{
			z = node_alloc.allocate(1);
			z->first.first = NULL;
			z->first.first = allocator_.allocate(1);
			allocator_.construct(z->first.first, value);
			z->second.first = NULL;
			z->second.second.first = NULL;
			z->second.second.second = NULL;
			z->first.second = RED;
		}
		catch(const std::exception& e)
		{
			if (z && z->first.first)
				allocator_.deallocate(z->first.first, 1);
			if (z)
				node_alloc.deallocate(z, 1);
			throw;
		}
		y = z;
		if (!rb_insert(z))
		{
			allocator_.deallocate(z->first.first, 1);
			node_alloc.deallocate(z, 1);
			return (pair<iterator, bool>(this->end(), 0));
		}
		size_++;
		return (pair<iterator, bool>(y, 1));
	}
	
	iterator insert( iterator hint, const value_type& value )
	{
		iterator it;
		Type *y = NULL;
		Type *z = NULL;
		Type *x;

		if (compare_(*hint, value))
		{
			while (compare_(*hint, value) && hint != this->end())
				hint++;
		}
		else
		{
			while (compare_(value, *hint) && hint != this->end())
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
					if (compare_(value, *(x->first.first)))
						x = static_cast<Type *>(x->second.second.first);
					else if (!compare_(*(x->first.first), value))
						return x;
					else
						x = static_cast<Type *>(x->second.second.second);
				}
				z = node_alloc.allocate(1);
				z->first.first = NULL;
				z->first.first = allocator_.allocate(1);
				allocator_.construct(z->first.first, value);
				z->second.first = NULL;
				z->second.second.first = NULL;
				z->second.second.second = NULL;
				z->first.second = RED;
				z->second.first = y;
				if (compare_(value, *(y->first.first)))
					y->second.second.first = z;
				else
					y->second.second.second = z;
				rb_insert_fixup(z);
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
		Type	*y = z;
		Type	*x = NULL;
		bool	color = y->first.second;
		Type	tmp = pair<pair<Key*, bool>, pair<void*, pair<void*,void*> > >(pair<Key*, bool>(&sample, 0), pair<void*, pair<void*,void*> >(NULL, pair<void*,void*>(NULL, NULL)));

		pos++;
		if (z->second.second.first == NULL)
		{
			if (z->second.second.second == NULL)
				z->second.second.second = &tmp;
			x = static_cast<Type*>(z->second.second.second);
			transplant(z, static_cast<Type*>(z->second.second.second));
		}
		else if (z->second.second.second == NULL)
		{
			if (z->second.second.first == NULL)
				z->second.second.first = &tmp;
			x = static_cast<Type*>(z->second.second.first);
			transplant(z, static_cast<Type*>(z->second.second.first));
		}
		else
		{
			y = tree_minimum(static_cast<Type*>(z->second.second.second));
			color = y->first.second;
			if (y->second.second.second == NULL)
				y->second.second.second = &tmp;
			x = static_cast<Type*>(y->second.second.second);
			if (y->second.first == z)
				x->second.first = y;
			else
			{
				transplant(y, static_cast<Type*>(y->second.second.second));
				y->second.second.second = z->second.second.second;
				static_cast<Type*>(y->second.second.second)->second.first = y;
			}
			transplant(z, y);
			y->second.second.first = z->second.second.first;
			static_cast<Type*>(y->second.second.first)->second.first = y;
			y->first.second = z->first.second;
		}
		if (color == BLACK)
			rb_delete_fixup(x);
		if (tmp.second.first)
		{
			if (static_cast<Type*>(tmp.second.first)->second.second.first == &tmp)
				static_cast<Type*>(tmp.second.first)->second.second.first = NULL;
			if (static_cast<Type*>(tmp.second.first)->second.second.second == &tmp)
				static_cast<Type*>(tmp.second.first)->second.second.second = NULL;				
		}
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
			if (compare_(key, *x->first.first))
				x = static_cast<Type *>(x->second.second.first);
			else if (!compare_(*x->first.first, key))
			{
				this->erase(iterator(x));
				return 1;
			}
			else
				x = static_cast<Type *>(x->second.second.second);
		}
		return 0;

	}

	void swap( set& other )
	{
		size_type							sz = size_;
		pair<void*, pair<void*, void*> >	pointers = root.second;
		allocator_type						alloc = allocator_;
		key_compare							comp = compare_;

		size_ = other.size_;
		root.second = other.root.second;
		allocator_ = other.allocator_;
		compare_ = other.compare_;

		other.size_ = sz;
		other.root.second = pointers;
		other.allocator_ = alloc;
		other.compare_ = comp;

		static_cast<Type*>(root.second.second.first)->second.first = &root;
		static_cast<Type*>(other.root.second.second.first)->second.first = &other.root;

	}

//lookup

	size_type count( const Key& key ) const
	{
		Type *x = static_cast<Type*>(root.second.second.first);

		while (x != NULL)
		{
			if (compare_(key, *x->first.first))
				x = static_cast<Type *>(x->second.second.first);
			else if (!compare_(*x->first.first, key))
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
			if (compare_(key, *x->first.first))
				x = static_cast<Type *>(x->second.second.first);
			else if (!compare_(*x->first.first, key))
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
			if (compare_(key, *x->first.first))
				x = static_cast<Type *>(x->second.second.first);
			else if (!compare_(*x->first.first, key))
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
			if (compare_(key, *x->first.first))
				x = static_cast<Type *>(x->second.second.first);
			else if (!compare_(*x->first.first, key))
				return pair<iterator, iterator>(x, tree_successor(x));
			else
				x = static_cast<Type *>(x->second.second.second);
		}
		if (compare_(key, *y->first.first))
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
			if (compare_(key, *x->first.first))
				x = static_cast<Type *>(x->second.second.first);
			else if (!compare_(*x->first.first, key))
				return pair<iterator, iterator>(x, tree_successor(x));
			else
				x = static_cast<Type *>(x->second.second.second);
		}
		if (compare_(key, *y->first.first))
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
	set::value_compare value_comp() const { return compare_; }


	private:

	Type	*tree_minimum(Type *p) const
	{
		while (p->second.second.first != NULL)
			p = static_cast<Type *>(p->second.second.first);
		return p;
	}

	Type	*tree_maximum(Type *p) const
	{
		while (p->second.second.second != NULL)
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

	Type	*tree_predecessor(Type *p) const
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

	void	rb_insert_fixup(Type *z)
	{
		while (static_cast<Type*>(z->second.first)->first.second == RED)
		{
			if (z->second.first == static_cast<Type*>((static_cast<Type*>(z->second.first)->second.first))->second.second.first)
			{
				Type *y = static_cast<Type*>(static_cast<Type*>((static_cast<Type*>(z->second.first)->second.first))->second.second.second);
				if (y && y->first.second == RED)
				{
					static_cast<Type*>(z->second.first)->first.second = BLACK;
					y->first.second = BLACK;
					static_cast<Type*>((static_cast<Type*>(z->second.first)->second.first))->first.second = RED;
					z = static_cast<Type*>((static_cast<Type*>(z->second.first)->second.first));
				}
				else if (z == static_cast<Type*>(z->second.first)->second.second.second)
				{
					z = static_cast<Type*>(z->second.first);
					left_rotate(z);
				}
				else
				{
					static_cast<Type*>(z->second.first)->first.second = BLACK;
					static_cast<Type*>((static_cast<Type*>(z->second.first)->second.first))->first.second = RED;
					right_rotate(static_cast<Type*>((static_cast<Type*>(z->second.first)->second.first)));
				}
			}
			else
			{
				Type *y = static_cast<Type*>(static_cast<Type*>((static_cast<Type*>(z->second.first)->second.first))->second.second.first);
				if (y && y->first.second == RED)
				{
					static_cast<Type*>(z->second.first)->first.second = BLACK;
					y->first.second = BLACK;
					static_cast<Type*>((static_cast<Type*>(z->second.first)->second.first))->first.second = RED;
					z = static_cast<Type*>((static_cast<Type*>(z->second.first)->second.first));
				}
				else if (z == static_cast<Type*>(z->second.first)->second.second.first)
				{
					z = static_cast<Type*>(z->second.first);
					right_rotate(z);
				}
				else
				{
					static_cast<Type*>(z->second.first)->first.second = BLACK;
					static_cast<Type*>((static_cast<Type*>(z->second.first)->second.first))->first.second = RED;
					left_rotate(static_cast<Type*>((static_cast<Type*>(z->second.first)->second.first)));
				}
			}
		}
		static_cast<Type*>(root.second.second.first)->first.second = BLACK;
	}

	bool	rb_insert(Type *z)
	{
		Type	*y = NULL;
		Type	*x = static_cast<Type*>(root.second.second.first);
		
		while (x != NULL)
		{
			y = x;
			if (compare_(*z->first.first, *x->first.first))
				x = static_cast<Type*>(x->second.second.first);
			else if (!compare_(*x->first.first, *z->first.first))
				return false;
			else
				x = static_cast<Type*>(x->second.second.second);
		}
		z->second.first = y;
		if (y == NULL)
		{
			root.second.second.first = z;
			root.second.second.second = z;
			z->second.first = &root;
		}
		else if (compare_(*z->first.first, *y->first.first))
			y->second.second.first = z;
		else
			y->second.second.second = z;
		rb_insert_fixup(z);
		return true;
	}

	void	rb_delete_fixup(Type *x)
	{
		while (x != root.second.second.first && x->first.second == BLACK)
		{
			if (x == static_cast<Type*>(x->second.first)->second.second.first)
			{
				Type *w = static_cast<Type*>(static_cast<Type*>(x->second.first)->second.second.second);
				if (w->first.second == RED)
				{
					w->first.second = BLACK;
					static_cast<Type*>(x->second.first)->first.second = RED;
					left_rotate(static_cast<Type*>(x->second.first));
					w = static_cast<Type*>(static_cast<Type*>(x->second.first)->second.second.second);
				}
				if ((!w->second.second.first || static_cast<Type*>(w->second.second.first)->first.second == BLACK) && (!w->second.second.second || static_cast<Type*>(w->second.second.second)->first.second == BLACK))
				{
					w->first.second = RED;
					x = static_cast<Type*>(x->second.first);
				}
				else if (!w->second.second.second || static_cast<Type*>(w->second.second.second)->first.second == BLACK)
				{
					static_cast<Type*>(w->second.second.first)->first.second = BLACK;
					w->first.second = RED;
					right_rotate(w);
					w = static_cast<Type*>(static_cast<Type*>(x->second.first)->second.second.second);
				}
				else
				{
					w->first.second = static_cast<Type*>(x->second.first)->first.second;
					static_cast<Type*>(x->second.first)->first.second = BLACK;
					static_cast<Type*>(w->second.second.second)->first.second = BLACK;
					left_rotate(static_cast<Type*>(x->second.first));
					x = static_cast<Type*>(root.second.second.first);
				}
			}
			else
			{
				Type *w = static_cast<Type*>(static_cast<Type*>(x->second.first)->second.second.first);
				if (w->first.second == RED)
				{
					w->first.second = BLACK;
					static_cast<Type*>(x->second.first)->first.second = RED;
					right_rotate(static_cast<Type*>(x->second.first));
					w = static_cast<Type*>(static_cast<Type*>(x->second.first)->second.second.first);
				}
				if ((!w->second.second.second || static_cast<Type*>(w->second.second.second)->first.second == BLACK) && (!w->second.second.first || static_cast<Type*>(w->second.second.first)->first.second == BLACK))
				{
					w->first.second = RED;
					x = static_cast<Type*>(x->second.first);
				}
				else if (!w->second.second.first || static_cast<Type*>(w->second.second.first)->first.second == BLACK)
				{
					static_cast<Type*>(w->second.second.second)->first.second = BLACK;
					w->first.second = RED;
					left_rotate(w);
					w = static_cast<Type*>(static_cast<Type*>(x->second.first)->second.second.first);
				}
				else
				{
					w->first.second = static_cast<Type*>(x->second.first)->first.second;
					static_cast<Type*>(x->second.first)->first.second = BLACK;
					static_cast<Type*>(w->second.second.first)->first.second = BLACK;
					right_rotate(static_cast<Type*>(x->second.first));
					x = static_cast<Type*>(root.second.second.first);
				}
			}
		}
		x->first.second = BLACK;

	}

	public:

	size_type		size_;
	allocator_type	allocator_;
	key_compare		compare_;
	Key				sample;
	Type			root;
	Allocator_node	node_alloc;

};


template< class Key, class Compare, class Alloc >
bool operator==( const set<Key,Compare,Alloc>& lhs,
                 const set<Key,Compare,Alloc>& rhs )
{
	if (lhs.size() != rhs.size())
		return false;
	for (typename set<Key,Compare,Alloc>::const_iterator it = lhs.begin(), ite = rhs.begin(); it != lhs.end(); ++it, ++ite)
	{
		if (*it != *ite)
			return false;
	}
	return true;
}

template< class Key, class Compare, class Alloc >
bool operator!=( const set<Key,Compare,Alloc>& lhs,
                 const set<Key,Compare,Alloc>& rhs )
{
	return !(lhs == rhs);
}

template< class Key, class Compare, class Alloc >
bool operator<( const set<Key,Compare,Alloc>& lhs,
                const set<Key,Compare,Alloc>& rhs )
{
	typename set<Key,Compare,Alloc>::const_iterator it = lhs.begin(), ite = rhs.begin();
	for (; it != lhs.end() && ite != rhs.end(); ++it, ++ite)
	{
		if (*it != *ite)
			return *it < *ite;
	}
	if (ite != rhs.end())
		return (true);
	return (false);
}

template< class Key, class Compare, class Alloc >
bool operator<=( const set<Key,Compare,Alloc>& lhs,
                 const set<Key,Compare,Alloc>& rhs )
{
	return !(rhs < lhs);
}

template< class Key, class Compare, class Alloc >
bool operator>( const set<Key,Compare,Alloc>& lhs,
                const set<Key,Compare,Alloc>& rhs )
{
	return rhs < lhs;
}

template< class Key, class Compare, class Alloc >
bool operator>=( const set<Key,Compare,Alloc>& lhs,
                 const set<Key,Compare,Alloc>& rhs )
{
	return !(lhs < rhs);
}

template< class Key, class Compare, class Alloc >
void swap( set<Key,Compare,Alloc>& lhs, 
           set<Key,Compare,Alloc>& rhs )
{
	lhs.swap(rhs);
}


}

#endif