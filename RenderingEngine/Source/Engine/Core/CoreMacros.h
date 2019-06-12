#pragma once
#define ASSERT(Condition) {\
	if(!Condition)\
		__debugbreak();\
}