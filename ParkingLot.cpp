#include "pch.h"
#include "ParkingLot.h"
#include <spdlog/spdlog.h>

ParkingLot::ParkingLot(int capacity) : capacity(capacity) {}

bool ParkingLot::arrive(int carId) {
    if (carId <= 0 || parkedCars.size() >= capacity) {
        spdlog::error("Car {} could not find a parking space.", carId);
        return false;
    }
    parkedCars[carId] = true;
    spdlog::info("Car {} parked.", carId);
    return true;
}

bool ParkingLot::depart(int carId) {
    if (carId <= 0 || parkedCars.find(carId) == parkedCars.end()) {
        spdlog::error("Car {} was not found in the parking lot.", carId);
        return false;
    }
    parkedCars.erase(carId);
    spdlog::info("Car {} departed from the parking lot.", carId);
    return true;
}