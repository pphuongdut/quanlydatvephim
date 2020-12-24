#pragma once
#include "Booking.h"
#include "DatabaseAccess.h"
#include "SeatAccess.h"
class BookingAccess : public DatabaseAccess
{
public:
    void Select(Booking *&);
    int Count();
    bool Insert(Booking &);
    int Search(int);
    bool Update();
    bool Delete();
    void Show();
    int LastID();
};

