template<>
class myTuple{
	myTuple() {}
	myTuple(const myTuple &t) {}
	myTuple(myTuple &&t) {}

	myTuple &operater=(const myTuple &t) {}
	myTuple &&operater=(myTuple &&t) {}

	bool Equal(const myTuple &t) {}
	bool Less(const myTuple &t) {}
	void swap(myTuple &t) {}
};

template<class This, class... Rest>
class myTuple : private myTuple<Rest...>{
	typename myTuple<This, Rest...> myT;
	typename myTuple<Rest...> myBase;

	myTuple():myBase(), this_val() {}
	myTuple(const This &_this, const myBase &_rest):myBase(_rest), this_val(_this) {}
	myTuple(This &&_this, myBase &&_rest):myBase(_rest), this_val(_this) {}
	myTuple(const myT &t):myBase(t.Rest()), this_val(t.this_val) {}
	myTuple(myT &&t):myBase(t.Rest()), this_val(t.this_val) {}
	template<class First, class Second>
	myTuple(const pair<First, Second> &p):myBase(myTuple<Second>(p.second)), this_val(pair.first) {}
	template<class First, class Second>
	myTuple(pair<First, Second> &&p):myBase(myTuple<Second>(p.second)), this_val(pair.first) {}

	myT &operater=(const myT &t) {myBase=t.Rest(); this_val=t.this_val; return (*this);}
	myT &operater=(myT &&t) {myBase=t.Rest(); this_val=t.this_val; return (*this);}
	template<class First, class Second>
	myTuple<First, Second> &operater=(const pair<First, Second> &p) {myBase=myTuple<Second>(p.second); this_val=p.first; return (*this);}
	template<class First, class Second>
	myT<First, Second> &operater=(pair<First, Second> &&p) {myBase=myTuple<Second>(p.second); this_val=p.first; return (*this);}

	bool Equal(const myT &t) 
	{
		static_assert(mySize==t.mySize, "comparing tuple with different size");
		return (this_val==t.this_val && myBase==t.Rest());
	}
	bool Less(const myT &t) 
	{
		static_assert(mySize==t.mySize, "comparing tuple with different size");
		return (this_val<t.this_val || !(t.this_val<this_val) && (myBase.Less(t.Rest())));
	}
	void swap(const myT &t)
	{
		This temp = t.this_val;
		t.this_val = this_val;
		this_val = temp;
		myBase temp2 = t.Rest();
		t.Rest() = this->Rest();
		this->Rest = temp2;
	}
	myBase &Rest() {return (*this);}
	template<class First, class Second>
	myTuple<Second> &Rest() {return myTuple<Second>(Rest());}

	This this_val;
	static const size_t mySize = sizeof...(Rest) + 1;
};

template<class This, class... Rest>
bool operater==(const myTuple<This, Rest> &left, const myTuple<This, Rest> &right) {return left.Equal(right);}
template<class This, class... Rest>
bool operater!=(const myTuple<This, Rest> &left, const myTuple<This, Rest> &right) {return (!(left==right));}
template<class This, class... Rest>
bool operater<(const myTuple<This, Rest> &left, const myTuple<This, Rest> &right) {return left.Less(right);}
template<class This, class... Rest>
bool operater>(const myTuple<This, Rest> &left, const myTuple<This, Rest> &right) {return (right<left);}
template<class This, class... Rest>
bool operater>=(const myTuple<This, Rest> &left, const myTuple<This, Rest> &right) {return !(left<right);}
template<class This, class... Rest>
bool operater<=(const myTuple<This, Rest> &left, const myTuple<This, Rest> &right) {return !(right<left);}

template<class This, class... Rest>
myTuple<This, Rest> &make_tuple(This &&_this, Rest&&... _rest)
{return myTuple<This, Rest>(_this, _rest);}

template<class This, class... Rest>
myTuple<This, Rest> &tie(This &_this, Rest&... _rest)
{return myTuple<This, Rest>(_this, _rest);}