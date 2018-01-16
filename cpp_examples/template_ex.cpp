// Template exercise from learncpp.com

#include<iostream>

template<class T>
class Pair1
{
public:
	Pair1() = default;
	Pair1(const T& first, const T& second) :
		m_first(first),
		m_second(second)
		{}

	const T& first() const
	{
		return m_first;
	}

	const T& second() const
	{
		return m_second;
	}

private:
	T m_first;
	T m_second;
};

template<class T1, class T2>
class Pair
{
public:
	Pair() = default;
	Pair(const T1& first, const T2& second) :
		m_first(first),
		m_second(second)
		{}

	const T1& first() const
	{
		return m_first;
	}

	const T2& second() const
	{
		return m_second;
	}

private:
	T1 m_first;
	T2 m_second;
};

template <class T>
class StringValuePair : public Pair<std::string, T>
{
public:
	StringValuePair(const std::string& key, const T& value)
		: Pair<std::string, T>(key, value)
	{
	}
};


int main()
{
	/* Ex 1
	Pair1<int> p1(5, 8);
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
 
	const Pair1<double> p2(2.3, 4.5);
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
 	*/

	// Ex 2
	Pair<int, double> p1(5, 6.7);
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
 
	const Pair<double, int> p2(2.3, 4);
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

	// Ex 3
	StringValuePair<int> svp("Hello", 5);
	std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

	return 0;
}