#pragma once

#define REFLECT(name) \
	friend struct TypeDescriptor;

#define CLASS(name) REFLECT(name);
#define STRUCT(name) REFLECT(name);
#define ENUM(name) REFLECT(name);

struct TypeDescriptor
{

};