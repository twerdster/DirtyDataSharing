
#include <iostream>
#include <fstream>

#define BOOST_ALL_NO_LIB

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>

using namespace std;
using namespace boost::interprocess;

#define SHAREDLENGTH (1024*1024) // 1mb of shared memory

// This structure is extremely brittle. 
struct sharedPt
{
	enum { dataLength = SHAREDLENGTH};
	interprocess_mutex mutex;
	uint8_t  data[dataLength]; 
};

shared_memory_object shm;
sharedPt * spt;
mapped_region region;

int setupSharedMemory(char * name)
{
	static bool inited = false;
	if (!inited)
	{
		inited = true;
		// Clear the object if it exists
		shared_memory_object::remove(name);

		shm = shared_memory_object(create_only  /*only create*/,name /*name*/,read_write/*read-write mode*/);

		printf("Size of shared structure: %i\n",sizeof(sharedPt));
		//Set size
		shm.truncate(sizeof(sharedPt));

		//Map the whole shared memory in this process
		region = mapped_region(shm, read_write);

		//Get the address of the mapped region
		void * addr  = region.get_address();

		//Construct the shared structure in the preallocated memory of shm
		spt = new (addr) sharedPt;
	}
	return 0;
}


int shutdownSharedMemory(char * name)
{
	shared_memory_object::remove(name);
	return 0;
}

void setSharedData(uint8_t *data,int ofs, int sz)
{
	static int imCnt = 0;		
	printf("Frame:%i\n",imCnt);
	imCnt++;
	if (data)
		memcpy(spt->data + ofs, data, sz);//Copy data to shared memory
	else
	{
		memset(spt->data + ofs,0,sz);
	}
}


