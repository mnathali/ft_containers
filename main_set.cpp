/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_set.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:19:35 by mnathali          #+#    #+#             */
/*   Updated: 2022/10/16 00:32:19 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <stack>
#include <map>
#include <list>
#include <set>
#include "templates/Vector.hpp"
#include "templates/Map.hpp"
#include "templates/Stack.hpp"
#include "templates/Set.hpp"
#include <iomanip>

typedef ft::pair<ft::pair<int*, bool>, ft::pair<void*, ft::pair<void*, void*> > > Type;
int main(int argc, char const *argv[])
{
	int sz = 5;
	if (argc > 1 && std::stoi(argv[1]) > 0)
		sz = std::stoi(argv[1]);
	std::list<int> L(sz); int i = 1;
	for(std::list<int>::iterator it = L.begin(); it != L.end(); it++, i++)
		*it = i;
	std::list<int> L_s(sz); i = 1;
	for(std::list<int>::iterator it = L_s.begin(); it != L_s.end(); it++, i++)
		*it = i;

	std::greater<int> comp;
	std::cout << std::left;
	ft::set<int> A;
	ft::set<int, std::greater<int> > B(comp);
	ft::set<int> C(L.begin(), L.end());
	ft::set<std::string> D;

	std::set<int> A_s;
	std::set<int, std::greater<int> > B_s(comp);
	std::set<int> C_s(L_s.begin(), L_s.end());
	std::set<std::string> D_s;

	std::cout << "ft:: before insert empty = " << A.empty() << std::endl;
	std::cout << "std:: before insert empty = " << A_s.empty() << std::endl;
	for (int i = 0; i < sz; ++i)
	{
		int a = rand();std::cout << a << std::endl;
		A.insert(a);
		A_s.insert(a);
	}
	std::cout << "---------After insert----------\n";
	std::cout << "ft:: after insert empty = " << A.empty() << std::endl;
	std::cout << "std:: after insert empty = " << A_s.empty() << std::endl;
	{
		ft::set<int> copy = A;
		ft::set<int> eq;
		std::set<int> copy_s = A_s;
		std::set<int> eq_s;
		eq_s = copy_s;
		eq = copy;
		ft::set<int>::iterator it = eq.begin();
		std::set<int>::iterator ite = eq_s.begin();
		std::cout << "size:" << eq.size() << " " << eq_s.size() << std::endl;
		while (it != eq.end())
		{
			std::cout << "key = " << std::setw(11) << *it << "   |   " << "key = " << std::setw(11) << *ite << std::endl;
			it++;
			ite++;
		}
	}

	for (ft::set<int>::iterator it = A.begin(); it != A.end(); ++it)
		B.insert(*it);
	for (std::set<int>::iterator it = A_s.begin(); it != A_s.end(); ++it)
		B_s.insert(*it);


		std::cout << "---------iterator----------\n";
	{
		ft::set<int>::iterator it = B.begin();
		std::set<int>::iterator ite = B_s.begin();
		while (it != B.end())
		{
			std::cout << "key = " << std::setw(11) << *it << "   |   " << "key = " << std::setw(11) << *ite << std::endl;
			it++;
			ite++;
		}
	}
	std::cout << "---------const_iterator----------\n";
	{
		ft::set<int>::const_iterator it = B.begin();
		std::set<int>::const_iterator ite = B_s.begin();
		while (it != B.end())
		{
			std::cout << "key = " << std::setw(11) << *it << "   |   " << "key = " << std::setw(11) << *ite << std::endl;
			it++;
			ite++;
		}
	}
	std::cout << "---------reverse_iterator----------\n";
	{
		ft::set<int>::reverse_iterator it = B.rbegin();
		std::set<int>::reverse_iterator ite = B_s.rbegin();
		while (it != B.rend())
		{
			std::cout << "key = " << std::setw(11) << *it << "   |   " << "key = " << std::setw(11) << *ite << std::endl;
			it++;
			ite++;
		}
	}
	std::cout << "---------const_reverse_iterator----------\n";
	{
		ft::set<int>::const_reverse_iterator it = B.rbegin();
		std::set<int>::const_reverse_iterator ite = B_s.rbegin();
		while (it != B.rend())
		{
			std::cout << "key = " << std::setw(11) << *it << "   |   " << "key = " << std::setw(11) << *ite << std::endl;
			it++;
			ite++;
		}
	}
	std::cout << "---------empty, size, max_size----------\n";
	std::cout << A.empty() << " " << A.size() << " " << A.max_size() << " | " << A_s.empty() << " " << A_s.size() << " " << A_s.max_size() << std::endl;

	std::cout << "---------after clear----------\n";
	A.clear();A_s.clear();
	std::cout << A.empty() << " " << A.size() << " " << A.max_size() << " | " << A_s.empty() << " " << A_s.size() << " " << A_s.max_size() << std::endl;
	
	A.insert(L.begin(), L.end());
	A_s.insert(L_s.begin(), L_s.end());
	std::cout << "-------insert using iterators----------\n";
	{
		ft::set<int>::iterator it = A.begin();
		std::set<int>::iterator ite = A_s.begin();
		while (it != A.end())
		{
			std::cout << "key = " << std::setw(11) << *it << "   |   " << "key = " << std::setw(11) << *ite << std::endl;
			++it;
			++ite;
		}
	}
	{
		A.insert(A.begin(), 1);
		A.insert(--A.end(), 1);
		A_s.insert(A_s.begin(), 1);
		A.insert(A.end(), 2147483647);
		A_s.insert(A_s.end(), 2147483647);
		A.insert(A.begin(), 2147483647);
		A_s.insert(A_s.begin(), 2147483647);
		int r = rand();
		ft::set<int>::iterator it = A.begin();
		std::set<int>::iterator ite = A_s.begin();
		for (std::size_t i = A.size(); i > A.size()/2; --i, ++it, ++ite)
			;
		A.insert(it, r);
		A_s.insert(ite, r);
	}
	std::cout << "-------insert using hint----------\n";
	{
		ft::set<int>::iterator it = A.begin();
		std::set<int>::iterator ite = A_s.begin();
		while (it != A.end())
		{
			std::cout << "key = " << std::setw(11) << *it << "   |   " << "key = " << std::setw(11) << *ite << std::endl;
			it++;
			ite++;
		}
	}

	std::cout << "-------erases----------\n";
	A.erase(A.find(3));
	A.erase(5);
	A_s.erase(A_s.find(3));
	A_s.erase(5);
	A.erase(--(--A.end()), A.end());
	A_s.erase(--(--A_s.end()), A_s.end());
	{
		ft::set<int>::iterator it = A.begin();
		std::set<int>::iterator ite = A_s.begin();
		while (ite != A_s.end())
		{
			std::cout << "key = " << std::setw(11) << *it << "   |   " << "key = " << std::setw(11) << *ite << std::endl;
			it++;
			ite++;
		}
	}

	A.swap(C);
	A_s.swap(C_s);
	A.insert(sz*2);
	A_s.insert(sz*2);
	std::cout << "-------member swap----------\n";
	{
		ft::set<int>::iterator it = A.begin();
		std::set<int>::iterator ite = A_s.begin();
		while (ite != A_s.end())
		{
			std::cout << "key = " << std::setw(11) << *it << "   |   " << "key = " << std::setw(11) << *ite << std::endl;
			it++;
			ite++;
		}
	}

	std::cout << "---------Lookup--------\n";
	std::cout << A.count(1) << " " << A.count(sz + 1) << " " << *A.find(5) << " " << *A.find(sz+1) << " " << *A.equal_range(3).first << " " << *A.equal_range(3).second;
	std::cout << " " << *A.equal_range(sz+1).first << " " << *A.lower_bound(sz+1) << " " << *A.lower_bound(sz*sz) << " " << *A.upper_bound(sz+1) << " " << *A.upper_bound(sz*sz) << std::endl;
	std::cout << A_s.count(1) << " " << A_s.count(sz + 1) << " " << *A_s.find(5) << " " << *A_s.find(sz+1) << " " << *A_s.equal_range(3).first << " " << *A_s.equal_range(3).second;
	std::cout << " " << *A_s.equal_range(sz+1).first << " " << *A_s.lower_bound(sz+1) << " " << *A_s.lower_bound(sz*sz) << " " << *A_s.upper_bound(sz+1) << " " << *A_s.upper_bound(sz*sz) << std::endl;


	D.insert("Hello world");
	D.insert(", ");
	D.insert("My");
	D.insert("Name");
	D.insert("Is");
	D.insert("Aizek");
	D_s.insert("Hello world");
	D_s.insert(", ");
	D_s.insert("My");
	D_s.insert("Name");
	D_s.insert("Is");
	D_s.insert("Aizek");

	const ft:: set<std::string> copy = D;
	const std::set<std::string> copy_s = D_s;
	D.erase(D.begin());
	D_s.erase(D_s.begin());
	{
		ft::set<std::string>::iterator it = D.begin();
		std::set<std::string>::iterator ite = D_s.begin();
		while (ite != D_s.end())
		{
			std::cout << "key = " << std::setw(11) << *it << "   |   " << "key = " << std::setw(11) << *ite << std::endl;
			it++;
			ite++;
		}
	}
	std::cout << "---------Comparisons--------\n";
	std::cout << (copy == D) << " " << (copy != D) << " " << (copy < D) << " " << (copy > D) << " " << (copy <= D) << " " << (copy >= D) << std::endl;
	std::cout << (copy_s == D_s) << " " << (copy_s != D_s) << " " << (copy_s < D_s) << " " << (copy_s > D_s) << " " << (copy_s <= D_s) << " " << (copy_s >= D_s) << std::endl;

	std::cout << "---------Constant object and const methods--------\n";

	const ft::set<int> cap(L.begin(), L.end());

	for (ft::set<int>::const_iterator it = cap.begin(); it != cap.end() ;++it)
		std::cout << "key = " << std::setw(11) << *it << std::endl;
	for (ft::set<int>::const_reverse_iterator it = cap.rbegin(); it != cap.rend() ;++it)
		std::cout << "key = " << std::setw(11) << *it << std::endl;

	std::cout << "const count:" << cap.count(3) << " | const find:" << *cap.find(3) << " | const equal range:" << *cap.equal_range(3).first << " " << *cap.equal_range(3).second;
	std::cout << " | const lower and upper bounds:" << *cap.lower_bound(3) << " " << *cap.upper_bound(3) << std::endl;


	return 0;
}
