/*
 * Keerthana Ramesh
 * SE 3377.501
 * kxr144230@utdallas.edu
 */

#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include "cdk.h"
#include <stdint.h>
#include <fstream>


#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Test Matrix"

const int maxRecordsStringLength = 25;

using namespace std;


// Classes to initialize vars
class BinaryFileRecord
{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordsStringLength];
};


class BinaryFileHeader
{
public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};
  

int main()
{
  
  BinaryFileHeader *myHeader = new BinaryFileHeader();

  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);

  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
  cout << "Value was: " << setprecision(10) << myHeader -> versionNumber << endl;


  BinaryFileRecord *myRecords = new BinaryFileRecord[myHeader -> numRecords]();
  for(uint32_t x = 0; x < myHeader -> numRecords; x++)
    {
      // pointer to existing and allocated memory and the length of BinaryFileRecord
      binInfile.read((char*)(myRecords + x), sizeof(BinaryFileRecord));
    }
  
  binInfile.close(); 


  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char 		*columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */
 
  //Declare buffer array
  char buffer[100];
  
  //Converts a decimal number into hex 
  sprintf(buffer,"%X", myHeader -> magicNumber);
  
  //Variable that holds the Magic Number 
  string s = "Magic: 0X";
  s = s + buffer; // Concatenates to the number from the buffer 
  
  setCDKMatrixCell(myMatrix, 1, 1, s.c_str());
  drawCDKMatrix(myMatrix, true);
  
  s = "Version:  ";
  s = s  + to_string(myHeader -> versionNumber);
  
  setCDKMatrixCell(myMatrix, 1, 2, s.c_str());
  drawCDKMatrix(myMatrix, true);
  
  s = "NumRecords:  ";
  s = s  + to_string(myHeader -> numRecords); // String Concatenation again
  
  setCDKMatrixCell(myMatrix, 1, 3, s.c_str());
  
  for(uint32_t x = 0; x < myHeader -> numRecords; x++)
    {
      string s = "strlen: " + to_string(static_cast<uint16_t>(myRecords[x].strLength));
      setCDKMatrixCell(myMatrix, 2 + x, 1, s.c_str());
      setCDKMatrixCell(myMatrix, 2 + x, 2, myRecords[x].stringBuffer);
    }

  drawCDKMatrix(myMatrix, true);


  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
