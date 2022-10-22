/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 00:11:43 by mnathali          #+#    #+#             */
/*   Updated: 2022/10/09 15:44:50 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
#define UTILITY_HPP
namespace ft
{

template< class T1, class T2 >
struct pair
{

	typedef T1	first_type;
	typedef T2	second_type;

	pair() try : first(), second() {}
	catch(const std::exception& e)
	{
		throw;
	}
	
	pair( const T1& x, const T2& y ) try : first(x), second(y) {}
	catch(const std::exception& e)
	{
		throw;
	}

	template< class U1, class U2 >
	pair( const pair<U1, U2>& p ) try : first(p.first), second(p.second) {}
	catch(const std::exception& e)
	{
		throw;
	}

	pair& operator=( const pair& other )
	{
		first = other.first;
		second = other.second;
		return *this;
	}

	first_type	first;
	second_type	second;
};

template< class T1, class T2 >
pair<T1, T2> make_pair( T1 t, T2 u )
{
	return pair<T1, T2>(t, u);
}

template< class T1, class T2 >
bool operator==( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return lhs.first == rhs.first && lhs.second == rhs.second; }

template< class T1, class T2 >
bool operator!=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return !(lhs == rhs); }

template< class T1, class T2 >
bool operator<( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return lhs.first == rhs.first ? lhs.second < rhs.second : lhs.first < rhs.first; }

template< class T1, class T2 >
bool operator<=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return !(lhs > rhs); }

template< class T1, class T2 >
bool operator>( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return rhs < lhs; }

template< class T1, class T2 >
bool operator>=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return !(lhs < rhs); }

template< class T >
struct less
{
	
	bool operator()( const T& lhs, const T& rhs ) const { return lhs < rhs; }

};

}
#endif