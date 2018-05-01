// Inspiration: http://www.cplusplus.com/reference/istream/istream/read/
// Read characters in a file and dump those characters in order and with hex value
#include <iostream>     // cout
#include <fstream>      // ifstream
#include <iomanip>      // setfill, setw

using namespace std;  // Use this to avoid repeated "std::cout", etc.
 // harcoded: Index to BMP data for width, height
int main()
{
	int dataCounter = 0;   // index through the buffer contents

	// Open the output file for writing of binary data
	ofstream os ("Assn2PartD_Junya009.bmp", ofstream::binary);
	// Open the provided file for reading of binary data
	ifstream is ( "MarthaStewart1.bmp", ifstream::binary);
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

        int width = 0, height = 0;  // 32-bit integers
        int dataIndex = 18;
	    width = buffer[dataIndex + 0] & 0xff;  // LeastSigByte of data is now in LeastSigByte of 32-bit int
	    width += (buffer[dataIndex + 1] & 0xff) << 8;  // This is the 2nd-leastSigByte
	    width += (buffer[dataIndex + 2] & 0xff)  << 16;  // This is the 3nd-leastSigByte
	    width += (buffer[dataIndex + 3] & 0xff)  << 24;   // This is the 4nd-leastSigByte ie MostSigByte

        height += buffer[dataIndex + 4] & 0xff;  // LeastSigByte of data is now in LeastSigByte of 32-bit int
	    height += (buffer[dataIndex + 5] & 0xff) << 8;  // This is the 2nd-leastSigByte
	    height += (buffer[dataIndex + 6] & 0xff)  << 16;  // This is the 3nd-leastSigByte
	    height += (buffer[dataIndex + 7] & 0xff)  << 24;


		cout << "Width = " << width << ", height = " << height;
		// Print the BMP header and information
		os.write (buffer, 54);  // write 54 bytes of BMP header and information
		//char tempC;
		//char *tempCPtr= &tempC;
		// Manipulate each row of the BMP image
        for (int i = 0;i < height ; i++)
        {
            dataCounter = 54 + (i * width*3);
            for (int j = 0; j < width*3; j+=3 )
            {
                    char r = buffer[dataCounter + j+ 0 ];
                    char g = buffer[dataCounter + j+ 1 ];
                    char b = buffer[dataCounter + j+ 2 ];
                    char  *pr=&r;
                    char  *pg=&g;
                    char  *pb=&b;
               if( (int)r  < 30 && (int)g < 40 && (int) b > 50)
                  {
                                r = 0;
                                g = (int)255;
                                b = 0;
                                 os.write(pg,1);
                                 os.write(pb,1);
                                 os.write(pr,1);
                  }
                  else
                    {
                                 os.write(pr,1);
                                 os.write(pg,1);
                                 os.write(pb,1);

                    }
            }

         }


		delete[] buffer; // Explicit freeing or de-allocation of memory.

	}
	else // There was some error opening file. Show message.
	{
		cout << "\n\n\tUnable to open file "<< "\n";
	}

	return 0;
}
