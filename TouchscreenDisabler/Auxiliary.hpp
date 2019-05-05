#ifndef AUXILIARY_HPP
#define AUXILIARY_HPP

/**
 * @brief Use it to safely remove anything. It calls delete obj, and then sets obj to 0.
 * @param obj What we need to delete
 */
template <typename T>
void SafeDelete(T obj)
{
	delete obj;
	obj = nullptr;
}

#endif // AUXILIARY_HPP
