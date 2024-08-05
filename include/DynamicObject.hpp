#ifndef DynamicObject_DynamicObject_HPP
#define DynamicObject_DynamicObject_HPP


#include <any>


class DynamicObject
{
private:
    template<typename T>
    static constexpr bool IsNotSelfT =
        !std::is_base_of_v<T, DynamicObject>;

public:
    /*
     * @brief DynamicObject's default constructor
    */
    constexpr DynamicObject() noexcept = default;

    /*
     * @brief Constructor from rvalue reference to std::any
     * @param[in] other Value to be stored
    */
    DynamicObject(std::any&& other) noexcept;

    /*
     * @brief Constructor from any type value
     * @param[in] other Value to be stored. If other is rvalue it will move
     * @warnung May throws any exception thrown by the constructor of the
     * contained type and std::bad_alloc
    */
    template<typename OtherT>
    DynamicObject(OtherT&& other) requires IsNotSelfT<OtherT>:
        data_(std::forward<OtherT>(other))
    {}

    /*
     * @brief Constructor with in-place value creation
     * @param[in] type Type of contained value
     * @param[in] args Arguments of contained value's construtor
     * If arguments are rvalue its will move
     * @warnung May throws any exception thrown by the constructor of the
     * contained type and std::bad_alloc
    */
    template<typename ValT, typename... Args >
    explicit DynamicObject(std::in_place_type_t<ValT> type,
                           Args&&... args):
        data_(type, std::forward<Args>(args)...)
    {}

    /*
     * @brief Constructor with in-place value creation with
     * std::initializer_list
     * @param[in] type Type of contained value
     * @param[in] initList First argument of contained value's construtor as
     * std::initializer_list
     * @param[in] args Other arguments of contained value's construtor
     * If arguments are rvalue its will move
     * @warnung May throws any exception thrown by the constructor of the
     * contained type and std::bad_alloc
    */
    template<typename ValT, typename InitListValT, typename... Args >
    explicit DynamicObject(std::in_place_type_t<ValT> type,
                           std::initializer_list<InitListValT> initList,
                           Args&&... args):
        data_(type, initList, std::forward<Args>(args)...)
    {}

    /*
     * @brief Assignment operator from any type except DynamicObject
     * @param[in] other Value to be stored. If other is rvalue it will move
     * @result Reference to this
     * @warnung May throws any exception thrown by the assignment operator of
     * the contained type and std::bad_alloc
    */
    template<typename OtherT>
    DynamicObject& operator=(OtherT&& other) & requires IsNotSelfT<OtherT>
    {
        data_ = std::forward<OtherT>(other);

        return *this;
    }

    /*
     * @brief In-place value creation function
     * @param[in] args Arguments of contained value's construtor
     * If arguments are rvalue its will move
     * @warnung May throws any exception thrown by the constructor of the
     * contained type and std::bad_alloc
    */
    template<typename ValT, typename... Args>
    std::decay_t<ValT>& emplace(Args&&... args) &
    {
        return data_.emplace<ValT>(std::forward<Args>(args)...);
    }

    /*
     * @brief In-place value creation function
     * std::initializer_list
     * @param[in] initList First argument of contained value's construtor as
     * std::initializer_list
     * @param[in] args Other Arguments of contained value's construtor
     * If arguments are rvalue its will move
     * @warnung May throws any exception thrown by the constructor of the
     * contained type and std::bad_alloc
    */
    template<typename ValT, typename InitListValT, typename... Args>
    std::decay_t<ValT>& emplace(std::initializer_list<InitListValT> initList,
                                Args&&... args) &
    {
        return data_.emplace<ValT>(initList, std::forward<Args>(args)...);
    }

    /*
     * @brief Cast rvalue DynamicObject to any type
     * @result Contained value moved to TatgetT
     * @warnung Throws std::bad_any_cast if TargetT and type of contained value
     * are different
    */
    template<typename TatgetT>
    operator TatgetT() &&
    {
        return std::any_cast<TatgetT>(std::move(data_));
    }

    /*
     * @brief Cast lvalue DynamicObject to reference to any type
     * @result Reference to contained value
     * @warnung Throws std::bad_any_cast if TargetT and type of contained value
     * are different
    */
    template<typename TatgetT>
    operator TatgetT&() &
    {
        TatgetT* const res(std::any_cast<TatgetT>(&data_));

        if (res == nullptr)
        {
            throw std::bad_any_cast();
        }

        return *res;
    }

    /*
     * @brief Cast const lvalue DynamicObject to const reference to any type
     * @result Const reference to contained value
     * @warnung Throws std::bad_any_cast if TargetT and contained value's type
     * are different
    */
    template<typename TatgetT>
    operator const TatgetT&() const &
    {
        const TatgetT* const res(std::any_cast<const TatgetT>(&data_));

        if (res == nullptr)
        {
            throw std::bad_any_cast();
        }

        return res;
    }

    /*
     * @brief Cast lvalue DynamicObject to any pointer type
     * @result Pointer to contained value. Return nullptr if TargetT and
     * contained value's type are different
    */
    template<typename TatgetT>
    operator TatgetT*() & noexcept
    {
        return std::any_cast<TatgetT>(&data_);
    }

    /*
     * @brief Cast lvalue DynamicObject to any pointer on const
     * type
     * @result Pointer to const contained value. Return nullptr if TargetT and
     * contained value's type are different
    */
    template<typename TatgetT>
    operator const TatgetT*() const & noexcept
    {
        return std::any_cast<TatgetT>(&data_);
    }

private:
    std::any data_;
};


#endif //!DynamicObject_DynamicObject_HPP
