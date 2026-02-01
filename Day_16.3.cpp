#include <bits/stdc++.h>
using namespace std;

class RideSharingSystem {
private:
    queue<int> riders;
    queue<int> drivers;
    unordered_set<int> waitingRiders;
    unordered_set<int> cancelledRiders;

public:
    RideSharingSystem() {}

    void addRider(int riderId) {
        riders.push(riderId);
        waitingRiders.insert(riderId);
    }

    void addDriver(int driverId) {
        drivers.push(driverId);
    }

    vector<int> matchDriverWithRider() {
        // Remove cancelled riders from front
        while (!riders.empty() && cancelledRiders.count(riders.front())) {
            waitingRiders.erase(riders.front());
            cancelledRiders.erase(riders.front());
            riders.pop();
        }

        if (riders.empty() || drivers.empty()) {
            return {-1, -1};
        }

        int driverId = drivers.front();
        int riderId = riders.front();

        drivers.pop();
        riders.pop();
        waitingRiders.erase(riderId);

        return {driverId, riderId};
    }

    void cancelRider(int riderId) {
        // Cancel only if rider is currently waiting
        if (waitingRiders.count(riderId)) {
            cancelledRiders.insert(riderId);
        }
    }
};
