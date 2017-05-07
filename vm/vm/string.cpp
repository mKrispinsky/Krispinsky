// $NAME <mak191@zips.uakron.edu>

#include "string.hpp"

//helper constructors and methods
String::String(int size)
{
	string_size = size;
	str = new char[size];

	for (int i = 0; i < size; i++)
		str[i] = '\0';
}

String::String(int size, const char* word)
{
	string_size = size;
	str = new char[size];

	for (int i = 0; i < size; i++)
		str[i] = '\0';

	//Protect the null and be sure that we don't go past word[];
	for (int i = 0; (i < size - 1) && (word[i] != '\0'); i++)
		str[i] = word[i];
}

void String::reset_capacity(int size)
{
	int temp_size = size + 1;
	char* temp = new char[size + 1];

	for (int i = 0; i < (size + 1); i++)
		temp[i] = '\0';

	for (int i = 0; (i < size) && str[i] != '\0'; i++)
		temp[i] = str[i];

	delete str;
	str = temp;
	string_size = temp_size;
}

// constructor: empty string, String('x'), and String("abcd")
String::String()
{
	string_size = 1;
	str = new char[1];
	str[0] = '\0';
}

String::String(char x)
{
	if (x == '\0')
	{
		string_size = 1;
		str = new char[1];
		str[0] = '\0';
	}
	else
	{
		string_size = 2;
		str = new char[2];

		str[0] = x;
		str[1] = '\0';
	}
}

String::String(const char* word)
{
	int size = 0;
	while (word[size] != '\0')
		size++;

	string_size = size + 1;
	str = new char[size + 1];

	for (int i = 0; i < size + 1; i++)
	{
		str[i] = word[i];
	}
}

// copy ctor, destructor, constant time swap, and assignment
String::String(const String& word)
{
	string_size = word.string_size;
	str = new char[string_size];

	for (int i = 0; i < string_size; i++)
		str[i] = word.str[i];
}

String::~String()
{
	delete[] str;
}

void String::swap(String& word)
{
	char* temp = word.str;
	int temp_size = word.string_size;

	word.str = str;
	word.string_size = string_size;

	str = temp;
	string_size = temp_size;
}

String& String::operator=(String word)
{
	if (this != &word)
	{
		delete[] str;
		str = new char[word.string_size];
		string_size = word.string_size;
		for (int i = 0; i < string_size; i++)
			str[i] = word[i];
	}
	return *this;
}

// subscript: accessor/modifier and accessor
char& String::operator[](int index)
{
	if (index >= string_size)
		return str[string_size - 1];

	return str[index];
}

char String::operator[](int index) const
{
	if (index >= string_size)
		return str[string_size - 1];

	return str[index];
}

// max chars that can be stored (not including null terminator)
int String::capacity() const
{
	return string_size - 1;
}
// number of char in string
int String::length() const
{
	int length = 0;
	while (str[length] != '\0')
		length++;

	return length;
}

// concatenation
String String::operator+ (const String& word) const
{
	String result(this->length() + word.length() + 1);

	int i = 0;
	for (; i < this->length(); i++)
		result[i] = str[i];

	for (int j = 0; j < word.length(); j++)
		result[i + j] = word[j];

	return result;
}

String& String::operator+=(String word)
{
	(*this) = (*this) + word;
	return *this;
}

String operator+(const char* word1, const String& word2)
{
	String temp(word1);
	return temp + word2;
}

String operator+(char x, const String& word)
{
	String temp(x);
	return temp + word;
}

// relational methods
bool String::operator==(const String& word)  const
{
	if (string_size != word.string_size)
		return false;

	for (int i = 0; i < string_size; i++)
	{
		if (word.str[i] != str[i])
			return false;
	}

	return true;
}

bool operator== (const char* word1, const String& word2)
{
	return word2 == word1;
}
bool operator== (char x, const String& word)
{
	return word == x;
}

bool String::operator<(const String& word)  const
{
	for (int i = 0; (i < string_size) && (i < word.string_size); i++)
	{
		if (str[i] != word[i])
			return str[i] < word[i];
	}

	return string_size < word.string_size;
}

bool operator<(const char* word1, const String& word2)
{
	String temp(word1);
	return temp < word2;
}

bool operator<(char x, const String& word)
{
	String temp(x);
	return temp < word;
}

bool operator<=(const String& word1, const String& word2)
{
	return (word1 < word2 || word1 == word2);
}

bool operator!=(const String& word1, const String& word2)
{
	return !(word1 == word2);
}

bool operator>=(const String& word1, const String& word2)
{
	return !(word1 < word2);
}

bool operator>(const String& word1, const String& word2)
{
	return !(word1 <= word2);
}

// i/o
std::ostream& operator<<(std::ostream& out, const String& word)
{
	out << word.str;
	return out;
}

std::istream& operator >> (std::istream& in, String& word)
{
	char input[256] = {};
	in >> input;
	String result(input);
	word = result;

	return in;
}

// Milestone 3 Methods
String String::substr(int start_pos, int count) const
{
	String result;
	if (start_pos < 0)
		return result;

	for (int i = 0; (i < count) && (i + start_pos < this->length()); i++)
		result += str[start_pos + i];

	return result;
}

int String::find(char ch, int start_pos) const
{
	for (int i = start_pos; i < this->length(); i++)
	{
		if (str[i] == ch)
			return i;
	}

	return -1;
}

int String::find(const String& s, int start_pos) const
{
	for (int i = start_pos; i + s.length() <= this->length(); i++)
	{
		for (int j = 0; j < s.length(); j++)
		{
			if (str[j + i] != s[j])
				break;
			if (j + 1 == s.length())
				return i;
		}
	}

	return -1;
}

std::vector<String> String::split(char x) const
{
	int splits = 0;

	std::vector<String> parts;
	parts.push_back(*this);

	while (parts[splits].find(x, 0) != -1)
	{
		int pos = parts[splits].find(x, 0);
		parts.push_back(parts[splits].substr(pos + 1, parts[splits].length()));
		parts[splits] = parts[splits].substr(0, pos);

		splits++;
	}

	return parts;
}

bool getline(std::istream& in, String& temp)
{
	if (!in)
	{
		in.clear();
		return false;
	}

	temp = "";
	char c;
	while (in.peek() != '\n' && in.peek() != EOF)
	{
		c = in.get();
		temp += c;
	}

	if (in.peek() == '\n')
	{
		in.get();
		return true;
	}
}

int stoi(String const& s)
{
	int number = 0;

	int i = s.length();

	int j = 0;
	do
	{
		i--;
		number += pow(10,j)*(s.str[i] - '0'); //Some character arithmetic to go from char to int.
		j++;
	} while (i > 0);

	return number;
}