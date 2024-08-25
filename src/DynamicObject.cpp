#include "DynamicObject.hpp"


DynamicObject::DynamicObject(std::any&& other) noexcept:
    data_(std::move(other))
{}

DynamicObject& DynamicObject::operator=(std::any&& other) & noexcept
{
    data_ = std::move(other);

    return *this;
}

void DynamicObject::reset() noexcept
{
    data_.reset();
}

void DynamicObject::swap(DynamicObject& other) noexcept
{
    data_.swap(other.data_);
}
