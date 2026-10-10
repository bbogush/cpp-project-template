#include "my_component.h"

#include <thread>

namespace project::my_component {

int MyComponent::add(int a, int b) const
{
    // Simulate some heavy computation
    std::this_thread::sleep_for(std::chrono::microseconds(1));

    return a + b;
}

} // namespace project::my_component
