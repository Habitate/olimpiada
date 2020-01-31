#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

struct Intersection{
	friend ostream& operator<<(ostream& stream, const Intersection& section){
		stream << section.word << ' ' << section.pos;

		return stream;
	}
	friend bool operator==(const Intersection& sec_1, const Intersection& sec_2){
		return sec_1.word == sec_2.word && sec_1.pos == sec_2.pos;
	}

	string word;
	unsigned int pos;
};

struct Connection{
	friend ostream& operator<<(ostream& stream, const Connection& con){
		stream << con.section_1 << ' ' << con.section_2;

		return stream;
	}
	friend bool operator==(const Connection& con_1, const Connection& con_2){
		//* Check if we're inspecting the same 2 words (ex. ALABAMA 1 APPAS 1 && ALABAMA 3 APPAS 4)
		if(con_1.section_1.word == con_2.section_1.word && con_1.section_2.word == con_2.section_2.word) return true;
		if(con_1.section_1.word == con_2.section_2.word && con_1.section_2.word == con_2.section_1.word) return true;
		
		//* Check if we cross the same spot twice (ex. ALABAMA 1 APPAS 1 && ALABAMA 1 APPAS 4)
		if(con_1.section_1 == con_2.section_1 || con_1.section_1 == con_2.section_2) return true;
		if(con_1.section_2 == con_2.section_1 || con_1.section_2 == con_2.section_2) return true;

		return false;
	}
	friend bool operator!=(const Connection& con_1, const Connection& con_2){
		return !(con_1 == con_2);
	}

	Intersection section_1, section_2;
};

void get_and_append_connections(vector<Connection>& connections, const string& word_1, const string& word_2){
	for(unsigned int i = 0, i_last = word_1.size(); i < i_last; ++i){
		for(unsigned int j = 0, j_last = word_2.size(); j < j_last; ++j){
			if(word_1[i] == word_2[j]){
				connections.emplace_back(Connection{word_1, i + 1, word_2, j + 1});
			}
		}
	}
}

int main(){
	vector<string> words(istream_iterator<string>{cin}, istream_iterator<string>{});
	vector<Connection> connections;
	connections.reserve(100);

	//Find all connenctions
	for(unsigned int i = 0; i < 3; ++i){
		for(unsigned int j = i + 1; j < 3; ++j){
			get_and_append_connections(connections, words[i], words[j]);
		}
	}

	//Find a good solution
	for(unsigned int i = 0, i_last = connections.size(); i < i_last; ++i){
		for(unsigned int j = i + 1; j < i_last; ++j){
            		if(connections[i] != connections[j]){
				cout << connections[i] << '\n' << connections[j];
				return 0;
			}
		}
	}

	return 0;
}
