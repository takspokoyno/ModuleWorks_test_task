#ifndef __FileWriter_hpp__
#define __FileWriter_hpp__

#include <string>
#include <map>
#include <utility>
#include <iostream>
#include <fstream>

//!This class represents a FileWriter.
/*!The FileWriter is a map of upper-layer 3d points and filepath.
*/
class FileWriter
{
public:

    typedef std::map<std::pair<double, double>, double> map;

    // Sets default FileWriter
    FileWriter()
    {
        mUpperLayer = map();
        mFilePath = "test.asc";
    };

    // Sets FileWriter with given filepath and given array of pairs with maxZ
    /* Array represents x, y coordinate of all points with max coordinate z
    */
    FileWriter(const std::string &filepath, std::pair<double, double> *arrayOfPairs, const int sizeOfArray, double maxZ)
    {
        mFilePath = filepath;
        mUpperLayer = map();
        for(int i = 0; i < sizeOfArray; i++)
        {
            mUpperLayer.insert(std::pair<std::pair<double, double>, double>(arrayOfPairs[i], maxZ));
        }
    };

    // Get filepath
    std::string getFilePath() const
    {
        return mFilePath;
    }; 

    // Get upper-layer 
    map getUpperLayer() const
    {
        return mUpperLayer;
    };

    // Set new value for element
    void ChangeValue(std::pair<double, double> pair, double newvalue)
    {
        //mUpperLayer[pair] = newvalue;
        map::iterator it = mUpperLayer.find(pair); 
        if (it != mUpperLayer.end())
        {
            it->second = newvalue;
        }
    };

    // Write information to the file
    void WriteToFile()
    {
        std::fstream my_file;
	    my_file.open(mFilePath, std::ios::out);
	    if (!my_file) 
        {
		    std::cout << "File not created!";
	    }
	    else 
        {
		    std::cout << "File created successfully!";
            for(map::const_iterator it = mUpperLayer.begin(); it != mUpperLayer.end(); it++)
            {
                my_file << it->first.first << " " << it->first.second << " " << it->second << "\n";
            }
		    my_file.close();
	    }
    }

private:
    map mUpperLayer;
    std::string mFilePath;
};

#endif //__FileWriter_hpp__