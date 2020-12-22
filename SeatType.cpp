#include "SeatType.h"

SeatType::SeatType()
{
	this->seat_type_id = 0;
	this->seat_price = 45000;
	strcpy_s(this->seat_type, 15, "");
}

SeatType::SeatType(char* seatType, int seatTypeID, int seatPrice)
	:seat_type_id(seatTypeID), seat_price(seat_price)
{
	strcpy_s(this->seat_type, 15, seatType);
}

SeatType::~SeatType()
{}

int SeatType::getSeatTypeID()
{
	return this->seat_type_id;
}

int SeatType::getSeatPrice()
{
	return this->seat_price;
}

char* SeatType::getSeatTypeName()
{
	return this->seat_type;
}

string SeatType::insertQuery()
{
	string t_query;
	string t_seatTypeID = to_string(this->seat_type_id);
	string t_seatTypeName(this->seat_type);
	string t_seatPrice = to_string(this->seat_price);
	t_query = t_seatTypeID + "','" + t_seatTypeName + "','" + t_seatPrice+ "')";
	return t_query;
}

void SeatType::Show()
{
	cout << left << setw(4) << this->seat_type_id;
	cout << left << setw(15) << this->seat_type;
	cout << right << setw(10) << this->seat_price;
}

void SeatType::setSeatType()
{
	cin.ignore();
	cout << "Seat type name: ";
	cin.getline(this->seat_type, 15);
	cout << "Seat price: ";
	cin >> this->seat_price;
}

void SeatType::Show()
{
	char* ST = this->seat_type;
	for (int i = strlen(ST) - 1; i >= 0; i--) {
		if (ST[i] != ' ') {
			ST[i + 1] = '\0';
			break;
		}
	}
	string temp(ST);
	cout << "\t\tSeat type: " << temp << endl;
	cout << "\t\tSeat price: " << this->seat_price << endl << endl;
}
