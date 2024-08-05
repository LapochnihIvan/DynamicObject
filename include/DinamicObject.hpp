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
    /*
     * @brief DinamicObject's default constructor
    */
    constexpr DinamicObject() noexcept = default;

    /*
     * @brief DinamicObject's constructor with value
     * @param[in] other Value to be stored. If other is rvalue it will move
     * @warnung May throws any exception thrown by the constructor of the
     * contained type and std::bad_alloc
    */
    template<typename OtherT>
    DinamicObject(OtherT&& other) requires IsNotSelfT<OtherT>:
        data_(std::forward<OtherT>(other))
    {}

    /*
     * @brief DinamicObject's constructor with in-place value creation
     * @param[in] type Type of contained value
     * @param[in] args Arguments of contained value's construtor
     * If arguments are rvalue its will move
     * @warnung May throws any exception thrown by the constructor of the
     * contained type and std::bad_alloc
    */
    template<typename ValT, typename... Args >
    explicit DinamicObject(std::in_place_type_t<ValT> type,
                           Args&&... args):
        data_(type, std::forward<Args>(args)...)
    {}

    /*
     * @brief Constructor with in-place value creation with
     * std::initializer_list
     * @param[in] type Type of contained value
     * @param[in] initList first argument of contained value's construtor as
     * std::initializer_list
     * @param[in] args Other arguments of contained value's construtor
     * If arguments are rvalue its will move
     * @warnung May throws any exception thrown by the constructor of the
     * contained type and std::bad_alloc
    */
    template<typename ValT, typename InitListValT, typename... Args >
    explicit DinamicObject(std::in_place_type_t<ValT> type,
                           std::initializer_list<InitListValT> initList,
                           Args&&... args):
        data_(type, initList, std::forward<Args>(args)...)
    {}

    /*
     * @brief Assignment operator from any type except DinamicObject
     * @param[in] other Value to be stored. If other is rvalue it will move
     * @warnung May throws any exception thrown by the assignment operator of
     * the contained type and std::bad_alloc
    */
    template<typename OtherT>
    DinamicObject& operator=(OtherT&& other) & requires IsNotSelfT<OtherT>
    {
        data_ = std::forward<OtherT>(other);

        return *this;
    }

    template<typename ValT, typename... Args>
    std::decay_t<ValT>& emplace(Args&&... args) &
    {
        return data_.emplace<ValT>(std::forward<Args>(args)...);
    }

    template<typename ValT, typename InitListValT, typename... Args>
    std::decay_t<ValT>& emplace(std::initializer_list<InitListValT> initList,
                                Args&&... args) &
    {
        return data_.emplace<ValT>(initList, std::forward<Args>(args)...);
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
