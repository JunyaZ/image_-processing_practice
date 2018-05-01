// Inspiration: http://www.cplusplus.com/reference/istream/istream/read/
// Read characters in a file and dump those characters in order and with hex value
#include <iostream>     // cout
#include <fstream>      // ifstream
#include <iomanip>      // setfill, setw

using namespace std;  // Use this to avoid repeated "std::cout", etc.

// int main(int argc, char *argv[])  // argv[1] is the first command-line argument
int main()
{
	int dataCounter = 0;   // index through the buffer contents
	char filename[256];
	char *filename_ptr;
	filename_ptr = &filename[0];

	// Prompt user for filename.BMP to use
	cout << "\n\n\tWhat BMP file is the input?  ";
	cin >> filename_ptr;

	// Open the provided file for reading of binary data
	ifstream is (filename_ptr, ifstream::binary);
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
		// cout << "buffer is:\n" << buffer << "\n";  // Print buffer



	    // read the image width and height which are stored in 32-bit integer, LSByte first.
	    // We need to swap the bytes around.
	    // Also, the bytes read are really unsigned bytes -- but C++ will treat them as signed.
		int width = 0, height = 0;  // 32-bit integers
		int dataIndex = 18;  // harcoded: Index to BMP data for width, height
	    width = buffer[dataIndex + 0] & 0xff;  // LeastSigByte of data is now in LeastSigByte of 32-bit int
	    width += (buffer[dataIndex + 1] & 0xff) << 8;  // This is the 2nd-leastSigByte
	    width += (buffer[dataIndex + 2] & 0xff)  << 16;  // This is the 3nd-leastSigByte
	    width += (buffer[dataIndex + 3] & 0xff)  << 24;   // This is the 4nd-leastSigByte ie MostSigByte

        height +=  buffer[dataIndex + 4] & 0xff;  // LeastSigByte of data is now in LeastSigByte of 32-bit int
	    height += (buffer[dataIndex + 5] & 0xff) << 8;  // This is the 2nd-leastSigByte
	    height += (buffer[dataIndex + 6] & 0xff)  << 16;  // This is the 3nd-leastSigByte
	    height += (buffer[dataIndex + 7] & 0xff)  << 24;


		cout << "Width = " << width << ", height = " << height;

		delete[] buffer; // Explicit freeing or de-allocation of memory.

	}
	else // There was some error opening file. Show message.
	{
		cout << "\n\n\tUnable to open file " << *filename_ptr << "\n";
	}

	return 0;
}
