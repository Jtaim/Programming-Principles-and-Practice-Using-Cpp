#ifndef UTILITY_GUARD_H
#define UTILITY_GUARD_H

#include <string>

// run-time checked narrowing cast (type conversion).
	template<typename Target, typename Source>
	Target narrow_cast(const Source& a)
	{
		auto r = static_cast<Target>(a);
		if(static_cast<Source>(r) != a){
			throw std::runtime_error("narrow_cast<>() failed");
		}
		return r;
	}

#endif // UTILITY_GUARD_H
