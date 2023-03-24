#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <thermostat.hpp>
#include "console_temp_controller.h"

using ::testing::AtLeast;
using ::testing::InSequence;

class MockTempController : public TempControllerInterface
{
public:
    MOCK_METHOD(void, start_heating, (), (override));
    MOCK_METHOD(void, start_cooling, (), (override));
    MOCK_METHOD(void, stop, (), (override));
};

TEST(Thermostat, heating)
{
    auto controller = std::make_shared<MockTempController>();
    EXPECT_CALL(*controller, start_heating()).Times(1);

    auto thermostat = std::make_unique<Thermostat<int>>(controller, 10, 20);
    thermostat->updateTemp(5);
}

TEST(Thermostat, cooling)
{
    auto controller = std::make_shared<MockTempController>();
    EXPECT_CALL(*controller, start_cooling()).Times(1);

    auto thermostat = std::make_unique<Thermostat<int>>(controller, 10, 20);
    thermostat->updateTemp(25);
}

TEST(Thermostat, heating_stopped)
{
    auto controller = std::make_shared<MockTempController>();

    {
        InSequence seq;
        EXPECT_CALL(*controller, start_heating()).Times(1);
        EXPECT_CALL(*controller, stop()).Times(1);
    }

    auto thermostat = std::make_unique<Thermostat<int>>(controller, 10, 20);

    for (auto i = 5; i <= 10; i += 1)
    {
        thermostat->updateTemp(i);
    }
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
