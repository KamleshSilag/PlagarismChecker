/* Following program is a C++ implementation of Rabin Karp 
Algorithm given in the CLRS book */
#include <bits/stdc++.h> 
#include<fstream>
#include<string>
using namespace std; 

#define d 256 

int searchPattern(string pat, string txt, int q) 
{ 
	int M = pat.length(); 
	int N = txt.length(); 
	int i, j; 
	int p = 0; // hash value for pattern 
	int t = 0; // hash value for txt 
	int h = 1; 

	// The value of h would be "pow(d, M-1)%q" 
	for (i = 0; i < M - 1; i++) 
		h = (h * d) % q; 

	// Calculate the hash value of pattern and first 
	// window of text 
	for (i = 0; i < M; i++) 
	{ 
		p = (d * p + pat[i]) % q; 
		t = (d * t + txt[i]) % q; 
	} 

	// Slide the pattern over text one by one 
	for (i = 0; i <= N - M; i++) 
	{ 

		// Check the hash values of current window of text 
		// and pattern. If the hash values match then only 
		// check for characters on by one 
		if ( p == t ) 
		{ 
			/* Check for characters one by one */
			for (j = 0; j < M; j++) 
			{ 
				if (txt[i+j] != pat[j]) 
					break; 
			} 

			// if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1] 
			if (j == M) 
			{
				cout<<"Pattern found at index "<< i<<" of length : "<<j<<endl; 
				return j;
			}
		} 

		// Calculate hash value for next window of text: Remove 
		// leading digit, add trailing digit 
		if ( i < N-M ) 
		{ 
			t = (d*(t - txt[i]*h) + txt[i+M])%q; 

			// We might get negative value of t, converting it 
			// to positive 
			if (t < 0) 
			t = (t + q); 
		} 
	} 
	return 0;
} 

int main() 
{ 
	string txt; 
	char pat[] = ""; 

 	fstream userfile; 
 	fstream patternfile;
	string word; 
 	string userfilename= "Userfile.txt"; 
 	string patternfilename = "Patternfile.txt";

	userfile.open(userfilename.c_str()); 
  	patternfile.open(patternfilename.c_str());

   	while (userfile >> word) 
    { 
        txt.append(word);
        txt.append(" ");
    } 
    
	string line;
	int cntPattern = 0;
	while(getline(patternfile, line)) 
	{
		
    	int q = 101; 
		cntPattern += searchPattern(line, txt, q); 	
    }
	

    float x = (float)cntPattern/txt.length();
    cout<<endl<<"Percentage of Plagarism : " <<(x*100)<<"%"<<endl;
	
	return 0; 
} 

