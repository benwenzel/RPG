/*
 * The FileParser class is responsible for parsing files (duh) and storing the results in its private member variables.
 * Clients are granted read access to the values stored in those member variables via FileParser's public accessors.
 * FileParser also implements a number of helper functions that can be utilized by clients to compare and filter the 
 * parsed data owned by FileParser;
 * The FileParser class does not implement any rules concerning how or whether the values it obtains from the parsing
 * operation are used; those rules must be implemented in the function that creates the FileParser instance.
 */

#include <fstream>
#include <string>
#include <stack>
#include <vector>

class FileParser
{
public:
	FileParser();
	~FileParser();
	
//top-level functions
	bool open(const std::string &filename);					// <- opens the file
	void close();											// <- closes the file
	bool notEOF();											// <- actually parses the file
	void getNextLine();										// <- get the next line and trim all whitespaces, tabs, and carriage returns
	
//accessors
	std::string currentLine() const;						// <- accessor for the current m_currentLine
	std::string key() const;								// <- accessor for m_key
	std::string value() const;								// <- accessor for m_value
	std::string currentTagset() const;						// <- returns the name of the tagset currently in the immediate scope
	double lineCount() const;								// <- returns the line number of the current line

//parsing functions
	void parseTag();										// <- parses the current line (assuming it's a tag)
	void parseKeypair();									// <- parses the current line (assuming it's a keypair)	
	
//helper functions
	bool isTag() const;										// <- whether the current line is a tag
	bool isKeypair() const;									// <- whether the current line is a keypair
	
	bool isOpeningTag() const;								// <- whether the current line is a closing tag
	bool isClosingTag() const;								// <- whether the current line is a closing tag
	bool isOpeningTagOf(const std::string &tagname) const;	// <- returns whether the current line is an opening tag for 'tagname'
	bool isClosingTagOf(const std::string &tagname) const;	// <- returns whether the current line is a closing tag for 'tagname'
	
	bool isChildOf(const std::string &tag) const;			// <- returns whether the current tagset is equal to the parameter 'tag'
	
//error functions
	//these are nothing fancy, they just log a simple error message to std::cerr describing the nature and location of the error
	void invalidKeypair() const;
	void invalidTagset() const;
	void invalidLine() const;
	
private:
//private helper functions
	bool isEmpty() const;					// <- whether the current line is empty, i.e., ""
	bool isComment() const;					// <- whether the current line is a comment, i.e., #this is a comment*/
		
//misc private methods
	std::string tagValue(const std::string &s) const;
	void reset();

//private members
	std::string m_filename;					// <- the name of the file being parsed
	std::ifstream m_infile;					// <- the filestream used to read the file
	std::string m_key;						// <- the key of the most recently parsed keypair
	std::string m_value;					// <- the value of the most recently parsed keypair
	std::string m_currentLine;				// <- the current line
	double m_lineCount;						// <- the line number of the current line	
	std::stack <std::string> m_tagStack;	// <- a stack of all the tagsets in the current infile, stored in the form "[tagset_name]"
	std::vector <std::string> m_tagVec;		// <- exact copy of m_tagStack that allows random access
};
