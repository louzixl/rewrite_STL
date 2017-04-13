template<>
class myTuple{
	typenam myTuple<> myT;

	myTuple() {}
	myTuple(const myTuple &t) {}

	bool Equal(const myT &t) const {return true;}
	bool Less(const myT &t) const {return false;}
	void swap(myT &t) {}
};

template<class This, class... Rest>
class myTuple<This, Rest> : private myTuple<Rest...>{
	typename myTuple<This, Rest...> myT;
	typename myTuple<Rest...> myBase;

	myTuple():myBase(), this_val() {}
	explicit myTuple(const This &_this, const Rest&... _rest):myBase(_rest...), this_val(_this) {}
	explicit myTuple(This &&_this, Rest&&... _rest)
		:myBase(std::forward<Rest>(_rest)...), this_val(std::forward<This>(_this)) {}
	myTuple(const myT &t):myBase(t.Rest()), this_val(t.this_val) {}
	myTuple(myT &&t):myBase(std::forward<myBase>(t.Rest())), this_val(std::forward<This>(t.this_val)) {}
	template<class First, class Second>
	myTuple(const pair<First, Second> &p):myBase(myTuple<Second>(p.second)), this_val(p.first) {}
	template<class First, class Second>
	myTuple(pair<First, Second> &&p)
		:myBase(myTuple<Second>(std::forward<Second>(p.second))), this_val(std::forward<First>(p.first)) {}

	myT &operater=(const myT &t) {(myBase&)*this=t.Rest(); this_val=t.this_val; return (*this);}
	myT &operater=(myT &&t) 
	{(myBase&)*this=std::forward<myBase>(t.Rest()); this_val=std::forward<This>(t.this_val); return (*this);}
	template<class First, class Second>
	myT &operater=(pair<First, Second> &&p) 
	{
		static_assert(mySize==2, "assigning to tuple from object with different size");
		(myBase&)*this=myTuple<Second>(std::forward<Second>(p.second)); 
		this_val=std::forword<First>(p.first); 
		return (*this);
	}

	bool Equal(const myT &t) const
	{
		static_assert(mySize==t.mySize, "comparing tuple with different size");
		return (this_val==t.this_val && myBase::Equal(t.Rest()));
	}
	bool Less(const myT &t) const
	{
		static_assert(mySize==t.mySize, "comparing tuple with different size");
		return (this_val<t.this_val || (!(t.this_val<this_val)) && (myBase::Less(t.Rest())));
	}
	void swap(myTuple &t)
	{
		This temp = t.this_val;
		t.this_val = this_val;
		this_val = temp;
		myBase::swap((myBase&)t);
	}
	myBase &Rest() {return (*this);}
	const myBase &Rest() {return (*this);}

	This this_val;
	static const size_t mySize = sizeof...(Rest) + 1;
};

template<class... Types>
bool operater==(const myTuple<Types...> &left, const myTuple<Types...> &right) {return left.Equal(right);}
template<class... Types>
bool operater!=(const myTuple<Types...> &left, const myTuple<Types...> &right) {return (!(left==right));}
template<class... Types>
bool operater<(const myTuple<Types...> &left, const myTuple<Types...> &right) {return left.Less(right);} 
template<class... Types>
bool operater>(const myTuple<Types...> &left, const myTuple<Types...> &right) {return (right<left);}
template<class... Types>
bool operater>=(const myTuple<Types...> &left, const myTuple<Types...> &right) {return !(left<right);}
template<class... Types>
bool operater<=(const myTuple<Types...> &left, const myTuple<Types...> &right) {return !(right<left);}

template<class... Types>
inline void swap(myTuple<Types...> &_this, myTuple<Types...> &_rest)
{return _this.swap(_rest);}

template<class... Types>
inline myTuple<Types...> make_tuple(Types&&... Args)
{return myTuple<Types...>(std::forward<Types>(Args)...);}

template<class... Types>
inline myTuple<Types&...> tie(Types&... Args)
{return myTuple<Types&...>(Args...);}