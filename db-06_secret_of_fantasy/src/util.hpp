#ifndef UTIL_HPP
#define UTIL_HPP

inline int mod(int a, int b) {
	int r = a % b;
	return r < 0 ? b + r : r;
}
/*
inline float frand() {
	return rand() / (float)RAND_MAX;
}
*/
template <typename T>
inline T clamp(T v, T min, T max)
{
	return (v < min ? min : (v > max ? max : v));
}

template <typename T>
inline T min(T a, T b)
{
	return a < b ? a : b;
}

template <typename T>
inline T max(T a, T b)
{
	return a > b ? a : b;
}

#ifndef M_PI
#define M_PI 3.14159265358979323
#endif

#endif