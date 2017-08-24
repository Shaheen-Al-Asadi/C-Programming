#pragma once //much better than #define , less overhead
//move schematics moving around objects, taking brains, and zombies get memory deleted

#include <utility> //for move
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

namespace w3 {

	class Text {

		size_t count; //size_t correlates to bits of the machine - 32 / 64 
		//size type on a keyboard / mouse uses micro processor, using 1bit! - size_type gurantees it works

		string* lineTable;
	public:

		size_t size() const{ //size_t correlates to bits of the machine - 32 / 64 
			return count;
		}

		void print() { //custom function to read file in use
			for (size_t i = 0; i < count; i++) {
				cout << i+1 << ": -->" << lineTable[i] << "<--\n";
			}
		}


		//create a "zombie" 
		Text() :count(0), lineTable(nullptr) {
		}

		//initializes count to zero
		Text(char* filename) : count(0), lineTable(nullptr) {
			fstream is(filename, ios::in);//take in filename and open an fstream obj

			if (is.is_open()) {

				string line;
				//your at end of file, you need to seek back to start, error state: end of file needs reset

				while (getline(is, line)) {
					count++;
				}

				cout << "file '" << filename << "' has " << count << " lines\n";

				lineTable = new string[count];

				is.clear(); //resest the eof error state
				is.seekg(0, ios_base::beg); //seek to offset 0 on file, second instruction says from start

				for (size_t i = 0; i < count; i++) {
					getline(is, lineTable[i]); //read up to newline and place into lineTable

					//file might have cariage return/tabs so we skip them
					auto cr = lineTable[i].find('\r');
					if (cr != string::npos) {
						lineTable[i].erase(cr);
					}
				}

				is.close();
					//print(); //custom function call, delete for issues/submission
			}
			else {
				cerr << "Cannot open file-->" << filename << "<--\n";
				exit(1);
			}
		}

		~Text() { delete [] lineTable; }//deallocate dynamic data

		//promise not to touch rhs of text 
		Text(const Text& rhs): count(0), lineTable(nullptr){

			*this = rhs; //reusing assignment operator logic
		}

		Text& operator=(const Text& rhs){
			//check for self assesment, then deep copy over rhs data 
			if (this != &rhs) {
				delete[] lineTable;
				count = rhs.count;
				lineTable = new string[count];

				for (size_t i = 0; i < count; i++) {
					lineTable[i] = rhs.lineTable[i];
				}
			}

		return *this;
		}


		//move constructor - moves data from rhs and makes rhs a zombie 
		Text(Text&& rhs) : count(0), lineTable(nullptr) {
			*this = move(rhs); //reusing move assignment operator logic 
			// ^^ note the move() over RHS this time
		}

		//move assignment operator, rhs copy then zombie
		Text&& operator=(Text&& rhs){
		
			if (this != &rhs) {
				delete[] lineTable;

				//steal brains
				count = rhs.count;
				lineTable = rhs.lineTable; //copy over the address it steals the address of the POINTER - MEM STEALING

				//turn rhs to zombie
				rhs.count = 0;
				rhs.lineTable = nullptr; //deleting this obj but not the "data" brains are in LHS
			}

			return move(*this); // like return *this but dont forget the move() fucnt9ion <utility>
		}

	};

} //namespace w3