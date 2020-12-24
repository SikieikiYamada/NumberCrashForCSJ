///////////////////////////////////////////////////////////////////////
//
// It returns seconds elapsed since start of program, as a double
//
// - take care of different platforms: WINDOWS and Unix/Linux
//
// mytime.c
//
// 2003
//
///////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <sys/timeb.h>
#include <time.h>
#elif defined __linux__ || defined __unix__
#include <sys/resource.h>
#include <sys/times.h>
#endif


double
myTime()
{
    // https://msdn.microsoft.com/en-us/library/95e68951.aspx
  #ifdef _WIN32

    struct _timeb timebuffer ;
    _ftime( &timebuffer );
    return ( timebuffer.time + timebuffer.millitm * 0.001 );

  #elif defined __linux__ || defined __unix__

    // http://man7.org/linux/man-pages/man2/getrusage.2.html
    struct rusage t;
    double procTime;

    /// (1) Get the rusage data structure at this moment
    getrusage(0,&t);

    // (2) What is the elapsed time?
    //     - CPU time = User time + system time

      // (2a) Get the seconds
      procTime = t.ru_utime.tv_sec + t.ru_stime.tv_sec ;

      // (2b) More precisely! Get the microseconds too! :)
      procTime += (t.ru_utime.tv_usec + t.ru_stime.tv_usec) * 1e-6 ;

    // (3) Return the time!
    return procTime ;

  #else

    fprintf( stderr , "Warning (myTime): doesn't support the current platform!\n" );
    return 0.0 ;

  #endif
}

