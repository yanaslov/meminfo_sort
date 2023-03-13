#include "MemInfoEntry.hpp"

#include <charconv>

using namespace std;

ostream& operator<<(ostream& out, const MemInfoEntry& l){

	out<<l.title;

	if(l.memsize >0)
		out<<l.memsize;
	else
		out<<"-";

	out<<" "<<l.units;
	return out;
}


MemInfoEntry::MemInfoEntry(string&& s)
	:MemInfoEntry()
{
	line_.swap(s);

	for(	size_t pos = 0
			;
		line_.npos !=
		(pos = line_.find(':', pos))
			;
	){
		line_.erase(pos, 1u);
			//line_.replace(pos, 1u, " ", 1u); //maybe faster
	}

	string_view sv=line_;

	size_t titleend=sv.find_first_of(" \t");
		if(titleend == sv.npos) return;
		titleend = sv.find_first_not_of(" \t",titleend);
		if(titleend == sv.npos) return;
	title=sv.substr(0, titleend);

	auto [ptr, ec] = from_chars(sv.data()+titleend,sv.data()+sv.size(),
	memsize);

	if(ec != std::errc(0))
		memsize=0;

	size_t size_kB_end = sv.find_first_of(" \t",titleend);
	size_kB_end = sv.find_first_not_of(" \t",size_kB_end);

	if(size_kB_end == sv.npos && ec == std::errc(0))
		return;

	units = sv.substr(size_kB_end,sv.size());
}
