#ifndef FLOW_COMPONENTS_ADD_HPP
#define FLOW_COMPONENTS_ADD_HPP

#include "Flow/Component.hpp"
#include "Flow/TypeManager.hpp"
#include "Flow/TypeName.hpp"

namespace Flow
{
namespace Components
{
    // =================================================================================================================

    template <typename T>
    class Add
        : public Component
    {
    public:
        static ComponentDefinition const Definition;

        Add(TypeManager const &type_manager,
            std::string instance_name,
            ComponentInputConnectionPtrsDict input_connection_ptrs_dict);
        Add(Add &&rhs) = default;
        Add(Add const &rhs) = delete;
        Add& operator = (Add &&rhs) = default;
        Add& operator = (Add const &rhs) = delete;
        ~Add() = default;

        virtual void Process() override;

        T const& GetResult() const;

    private:
        // members:
        T const &m_Lhs;
        T const &m_Rhs;
        T m_Result;
    };

    // =================================================================================================================
} // namespace Components
} // namespace Flow

// =====================================================================================================================

namespace Flow
{
    // =================================================================================================================

    template <>
    struct TypeName<Flow::Components::Add<bool>>
    {
        constexpr static char const * const value = "Add<bool>";
    };

    // -----------------------------------------------------------------------------------------------------------------

    template <>
    struct TypeName<Flow::Components::Add<int>>
    {
        constexpr static char const * const value = "Add<int>";
    };

    // -----------------------------------------------------------------------------------------------------------------

    template <>
    struct TypeName<Flow::Components::Add<float>>
    {
        constexpr static char const * const value = "Add<float>";
    };

    // =================================================================================================================
} // namespace Flow

// =====================================================================================================================

template <typename T>
/*static*/ Flow::ComponentDefinition const Flow::Components::Add<T>::Definition =
{
    // Name
    GetTypeName<Add<T>>(),
    // InputPorts
    {
        {
            "Lhs",
            GetTypeName<T>(),
            InputPortOptional::No,
            InputPortMultiplex::No,
        },
        {
            "Rhs",
            GetTypeName<T>(),
            InputPortOptional::No,
            InputPortMultiplex::No,
        },
    },
    // OutputPorts
    {
        {
            "Result",
            GetTypeName<T>(),
        },
    },
    // Annotations
    {
        // TODO - consider if inputs are all Process::Ignore, then this instance should be Process::Ignore too
        ComponentProcessAnnotation::Default, // Process
    },
};

// ---------------------------------------------------------------------------------------------------------------------

template <typename T>
Flow::Components::Add<T>::Add(TypeManager const &type_manager,
                              std::string instance_name,
                              ComponentInputConnectionPtrsDict input_connection_ptrs_dict)
    : Component(type_manager,
                Definition,
                ComponentInstance{std::move(instance_name),
                                  std::move(input_connection_ptrs_dict),
                                  {{"Result", &m_Result}}})
    , m_Lhs(GetInputConnectionRef<T>(GetInputPortDict(), "Lhs"))
    , m_Rhs(GetInputConnectionRef<T>(GetInputPortDict(), "Rhs"))
    , m_Result()
{
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T>
/*virtual*/ void Flow::Components::Add<T>::Process() /*override*/
{
    m_Result = m_Lhs + m_Rhs;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T>
T const& Flow::Components::Add<T>::GetResult() const
{
    return m_Result;
}

// =====================================================================================================================

#endif // FLOW_COMPONENTS_ADD_HPP
