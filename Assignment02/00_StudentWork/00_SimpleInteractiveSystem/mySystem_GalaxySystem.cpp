//
// Instructor: Sai-Keung WONG
// Email:	cswingo@nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2022/03/17
//
#include "mySystem_GalaxySystem.h"
#include <iostream>

using namespace std;

namespace {
    // randomly generate a double number between [L, U] (inclusive).
    double getRandDouble( double L, double U ) {
        return L + (U-L)*rand( )/(double) RAND_MAX;
    }
};

GALAXY_SYSTEM::GALAXY_SYSTEM( )
{
    mTimeStep = 0.0025; 
    mMaxV = 100.0;
    mNumOfObjs = 100;
    mNumLargeObjs = 2;
    mActiveObjectNumber = mNumOfObjs;
    mMinR = 0.5;                        //minimum radius of objects
    mMaxR = 3.0;                        //maximum radius of objects
    mSpaceSize = 300.0;
    mG = 5.0;                           //gravitational constant
    //
    mNumFrames = 0;
    generateObjects( );
}

/*
Generate randomly the positions,  
velocities and radii of the objects.

Also, if the objects are large, 
set their masses to be a large number.

The mass of an  object depends on the object's radius.

The position of an object is inside 
[-halfSpaceSize, halfSpaceSize]x[-halfSpaceSize, halfSpaceSize].

The velocity of an object is inside
[-100.0, 100]x[-100.0, 100].

Initialize the alive flag of each object.
the alive flag indicates whether the object is alive or not.
If the object is not alive, ignore it in all the calculations.

If there's only one large object,
set its position to the origin
and set its velocity to zero.

*/
void GALAXY_SYSTEM::generateObjects( )
{
    mNumFrames = 0;
    mX.clear();
    mY.clear();
    mR.clear();
    mMass.clear();
    mVx.clear();
    mVy.clear();
    mFx.clear();
    mFy.clear();
    mAlive.clear();
    mTails.clear();

    // fill/modify your own stuff
    // You can remove the following lines.
           mX.resize(mNumOfObjs);
    mY.resize(mNumOfObjs);
    mR.resize(mNumOfObjs);
    mMass.resize(mNumOfObjs);
           mVx.resize(mNumOfObjs);
    mVy.resize(mNumOfObjs);
           mFx.resize(mNumOfObjs);
    mFy.resize(mNumOfObjs);
           mAlive.resize(mNumOfObjs);
           mTails.resize(mNumOfObjs);

           for (int i = mNumLargeObjs; i < mNumOfObjs; i++) {
                       mX[i] = getRandDouble(-mSpaceSize / 2, mSpaceSize / 2);
                       mY[i] = getRandDouble(-mSpaceSize / 2, mSpaceSize / 2);
                       mVx[i] = getRandDouble(-100, 100);
                       mVy[i] = getRandDouble(-100, 100);
                       mR[i] = getRandDouble(mMinR, mMaxR);
                       mMass[i] = mR[i] * mR[i];
                       mAlive[i] = true;
                       TAIL_PLANET tail(mX[i], mY[i]);
                       mTails[i] = tail;
           }
           for (int i = 0; i < mNumLargeObjs; i++) {
                       mX[i] = mNumLargeObjs == 1 ? 0.0 : getRandDouble(-mSpaceSize / 2, mSpaceSize / 2);
                       mY[i] = mNumLargeObjs == 1 ? 0.0 : getRandDouble(-mSpaceSize / 2, mSpaceSize / 2);
                       mVx[i] = 0.0;
                       mVy[i] = 0.0;
                       mR[i] = mMaxR * 2.0;
                       mMass[i] = mMaxR * mMaxR * 1000;
                       mAlive[i] = true;
                       TAIL_PLANET tail(mX[i], mY[i]);
                       mTails[i] = tail;
           }
    
       mFx.resize(mNumOfObjs);
       mFy.resize(mNumOfObjs);

    
}

/*
Handle the key events.
*/
bool GALAXY_SYSTEM::handleKeyPressedEvent( int key )
{
    bool flgHandled = false;
    switch( key ) {
    case '1':
        mNumLargeObjs = 1;
        flgHandled = true;
        break;
    case '2':
        mNumLargeObjs = 2;
        flgHandled = true;

        break;
    case '3':
        mNumLargeObjs = 3;
        flgHandled = true;
        break;
    case 'r':
    case 'R':
        reset();
        flgHandled = true;

        break;
    }
    if ( flgHandled ) reset( );
    return flgHandled;
}

/*
Generate the objects.
Call generateObjects( ).
*/
void GALAXY_SYSTEM::reset( )
{
    generateObjects( );
}

/*
Show the system title.
Show the key usage.
*/
void GALAXY_SYSTEM::askForInput( )
{
    cout << "GALAXY_SYSTEM::askForInput" << endl;
    cout << "Key usage:" << endl;
    cout << "1: one large object" << endl; // generate the objects. Only one large object
    cout << "2: two large object" << endl; // generate the objects. Only two large objects
    cout << "3: three large object" << endl; // generate the objects. Only three large objects
    cout << "r: reset" << endl; 		// reset the positions of the objects
    // fill/modify your own stuff
}

/*
Return the number of objects
*/
int GALAXY_SYSTEM::getNumOfObjs( ) const
{
    return mNumOfObjs;
}

/*
* Return the number of active objects
* 
*/ 
int GALAXY_SYSTEM::getNumberOfActiveObjects() const
{
    return mActiveObjectNumber;
}

/*
Get the object information based on the object index.
(x,y) = position
r = radius
Return the alive flag.
*/
bool GALAXY_SYSTEM::getObjInfo( int objIndex, double &x, double &y, double &r ) const
{
    
    x = mX[objIndex];
    y = mY[objIndex];
    r = mR[objIndex];
    
    // fill/modify your own stuff
   // x = 1;
    //y = 2;
   // r = 4;
    return mAlive[objIndex];
}

/*
Merge the objects if they overlap with each other.
Modify the velocities of the objects after merging
based on the conservation of momentum.
Set the alive flags of the objects accordingly.

Pseudo-code

For each pair of the objects
  if they do not overlap continue
  If they overlap
    do
      turn off the alive flag of the object with smaller radius
      compute the new velocity of the larger object
*/
void GALAXY_SYSTEM::mergeObjects( )
{
    // fill/modify your own stuff
    for (int i = 0; i < mNumOfObjs; ++i) {
        if (!mAlive[i]) continue;
        for (int j = i + 1; j < mNumOfObjs; ++j) {
            if (!mAlive[j]) continue;
            if ((mX[i] - mX[j]) * (mX[i] - mX[j]) + (mY[i] - mY[j]) * (mY[i] - mY[j]) < (mR[i] + mR[j]) * (mR[i] + mR[j])) {
                int mivi_mjvj_X = mVx[i] * mMass[i] + mVx[j] * mMass[j];
                int mivi_mjvj_Y = mVy[i] * mMass[i] + mVy[j] * mMass[j];

                if (mMass[i] < mMass[j]) {
                    mMass[j] += mMass[i];
                    mVx[j] = mivi_mjvj_X / mMass[j];
                    mVy[j] = mivi_mjvj_Y / mMass[j];
                    mAlive[i] = 0;
                }
                else {
                    mMass[i] += mMass[j];
                    mVx[i] = mivi_mjvj_X / mMass[i];
                    mVy[i] = mivi_mjvj_Y / mMass[i];
                    mAlive[j] = 0;
                }
            }
        }
    }
}
/*
* Compute the number of active objects
*/

void GALAXY_SYSTEM::computeNumberOfActiveObjects()
{
    mActiveObjectNumber = 0;
    for (int i = 0; i < mNumOfObjs; ++i) {
        double mi = mMass[i];
        if (!mAlive[i]) continue;
        ++mActiveObjectNumber;
    }
}

void GALAXY_SYSTEM::computeForcesOfObjects()
{
    for (int i = 0; i < mNumOfObjs; ++i) {
        mFx[i] = 0.0;
        mFy[i] = 0.0;
    }
    //
    for (int i = 0; i < mNumOfObjs; ++i) {
        if (!mAlive[i]) continue;
        for (int j = i + 1; j < mNumOfObjs; ++j) {
            if (!mAlive[j]) continue;
            double d = sqrt((mX[i] - mX[j]) * (mX[i] - mX[j]) + (mY[i] - mY[j]) * (mY[i] - mY[j]));
            double dx = mX[i] - mX[j], dy = mY[i] - mY[j];
            double nx = dx / d; //normalize along the x-axis
            double ny = dy / d; //normalize along the y-axis

            double mij = mMass[i] * mMass[j];

            mFx[i] -= mij * mG * nx / d/d; 	//notice the negative sign	
            mFy[i] -= mij * mG * ny / d/d;	//notice the negative sign

            mFx[j] += mij * mG * nx / d/d;	//notice the positive sign
            mFy[j] += mij * mG * ny / d/d;  //notice the positive sign

        }
    }
}

void GALAXY_SYSTEM::updateVelocitiesOfObjects()
{

    for (int i = 0; i < mNumOfObjs; ++i) {
        double m = mMass[i];  
        mVx[i] = mVx[i] + mFx[i] / m * mTimeStep;
        mVy[i] = mVy[i] + mFy[i] / m * mTimeStep;
        if (mVx[i] < -100) mVx[i] = -100;
        if (mVx[i] > 100) mVx[i] = 100;
        if (mVy[i] < -100) mVy[i] = -100;
        if (mVy[i] > 100) mVy[i] = 100;
    }
}

void GALAXY_SYSTEM::updatePositionsOfObjectsAndTails()
{
    int skipFrames = 10;
    double halfSpaceSize = mSpaceSize / 2.0;
    for (int i = 0; i < mNumOfObjs; ++i) {
                if (!mAlive[i]) continue;

                mX[i] = mX[i] + mVx[i] * mTimeStep;
                mY[i] = mY[i] + mVy[i] * mTimeStep;
                if (mX[i] > halfSpaceSize) mX[i] = -halfSpaceSize;
                if (mX[i] < -halfSpaceSize) mX[i] = halfSpaceSize;
                if (mY[i] > halfSpaceSize) mY[i] = -halfSpaceSize;
                if (mY[i] < -halfSpaceSize) mY[i] = halfSpaceSize;

                if (skipFrames == 0 || mNumFrames % skipFrames == 0) {
                    mTails[i].add_to_front(mX[i], mY[i]);
                }
        
    }
}
/*
Update the position of the objects
Steps:
1. compute the forces exerting on each object
2. compute the velocity of each object
3. compute the position of each object

Constraints:
The component of a velocity must be inside [-mMaxV, mMaxV].

The component of a position must be inside [-halfSpaceSize, halfSpaceSize].
Warp the position if it's outside of the range.
Consider a position (x,y).
If x > halfSpaceSize, set x = -halfSpaceSize;


*/
void GALAXY_SYSTEM::update( ) 
{
    /*
    * Do not change here
    */
    mergeObjects();
    computeForcesOfObjects();
    updateVelocitiesOfObjects();
    updatePositionsOfObjectsAndTails();
    computeNumberOfActiveObjects();
    
    ++mNumFrames;
}

//
// return the number of sample points of the tail
// of an object with index planet_index
int GALAXY_SYSTEM::getTail_NumSamplePoints( int planet_index ) const 
{ 
    //
    // fill/modify your own stuff
    //
    return mTails[planet_index].points.size();
    //return 0;
}

//
// return the coordinates of the sample point of an object
//
COORD_2D GALAXY_SYSTEM::getTail_SamplePointCoords( 
    int planet_index, 
    int sample_point_index ) const 
{ 
    return mTails[planet_index].points[sample_point_index];
    //return COORD_2D(0, 0);
}