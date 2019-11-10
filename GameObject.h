#pragma once

#define CLASS_IDENTIFICATION( inCode, inClass ) \
enum { kClassId = inCode }; \
virtual uint32_t getClassId() const { return kClassId; } \
static GameObject* createInstance() { return static_cast< GameObject* >( new inClass() ); } \


class GameObject
{

};