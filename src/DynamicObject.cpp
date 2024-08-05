#include "DynamicObject.hpp"


DynamicObject::DynamicObject(std::any&& other) noexcept:
    data_(std::move(other))
{}
