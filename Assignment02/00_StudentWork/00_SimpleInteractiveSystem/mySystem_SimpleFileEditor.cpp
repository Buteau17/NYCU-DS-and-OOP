//
// Instructor: Sai-Keung WONG
// Email:	cswingo@nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2022/03/17
//
#include "mySystem_SimpleFileEditor.h"
#include <iostream>
#include <fstream>
using namespace std;

#define FILE_NAME "oop.txt"

SIMPLE_FILE_EDITOR::SIMPLE_FILE_EDITOR( )
{
    //BEGIN: DO NOT CHANGE
    mNX = 100; // number of columns
    mNY = 100; // number of rows
    mBitmap = new int[mNX*mNY];
    for ( int i = 0; i < mNX*mNY; ++i ) {
        mBitmap[ i ] = 0;
    }
    readFile( );
    //END: DO NOT CHANGE

}

/*
Set up the bitmap based on the data stored in a file.

Each line in the file is mapped to one row
of the bitmap in a consecutive manner.

Steps:
Open the file.
Read a file.
 Repeat until EOF
   read a line from the file each time
   set the bitmap based on the current line
Close the file.
*/
void SIMPLE_FILE_EDITOR::readFile( )
{
    mCurX = 0;
    mCurY = 0;
    ifstream inFile;
    inFile.open( FILE_NAME );
    string inputString;
    //
    // fill/modify your own stuff
    //
    
    while ( inFile ) {
        getline(inFile, inputString );
        if (inputString.size() == 0) continue;
        storeOneRowToBitmap(inputString);
        inputString.clear();
    }
    
    inFile.close( );
}

/*
Set one row of the bitmap based on the input string inputString.
The elements of the row are mapped one to one to the input string.

The element of a bitmap is set as follows.

If inputString[i] is the space character, 
the value of the element is set as 0.
Otherwise, the value of the element is set to (int) inputString[i].
*/
void SIMPLE_FILE_EDITOR::storeOneRowToBitmap( const string &inputString )
{
    if (mCurY>= mNY) return;
    int index = mCurX + mCurY*mNX;

    for (int i = 0; i < inputString.size(); i++) {
        if (inputString[i] == ' ') mBitmap[i + index] = 0;
        else mBitmap[i + index] = (int)inputString[i];
    }

    ++mCurY;
}

/*
Show the system title.
Show "No input is required!".
*/
void SIMPLE_FILE_EDITOR::askForInput( )
{
    //Show the system title
    //
    cout << "SIMPLE_FILE_EDITOR" << endl;
    //cout << "No input is required!" << endl;
    cout << "<: rotate to left\n";
    cout << ">: rotate to right";

}

/*
Get the dimension of the bitmap to (nx, ny).
nx : number of columns
ny : number of rows
*/
void SIMPLE_FILE_EDITOR::getBitmapDimension(int &nx, int &ny) const
{
    nx =this ->  mNX;
    ny =this-> mNY;
}

/*
Return the bitmap value at (x, y).
x : column index
y : row index
*/
int SIMPLE_FILE_EDITOR::getBitmapValue(int x, int y) const
{
    //
    // fill/modify your own stuff
    //
    
    return mBitmap[x + y * mNX];
}

bool SIMPLE_FILE_EDITOR::handleKeyPressedEvent( int key )
{
    bool flg =false;
    switch(key) {
    case '<':
        rotateToLeft( );
        flg = true;
        break;
        case '>':
        rotateToRight( );
        flg = true;
        break;
    }

    return flg;
}
void SIMPLE_FILE_EDITOR::rotateToLeft()
{
    vector<int> temp;
    for (int j = mNX-1; j >= 0; j--) {
        for (int i = j; i < mNX * mNY; i += mNX) {
            temp.push_back(mBitmap[i]);
        }
    }
    for (int i = 0; i < mNX * mNY; i++) {
        mBitmap[i] = temp[i];
    }
    int tmp = mNX;
    mNX = mNY;
    mNY = tmp;
    /*
    vector<int> temp;
    for (int i = 0; i < mNY; ++i) {
        temp.push_back(mBitmap[0 + i * mNX]);
    }
    for (int i = 1; i < mNX - 1; ++i) {
        for (int j = 0; j < mNY; ++j) {
            mBitmap[j + i * mNX] = mBitmap[j + 1 + i * mNX];
        }
    }
    for (int i = 0; i < mNY; ++i) {
        mBitmap[mNX - 1 + i * mNX] = temp[i];
    }*/
}

void SIMPLE_FILE_EDITOR::rotateToRight()
{
    vector<int> temp;
    for (int j = 0; j < mNX; j++) {
        for (int i = mNX * mNY-mNX+j; i >= 0 ; i -=mNX ) {
            temp.push_back(mBitmap[i]);
        }
    }
    for (int i = 0; i < mNX * mNY; i++) {
        mBitmap[i] = temp[i];
    }
    int tmp = mNX;
    mNX = mNY;
    mNY = tmp;
    /*
    for (int i = 0; i < mNY; ++i) {
        temp.push_back(mBitmap[mNX - 1 + i * mNX]);
    }
    for (int i = 1; i < mNX - 1; ++i) {
        for (int j = mNY - 1; j >= 0; --j) {
            mBitmap[j + i * mNX] = mBitmap[j - 1 + i * mNX];
        }
    }
    for (int i = 0; i < mNY; ++i) {
        mBitmap[0 + i * mNX] = temp[i];
    }*/
}

