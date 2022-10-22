/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 23:08:50 by mnathali          #+#    #+#             */
/*   Updated: 2022/10/16 02:08:13 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include "Iterator_traits.hpp"
#include "Type_traits.hpp"

namespace ft
{

template< class InputIt1, class InputIt2 >
bool equal( typename enable_if<is_iterator<InputIt1>::value, InputIt1>::type first1, InputIt1 last1,
			InputIt2 first2 )
{
	for (; first1 != last1 && *first1 == *first2; ++first1, ++first2)
		;
	if (first1 == last1)
		return true;
	return (false);
}

template< class InputIt1, class InputIt2, class BinaryPredicate >
bool equal( typename enable_if<is_iterator<InputIt1>::value, InputIt1>::type first1, InputIt1 last1, 
			InputIt2 first2, BinaryPredicate p )
{
	for (; first1 != last1 && p(*first1, *first2); ++first1)
		;
	if (first1 == last1)
		return true;
	return (false);
}

template< class InputIt1, class InputIt2 >
bool lexicographical_compare( typename enable_if<is_iterator<InputIt1>::value, InputIt1>::type first1, InputIt1 last1,
			typename enable_if<is_iterator<InputIt2>::value, InputIt2>::type first2, InputIt2 last2 )
{
	for (; first1 != last1 && first2 != last2 && *first1 == *first2; ++first1, ++first2)
		;
	if (first1 != last1 && first2 != last2)
		return (*first1 < *first2);
	else if (first1 == last1 && first2 != last2)
		return (true);
	return (false);
}

template< class InputIt1, class InputIt2, class Compare >
bool lexicographical_compare( typename enable_if<is_iterator<InputIt1>::value, InputIt1>::type first1, InputIt1 last1,
			typename enable_if<is_iterator<InputIt2>::value, InputIt2>::type first2, InputIt2 last2, Compare comp )
{
	for (; first1 != last1 && first2 != last2 && *first1 == *first2; ++first1, ++first2)
		;
	if (first1 != last1 && first2 != last2)
		return (comp(*first1, *first2));
	else if (first1 == last1 && first2 != last2)
		return (true);
	return (false);
}

}

#endif