/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:18:40 by mnathali          #+#    #+#             */
/*   Updated: 2022/10/16 00:25:32 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <stack>
#include <list>
#include <map>
#include "templates/Vector.hpp"
#include "templates/Map.hpp"
#include "templates/Stack.hpp"
#include <iomanip>

int main(int argc, char const *argv[])
{
	int sz = 5;
	if (argc > 1 && std::stoi(argv[1]) > 0)
		sz = std::stoi(argv[1]);
	std::list<ft::pair<int,int> > L(sz); int i = 1;
	for(std::list<ft::pair<int,int> >::iterator it = L.begin(); it != L.end(); it++, i++)
		*it = ft::make_pair(i, i*i);
	std::list<std::pair<int,int> > L_s(sz); i = 1;
	for(std::list<std::pair<int,int> >::iterator it = L_s.begin(); it != L_s.end(); it++, i++)
		*it = std::make_pair(i, i*i);

	std::greater<int> comp;
	std::cout << std::left;
	ft::map<int,int> A;
	ft::map<int,int, std::greater<int> > B(comp);
	ft::map<int,int> C(L.begin(), L.end());
	ft::map<std::string, double> D;

	std::map<int,int> A_s;
	std::map<int,int, std::greater<int> > B_s(comp);
	std::map<int,int> C_s(L_s.begin(), L_s.end());
	std::map<std::string, double> D_s;

	std::cout << "ft:: before insert empty = " << A.empty() << std::endl;
	std::cout << "std:: before insert empty = " << A_s.empty() << std::endl;
	for (int i = 0; i < sz; ++i)
	{
		int a = rand(), b = rand();std::cout << a << std::endl;
		A.insert(ft::make_pair(a, b));
		A_s.insert(std::make_pair(a, b));
	}
	std::cout << "---------After insert----------\n";
	std::cout << "ft:: after insert empty = " << A.empty() << std::endl;
	std::cout << "std:: after insert empty = " << A_s.empty() << std::endl;
	{
		ft::map<int, int> copy = A;
		ft::map<int, int> eq;
		std::map<int, int> copy_s = A_s;
		std::map<int, int> eq_s;
		eq_s = copy_s;
		eq = copy;
		ft::map<int,int>::iterator it = eq.begin();
		std::map<int,int>::iterator ite = eq_s.begin();
		std::cout << "size:" << eq.size() << " " << eq_s.size() << std::endl;
		while (it != eq.end())
		{
			std::cout << "key = " << std::setw(11) << it->first << " value = " << std::setw(11) << it->second << "   |   " << "key = " << std::setw(11) << ite->first << " value = " << std::setw(11) << ite->second << std::endl;
			it++;
			ite++;
		}
	}
	std::cout << "---------accessors----------\n";
	A[4221] = 1224;
	A_s[4221] = 1224;
	std::cout<< A[4221] << " " << A.at(4221) << " | " << A_s[4221] << " " << A_s.at(4221) << std::endl;

	for (ft::map<int, int>::iterator it = A.begin(); it != A.end(); ++it)
		B.insert(*it);
	for (std::map<int, int>::iterator it = A_s.begin(); it != A_s.end(); ++it)
		B_s.insert(*it);

	std::cout << "---------iterator----------\n";
	{
		ft::map<int,int>::iterator it = B.begin();
		std::map<int,int>::iterator ite = B_s.begin();
		while (it != B.end())
		{
			std::cout << "key = " << std::setw(11) << it->first << " value = " << std::setw(11) << it->second << "   |   " << "key = " << std::setw(11) << ite->first << " value = " << std::setw(11) << ite->second << std::endl;
			it++;
			ite++;
		}
	}
	std::cout << "---------const_iterator----------\n";
	{
		ft::map<int,int>::const_iterator it = B.begin();
		std::map<int,int>::const_iterator ite = B_s.begin();
		while (it != B.end())
		{
			std::cout << "key = " << std::setw(11) << it->first << " value = " << std::setw(11) << it->second << "   |   " << "key = " << std::setw(11) << ite->first << " value = " << std::setw(11) << ite->second << std::endl;
			it++;
			ite++;
		}
	}
	std::cout << "---------reverse_iterator----------\n";
	{
		ft::map<int,int>::reverse_iterator it = B.rbegin();
		std::map<int,int>::reverse_iterator ite = B_s.rbegin();
		while (it != B.rend())
		{
			std::cout << "key = " << std::setw(11) << it->first << " value = " << std::setw(11) << it->second << "   |   " << "key = " << std::setw(11) << ite->first << " value = " << std::setw(11) << ite->second << std::endl;
			it++;
			ite++;
		}
	}
	std::cout << "---------const_reverse_iterator----------\n";
	{
		ft::map<int,int>::const_reverse_iterator it = B.rbegin();
		std::map<int,int>::const_reverse_iterator ite = B_s.rbegin();
		while (it != B.rend())
		{
			std::cout << "key = " << std::setw(11) << it->first << " value = " << std::setw(11) << it->second << "   |   " << "key = " << std::setw(11) << ite->first << " value = " << std::setw(11) << ite->second << std::endl;
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
		ft::map<int,int>::iterator it = A.begin();
		std::map<int,int>::iterator ite = A_s.begin();
		while (it != A.end())
		{
			std::cout << "key = " << std::setw(11) << it->first << " value = " << std::setw(11) << it->second << "   |   " << "key = " << std::setw(11) << ite->first << " value = " << std::setw(11) << ite->second << std::endl;
			it++;
			ite++;
		}
	}
	{
		A.insert(A.begin(), ft::make_pair(1,12));
		A.insert(--A.end(), ft::make_pair(1,12));
		A_s.insert(A_s.begin(), std::make_pair(1,12));
		A.insert(A.end(), ft::make_pair(2147483647,12));
		A_s.insert(A_s.end(), std::make_pair(2147483647,12));
		A.insert(A.begin(), ft::make_pair(2147483647,12));
		A_s.insert(A_s.begin(), std::make_pair(2147483647,12));
		int r = rand();
		ft::map<int,int>::iterator it = A.begin();
		std::map<int,int>::iterator ite = A_s.begin();
		for (std::size_t i = A.size(); i > A.size()/2; --i, ++it, ++ite)
			;
		A.insert(it, ft::make_pair(r,18));
		A_s.insert(ite, std::make_pair(r,18));
	}
	std::cout << "-------insert using hint----------\n";
	{
		ft::map<int,int>::iterator it = A.begin();
		std::map<int,int>::iterator ite = A_s.begin();
		while (it != A.end())
		{
			std::cout << "key = " << std::setw(11) << it->first << " value = " << std::setw(11) << it->second << "   |   " << "key = " << std::setw(11) << ite->first << " value = " << std::setw(11) << ite->second << std::endl;
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
		ft::map<int,int>::iterator it = A.begin();
		std::map<int,int>::iterator ite = A_s.begin();
		while (ite != A_s.end())
		{
			std::cout << "key = " << std::setw(11) << it->first << " value = " << std::setw(11) << it->second << "   |   " << "key = " << std::setw(11) << ite->first << " value = " << std::setw(11) << ite->second << std::endl;
			it++;
			ite++;
		}
	}

	A.swap(C);
	A_s.swap(C_s);
	A.insert(ft::make_pair(sz*2, sz));
	A_s.insert(std::make_pair(sz*2, sz));
	std::cout << "-------member swap----------\n";
	{
		ft::map<int,int>::iterator it = A.begin();
		std::map<int,int>::iterator ite = A_s.begin();
		while (ite != A_s.end())
		{
			std::cout << "key = " << std::setw(11) << it->first << " value = " << std::setw(11) << it->second << "   |   " << "key = " << std::setw(11) << ite->first << " value = " << std::setw(11) << ite->second << std::endl;
			it++;
			ite++;
		}
	}

	std::cout << "---------Lookup--------\n";
	std::cout << A.count(1) << " " << A.count(sz + 1) << " " << A.find(5)->second << " " << A.find(sz+1)->second << " " << A.equal_range(3).first->first << " " << A.equal_range(3).second->first;
	std::cout << " " << A.equal_range(sz+1).first->first << " " << A.lower_bound(sz+1)->first << " " << A.lower_bound(sz*sz)->first << " " << A.upper_bound(sz+1)->first << " " << A.upper_bound(sz*sz)->first << std::endl;
	std::cout << A_s.count(1) << " " << A_s.count(sz + 1) << " " << A_s.find(5)->second << " " << A_s.find(sz+1)->second << " " << A_s.equal_range(3).first->first << " " << A_s.equal_range(3).second->first;
	std::cout << " " << A_s.equal_range(sz+1).first->first << " " << A_s.lower_bound(sz+1)->first << " " << A_s.lower_bound(sz*sz)->first << " " << A_s.upper_bound(sz+1)->first << " " << A_s.upper_bound(sz*sz)->first << std::endl;


	D.insert(ft::make_pair("Hello world", 5.0));
	D.insert(ft::make_pair(", ", 5.0));
	D.insert(ft::make_pair("My", 5.0));
	D.insert(ft::make_pair("Name", 5.0));
	D.insert(ft::make_pair("Is", 5.0));
	D.insert(ft::make_pair("Aizek", 5.0));
	D_s.insert(std::make_pair("Hello world", 5.0));
	D_s.insert(std::make_pair(", ", 5.0));
	D_s.insert(std::make_pair("My", 5.0));
	D_s.insert(std::make_pair("Name", 5.0));
	D_s.insert(std::make_pair("Is", 5.0));
	D_s.insert(std::make_pair("Aizek", 5.0));

	const ft::map<std::string,double> copy = D;
	const std::map<std::string,double> copy_s = D_s;
	D.erase(D.begin());
	D_s.erase(D_s.begin());
	{
		ft::map<std::string,double>::iterator it = D.begin();
		std::map<std::string,double>::iterator ite = D_s.begin();
		while (ite != D_s.end())
		{
			std::cout << "key = " << std::setw(11) << it->first << " value = " << std::setw(11) << it->second << "   |   " << "key = " << std::setw(11) << ite->first << " value = " << std::setw(11) << ite->second << std::endl;
			it++;
			ite++;
		}
	}
	std::cout << "---------Comparisons--------\n";
	std::cout << (copy == D) << " " << (copy != D) << " " << (copy < D) << " " << (copy > D) << " " << (copy <= D) << " " << (copy >= D) << std::endl;
	std::cout << (copy_s == D_s) << " " << (copy_s != D_s) << " " << (copy_s < D_s) << " " << (copy_s > D_s) << " " << (copy_s <= D_s) << " " << (copy_s >= D_s) << std::endl;

	std::cout << "---------Constant object and const methods--------\n";

	const ft::map<int, int> cap(L.begin(), L.end());

	for (ft::map<int, int>::const_iterator it = cap.begin(); it != cap.end() ;++it)
		std::cout << "key = " << std::setw(11) << it->first << " value = " << std::setw(11) << it->second << std::endl;
	for (ft::map<int, int>::const_reverse_iterator it = cap.rbegin(); it != cap.rend() ;++it)
		std::cout << "key = " << std::setw(11) << it->first << " value = " << std::setw(11) << it->second << std::endl;

	std::cout << "at const: " << cap.at(3) << " | const count:" << cap.count(3) << " | const find:" << cap.find(3)->first << " | const equal range:" << cap.equal_range(3).first->first << " " << cap.equal_range(3).second->first;
	std::cout << " | const lower and upper bounds:" << cap.lower_bound(3)->first << " " << cap.upper_bound(3)->first << std::endl;

	return 0;
}