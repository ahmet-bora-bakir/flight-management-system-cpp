//
//  FlightManagerClass.h
//  Flight Information and Passenger Operations System
//
//  Created by Ahmet Bora Bakır on 3/6/26.
//

#ifndef FlightManagerClass_h
#define FlightManagerClass_h

#include "FlightClass.h"

class FlightManager
{
    vector<Flight> flights;
    
public:
    void addFlight(const Flight& flight);
    bool removeFlight(const string& flightNumber);
    void listAllFlights();
    Flight* getFlightByNumber(const string& flightNumber);
    Flight getFlightByDestination(const string&destination);
    
    Flight getFlight(int index) const
    {
        if(index < 0 || index >= flights.size())
            throw runtime_error("Flights' index size should be in range.\n");
        return flights[index];
    }
    void flightNumberValidator(bool& flag, string& flightCode, int choice);
};
void FlightManager::addFlight(const Flight &flight)
{
    /*
    string flightCode = flight.getFlightNo();
    
    if(flightCode.size() > 7)
        throw runtime_error("This flight number format is not defined.\n");
    string temp_flightCode;
    temp_flightCode.push_back(flightCode[0]);
    temp_flightCode.push_back(flightCode[1]);             // '\0' assign etmediğim için hata alabilirim belki
    
    if(temp_flightCode != "TK" || temp_flightCode != "PG")
        throw runtime_error("This flight number format is not defined.\n");
    
    else
    {
        for(int j = 3 ; j < flightCode.size() ; j++)
        {
            if(flightCode[j] < '0' || flightCode[j] > '9')
                throw runtime_error("This flight number format is not defined.\n");
        }
    }
    */
    flights.push_back(flight);
    
    
}

bool FlightManager::removeFlight(const string& flightNumber)
{
    /*
    unsigned long flightsSize = flights.size();
    for(int i = 0 ; i < flightsSize ; i++)
    {
        if(flights[i].getFlightNo() == flightNumber)
        {
            for(int j = i ; j < flightsSize - 1 ; j++)
                flights[j] = flights[j + 1];
            return true;
        }
    }
     */
    unsigned long flightsSize = flights.size();
    for(int i = 0 ; i < flightsSize ; i++)
    {
        if(flights[i].getFlightNo() == flightNumber)
        {
            flights.erase(flights.begin() + i);
            return true;
        }
    }
    
    
    return false;
}

void FlightManager::listAllFlights()
{
    unsigned long flightsSize = flights.size();
    
    char decision;
    
    do {
        
        cout << "Do you want to see passenger list(y/n)? ";
        cin >> decision;
        if(decision == 'Y' || decision == 'y' || decision == 'N' || decision == 'n')
            break;
    } while (true);
    
    if(decision == 'Y' || decision == 'y')
    {
        for(int i = 0 ; i < flightsSize ; i++)
        {
            cout << "Passenger list: " << endl;
            flights[i].printPassengers();
            cout << "Destination: " << flights[i].getDestination() << endl;
            cout << "Flight number: " << flights[i].getFlightNo() << endl;
            cout << "Max seats: " << flights[i].getMaxSeats() << endl;
            cout << "Passenger size: " << flights[i].getNumPassengers() << endl;
        }
    }
    
    else
    {
        for(int i = 0 ; i < flightsSize ; i++)
        {
            cout << "Flight number: " << flights[i].getFlightNo() << endl;
            cout << "Destination: " << flights[i].getDestination() << endl;
            cout << "Max seats: " << flights[i].getMaxSeats() << endl;
            cout << "Passenger number: " << flights[i].getNumPassengers() << endl;
        }
    }
        
}

Flight* FlightManager::getFlightByNumber(const string& flightNumber)
{
    unsigned long flightsSize = flights.size();
    for(int i = 0 ; i < flightsSize ; i++)
    {
        if(flightNumber == flights[i].getFlightNo())
            return &flights[i];
    }
    
    throw runtime_error("Flight couldn't be found.\n");
}

Flight FlightManager::getFlightByDestination(const string&destination)
{
    unsigned long flightsSize = flights.size();
    for(int i = 0 ; i < flightsSize ; i++)
    {
        if(destination == flights[i].getDestination())
            return flights[i];
    }
    
    throw runtime_error("Flight couldn't be found.\n");
}
void FlightManager::flightNumberValidator(bool& flag, string& flightCode, int choice)
{
    int i = 0;
    do {
        try
        {
            flag = true;
            if(i < 3)
            {
                cout << "Enter Flight Number: ";
                cin >> flightCode;
            }
            else
            {
                int decision;
                do
                {
                    cout << "1)Enter Flight Number" << endl
                    << "0) Exit" << endl;
                    cin >> decision;
                }while(decision != 0 && decision != 1);
                if(decision == 0)
                {
                    flag = false;
                    break;
                }
                else
                {
                    cout << "Enter Flight Number ";
                    cin >> flightCode;
                }
            }
            if(flightCode.size() > 6 || flightCode.size() < 3)
                throw runtime_error("This flight number format is not defined.\n");
            else
            {
                string temp_flightCode;
                
                temp_flightCode.push_back(flightCode[0]);
                temp_flightCode.push_back(flightCode[1]);             // '\0' assign etmediğim için hata alabilirim belki
               // temp_flightCode.push_back('\0');
                
                if(temp_flightCode != "TK" && temp_flightCode != "PG")
                    throw runtime_error("This flight number format is not defined(airlanes code).\n");
                else
                {
                    for(int j = 2 ; j < flightCode.size() ; j++)
                    {
                        if(flightCode[j] < '0' || flightCode[j] > '9')
                            throw runtime_error("This flight number format is not defined(integer part).\n");
                    }
                   // break;
                }
            }
            if(choice == 1)
            {
                for(int j = 0 ; j < flights.size() ; j++)
                {
                    if(flights[i].getFlightNo() == flightCode)
                        throw runtime_error("Flight number must be different from existing flights.\n");
                }
            }
            
            i++;
            
        }
        catch(const runtime_error& error)
        {
            flag = false;
            cout << error.what();
        }
    } while (!flag);
}

#endif /* FlightManagerClass_h */
