// Test lambda functions and std::transform

#include<iostream>	// std::cout
#include<vector>	// std::vector
#include<algorithm>	// std::transform

int main()
{
	std::size_t size = 5;

	std::vector<int> vec(size);

	int a = 2;

	
	std::transform(	vec.begin(),
					vec.end(),
					vec.begin(),
					[](int x){return x+1;});
	

	std::transform(	vec.begin(),
					vec.end(),
					vec.begin(),
					[&](auto x){++a; return x+a;});	// capturing by value gives a compile time error

	std::transform(	vec.begin(),
					vec.end(),
					vec.begin(),
					[a](int x) -> int {return x+a;});	// a captures only a by copy
														// -> specifies the return type

	std::vector<int> vec1(size);

	std::transform(	vec.begin(),
					vec.end(),
					vec1.begin(),	// WARNING : need to check first that vec1 can contain all the elements
					[=](int x) -> int {return x+a;});

	std::vector<int> vec2(size);

	std::transform(	vec.begin(),
					vec.end(),
					vec1.begin(),	// iterating also on vec1 (that can be bigger than vec)
					vec2.begin(),
					[](int x, int y){return x+y;});

	for (auto& i : vec)
		std::cout << i << "\n";

	for (auto& i : vec1)
		std::cout << i << "\n";

	for (auto& i : vec2)
		std::cout << i << "\n";

	return 0;
}