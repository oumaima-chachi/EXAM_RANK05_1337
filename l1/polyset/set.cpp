#include "set.hpp"
#include <cstddef>
set::set() : bag(NULL){}
set::set(const set &other) : bag(other.bag) {}

set &set::operator=(const set &other)
{
    if (this != &other)
        bag = other.bag;
    return *this;
}

set::~set() {}

set::set(searchable_bag &bag_ref) : bag(&bag_ref){}
void set::insert(int val)
{
	if (!bag) return;
	if (!bag->has(val))
		bag->insert(val);
}
void set::insert(int *array, int size)
{
	if (!bag) return;
	for(int i = 0 ; i < size; ++i)
	{
		insert(array[i]);
	}
}
void set::print() const
{
	if (!bag) return;
	bag->print();
}
void set::clear()
{
	if (!bag) return;
	bag->clear();
}
bool set::has(int val) const
{
	if (!bag) return false;
	return bag->has(val);
}
searchable_bag &set::get_bag()
{
	return *bag;
}