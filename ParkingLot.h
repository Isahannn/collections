#ifndef PARKING_LOT_H
#define PARKING_LOT_H

#include <unordered_map>

class ParkingLot {
public:
    ParkingLot(int capacity);
    bool arrive(int carId);
    bool depart(int carId);

private:
    int capacity;
    std::unordered_map<int, bool> parkedCars;

    // Друзья для доступа к приватным методам в тестах
    friend class ParkingLotTest;
};

#endif // PARKING_LOT_H