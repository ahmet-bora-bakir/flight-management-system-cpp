//
//  PassengerClass.h
//  Flight Information and Passenger Operations System
//
//  Created by Ahmet Bora Bakır on 3/6/26.
//

#ifndef PassengerClass_h
#define PassengerClass_h

#include <iostream>
#include <cctype>
using namespace std;

class Passenger
{
    string name;
    string surname;
    char gender;
    
    mutable string seat; //this variable is not definied in question but we have to use that variable to understand which seat is empty.
    
public:
    Passenger()
    {
        name = "NULL";
        surname = "NULL";
        gender = 'N';
        seat = "NULL";
    }
    Passenger(string &n, string &sn, char &g): name(n), surname(sn), gender(g){}
    string getName() const {return name;}
    string getSurname() const {return surname;}
    char getGender() const {return gender;}
    string getSeat() const {return seat;}
    
    void setName(string passengerName){name = passengerName;}
    void setSurname(string passengerSurname){surname = passengerSurname;}
    void setGender(char passengerGender)
    {
        if(passengerGender != 'F' && passengerGender != 'f' && passengerGender != 'M' && passengerGender != 'm')
            throw runtime_error("You should enter 'F' or 'f' for \"female\" or 'M' or 'm' for \"male\".\n");
        gender = toupper(passengerGender);
    }
    void setSeat(string passengerSeat) const
    {
        unsigned long passengerSeatSize = passengerSeat.size();
        if(passengerSeat[passengerSeatSize - 1] != 'A' && passengerSeat[passengerSeatSize - 1] != 'B' && passengerSeat[passengerSeatSize - 1] != 'C' && passengerSeat[passengerSeatSize - 1] != 'D' && passengerSeat != "NULL")
            throw runtime_error("You should be enter letter code as 'A', 'B', 'C', or 'D'.\n");
        string temp = passengerSeat;
        
        if(passengerSeat != "NULL")
        {
            size_t positionStoi;        //to understand whether Stoi read the entire text or only a specific section of it
            int passengerSeatNumber = stoi(temp, &positionStoi);
            if((temp.size() - positionStoi) != 1 && passengerSeat != "NULL")
                throw runtime_error("The format of seat code must be number and one letter.\n");
            if(passengerSeatNumber <= 0 && passengerSeat != "NULL")
                throw runtime_error("Passenger seat number must be greater than 0.\n");
            
            /*char* temp_ = new(passengerSeatSize);
            
            for(int i = 0 ; i < passengerSeatSize ; i++)
            {
                if((temp[i] < '0' || temp[i] > '9') && passengerSeatSize - 2 != i)
                {
                    throw runtime_error("The format of seat code must be number and one letter.\n");
                }
                else
                {
                    
                }
            }
             */
        }
        
       seat = passengerSeat;
    }
    
    Passenger operator=(const Passenger passenger)
    {
        if(this != &passenger)
        {
            name = passenger.name;
            surname = passenger.surname;
            gender = passenger.gender;
            seat = passenger.seat;
        }
        return *this;
    }
};
#endif /* PassengerClass_h */
