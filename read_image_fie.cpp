/**Read characters in a file and dump those characters in order and with hex value
Junya009
02/03/2018
**/
#include <iostream>     // cout
#include <fstream>      // ifstream
#include <iomanip>      // setfill, setw
#include <vector>

using namespace std;  // Use this to avoid repeated "std::cout", etc.

int main(int argc, char *argv[])  // argv[1] is the first command-line argument
{
    // Check that the user has provided a filename to be read.
    if (argc != 2)
    {
        cout << "\n\n\tUsage:  MSUdebug <filename>" << endl;
        exit(0);
    }

    // Open the provided file for reading of binary data
    ifstream is (argv[1], ifstream::binary);
    if (is)   // if file was opened correctly . . .
    {

        is.seekg (0, is.end);   // Move to the end of the file
        int length = is.tellg();   // Find the current position, which is file length
        is.seekg (0, is.beg);  // Move to the beginning of the file

        char * buffer = new char [length]; // Explicit allocation of memory.

        cout << "Reading " << length << " characters... ";
        is.read (buffer,length);  // read data as a block or group (not individually)

        if (is)
            cout << "all characters read successfully.\n";
        else
            cout << "error: only " << is.gcount() << " could be read.\n";
        is.close();

        // Now buffer contains the entire file. The buffer can be printed as if it
        // is a _string_, but by definition that kind of print will stop at the first
        // occurrence of a zero character, which is the string-ending mark.
        cout << "buffer is:\n" << buffer << "\n";  // Print buffer

        std :: vector<char> readFile;

		for (int i=0; i< length; i++) // upper range limit is typically length
        {
            // Print each character of the data, using both decimal and hex formats
            if ( i == 0 || i % 16 == 0)   cout << setfill('0') << setw(4) << hex << i << "   ";
            readFile.push_back(buffer[i]);
            cout << setfill('0') << setw(2) << hex << (0xff & (int)buffer[i]) << " ";// Must convert char to int
            if (  (i+1) % 16 == 0)
            {
			  for (char display : readFile) cout << display;
              cout << "\n";
              readFile.clear();
            }
        }
        for (char display:readFile)
            cout << display;
        readFile.clear();
        delete[] buffer; // Explicit freeing or de-allocation of memory.
    }
    else // There was some error opening file. Show message.
    {
        cout << "\n\n\tUnable to open file " << argv[1] << "\n";
    }

    return 0;
}
