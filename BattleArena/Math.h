#pragma once
namespace Math {
	template<class T>
	T clamp(T* value, T min, T max) {
		return (*value = *value < min ? min : *value > max ? max : *value);

	}
	
	template<class T>
	T clamp(T* value) {
		return (*value = *value < 0 ? 0 : *value > 1 ? 1 : *value);
	}
}

