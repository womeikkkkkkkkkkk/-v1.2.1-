#include "ComputerRoom.h"

ComputerRoom::ComputerRoom() {
	this->CRID = NULLID; this->MAXC = NULLCONTAINER; this->bookedcount = 0;
}

void ComputerRoom::SetId(int& id) {
	this->CRID = id;
}

void ComputerRoom::SetMax(int& max) {
	this->MAXC = max;
}

void ComputerRoom::SetBookedCount(int count) {
	this->bookedcount = count;
}

int ComputerRoom::getId()const {
	return this->CRID;
}

int ComputerRoom::GetMax()const {
	return this->MAXC;
}

int ComputerRoom::GetBookedCount() const {
	return this->bookedcount;
}

std::istream& operator>>(std::istream& is, ComputerRoom& s) {
	int id;
	int max;
	is >> id;
	is >> max;
	s.SetId(id);
	s.SetMax(max);
	return is;
}