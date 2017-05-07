// $NAME <mak191@zips.uakron.edu>

#ifndef CS23001_STRING_INTERFACE_HPP
#define CS23001_STRING_INTERFACE_HPP

#include <iostream>
#include <vector>

/**
* @invariant str[length()] == 0
*         && length()      == capacity()
*         && capacity()    == stringSize - 1
*/
class String {
private:
	// helper constructors and methods
	String(int);
	String(int, const char *);
	void reset_capacity(int);

	char* str;

	// size includes NULL terminator
	int string_size;

public:

	bool empty() const { return this->length() == 0; }
	// constructor: empty string, String('x'), and String("abcd")
	String(); //d
	String(char); //d 
	String(const char *); //d 

						  // copy ctor, destructor, constant time swap, and assignment
	String(const String&);  //d
	~String(); //d
	void swap(String &); //d 
	String& operator=(String); //d 

							   // subscript: accessor/modifier and accessor
	char & operator[](int); //d
	char   operator[](int) const; //d 

								  // max chars that can be stored (not including null terminator)
	int capacity() const; //d
						  // number of char in string
	int length() const; //d

						// concatenation
	String   operator+ (const String &) const; //d
	String & operator+=(String); //d

								 // relational methods
	bool operator==(const String &)  const; //d 
	bool operator< (const String &)  const; //d

											// i/o
	friend std::ostream& operator<<(std::ostream &, const String &); //d
	friend std::istream& operator >> (std::istream &, String &); //d
	friend int stoi(String const& s);

																 //milestone3 methods
	String substr(int start_pos, int count) const; //d
	int find(char ch) const { this->find(ch, 0); } //d
	int find(char ch, int start_pos) const; //d
	int find(const String& s) const { this->find(s, 0); } //d
	int find(const String& s, int start_pos) const; //d
	std::vector<String> split(char) const;

};

// free functios for concatenation and relational
String operator+       (const char *, const String &); //d
String operator+       (char, const String &); //d
bool   operator==      (const char *, const String &); //d
bool   operator==      (char, const String &); //d
bool   operator<       (const char *, const String &); //d
bool   operator<       (char, const String &); //d
bool   operator<=      (const String &, const String &); //d
bool   operator!=      (const String &, const String &); //d
bool   operator>=      (const String &, const String &); //d
bool   operator>       (const String &, const String &); //d

bool getline(std::istream& in, String& temp);

#endif
