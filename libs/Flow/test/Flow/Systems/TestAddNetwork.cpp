#include "Flow/Systems/AddNetwork.hpp"
#include "Flow/Components/Add.hpp"
#include "Flow/Components/Constant.hpp"
#include "Flow/TypeManager.hpp"

bool TestSystem_AddNetwork()
{
    using namespace Flow;
    using namespace Flow::Components;
    using namespace Flow::Systems;

    ComponentDefinition const c0_definition = {
        // Name
        "Constant<int>{0}",
        Constant<int>::Definition.InputPorts,
        Constant<int>::Definition.OutputPorts,
        Constant<int>::Definition.Annotations,
    };

    ComponentDefinition const c1_definition = {
        // Name
        "Constant<int>{1}",
        Constant<int>::Definition.InputPorts,
        Constant<int>::Definition.OutputPorts,
        Constant<int>::Definition.Annotations,
    };

    ComponentDefinition const c2_definition = {
        // Name
        "Constant<int>{2}",
        Constant<int>::Definition.InputPorts,
        Constant<int>::Definition.OutputPorts,
        Constant<int>::Definition.Annotations,
    };

    ComponentDefinition const c4_definition = {
        // Name
        "Constant<int>{4}",
        Constant<int>::Definition.InputPorts,
        Constant<int>::Definition.OutputPorts,
        Constant<int>::Definition.Annotations,
    };

    TypeManager const type_manager
    {{
        // ComponentTypes
        {
            //                        Definition                 MakeInstanceFunc
            {          Constant<int>::Definition,                         nullptr},
            {                      c0_definition,  GetMakeConstantInstanceFunc(0)}, // TODO - handle parameters
            {                      c1_definition,  GetMakeConstantInstanceFunc(1)},
            {                      c2_definition,  GetMakeConstantInstanceFunc(2)},
            {                      c4_definition,  GetMakeConstantInstanceFunc(4)},
            {               Add<int>::Definition,   MakeSystemComponent<Add<int>>},
            {   AddNetwork::Definition.Interface, MakeSystemComponent<AddNetwork>},
        },
        // ConnectionTypes
        {
            // Name    BaseNames
            {  "bool",        {}},
            {   "int",        {}},
            { "float",        {}},
        },
    }};

    Systems::AddNetwork add_network(type_manager, "add_network", {});
    add_network.Process();
    assert(add_network.GetResult() == 7);

    return true;
}
