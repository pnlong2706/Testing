#include "main.h"
#include "Restaurant.cpp"
#include <time.h>
#include <fstream>
#include <stdio.h>


void simulate(string filename, imp_res* r)
{
	ifstream ss(filename);
	string str, maxsize, name, energy, num;
	while(ss >> str)
	{ 
		if(str == "MAXSIZE")
		{
			ss >> maxsize;
			MAXSIZE = stoi(maxsize); 
    	}
        else if(str == "RED") // RED <NAME> <ENERGY>
        {
            ss >> name;
            ss >> energy;
            r->RED(name, stoi(energy));
    	}
    	else if(str == "BLUE") // BLUE <NUM>
    	{
                ss >> num;
    			r->BLUE(stoi(num));
		}
    	else if(str == "PURPLE") // PURPLE
    	{
    			r->PURPLE();
		}
		else if(str == "REVERSAL") // REVERSAL
		{
    			r->REVERSAL();	
		}
    	else if(str == "UNLIMITED_VOID") // UNLIMITED_VOID
     	{   	
    			r->UNLIMITED_VOID();
    	}
    	else if(str == "DOMAIN_EXPANSION") // DOMAIN_EXPANSION
    	{
    			r->DOMAIN_EXPANSION();
    	}
    	else // LIGHT <NUM>
    	{
                ss >> num;
    			r->LIGHT(stoi(num));
    	}
    }
}
// -2: time limit, -1 accepted, x: wrong at line x 
int check(string fileOUT, string fileS_OUT) {
	ifstream out(fileOUT);
	ifstream s_out(fileS_OUT);
	string st, tt;
	int i=1;
	while( (s_out >> st) && (out >> tt)) {
		if(tt=="TIME:") {
			double tm;
			out >> tm;
			if(tm>5.0) return -2;
			else return -1;
		}
		else if(st!=tt) return i;
		i++;
	}
	return i;
}

int main(int argc, char* argv[]) {
	//if (argc < 2)
    //	return 1;
	//  string fileName = argv[1];
	int t=30;
	for(int i=1; i<=t; i++) {
		
		string inp="test"+to_string(i)+".INP";
		string out="output"+to_string(i)+".OUT";
		const char *outt=out.data();
		freopen(outt,"w",stdout);
		clock_t begin=clock();

		imp_res* r = new imp_res();
		string fileName = inp;
    	simulate(fileName, r);
  		delete r;

		cout << "TIME: " << (double)(clock()-begin)/CLOCKS_PER_SEC;
		
		freopen( "CON", "w", stdout );
		string our="out"+to_string(i)+".OUT";
		int ck=check(out,our) ;
		if(ck==-1) cout << "TEST " << i << " : " << "ACCEPTED" << endl;
		else if(ck==-2) {
			cout << "TEST " << i << " : " << "TIME LIMIT EXCEED" << endl;
			return 0;
		}
		else {
			cout << "TEST " << i << " : " << "DIFFER AT LINE " << ck << endl;
			return 0;
		}
	}

	
	return 0;
}

