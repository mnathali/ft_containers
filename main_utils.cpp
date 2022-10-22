/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 00:46:06 by mnathali          #+#    #+#             */
/*   Updated: 2022/10/16 02:06:06 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "templates/Iterator_traits.hpp"
#include "templates/Type_traits.hpp"
#include "templates/Utility.hpp"
#include "templates/Algorithm.hpp"
#include "templates/Vector.hpp"
#include <iterator>
#include <type_traits>
#include <algorithm>
#include <utility>
#include <vector>

int main(int argc, char const *argv[])
{
	(void)argc; (void)argv;

	ft::vector<int> A(500);
	std::vector<int> B(500);
	ft::vector<int> C(1, 500);
	std::vector<int> D(1, 500);
	D[499] = 2;
	A.pop_back();

	std::cout << ft::lexicographical_compare(A.begin(), A.end(), B.begin(), B.end()) << std::endl;
	std::cout << std::lexicographical_compare(A.begin(), A.end(), B.begin(), B.end()) << std::endl;
	std::cout << ft::lexicographical_compare(A.begin(), A.end(), B.begin(), B.end(), std::greater<int>()) << std::endl;
	std::cout << std::lexicographical_compare(A.begin(), A.end(), B.begin(), B.end(), std::greater<int>()) << std::endl;
	std::cout << ft::equal(C.begin(), C.end(), D.begin()) << std::endl;
	std::cout << std::equal(C.begin(), C.end(), C.begin()) << std::endl;
	std::cout << ft::equal(D.begin(), D.end(), D.begin(), std::greater<int>()) << std::endl;
	std::cout << std::equal(C.begin(), C.end(), D.begin(), std::greater<int>()) << std::endl;
	return 0;
}
