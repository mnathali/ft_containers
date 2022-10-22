/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 12:03:04 by mnathali          #+#    #+#             */
/*   Updated: 2022/10/16 01:23:05 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <iostream>
#include "Type_traits.hpp"

namespace ft
{

template <class Iterator, bool B = !(is_integral<Iterator>::value || is_builtin<Iterator>::value)>
struct iterator_traits
{
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
};

template <class T>
struct iterator_traits<T *, true>
{
	typedef std::ptrdiff_t					difference_type;
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef std::random_access_iterator_tag	iterator_category;
};

template <class T>
struct iterator_traits<const T*, true>
{

	typedef std::ptrdiff_t					difference_type;
	typedef T								value_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	typedef std::random_access_iterator_tag	iterator_category;
};

template <class Iterator>
struct iterator_traits<Iterator, false>
{

	typedef std::size_t							difference_type;
	typedef void								value_type;
	typedef void								pointer;
	typedef void								reference;
	typedef std::output_iterator_tag			iterator_category;
};

template<typename T, typename = typename enable_if<!is_same<typename iterator_traits<T>::value_type, void>::value, T>::type>
struct is_iterator
{
   static const bool value = true;
};

template<typename T>
struct is_iterator<T, void>
{
   static const bool value = false;
};

}


#endif