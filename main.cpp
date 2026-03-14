//
//  main.cpp
//  Flight Information and Passenger Operations System
//
//  Created by Ahmet Bora Bakır on 3/6/26.
//


#include "FlightManagerClass.h"


void flightNumberValidator(bool& flag, string& flightCode);

int main()
{
    FlightManager flightManager;
    cout << "==========================================\n" << "\tFLIGHT MANAGEMENT SYSTEM\n" << "==========================================\n";
    
    int choice;
    do
    {
        cout << "1. Add a Flight\n"
        << "2. Remove a Flight\n"
        << "3. List All Flights\n"
        << "4. Select a Flight and Manage Passengers\n"
        << "5. Exit\n"
        << "------------------------------------------\n"
        << "Choice: ";
        cin >> choice;
        
        if(choice == 1)
        {
            Flight flight;
            
            string flightCode;
            
            try
            {
                
                bool flag;
                
                flightManager.flightNumberValidator(flag, flightCode, choice);
                
                if(flag)
                {
                    flight.setFlightNo(flightCode);
                    
                    string destination;
                    cout << "Enter Destination: ";
                    cin.ignore();
                    getline(cin, destination);
                    
                    flight.setDestination(destination);
                    
                    int seatNo;
                    do
                    {
                        try
                        {
                            cout << "Enter Max Seats (0-80, must be even): ";
                            cin >> seatNo;
                            
                            flight.setMaxSeats(seatNo);
                            break;
                        }
                        catch(const runtime_error& error)
                        {
                            cout << error.what();
                        }
                    }while(true);
                    
                    flightManager.addFlight(flight);
                    cout << "[SUCCESS] Flight " << flight.getFlightNo() << " to " << flight.getDestination() << " added." << endl;
                }
                
            }
            
            catch(const runtime_error& error)
            {
                cout << error.what();
            }
            
        }
        
        
        else if(choice == 2)
        {
            string flightCode;
            
            bool flag;
            flightManager.flightNumberValidator(flag, flightCode, choice);
            
            if(flag == true)
                flightManager.removeFlight(flightCode);
        }
        
        else if(choice == 3)
            flightManager.listAllFlights();
        
        else if(choice == 4)
        {
            bool flag;
            string flightCode;
            flightManager.flightNumberValidator(flag, flightCode, choice);
            
            
            int choice_managePassengers;
            do {
                cout << "MANAGING FLIGHT: " << flightManager.getFlightByNumber(flightCode)->getFlightNo()
                << " (Destination: " << flightManager.getFlightByNumber(flightCode)->getDestination() << ")\n";
                cout << "------------------------------------------" << endl
                << "1. Add passenger\n"
                << "2. Reserve a Seat\n"
                << "3. Cancel a Reservation\n"
                << "4. View Passenger List\n"
                << "5. Back to Flight Management Menu\n"
                << "------------------------------------------\n"
                << "Choice: ";
                cin >> choice_managePassengers;
                
                if(choice_managePassengers == 1)
                {
                    flightManager.getFlightByNumber(flightCode)->setPassenger();
                }
                if(choice_managePassengers == 2)
                {
                    try
                    {
                        bool flag = true;           //if passinger couldn't be found turns true.
                        //Passenger passenger = flightManager.getFlightByNumber(flightCode)->getPassenger(flag);
                        if(flightManager.getFlightByNumber(flightCode)->getNumPassengers() == 0)
                            throw runtime_error("You have to add at least one passenger to continue this process.\n");
                        if(flag)
                            flightManager.getFlightByNumber(flightCode)->reserveSeat(flightManager.getFlightByNumber(flightCode)->getPassenger(flag));
                        else
                            cout << "The passenger is not existed.\n";
                    }
                    catch(const runtime_error& error)
                    {
                        cout << error.what();
                    }
                    
                    
                }
                
                else if(choice_managePassengers == 3)
                {
                    try
                    {
                        if(flightManager.getFlightByNumber(flightCode)->getNumPassengers() == 0)
                            throw runtime_error("You have to add at least one passenger to continue this process.\n");
                        Passenger passenger = flightManager.getFlightByNumber(flightCode)->getPassenger(flag);
                        if(flag)
                            flightManager.getFlightByNumber(flightCode)->cancelReservation(passenger);
                        else
                            cout << "The passenger is not existed.\n";
                    }
                    catch(const runtime_error& error)
                    {
                        cout << error.what();
                    }
                }
                
                else if(choice_managePassengers == 4)
                {
                    flightManager.getFlightByNumber(flightCode)->printPassengers();
                }
                
                else if(choice_managePassengers == 5)
                    break;
            } while (choice_managePassengers != 1 && choice_managePassengers != 2 && choice_managePassengers != 3 && choice_managePassengers != 4);
        }
        
    }while(choice != 5);
}


