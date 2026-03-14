//
//  FlightClass.h
//  Flight Information and Passenger Operations System
//
//  Created by Ahmet Bora Bakır on 3/6/26.
//

#ifndef FlightClass_h
#define FlightClass_h

#include "PassengerClass.h"

#include <vector>

#include <string>

class Flight
{
    string flightNo;
    string destination;
    int maxSeats = 40;
    int numPassengers;
    vector<Passenger> passengers;
    
public:
    
    Flight()
    {
        flightNo = "NULL";
        destination = "NULL";
        maxSeats = 40;
        numPassengers = 0;
    }
    
    void reserveSeat(Passenger& passenger);
    void cancelReservation();
    void cancelReservation(const Passenger& passenger);
    int numberOfPassengers(){return (int)passengers.size();}
    void printPassengers();
    bool isFlyingTo(const std::string& destination);
    
    string getFlightNo() const {return flightNo;}
    string getDestination() const {return destination;}
    int getMaxSeats() const {return maxSeats;}
    int getNumPassengers() const {return numPassengers;}
    Passenger& getPassenger(int index)
    {
        if(index < 0 || index >= passengers.size())
            throw runtime_error("Passengers' index size should be in range.\n");
        return passengers[index];
    }
    Passenger& getPassenger(bool& flag)
    {
        int input;
        while(true)
        {
            cout << "1) Index" << endl
            << "2) Name" << endl
            << "0) Exit" << endl
            << "Enter 1, 2, or 0 to identify process that you want to continue: ";
            cin >> input;
            
            if(input != 0 && input != 1 && input != 2)
                cout << "An error occured while entering number.\n";
            else break;
        }
        
        if(input == 1)
        {
            int passengersIndex;
            while(true)
            {
                cout << "Input the index number: ";
                cin >> passengersIndex;
                
                if(passengersIndex < 0 || passengersIndex >= passengers.size())
                    cout << "Out of range!\nRange is 0 - " << passengers.size() - 1 << endl;
                else break;
            }
            
            return passengers[passengersIndex];
            
            
        }
        
        else if(input == 2)
        {
            string nameInput;
            
            cin.ignore();
            cout << "Enter the name - surname of the person: ";
            getline(cin, nameInput);
            
            char gender;
            
            cout << "Enter gender: ";
            cin >> gender;
            
            gender = toupper(gender);
            bool flag_name = false;
            unsigned long passengersSize = passengers.size();
            
            vector<int> indexHolder;    //hold indexes incase of same name situations.
            
            for(int i = 0 ; i < passengersSize ; i++)
            {
                string fullName = passengers[i].getName() + " " + passengers[i].getSurname();
               // cout << fullName << "**" << nameInput << "**" << gender << "**" << passengers[i].getGender() << endl;
                
                if(fullName == nameInput && flag_name == false && (gender == passengers[i].getGender()))
                {
                    flag_name = true;
                    indexHolder.push_back(i);
                }
                else if(fullName == nameInput && flag_name == true && (gender == passengers[i].getGender()))
                {
                    
                    indexHolder.push_back(i);
                }
            }
            
            if(indexHolder.size() > 1)
            {
                int passengersIndex;
                bool continue_inputIndex;
                do
                {
                    continue_inputIndex = false;
                    try
                    {
                        cout << "Seems like there are two people that carries same name and gender, please specify passenger index\n ";
                        cout << "Indexes: ";
                        for(int i = 0 ; i < indexHolder.size() ; i++)
                            cout << indexHolder[i] << " ";
                        cout << "\nInput: ";
                        cin >> passengersIndex;
                        
                        if(passengersIndex < 0 || passengersIndex >= passengers.size())
                            throw runtime_error("Index should be in range.\n");
                        else return passengers[passengersIndex];
                    }
                    catch(const runtime_error& error)
                    {
                        cout << error.what();
                        continue_inputIndex = true;
                    }
                }while(continue_inputIndex);
            }
            else if(indexHolder.size() == 0)
                cout << "Passenger couldn't be found.\n";
            else
                return passengers[indexHolder[0]];
        }
        
        else throw runtime_error("Exiting from getting passenger.\n");
        
        flag = false;
        
        
        return passengers[0];         //kontrol ettttttttt!!!!!!!!!1
    }
    void setNumPassengers(int numPassengers)
    {
        if(numPassengers < 0)
            throw runtime_error("Number of passengers must be greater than 0.\n");
        this -> numPassengers = numPassengers;
    }
    void setPassenger(const Passenger &passenger){this -> passengers.push_back(passenger);}
    void setPassenger()
    {
        do
        {
            Passenger passenger;
            try
            {
                string name, surname;
                cout << "Please enter passenger name: ";
                cin.ignore();
                getline(cin, name);
                
                passenger.setName(name);
                
                cout << "Please enter passenger surname: ";
                cin >> surname;
                passenger.setSurname(surname);
                
                char gender;
                cout << "Please enter passenger gender(f/m): ";
                cin >> gender;
                
                passenger.setGender(gender);
                //passenger.setSeat("NULL");
                
                passengers.push_back(passenger);         // I'm aware I haven't set seats to "NULL"; it looks better this way.
                for(int i = 0; i < passengers.size(); i++)
                {
                    cout << passengers[i].getName() << " " << passengers[i].getSurname() << endl;
                }
                setNumPassengers((int)passengers.size());
                
                cout << "Current passengers size: "  << passengers.size() << endl;
                break;
            }
            
            catch(const runtime_error& error)
            {
                string exit;
                cout << error.what();
                
                cout << "To exit type \"exit\" else otherwise: ";
                cin >> exit;
                
                if(exit == "exit" || exit == "EXIT")
                    break;
            }
            
        }while(true);
    }
    void setFlightNo(string flightNo){this -> flightNo = flightNo;}
    void setDestination(string destination){this -> destination = destination;}
    void setMaxSeats(int maxSeats)
    {
        if(maxSeats % 2 == 1 || maxSeats > 80 || maxSeats < 0)
            throw runtime_error("Number of seats must be even, and upper limit is 80, and lower limit is 0.\n");
        this -> maxSeats = maxSeats;
    }
    
};

void Flight::reserveSeat(Passenger& passenger)
{
    string seatCode[4] = {"A", "B", "C", "D"};
    unsigned long passengersSize = passengers.size();
    
    cout << "X - Occupied Seat\nO - Vacant Seat\n";
    cout << "Seating Plan" << endl << "-------------Front-------------" << endl;
    
    //If memory is high enough this method can be used.
    /*
    vector<string> seats;
    for(int i = 0 ; i < maxSeats / 4 ; i++)
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            for(int k = 0 ; k < passengersSize ; k++)
            {
                if(to_string(i) + seatCode[j] == passengers[k].getSeat())
                    seats.push_back(to_string(i) + seatCode[j] + " X");
                else
                    seats.push_back(to_string(i) + seatCode[j] + " O");
            }
        }
    }
    
    for(int i = 0 ; i < maxSeats ;)
    {
        cout << "| " << seats[i] << " | " << seats[i + 1] << " | | " << seats[i + 2] << " | " << seats[i + 3] << " |" << endl;
        i *= 4;
    }
    */
    
    for(int i = 1 ; i <= maxSeats / 4 ; i++)
    {
        int l = 4;
        if(i == maxSeats / 4)
            l = maxSeats % 4;
        for(int j = 0 ; j < l ; j++)
        {
            if(j < 2)
            {
                cout << "| " << i << seatCode[j] << " ";
                bool flag_seatEmpty = false;
                for(int k = 0 ; k < passengersSize ; k++)
                {
                    if(passengers[k].getSeat() == to_string(i) + seatCode[j])
                    {
                        flag_seatEmpty = true;
                        if(i < 10)
                            cout << "X ";
                        else
                            cout << "X";
                    }
                }
                if(!flag_seatEmpty && i < 10)
                    cout << "O ";
                else if(!flag_seatEmpty && i >= 10)
                    cout << "O";
                
            }
            if(j >= 2)
            {
                if(j == 2)
                    cout << "| ";
                
                cout << "| " << i << seatCode[j] << " ";
                bool flag_seatEmpty = false;
                for(int k = 0 ; k < passengersSize ; k++)
                {
                    if(passengers[k].getSeat() == to_string(i) + seatCode[j])
                    {
                        flag_seatEmpty = true;
                        if(i < 10)
                            cout << "X ";
                        else
                            cout << "X";
                    }
                }
                if(!flag_seatEmpty && i < 10)
                    cout << "O ";
                else if(!flag_seatEmpty && i >= 10)
                    cout << "O";
                if(j == 3)
                    cout << "|\n";
            }
        }
        cout << endl;
    }
    
    
    cout << "\tPassenger Info" << endl
    << "Name: " << passenger.getName() << endl
    << "Surname: " << passenger.getSurname() << endl
    << "Gender: " << passenger.getGender() << endl;
    
    string seat_;
    
    bool seatFlag;
    do
    {
        seatFlag = true;
        try
        {
            cout << "Please enter seat information: ";
            cin >> seat_;
            
            for(int i = 0 ; i  < passengersSize ; i++)
            {
                if(passengers[i].getSeat() == seat_)
                    throw runtime_error("Same seat cannot be occupied.\n");
            }
            
            passenger.setSeat(seat_);
        }
        catch (const runtime_error& error)
        {
            cout << error.what();
            seatFlag = false;
        }
     }while(!seatFlag);
    
    
    
    
}

void Flight::cancelReservation(const Passenger& passenger)
{
    unsigned long passengersSize = passengers.size();
    
    for(int i = 0 ; i < passengersSize ; i++)
    {
        if(passengers[i].getSeat() == passenger.getSeat())
        {
            passengers[i].setSeat("NULL");
        }
    }
}

void Flight::cancelReservation()
{
    int input;
    try
    {
        while(true)
        {
            cout << "1) Index" << endl
            << "2) Name" << endl
            << "0) Exit" << endl
            << "Enter 1, 2, or 0 to identify process that you want to continue: ";
            cin >> input;
            
            if(input != 0 && input != 1 && input != 2)
                cout << "An error occured while entering number.\n";
            else break;
        }
        
        if(input == 1)
        {
            int passengersIndex;
            while(true)
            {
                cout << "Input the index number: ";
                cin >> passengersIndex;
                
                if(passengersIndex < 0 || passengersIndex >= passengers.size())
                    cout << "Out of range!\nRange is 0 - " << passengers.size() << endl;
                else break;
            }
            
            passengers[passengersIndex].setSeat("NULL");
            
        }
        
        else if(input == 2)
        {
            string nameInput;
            
            cin.ignore();
            cout << "Enter the name - surname of person that you want to cancel reservation: ";
            getline(cin, nameInput);
            
            char gender;
            
            cout << "Enter gender: ";
            cin >> gender;
            
            
            bool flag_name = false;
            unsigned long passengersSize = passengers.size();
            
            vector<int> indexHolder;    //hold indexes incase of same name situations.
            
            for(int i = 0 ; i < passengersSize ; i++)
            {
                if(passengers[i].getName() == nameInput && flag_name == false && (gender == 'F' || gender == 'f' || gender == 'M' || gender == 'm'))
                {
                    flag_name = true;
                    indexHolder.push_back(i);
                }
                else if(passengers[i].getName() == nameInput && flag_name == true && (gender == 'F' || gender == 'f' || gender == 'M' || gender == 'm'))
                {
                    
                    indexHolder.push_back(i);
                }
            }
            
            if(indexHolder.size() > 1)
            {
                string passengerSeat;
                bool continue_inputSeat = false;
                do
                {
                    cout << "Seems like there are two people that carries same name and gender, please specify seat number that you want to cancel: ";
                    cin >> passengerSeat;
                    
                    unsigned long passengerSeatSize = passengerSeat.size();
                    if(passengerSeat[passengerSeatSize - 1] != 'A' || passengerSeat[passengerSeatSize - 1] != 'B' || passengerSeat[passengerSeatSize - 1] != 'C' || passengerSeat[passengerSeatSize - 1] != 'D' || passengerSeat != "NULL")
                        throw runtime_error("You should be enter letter code as 'A', 'B', 'C', or 'D'.\n");
                    string temp;
                    for(int i = 0 ; i < passengerSeatSize ; i++)
                        temp[i] = passengerSeat[i];
                    
                    size_t positionStoi;        //to understand whether Stoi read the entire text or only a specific section of it
                    int passengerSeatNumber = std::stoi(temp, &positionStoi);
                    if(temp.size() != positionStoi && passengerSeat != "11A")
                    {
                        cout << "The format of seat code must be number and one letter.\n";
                        continue_inputSeat = true;
                    }
                    if(passengerSeatNumber <= 0 && passengerSeat != "NULL")
                    {
                        throw runtime_error("Passenger seat number must be greater than 0.\n");
                        continue_inputSeat = true;
                    }
                    else continue_inputSeat = false;
                    
                }while(continue_inputSeat);
                
                unsigned long size_indexHolder = indexHolder.size();
                for(int i = 0 ; i < size_indexHolder ; i++)
                {
                    if(passengers[indexHolder[i]].getSeat() == passengerSeat)
                        passengers[i].setSeat("NULL");
                }
            }
            if(flag_name == false)
                cout << "Passenger couldn't be found." << endl;
        }
        else
            cout << "Exiting from the function." << endl;
    }
    catch(const runtime_error& error)
    {
        cout << error.what();
    }
}

void Flight::printPassengers()
{
    cout <<"Seat|Passenger Name |Gender" << endl
    << "----|---------------|-----" << endl;
    
    unsigned long sizePassengers = passengers.size();
    for(int i = 0 ; i < sizePassengers ; i++)
    {
        string fullName = passengers[i].getName() + " " + passengers[i].getSurname();
        string arranged_passengerName;
        if(passengers[i].getSeat() != "NULL")
            cout << passengers[i].getSeat() << "\t|";
        else
            cout << passengers[i].getSeat() << " |";
            
        if(fullName.size() > 15)
        {
            arranged_passengerName = fullName.substr(0, 14) + ".";
            cout << arranged_passengerName << "|"
                 << passengers[i].getGender() << endl;
        }
        else if(fullName.size() < 12 )
        {
            arranged_passengerName = fullName;
            cout << arranged_passengerName << "\t\t|"
            << passengers[i].getGender() << endl;
        }
        else
        {
            arranged_passengerName = fullName;
            cout << arranged_passengerName << "\t|"
            << passengers[i].getGender() << endl;
        }
    }
}

#endif /* FlightClass_h */
