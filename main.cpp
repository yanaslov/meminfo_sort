#include <vector>



#include <fstream>
#include <iostream>

#include <algorithm>

#include "MemInfoEntry.hpp"


using namespace std;


const string path_proc_meminfo{"/proc/meminfo"};
const string default_ofilename {"meminfo_sorted.txt"};
void print_help(){
	cout<<
"Print /proc/meminfo lines sorted by memory size"<<endl<<
"usage:" <<endl<<
"meminfo          :print to default 'meminfo_sorted.txt'"<<endl<<
"meminfo filename :print to filename"<<endl<<
"meminfo -        :print to Stdout,"<<endl<<
"meminfo -h       :print help and exit" <<endl;

}

int main(int argc, char** argv){

	string out_file_name;
	ofstream outfile;
	if(argc<2){
		cerr<<"Out to default file:"<<default_ofilename<<endl;
		out_file_name=default_ofilename;
		outfile.open(out_file_name);
	}else if(*argv[1]=='-'){
		if(string("-h")==argv[1]){
			print_help();
			return 0;
		}
		out_file_name="";
	}else{
		out_file_name=argv[1];
		outfile.open(out_file_name);
	}

	ostream& outstream = outfile.is_open()
				?
			outfile : cout;


	ifstream infile(path_proc_meminfo);
	if (!infile.is_open()){
		cerr<<"Can't open file /proc/meminfo";
		return 1;
	}

	vector<MemInfoEntry> lines;

	for(string line;getline(infile, line);){
		lines.push_back(move(line));
	}

	sort(begin(lines),end(lines));

	for(auto& l:lines){
		outstream<<l<<endl;
	}

	return 0;

}
