#include "DynamicObject.hpp"


DynamicObject::DynamicObject(std::any&& other) noexcept:
    data_(std::move(other))
{}

DynamicObject& DynamicObject::operator=(std::any&& other) & noexcept
{
    data_ = std::move(other);

    return *this;
}
