#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "11";
	static const char MONTH[] = "08";
	static const char YEAR[] = "2023";
	static const char UBUNTU_VERSION_STYLE[] =  "23.08";
	
	//Software Status
	static const char STATUS[] =  "Release Candidate";
	static const char STATUS_SHORT[] =  "rc";
	
	//Standard Version Type
	static const long MAJOR  = 3;
	static const long MINOR  = 5;
	static const long BUILD  = 1;
	static const long REVISION  = 1;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 0;
	#define RC_FILEVERSION 3,5,1,1
	#define RC_FILEVERSION_STRING "3, 5, 1, 1\0"
	static const char FULLVERSION_STRING [] = "3.5.1.1";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 99;
	

}
#endif //VERSION_H
