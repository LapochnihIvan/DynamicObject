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

    template<typename OtherT>
    DinamicObject& operator=(OtherT&& other) & requires IsNotSelfT<OtherT>
    {
        data_ = std::forward<OtherT>(other);

        return *this;
    }

    template<typename TatgetT>
    operator TatgetT() &&
    {
        return std::any_cast<TatgetT>(std::move(data_));
    }

    template<typename TatgetT>
    operator TatgetT&() &
    {
        validateCastType<TatgetT>();

        return *std::any_cast<TatgetT>(&data_);
    }

    template<typename TatgetT>
    operator const TatgetT&() const &
    {
        validateCastType<TatgetT>();

        return *std::any_cast<const TatgetT>(&data_);
    }

    template<typename TatgetT>
    operator TatgetT*() & noexcept
    {
        return std::any_cast<TatgetT>(&data_);
    }

    template<typename TatgetT>
    operator const TatgetT*() const & noexcept
    {
        return std::any_cast<TatgetT>(&data_);
    }

private:
    std::any data_;

    template<typename CastT>
    void validateCastType()
    {
        if (data_.type() != typeid(CastT))
        {
            throw std::bad_any_cast();
        }
    }
};


#endif //!DINAMICOBJECT_DINAMICOBJECT_HPP
