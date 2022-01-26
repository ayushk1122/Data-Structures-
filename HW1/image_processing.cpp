#include <iostream>  
#include <cmath>      
#include <cstdlib>  
#include <fstream>
#include <vector>
#include <array>
#include <string>
using namespace std;
/*
This program performs simulation image processing functions to emulate image editing techniques.
These functions are executed with ASCII characters to visualize the operations effects. 
Author: Ayush Krishnappa 
Professor Plum, Section 1
*/

void replace(vector<string>& image, char rstr, char rkey) { //replaces a designated char with another designated char
	//rstr = char to replace
	//rkey = char used to replace 
	for (int i = 0; i < image.size(); i++) {
		for (int j = 0; j < image[i].size(); j++) {
			if (image[i][j] == rstr) {
				image[i][j] = rkey;
			}
		}
	}
}

void dilation(vector<string>& image, char fchar) { //inputs designated char to correct location in image, 
	//purpose of expanding the boundary 
	//vectors used to store coordinate points of where to input chars
	//used to avoid incorrect placement of chars due to consecutive placement 
	vector<int> xcoors;
	vector<int> ycoors;

	for (int i = 0; i < image.size(); i++) {
		for (int j = 0; j < image[i].size(); j++) {
			//conditional block to check adjacent positions of each "pixel" of the image in a plus-shaped figure
			if (image[i][j] != fchar) {
				if (((j - 1) >= 0) && (image[i][j - 1] == fchar)) { //left neighbor
					xcoors.push_back(i);
					ycoors.push_back(j);
					continue; //continue in order to avoid unnecessary checks 
				}
				else if (((j + 1) < image[i].size()) && (image[i][j + 1] == fchar)) { //right neighbor
					xcoors.push_back(i);
					ycoors.push_back(j);
					continue;
				}
				else if (((i - 1) >= 0) && (image[i - 1][j] == fchar)) { //top neighbor
					xcoors.push_back(i);
					ycoors.push_back(j);
					continue;
				}
				else if (((i + 1) < image.size()) && (image[i + 1][j] == fchar)) { //bottom neighbor 
					xcoors.push_back(i);
					ycoors.push_back(j);
					continue;
				}
				else {
					continue;
				}
			}
		}
	}

	for (int i = 0; i < xcoors.size(); i++) { //loops through image and adds designated char to respective locations
		image[xcoors[i]][ycoors[i]] = fchar;
	}
}

void erosion(vector<string>& image, char fchar, char bchar) { //shrinks the boundary of the image
	//and replaces foreground color with background color
	vector<int> xcoors;
	vector<int> ycoors;
	for (int i = 0; i < image.size(); i++) {
		for (int j = 0; j < image[i].size(); j++) {
			//checks all edge cases, since any edge will automatically not fit in the plus-shaped cluster
			if ((i != 0) && (j != 0) && (i != (image.size() - 1)) && (j != (image[i].size() - 1))) {
				if (image[i][j] == bchar) {
					//checks if the pixel does not fully fit within the plus-shaped cluster
					if ((image[i + 1][j] != bchar) || (image[i - 1][j] != bchar) || 
					(image[i][j - 1] != bchar) || (image[i][j + 1] != bchar)) {
						//stores location of pixel that needs to be changed
						xcoors.push_back(i);
						ycoors.push_back(j);
					}
				}
			}
		}
	}

	//loops through image and sets respective locations back to the original char
	for (int i = 0; i < xcoors.size(); i++) {
		image[xcoors[i]][ycoors[i]] = fchar;
	}
}

int main(int argc, char* argv[]) { //main program to execute correct operations and functions 
	//creates in stream to get data from input file
	ifstream in_str(argv[1]);
	if (!in_str.good()) {
		std::cerr << "Can't open " << argv[1] << " to read.\n";
		exit(1);
	}
	vector<string> image; //vector of strings to hold ASCII chars

	//loops through and gets each line from the input file and adds it to the vector 
	string line;
	while (getline(in_str, line)) {
		image.push_back(line);
	}

	//condiitonal block to execute the correct operation
	if (argc == 5) {
		string operation = string(argv[3]);
		
		char foreground = char(argv[4][0]);
		dilation(image, foreground); //performs dilation operation to image
	}
	else if (argc == 6) {
		string operation = string(argv[3]);

		/*
		since replaceand erosion have same number of args, must use compare to check 
		which operation to use
		*/
		if (operation.compare("replace") == 0) {
			char c_val = char(argv[4][0]);
			char replace_c = char(argv[5][0]);
			replace(image, c_val, replace_c); //performs replace operation to image
		}
		else if (operation.compare("erosion") == 0) {
			char foreground = char(argv[5][0]);
			char background = char(argv[4][0]);
			erosion(image, foreground, background); //performs erosion operation to image
		}
	}

	//creates outstream to print data to a designated output file
    ofstream out_f(argv[2]);
	if (!out_f.good()) {
		std::cerr << "Can't open " << argv[4] << " to write.\n";
		exit(1);
	}

	//loops through and prints contents of vector image to the output file
	if (out_f.is_open()) {
		for (string line : image) {
			out_f << line << endl;
		}
		out_f.close();
	}
	return 0;
}