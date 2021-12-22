//============================================================================
// Name        : minify_function.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "minify_function.h"

void minify(string file_name)
{					  /*input the name of the file to be minified*/
	ifstream in_file; /*just read the file so it can not be modified */
	ofstream out_file;

	in_file.open(file_name); /*read mode */
	out_file.open("minify_output.xml");

	string s;

	assert(in_file);

	while (getline(in_file, s))
	{
		int i = 0;
		while (s[i] == ' ') // to remove the spaces in the begin of the line
			i++;
		s.erase(s.begin(), s.begin() + i);

		out_file << s;
	}
	in_file.close();
	out_file.close();
}
int main()
{
	minify("../sample.xml");

	return 0;
}
