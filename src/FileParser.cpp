#include <iostream>
#include <algorithm> 	// for find(std::string::iterator)
#include <cstddef>		// for std::size_t

#include "UtilsParsing.h"
#include "FileParser.h"

/**********************************************************
 * top-level functions
 **********************************************************/

FileParser::FileParser() : m_key(""), m_value(""), m_infile(NULL), m_filename(""), m_currentLine(""), m_lineCount(0)
{
	
}


FileParser::~FileParser()
{
	if (m_tagStack.size() > 0)
	{
		std::cerr << "Error: End of file reached, but missing closing tag for tagset " << m_tagStack.top() << " in file '" << m_filename << "':" << std::endl;
	}
}


bool FileParser::open(const std::string &filename)
{
	m_filename = filename;
	
	m_infile.open(filename.c_str(), std::ios::in);	
	if (!m_infile.is_open())
		std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
	
	return m_infile.is_open();
}


void FileParser::close()
{	
	if (m_infile.is_open())
	{
		m_infile.close();
	}
}


bool FileParser::notEOF()
{	
	/*
	 * The reason for this internal loop is to skip over all comments and empty lines until we find a line of code/data.
	 * If a code/data line is found, immediately return true for the function (thereby ending the function's internal loop).
	 * If the EOF is encountered before we find a code/data line, that means there aren't any more lines left to process, 
	 * so the function's interal loop won't run and the return value of the function will be false.
	 */	
	while (m_infile.good())	//while we haven't hit EOF
	{	
		getNextLine();
		
		//skip all empty lines and comments
		if (isEmpty() || isComment())
		{
			continue;
		}
		/* Since the function execution will only ever reach this point if the current line isn't an empty or a comment line,
		the current line must be a data/code line, so the function returns true. */
		return true;	// <- as long as we haven't hit EOF, we've still got more lines to parse	
	}
	
	//reached the end of the file, so the above loop was not executed on this iteration and the function now returns false
	return false;
}


void FileParser::getNextLine()
{
	reset();	//reset members
	m_lineCount++;	//increment the line count
	
	std::string line;
	if (!std::getline(m_infile, line))
	{
		line = "";
	}
	else
	{
		line = stripCarriageReturn(line);
		line = trim(line, ' ');		//remove whitespace from both ends
		line = trim(line, '\t');	//remove tabs from both ends
	}
	
	m_currentLine = line;	
}


/**********************************************************
 * accessors
 **********************************************************/

std::string FileParser::currentLine() const
{
	return m_currentLine;
}


std::string FileParser::key() const
{
	return m_key;
}


std::string FileParser::value() const
{
	return m_value;
}


std::string FileParser::currentTagset() const
{
	if (m_tagStack.size() > 0)
	{
		return m_tagStack.top();
	}
	else
	{
		return "";
	}
}


double FileParser::lineCount() const
{
	return m_lineCount;
}


/**********************************************************
 * helper functions
 **********************************************************/

bool FileParser::isTag() const
{
	return (m_currentLine[0] == '[' && m_currentLine[m_currentLine.length()-1] == ']');
}


bool FileParser::isKeypair() const
{
	size_t found = m_currentLine.find_first_of('=');
	return (found != std::string::npos);
}


bool FileParser::isOpeningTag() const
{
	return (m_currentLine[1] != '/');
}


bool FileParser::isClosingTag() const
{
	return (m_currentLine[1] == '/');
}


bool FileParser::isOpeningTagOf(const std::string &tagname) const
{	
	std::string tag ("[" + tagname + "]");
	return (m_currentLine == tag);
}


bool FileParser::isClosingTagOf(const std::string &tagname) const
{
	std::string tag = "[/" + tagname + "]";
	return (m_currentLine == tag);
}


bool FileParser::isChildOf(const std::string &tag) const
{
	//make sure the current line isn't toplevel scope (since toplevel lines can't have a parent tagset by definition)
	if (m_tagStack.size() > 0)
	{
		//special handling needed for tags
		if (isTag())
		{
			if (isOpeningTag())
			{
				if (m_tagStack.size() > 1)
					return (m_tagVec[m_tagVec.size()-2] == tag);
				else
					return false;
			}
			else //this is a closing tag
			{
				if (m_tagStack.size() > 0)
					return (m_tagVec[m_tagVec.size()-1] == tag);
				else
					return false;
			}
		}
		else
		{
			return (m_tagStack.top() == tag);
		}
	}
	else
	{
		return false;
	}
}


/**********************************************************
 * error functions
 **********************************************************/

void FileParser::invalidKeypair() const
{
	std::cerr << "Error: Unrecognized keypair '" << m_currentLine << "' at line " << m_lineCount << " of '"<< m_filename << "'" << std::endl;
}


void FileParser::invalidTagset() const
{
	std::cerr << "Error: Unrecognized tagset '" << m_currentLine << "' at line " << m_lineCount << " of '"<< m_filename << "'" << std::endl;
}


void FileParser::invalidLine() const
{
	std::cerr << "Error: Unrecognized string '" << m_currentLine << "' at line " << m_lineCount << " of '"<< m_filename << "'" << std::endl;
}


/**********************************************************
 * private methods
 **********************************************************/

bool FileParser::isEmpty() const
{
	return (m_currentLine.length() == 0);
}


bool FileParser::isComment() const
{
	return (m_currentLine[0] == '#');
}


void FileParser::parseTag()
{
	if (isOpeningTag())
	{
		//the new tagset is now in the immediate scope, so add it as the current tagset
		m_tagStack.push(m_currentLine);
		m_tagVec.push_back(m_currentLine);
	}
	else	//since we already know the current line is a tag, but not an opening tag, it must be a closing tag
	{
		if (isClosingTagOf(tagValue(currentTagset()) ))
		{
			//the immediate-level tagset goes out of scope, so discard it
			m_tagStack.pop();
			m_tagVec.pop_back();
		}
		else
		{
			std::cerr << "Error: missing closing tag for tag " << currentTagset() << " at line " << m_lineCount << " in file " << m_filename << std::endl;
		}
	}
}


void FileParser::parseKeypair()
{
	std::size_t equals = m_currentLine.find_first_of('=');
	std::string tempKey = m_currentLine.substr(0, equals);
	std::string tempValue = m_currentLine.substr(equals+1);
	m_key = trim(tempKey, ' ');
	m_value = trim(tempValue, ' ');
}


std::string FileParser::tagValue(const std::string &s) const
{
	std::string str = s;
	std::size_t first = str.find_first_not_of("[/");
	std::size_t last = str.find_last_not_of("]");
	
	if (first != std::string::npos && last != std::string::npos)
	{
		str = str.substr(first, last);
		//std::cout << "tagValue(): Returning " << str.c_str() << " from " << s.c_str() << std::endl;
		return str;
	}
	else
	{
		return "";
	}
}


void FileParser::reset()
{
	m_currentLine = "";
	m_key = "";
	m_value = "";
}
