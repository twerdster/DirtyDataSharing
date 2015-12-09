

// Compile with
//mex getShared.cpp -I"C:\Development\boost_1_48_0" 

#include <math.h>

#define BOOST_ALL_NO_LIB
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "mex.h"

using namespace boost::interprocess;
#define SHAREDLENGTH (1024*1024) // 1mb of shared memory

// This structure is extremely brittle. It needs to be changed for every
// different type of data
struct sharedPt
{
	enum { dataLength = SHAREDLENGTH};
	interprocess_mutex mutex;
	uint8_t  data[dataLength]; 
};

shared_memory_object shm;

mapped_region region;

void getSharedData(char* name, uint8_t *data, int ofs, int sz)
{      
	try 
	{
		//Open the shared memory object.
		shared_memory_object shm(open_only ,name, read_write);

		//Map the whole shared memory in this process
		mapped_region region(shm ,read_write);

		//Get the address of the mapped region
		void * addr = region.get_address();

		//Construct the shared structure in memory
		sharedPt * spt_ = static_cast<sharedPt*>(addr);

		//scoped_lock<interprocess_mutex> lock(sIm->mutex);
		memcpy(data, (uint8_t*)spt_->data + ofs, sz);   
	}	
	catch (interprocess_exception &ex)
	{
		mexPrintf("getFrame:%s\n", ex.what());
	}
}


void mexFunction(int nlhs, mxArray *plhs[ ], int nrhs, const mxArray *prhs[ ])
{
    char* name = mxArrayToString(prhs[0]);
    int ofs = mxGetScalar(prhs[1]);
    int sz = mxGetScalar(prhs[2]);
    
    plhs[0] = mxCreateNumericMatrix(sz, 1, mxUINT8_CLASS, mxREAL);
	uint8_t* data = (uint8_t*)mxGetData(plhs[0]);
    
    try
    {
       getSharedData(name, data, ofs, sz);
    }
    catch (interprocess_exception &ex)
    {
        mexPrintf("getFrame:%s\n", ex.what());
    }
}

