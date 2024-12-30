#include "pch.h"
#include <gtest/gtest.h>
#include "ParkingLot.h"
#include <spdlog/spdlog.h>

void setupLogger() {
    if (!spdlog::get("console")) {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        spdlog::stdout_color_mt("console");
    }
    spdlog::set_level(spdlog::level::info);
}

class ParkingLotTest : public ::testing::Test {
protected:
    ParkingLot* parking;

    void SetUp() override {
        setupLogger();
        parking = new ParkingLot(5);
    }

    void TearDown() override {
        delete parking;
        spdlog::drop("console");
    }
};

// Основные тесты
TEST_F(ParkingLotTest, TestArriveSuccess) {
    EXPECT_TRUE(parking->arrive(1));
    EXPECT_TRUE(parking->arrive(2));
}

TEST_F(ParkingLotTest, TestDepartSuccess) {
    parking->arrive(1);
    EXPECT_TRUE(parking->depart(1));
}

TEST_F(ParkingLotTest, TestDepartFailure) {
    EXPECT_FALSE(parking->depart(1)); // Автомобиль не был заезжён
}

TEST_F(ParkingLotTest, TestArriveFull) {
    for (int i = 1; i <= 5; ++i) {
        parking->arrive(i);
    }
    EXPECT_FALSE(parking->arrive(6)); // Парковка полна
}

TEST_F(ParkingLotTest, TestDepartInvalidCarId) {
    EXPECT_FALSE(parking->depart(-1)); // Негативный идентификатор
    EXPECT_FALSE(parking->depart(0));  // Нулевой идентификатор
}

TEST_F(ParkingLotTest, TestDepartNonExistentCar) {
    EXPECT_FALSE(parking->depart(99)); // Автомобиль 99 не заезжал
}

TEST_F(ParkingLotTest, TestArriveInvalidCarId) {
    EXPECT_FALSE(parking->arrive(-1)); // Негативный идентификатор
    EXPECT_FALSE(parking->arrive(0));  // Нулевой идентификатор
}

TEST_F(ParkingLotTest, TestArriveWhenFull) {
    for (int i = 1; i <= 5; i++) {
        parking->arrive(i);
    }
    EXPECT_FALSE(parking->arrive(6)); // Парковка полна
}

// Запуск тестов
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    setupLogger();
    return RUN_ALL_TESTS();
}