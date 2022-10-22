/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:18:40 by mnathali          #+#    #+#             */
/*   Updated: 2022/10/16 00:43:16 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <list>
#include "templates/Vector.hpp"

int main(int argc, char const *argv[])
{
	int sz = 5;
	if (argc > 1)
		sz = std::stoi(argv[1]);
	std::list<int> LI(sz); int i = 1;
	for(std::list<int>::iterator it = LI.begin(); it != LI.end(); it++, i++)
		*it = i;
	ft::vector<int>	A(10, 5);
	std::vector<int> A_s(10, 5);
	ft::vector<int> B(LI.begin(), LI.end());
	std::vector<int> B_s(LI.begin(), LI.end());
	ft::vector<std::string> S(134, "Hello world");
	std::vector<std::string> S_s(134, "Hello world");
	ft::vector<char> D;
	std::vector<char> D_s;
	ft::vector<int> C(A);
	std::vector<int> C_s(A_s);

	std::cout << "---------Created with args----------\n";
	{
		ft::vector<int>::iterator it = A.begin();
		std::vector<int>::iterator ite = A_s.begin();
		std::cout << "size:" << A.size() << " " << A_s.size() << " | capacity: " << A.capacity() << " " << A_s.capacity() << std::endl;
		while (it != A.end())
		{
			std::cout << "     " << *it << "   |   " << *ite << std::endl;
			it++;
			ite++;
		}
	}
	std::cout << "---------The same but with const iterator----------\n";
	{
		ft::vector<int>::const_iterator it = A.begin();
		std::vector<int>::const_iterator ite = A_s.begin();
		std::cout << "size:" << A.size() << " " << A_s.size() << " | capacity: " << A.capacity() << " " << A_s.capacity() << std::endl;
		while (it != A.end())
		{
			std::cout <<  "     " << *it << "   |   " << *ite << std::endl;
			it++;
			ite++;
		}
	}
	std::cout << "---------Created from list----------\n";
	{
		ft::vector<int>::iterator it = B.begin();
		std::vector<int>::iterator ite = B_s.begin();
		std::cout << "size:" << B.size() << " " << B_s.size() << " | capacity: " << B.capacity() << " " << B_s.capacity() << std::endl;
		while (it != B.end())
		{
			std::cout <<  "     " << *it << "   |   " << *ite << std::endl;
			it++;
			ite++;
		}
	}
	std::cout << "---------Const reverse iterator----------\n";
	{
		ft::vector<int>::const_reverse_iterator it = A.rbegin();
		std::vector<int>::const_reverse_iterator ite = A_s.rbegin();
		std::cout << "size:" << A.size() << " " << A_s.size() << " | capacity: " << A.capacity() << " " << A_s.capacity() << std::endl;
		while (it != A.rend())
		{
			std::cout <<  "     " << *it << "   |   " << *ite << std::endl;
			it++;
			ite++;
		}
	}
	std::cout << "---------reverse iterator----------\n";
	{
		ft::vector<int>::reverse_iterator it = B.rbegin();
		std::vector<int>::reverse_iterator ite = B_s.rbegin();
		std::cout << "size:" << B.size() << " " << B_s.size() << " | capacity: " << B.capacity() << " " << B_s.capacity() << std::endl;
		while (it != B.rend())
		{
			std::cout <<  "     " << *it << "   |   " << *ite << std::endl;
			it++;
			ite++;
		}
	}

	std::cout << "-----------------simple member functions------------------------\n";
	std::cout << S.end()[-1] << " ; " << S.size() << " ; " << S.max_size() << " ; " << S.capacity() << " ; " << S.data() << " ; " << S.empty() << " ; " << D.size() << " ; " << D.empty() << " ; " << D.capacity() << std::endl;
	std::cout << S_s.end()[-1] << " ; " << S_s.size() << " ; " << S_s.max_size() << " ; " << S_s.capacity() << " ; " << S_s.data() << " ; " << S_s.empty() << " ; " << D_s.size() << " ; " << D_s.empty() << " ; " << D_s.capacity() << std::endl;
	
	A = B;
	A_s = B_s;
	{
		std::cout << "-----------------after = operator------------------------\n";
		ft::vector<int>::iterator it = A.begin();
		std::vector<int>::iterator ite = A_s.begin();
		std::cout << "size:" << A.size() << " " << A_s.size() << " | capacity: " << A.capacity() << " " << A_s.capacity() << std::endl;
		while (it != A.end())
		{
			std::cout << "     " << it[0] << "   |   " << ite[0] << std::endl;
			it++;
			ite++;
		}
	}

	A.assign(B.begin()+1,B.end());
	A_s.assign(B_s.begin()+1,B_s.end());
	
	{
		std::cout << "-----------------after assign member func------------------------\n";
		ft::vector<int>::iterator it = A.begin();
		std::vector<int>::iterator ite = A_s.begin();
		std::cout << "size:" << A.size() << " " << A_s.size() << " | capacity: " << A.capacity() << " " << A_s.capacity() << std::endl;
		while (it != A.end())
		{
			std::cout << "     " << *it << "   |   " << *ite << std::endl;
			it++;
			ite++;
		}
	}

	std::cout << "-----element access---------------------\n";
	S[42] = "School_42";S[21] = "School_21";S[133] = "back element"; S[0] = "front element";
	S_s[42] = "School_42";S_s[21] = "School_21";S_s[133] = "back element"; S_s[0] = "front element";
	std::cout << S.front() << " | " << S.back() << " | (" << S.at(42) << "==" << S[21] << ")=true" << std::endl;
	std::cout << S_s.front() << " | " << S_s.back() << " | (" << S_s.at(42) << "==" << S_s[21] << ")=true" << std::endl;

	std::cout << "-----crear/reserve/insert---------------------\n";
	A.reserve(100);A.clear();
	A_s.reserve(100);A_s.clear();
	std::cout << A.size() << " " << A.capacity() << " " << *A.insert(A.begin(), A.begin() - A.end()) <<std::endl;
	std::cout << A_s.size() << " " << A_s.capacity() << " " << *A_s.insert(A_s.begin(), A_s.begin() - A_s.end()) <<std::endl;
	A.insert(A.end() - 1, LI.begin(), LI.end());
	A_s.insert(A_s.end() - 1, LI.begin(), LI.end());

	{
		std::cout << "-----------------after = insert------------------------\n";
		ft::vector<int>::iterator it = A.begin();
		std::vector<int>::iterator ite = A_s.begin();
		std::cout << "size:" << A.size() << " " << A_s.size() << " | capacity: " << A.capacity() << " " << A_s.capacity() << std::endl;
		while (it != A.end())
		{
			std::cout << "     " << it[0] << "   |   " << ite[0] << std::endl;
			it++;
			ite++;
		}
	}

	S.pop_back();
	S.erase(S.begin()+21, S.begin()+42);
	S.push_back("New pushed string");
	S_s.pop_back();
	S_s.erase(S_s.begin()+21, S_s.begin()+42);
	S_s.push_back("New pushed string");
	std::cout << "----------pop/push/erase--------------------\n";

	std::cout << S.front() << " | " << S.back() << " | (" << S.at(42) << "==" << S[21] << ")=false" << std::endl;
	std::cout << S_s.front() << " | " << S_s.back() << " | (" << S_s.at(42) << "==" << S_s[21] << ")=false" << std::endl;


	B.resize(8,8);B_s.resize(8,8);
	{
		std::cout << "-----------------after resize------------------------\n";
		ft::vector<int>::iterator it = B.begin();
		std::vector<int>::iterator ite = B_s.begin();
		std::cout << "size:" << B.size() << " " << B_s.size() << " | capacity: " << B.capacity() << " " << B_s.capacity() << std::endl;
		while (it != B.end())
		{
			std::cout << "     " << it[0] << "   |   " << ite[0] << std::endl;
			it++;
			ite++;
		}
	}

	B.resize(0,8);B_s.resize(0,8);
	std::cout << " size=" << B.size() << " " << B.capacity() << " " << B.data() << std::endl;
	std::cout << " size=" << B_s.size() << " " << B_s.capacity() << " " << B_s.data() << std::endl;

	std::cout << "-----------------member swap------------------------\n";
	ft::swap(A, B);
	std::swap(A_s, B_s);
	std::cout << " size=" << A.size() << " " << A.capacity() << " " << A.data() << std::endl;
	std::cout << " size=" << A_s.size() << " " << A_s.capacity() << " " << A_s.data() << std::endl;

	std::cout << "-----------------comparisons------------------------\n";

	std::cout << (A == B) << " " << (A != B) << " " << (A < B) << " " << (A > B) << " " << (A <= B) << " " << (A >= B) << std::endl;
	std::cout << (A_s == B_s) << " " << (A_s != B_s) << " " << (A_s < B_s) << " " << (A_s > B_s) << " " << (A_s <= B_s) << " " << (A_s >= B_s) << std::endl;

	std::cout << "-----------------const object------------------------\n";

	const ft::vector<int> cap(LI.begin(), LI.end());

	for (ft::vector<int>::const_iterator it = cap.begin(); it < cap.end(); ++it)
		std::cout << *it << std::endl;
	for (ft::vector<int>::const_reverse_iterator it = cap.rbegin(); it < cap.rend(); ++it)
		std::cout << *it << std::endl;

	std::cout << "const front and back : " << cap.front() << " " << cap.back() << " const data: " << cap.data() << std::endl;


	return 0;
}

