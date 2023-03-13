#ifndef MEMINFOENTRY_HPP_
#define MEMINFOENTRY_HPP_

#include <string>
#include <string_view>
#include <iostream>

class MemInfoEntry{
	std::string line_;
	std::string_view title;
	std::size_t memsize=0;
	std::string_view units;

public:
	MemInfoEntry(){}
	~MemInfoEntry(){}

	MemInfoEntry(std::string&& s);

	MemInfoEntry(MemInfoEntry&& m){
		line_.swap(m.line_);
		title.swap(m.title);
		memsize=m.memsize; m.memsize=0;
		units.swap(m.units);
	}

	MemInfoEntry& operator=(MemInfoEntry&& m){
		line_.swap(m.line_);
		title.swap(m.title);
		memsize=m.memsize;
		units.swap(m.units);
		return *this;
	}

	friend bool operator<(const MemInfoEntry& l,const MemInfoEntry& r);
	friend std::ostream& operator<<(std::ostream& out, const MemInfoEntry& l);
};

inline bool operator<(const MemInfoEntry& l,const MemInfoEntry& r){
	//  ">" for descending sort
	if(l.units != r.units)
		return l.units > r.units;
	return l.memsize > r.memsize;
}

#endif /* MEMINFOENTRY_HPP_ */
