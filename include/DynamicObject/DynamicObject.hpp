/**
 * @file
 * @brief File with declaration of DynamicObject
*/

#ifndef DynamicObject_DynamicObject_HPP
#define DynamicObject_DynamicObject_HPP


#include <any>


/**
 * @brief Class witch implements dynamic typization
*/
class DynamicObject
{
private:
    template<typename T>
    static constexpr bool IsNotDynamicObject =
        !std::is_base_of_v<std::remove_cvref_t<T>, DynamicObject>;

public:
    /**
     * @brief DynamicObject's default constructor
    */
    constexpr DynamicObject() noexcept = default;

    /**
     * @brief Constructor from rvalue reference to std::any
     * @param[in] other Value to be stored
     * @result None
    */
    DynamicObject(std::any&& other) noexcept;

    /**
     * @brief Constructor from any type value except DynamicObject, it's
     * inheritors and rvalue reference to std::any
     * @param[in] other Value to be stored. If other is rvalue it will move
     * @result None
     * @throw std::bad_alloc Throws if memory in free store can't be allocated
     * @throw std::exception Throws any exception thrown by the constructor of
     * the contained type
    */
    template<typename OtherT>
    DynamicObject(OtherT&& other) requires IsNotDynamicObject<OtherT>:
        data_(std::forward<OtherT>(other))
    {}

    /**
     * @brief Constructor with in-place value creation
     * @param[in] type Type of contained value
     * @param[in] args Arguments of contained value's constructor. If args are
     * rvalue its will move
     * @result None
     * @throw std::bad_alloc Throws if memory in free store can't be allocated
     * @throw std::exception Throws any exception thrown by the constructor of
     * the contained type
    */
    template<typename ValT, typename... Args>
    explicit DynamicObject(std::in_place_type_t<ValT> type,
                           Args&&... args):
        data_(type, std::forward<Args>(args)...)
    {}

    /**
     * @brief Constructor with in-place value creation with
     * std::initializer_list
     * @param[in] type Type of contained value
     * @param[in] initList First argument of contained value's constructor as
     * std::initializer_list
     * @param[in] args Other arguments of contained value's constructor
     * If arguments are rvalue its will move
     * @result None
     * @throw std::bad_alloc Throws if memory in free store can't be allocated
     * @throw std::exception Throws any exception thrown by the constructor of
     * the contained type
    */
    template<typename ValT, typename InitListValT, typename... Args>
    explicit DynamicObject(std::in_place_type_t<ValT> type,
                           std::initializer_list<InitListValT> initList,
                           Args&&... args):
        data_(type, initList, std::forward<Args>(args)...)
    {}

    /**
     * @brief Assignment operator from rvalue reference to std::any
     * @param[in] other Value to be stored
     * @result Reference to this
    */
    DynamicObject& operator=(std::any&& other) & noexcept;

    /**
     * @brief Assignment operator from any type except DynamicObject, it's
     * inheritors and rvalue reference to std::any
     * @param[in] other Value to be stored. If other is rvalue it will move
     * @result Reference to this
     * @throw std::bad_alloc Throws if memory in free store can't be allocated
     * @throw std::exception Throws any exception thrown by the constructor of
     * the contained type
    */
    template<typename OtherT>
    DynamicObject& operator=(OtherT&& other) &
        requires IsNotDynamicObject<OtherT>
    {
        data_ = std::forward<OtherT>(other);

        return *this;
    }

    /**
     * @brief In-place value creation function
     * @param[in] args Arguments of contained value's constructor. If args are
     * rvalue its will move
     * @result Reference to the new contained object
     * @throw std::bad_alloc Throws if memory in free store can't be allocated
     * @throw std::exception Throws any exception thrown by the constructor of
     * the contained type
    */
    template<typename ValT, typename... Args>
    std::decay_t<ValT>& emplace(Args&&... args) &
    {
        return data_.emplace<ValT>(std::forward<Args>(args)...);
    }

    /**
     * @brief In-place value creation function
     * std::initializer_list
     * @param[in] initList First argument of contained value's constructor as
     * std::initializer_list
     * @param[in] args Other Arguments of contained value's constructor
     * If arguments are rvalue its will move
     * @result Reference to the new contained object
     * @throw std::bad_alloc Throws if memory in free store can't be allocated
     * @throw std::exception Throws any exception thrown by the constructor of
     * the contained type
    */
    template<typename ValT, typename InitListValT, typename... Args>
    std::decay_t<ValT>& emplace(std::initializer_list<InitListValT> initList,
                                Args&&... args) &
    {
        return data_.emplace<ValT>(initList, std::forward<Args>(args)...);
    }

    /**
     * @brief Cast rvalue DynamicObject to any type
     * @result Contained value moved to TargetT
     * @throw std::bad_any_cast If TargetT and type of contained value are
     * different
    */
    template<typename TargetT>
    operator TargetT() &&
    {
        return std::any_cast<TargetT>(std::move(data_));
    }

    /**
     * @brief Cast lvalue DynamicObject to reference to any type
     * @result Reference to contained value
     * @throw std::bad_any_cast If TargetT and type of contained value are
     * different
    */
    template<typename TargetT>
    operator TargetT&() &
    {
        TargetT* const res(std::any_cast<TargetT>(&data_));

        if (res == nullptr)
        {
            throw std::bad_any_cast();
        }

        return *res;
    }

    /**
     * @brief Cast const lvalue DynamicObject to const reference to any type
     * @result Const reference to contained value
     * @throw std::bad_any_cast If TargetT and type of contained value are
     * different
    */
    template<typename TargetT>
    operator const TargetT&() const &
    {
        const TargetT* const res(std::any_cast<const TargetT>(&data_));

        if (res == nullptr)
        {
            throw std::bad_any_cast();
        }

        return res;
    }

    /**
     * @brief Cast lvalue DynamicObject to any pointer type
     * @result Pointer to contained value. Return nullptr if TargetT and
     * contained value's type are different
    */
    template<typename TargetT>
    operator TargetT*() & noexcept
    {
        return std::any_cast<TargetT>(&data_);
    }

    /**
     * @brief Cast lvalue DynamicObject to any pointer on const
     * type
     * @result Pointer to const contained value. Return nullptr if TargetT and
     * contained value's type are different
    */
    template<typename TargetT>
    operator const TargetT*() const & noexcept
    {
        return std::any_cast<TargetT>(&data_);
    }

    /**
     * @brief Method witch destroys the contained value
     * @result None
    */
    void reset() noexcept;

    /**
     * @brief Method witch swaps the content of two DynamicObject
     * implementations
     * @param[in] other Object to swap
     * @result None
    */
    void swap(DynamicObject& other) noexcept;

    /**
     * @brief Wrapper over constructor
     * type
     * @param[in] type Type of contained value
     * @param[in] args Arguments of contained value's constructor. If arguments
     * are rvalue its will move
     * @result New DynamicObject implementation
     * @throw std::bad_alloc Throws if memory in free store can't be allocated
     * @throw std::exception Throws any exception thrown by the constructor of
     * the contained type
    */
    template<typename ValT, typename... Args>
    static DynamicObject make(Args&&... args)
    {
        return DynamicObject(std::in_place_type_t<ValT>(),
                             std::forward<Args>(args)...);
    }

    /**
     * @brief Wrapper over constructor
     * @param[in] type Type of contained value
     * @param[in] initList First argument of contained value's constructor as
     * std::initializer_list
     * @param[in] args Other arguments of contained value's constructor
     * If arguments are rvalue its will move
     * @result New DynamicObject implementation
     * @throw std::bad_alloc Throws if memory in free store can't be allocated
     * @throw std::exception Throws any exception thrown by the constructor of
     * the contained type
    */
    template<typename ValT, typename InitListValT, typename... Args>
    static DynamicObject make(std::initializer_list<InitListValT> initList,
                              Args&&... args)
    {
        return DynamicObject(std::in_place_type<ValT>,
                             initList,
                             std::forward<Args>(args)...);
    }

private:
    std::any data_;
};


namespace std
{
    template<>
    inline void swap(DynamicObject& left, DynamicObject& right) noexcept
    {
        left.swap(right);
    }
}


#endif //!DynamicObject_DynamicObject_HPP
