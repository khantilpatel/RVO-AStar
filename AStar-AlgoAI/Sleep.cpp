//
//  Sleep.cpp
//

#include <cassert>

#include "Sleep.h"



#ifdef _WIN32

	#include <windows.h>  // needed for Sleep(millisec)

	void sleep (double seconds)
	{
		assert(seconds >= 0.0);

		int milliseconds = (int)(seconds * 1000.0);

		if(milliseconds > 0)
			Sleep(milliseconds);
		else
			Sleep(0);
	}

#else	// linux or Mac OSX

	#include <unistd.h>  // needed for usleep(microsec)

	void sleep (double seconds)
	{
		assert(seconds >= 0.0);

		int microseconds = (int)(seconds * 1000000.0);

		if(microseconds > 0)
			usleep(microseconds);
		else
			usleep(0);
	}

#endif
