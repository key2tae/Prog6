/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Author: Stephen Perkins
 * Email:  stephen.perkins@utdallas.edu
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
  for(uint32_t i = 0; i < myHeader -> numRecords; i++)
    {
      binInfile.read((char*)(myRecords + i), sizeof(BinaryFileRecord));
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
  
  char buffer[100];
  sprintf(buffer,"%X", myHeader -> magicNumber);
  string str = "Magic: 0X";
  str = str + buffer;
  setCDKMatrixCell(myMatrix, 1, 1, str.c_str());
  drawCDKMatrix(myMatrix, true);
  str = "Version:  ";
  str = str  + to_string(myHeader -> versionNumber);
  setCDKMatrixCell(myMatrix, 1, 2, str.c_str());
  drawCDKMatrix(myMatrix, true);
  str = "NumRecords:  ";
  str = str  + to_string(myHeader -> numRecords);
  setCDKMatrixCell(myMatrix, 1, 3, str.c_str());
  
  for(uint32_t i = 0; i < myHeader -> numRecords; i++)
    {
      string str = "strlen: " + to_string(static_cast<uint16_t>(myRecords[i].strLength));
      setCDKMatrixCell(myMatrix, 2 + i, 1, str.c_str());
      setCDKMatrixCell(myMatrix, 2 + i, 2, myRecords[i].stringBuffer);
    }

  drawCDKMatrix(myMatrix, true);


  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
