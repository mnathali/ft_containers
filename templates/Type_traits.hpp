/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:37:15 by mnathali          #+#    #+#             */
/*   Updated: 2022/10/02 23:59:07 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include "Utility.hpp"

namespace ft
{

template <class T, T v>
struct integral_constant {
	static const T value = v;
	typedef T value_type;
	typedef integral_constant<T,v> type;
	operator T() const { return v; }
	operator bool() { return static_cast<bool>(v); }
};

template <class T>
struct is_integral : integral_constant<bool, 0> {};

template <>
struct is_integral<bool> : integral_constant<bool, 1> {};

template <>
struct is_integral<char> : integral_constant<bool, 1> {};

template <>
struct is_integral<wchar_t> : integral_constant<bool, 1> {};

template <>
struct is_integral<signed char> : integral_constant<bool, 1> {};

template <>
struct is_integral<int> : integral_constant<bool, 1> {};

template <>
struct is_integral<short int> : integral_constant<bool, 1> {};

template <>
struct is_integral<long int> : integral_constant<bool, 1> {};

template <>
struct is_integral<long long int> : integral_constant<bool, 1> {};

template <>
struct is_integral<unsigned char> : integral_constant<bool, 1> {};

template <>
struct is_integral<unsigned int> : integral_constant<bool, 1> {};

template <>
struct is_integral<unsigned short int> : integral_constant<bool, 1> {};

template <>
struct is_integral<unsigned long int> : integral_constant<bool, 1> {};

template <>
struct is_integral<unsigned long long int> : integral_constant<bool, 1> {};

template <class T>
struct is_builtin : is_integral<T> {};

template <>
struct is_builtin<float> : is_integral<bool> {};

template <>
struct is_builtin<double> : is_integral<bool> {};

template <>
struct is_builtin<long double> : is_integral<bool> {};

template<bool B, class T = void>
struct enable_if { typedef void type; };
 
template<class T>
struct enable_if<true, T> { typedef T type; };

template<class T, class U>
struct is_same
{
	static const bool value = false;
};

template<class T>
struct is_same<T, T>
{
	static const bool value = true;
};

}


#endif