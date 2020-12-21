﻿#include "SeatAccess.h"
#include <iomanip>

void SeatAccess::Select(Seat*& seat , int choice , int room)
{
	// 1 : all seat , choice bằng 1 thì room bằng -1
	// 2 :seat của room 

	int i = 0;
	string c_query = "";
	switch (choice)
	{
	case 1:
		c_query = "select * from seat";
		break;
	case 2:
		c_query = "select * from seat where room_id = " + to_string(room);
		break;
	}
	
	const char* q = c_query.c_str();
	if (SQL_SUCCESS != SQLExecDirectA(SQLStateHandle, (SQLCHAR*)q, SQL_NTS))
	{
		cout << "Co loi xay ra, vui long thu lai!" << endl;
		Close();
	}
	else
	{
		SQLINTEGER PtrSQLVersion;
		int seat_id;
		int seatType_id;
		int room_id;
		char seat_row[5];
		char seat_number[5];
		int seat_status;
		int i = 0;
		while (SQLFetch(SQLStateHandle) == SQL_SUCCESS)
		{
			SQLGetData(SQLStateHandle, 1, SQL_INTEGER, &seat_id, sizeof(seat_id), NULL);
			SQLGetData(SQLStateHandle, 2, SQL_INTEGER, &seatType_id, sizeof(seatType_id), NULL);
			SQLGetData(SQLStateHandle, 3, SQL_INTEGER, &room_id, sizeof(room_id), NULL);
			SQLGetData(SQLStateHandle, 4, SQL_CHAR, seat_row, sizeof(seat_row), NULL);
			SQLGetData(SQLStateHandle, 5, SQL_CHAR, seat_number, sizeof(seat_number), NULL);
			SQLGetData(SQLStateHandle, 6, SQL_INTEGER, &seat_status, sizeof(seat_status), NULL);

			Seat* temp = new Seat(seat_row, seat_number,seat_id, seatType_id, room_id, seat_status);
			*(seat + i) = *temp;
			i++;
		}
	}
	SQLCancel(SQLStateHandle);
}

void SeatAccess::Show(int room)
{
	Seat* ptr = new Seat[this->Count(3,room)];
	this->Select(ptr,2,room);
	for (int i = 0; i < this->Count(3, room); i++)
	{
		if ((i % this->Count(2, room)) == 0) cout << endl;
		cout << ptr[i].getSeatRow() << ptr[i].getSeatNumber();
		if (ptr[i].getStatus() == 0) cout << " O  ";
		else cout << " X  ";
	}
	cout << endl;
}

int SeatAccess::Count(int choice, int roomID)
{
	// 1: đếm hàng
	// 2: đếm cột
	// 3: đếm số seat của room
	int i = 0;
	string c_query = "";
	switch (choice)
	{
	case 1:
		c_query = "select distinct seat_row from seat where room_id = " + to_string(roomID);
		break;
	case 2:
		c_query = "select distinct seat_number from seat where room_id = " + to_string(roomID);
		break;
	case 3:
		c_query = "select  * from seat where room_id = " + to_string(roomID);
		break;
	case 4:
		c_query = "select  * from seat " ;
		break;
	}
	const char* q = c_query.c_str();
	if (SQL_SUCCESS != SQLExecDirectA(SQLStateHandle, (SQLCHAR*)q, SQL_NTS))
	{
		cout << "Co loi xay ra, vui long thu lai!" << endl;
		Close();
	}
	else
	{
		while (SQLFetch(SQLStateHandle) == SQL_SUCCESS)
		{
			i++;
		}
	}
	SQLCancel(SQLStateHandle);
	return i;
}
int SeatAccess::Search(int seatID, int roomID)
{
	Seat* ptr = new Seat[this->Count(3, roomID)];
	this->Select(ptr,1,-1);
	for (int i = 0; i < (this->Count(3, roomID)); i++)
	{
		if (ptr[i].getSeatID() == seatID) return i;
	}
	return -1;
}
bool SeatAccess::Insert()
{
	string c_query = "insert into seat values ('";
	Seat seat;
	seat.setSeat();
	string t_ID = to_string(this->LastID() + 1);
	c_query += t_ID + "','";
	c_query += seat.insertQuery();
	const char* q = c_query.c_str();
	cout << q;
	if (SQL_SUCCESS != SQLExecDirectA(SQLStateHandle, (SQLCHAR*)q, SQL_NTS))
	{
		cout << "Co loi xay ra, vui long thu lai!!" << endl;
		Close();
	}
	else
	{
		cout << c_query;
		cout << "Them du lieu thanh cong !" << endl;
		return true;
	}
	SQLCancel(SQLStateHandle);
	return false;
	return 0;
}
int SeatAccess::LastID() {
	Seat* ptr = new Seat[this->Count(3,-1)];
	this->Select(ptr,1,-1);
	return ptr[this->Count(1, -1) - 1].getSeatID();
}
bool SeatAccess::Update()
{
	return 0;
}

bool SeatAccess::Delete()
{
	return 0;
}

