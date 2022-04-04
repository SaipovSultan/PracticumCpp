#ifndef YANDEXPRACTICUMCPP_BUSMANAGER_H
#define YANDEXPRACTICUMCPP_BUSMANAGER_H

#endif //YANDEXPRACTICUMCPP_BUSMANAGER_H


#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses,
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator>>(istream& is, Query& q) {
    std::string operation_code;
    is >> operation_code;
    if (operation_code == "NEW_BUS"s) {
        q.type = QueryType::NewBus;
        int stop_count;
        is >> q.bus >> stop_count;
        vector<string>& stops = q.stops;
        stops.resize(stop_count);
        for (string& stop : stops) {
            cin >> stop;
        }
    } else if (operation_code == "BUSES_FOR_STOP"s) {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    } else if (operation_code == "STOPS_FOR_BUS"s) {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    } else if (operation_code == "ALL_BUSES"s) {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    std::string stop;
    std::vector<std::string> buses;
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
    if(r.buses.empty()){
        os << "No stop"s << endl;
    }else{
        for (const string& bus : r.buses) {
            os << bus << " "s;
        }
        os << endl;
    }
    return os;
}

struct StopsForBusResponse {
    std::string bus;
    std::vector<std::string> stops;
    std::map<std::string, std::vector<std::string>> stops_to_buses;
};

ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
    if (r.stops.empty()) {
        os << "No bus"s << endl;
    } else {
        for (const string& stop : r.stops) {
            os << "Stop "s << stop << ": "s;
            if (r.stops_to_buses.at(stop).size() == 1) {
                os << "no interchange"s;
            } else {
                for (const string& other_bus : r.stops_to_buses.at(stop)) {
                    if (r.bus != other_bus) {
                        os << other_bus << " "s;
                    }
                }
            }
            os << endl;
        }
    }
    return os;
}

struct AllBusesResponse {
    std::map<std::string, std::vector<std::string>> buses_to_stops;
};

ostream& operator<<(ostream& os, const AllBusesResponse& r) {
    if (r.buses_to_stops.empty()) {
        os << "No buses"s << endl;
    } else {
        for (const auto& bus_item : r.buses_to_stops) {
            os << "Bus "s << bus_item.first << ": "s;
            for (const string& stop : bus_item.second) {
                os << stop << " "s;
            }
            os << endl;
        }
    }
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus] = stops;
        for(const std::string& stop : buses_to_stops[bus]){
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        if(stops_to_buses.count(stop) == 0){
            return {stop, std::vector<std::string>{}};
        }else{
            return {stop, stops_to_buses.at(stop)};
        }
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        if(buses_to_stops.count(bus) == 0){
            return {bus, std::vector<std::string>{}, stops_to_buses};
        }else{
            return {bus, buses_to_stops.at(bus), stops_to_buses};
        }
    }

    AllBusesResponse GetAllBuses() const {
        return {buses_to_stops};
    }
private:
    std::map<std::string, std::vector<std::string>> buses_to_stops, stops_to_buses;
};
