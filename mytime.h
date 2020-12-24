///////////////////////////////////////////////////////////////////////
//
// It returns seconds elapsed since start of program, as a double
//
// - take care of different platforms: WINDOWS and Unix/Linux
//
// mytime.h
//
// 2003
//
///////////////////////////////////////////////////////////////////////


#ifndef _MY_TIME_HH
#define _MY_TIME_HH


// add this so that the C code can be incorporated into C++
#ifdef __cplusplus
extern "C" {
#endif


// It returns seconds elapsed since start of program, as a double
extern double myTime();


#ifdef __cplusplus
}
#endif


#endif
