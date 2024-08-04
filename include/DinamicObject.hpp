#ifndef DINAMICOBJECT_DINAMICOBJECT_HPP
#define DINAMICOBJECT_DINAMICOBJECT_HPP


#include <any>


class DinamicObject
{
private:
    template<typename T>
    static constexpr bool IsNotSelfT =
        !std::is_base_of_v<T, DinamicObject>;

public:
    DinamicObject() noexcept;

    template<typename OtherT>
    DinamicObject(OtherT&& other) requires IsNotSelfT<OtherT>:
        data_(std::forward<OtherT>(other))
    {}

private:
    std::any data_;
};


#endif //!DINAMICOBJECT_DINAMICOBJECT_HPP
