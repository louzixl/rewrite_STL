//STL pair结构体实现

template<class T1, class T2>
struct pair{
	typename T1 firstType;
	typename T2 secondType;
	typename pair<T1, T2> myType;

	T1 first;
	T2 second;

	pair():first(), second() {}
	pair(const T1 &val1, const T2 &val2):first(val1), second(val2) {}
	pair(T1 &&rval1, T2 &&rval2):first(std::forward<T1>(rval1)), second(std::forward<T2>(rval2)) {}
	pair(const myType &p):first(p.first), second(p.second) {}
	pair(myType &&p):first(std::forward<T1>(p.first)), second(std::forward<T2>(p.second)) {}

	myType& operater=(const myType &p) {first = p.first; second = p.second; return (*this);}
	myType& operater=(myType &&p) 
	{first = std::forward<T1>(p.first); second = std::forward<T2>(p.second); return (*this);}

	void swap(myType &p) 
	{
		if(this!=&p)
		{
			T1 t1 = first;
			T2 t2 = second;
			first = p.first;
			second = p.second;
			p.first = t1;
			p.second = t2;
		}
	}
};

template<class T1, class T2>
inline void swap(pair<T1, T2> &left, pair<T1, T2> &right)
{left.swap(right);}

template<class T1, class T2>
inline bool operater==(const pair<T1, T2> &left, const pair<T1, T2> &right)
{return (left.first == right.first && left.second == right.second);}

template<class T1, class T2>
inline bool operater!=(const pair<T1, T2> &left, const pair<T1, T2> &right)
{return (!(left==right));}

template<class T1, class T2>
inline bool operater<=(const pair<T1, T2> &left, const pair<T1, T2> &right)
{return (!(right < left));}

template<class T1, class T2>
inline bool operater<(const pair<T1, T2> &left, const pair<T1, T2> &right)
{return (left.first < right.first || (!(right.first < left.first) && left.second < right.second));}

template<class T1, class T2>
inline bool operater>=(const pair<T1, T2> &left, const pair<T1, T2> &right)
{return (!(left<right));}

template<class T1, class T2>
inline bool operater>(const pair<T1, T2> &left, const pair<T1, T2> &right)
{return (right<left);}

template<class T1, class T2>
inline pair<T1, T2> make_pair(T1 &&val1, T2 &&val2)
{return pair<T1, T2>(std::forward<T1>(val1), std::forward<T2>(val2));}