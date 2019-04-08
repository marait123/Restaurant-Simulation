#pragma once
template<typename Tf, typename Ts>
class Pair
{
	Tf first;
	Ts second;

public:
	Pair();
	Pair(Tf f, Ts s);
	~Pair();

	void setFirst(Tf f);
	void setSecond(Ts s);
	Tf getFirst() const;
	Ts getSecond() const;
	bool operator>(const Pair<Tf, Ts>& p);
};

template<typename Tf, typename Ts>
inline Pair<Tf, Ts>::Pair()
{
}

template<typename Tf, typename Ts>
inline Pair<Tf, Ts>::Pair(Tf f, Ts s) : first(f), second(s)
{
}

template<typename Tf, typename Ts>
inline Pair<Tf, Ts>::~Pair()
{
}

template<typename Tf, typename Ts>
inline void Pair<Tf, Ts>::setFirst(Tf f)
{
	this->first = f;
}

template<typename Tf, typename Ts>
inline void Pair<Tf, Ts>::setSecond(Ts s)
{
	this->second = second;
}

template<typename Tf, typename Ts>
inline Tf Pair<Tf, Ts>::getFirst() const
{
	return Tf(first);
}

template<typename Tf, typename Ts>
inline Ts Pair<Tf, Ts>::getSecond() const
{
	return Ts(second);
}

template<typename Tf, typename Ts>
inline bool Pair<Tf, Ts>::operator>(const Pair<Tf, Ts>& p)
{
	return this->first > p.getFirst();
}