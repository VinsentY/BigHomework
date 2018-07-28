#include "Item.h"
using namespace std;



ostream & operator<<(ostream & o, Item & i) {
	o << setw(10) << i.name << "       ¼Û¸ñ " << i.price << endl;
	return o;
}

ofstream & operator<<(ofstream & out, Item & i) {
	out << i.number << " " << i.name << " " << i.price << " " << i.attribute
		<< " ";
	return out;
}

ifstream & operator >> (ifstream & in, Item & i) {
	in >> i.number >> i.name >> i.price >> i.attribute;
	return in;
}

Item::Item() {
}

Item::Item(string name, int number, int price, int attribute, string intro) {
	this->name = name;
	this->number = number;
	this->price = price;
	this->attribute = attribute;
	this->introduction = intro;
}

void Item::setItem(string name, int number, int price, int attribute, string intro) {
	this->name = name;
	this->number = number;
	this->price = price;
	this->attribute = attribute;
	this->introduction = intro;
}



//52 16

