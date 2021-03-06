#include "stdafx.h"
#include"kra.h"
#include <iostream>
#include <string>
#include<sstream>


#define MaxSize 4
using namespace std;


void clr() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear input buffer
}

int main() {

	cout << "******************* KRA VEHICLE REGISTRATION *******************" << endl;
	int opt;

	Mcycle *mcy = new Mcycle;
	clr();
	Ovehicle *ove = new Ovehicle;
	clr();
	Ctruck *ctr = new Ctruck;
	clr();

sta:
	cout << "\nSelect operation to perform" << endl
		<< "***************************" << endl
		<< " [1] Register vehicle" << endl
		<< " [2] Show registered vehicles" << endl
		<< " [0] Exit" << endl
		<< "***************************" << endl << ":";
	cin >> opt;

	switch (opt) {
	case 1:
		char opt1;
		cout << "[C]hange ownership or [N]ew vehicle: ";
		cin >> opt1;
		(opt1 == 'C' || opt1 == 'c') ?
			vehOpr(mcy, ove, ctr, 1) : //change ownership
			vehOpr(mcy, ove, ctr, 2); //new vehicle
		goto sta;
	case 2:
		vehOpr(mcy, ove, ctr, 3); //list vehicles
		goto sta;
	case 0:
		cout << "*****************************************************" << endl;
		break;
	default:
		cout << "[!] Option not on list";
		clr();
		goto sta;
	}

	return 0;
}

bool vehOpr(Mcycle*& mc, Ovehicle*& ov, Ctruck*& ct, int opr) {
	switch (opr) {
	case 1:
	{
		int prevID, prevTel;
		char vehOpt;
		string vehReg;

		cout << "Specify vehicle:" << endl
			<< "[M]otorcycle, [O]rdinary vehicle, [C]ommercial truck";
		cin >> vehOpt;
		cout << "Input vehicle registration number: \n";
		cin >> vehReg;
		cout << "Input previous owner's ID number: \n";
		cin >> prevID;
		cout << "Input previous owner's telephone number: \n";
		cin >> prevTel;

		switch (vehOpt) {
		case 'M':
		case 'm':
			for (int x = 0; x<mc->numVeh; x++) {
				if (mc->Q->numberP.find(vehReg) != string::npos && mc->Q->tele == prevTel && mc->Q->id == prevID) {
					cout << "Vehicle found \n";
					cout << "Input new owner's name: \n";
					cin >> mc->Q->owner;
					cout << "Input new owner's ID number: \n";
					cin >> mc->Q->id;
					cout << "Input new owner's telephone number: \n";
					cin >> mc->Q->tele;
					break;
				}
				else
					mc->Q = mc->Q->next;

				if (mc->Q == NULL) {
					cout << "Vehicle not found" << endl;
					return false;
				}
			}
			break;
		case 'O':
		case 'o':
			for (int x = 0; x<ov->numVeh; x++) {
				if (ov->Q->numberP.find(vehReg) != string::npos && ov->Q->tele == prevTel && ov->Q->id == prevID) {
					cout << "Vehicle found \n";
					cout << "Input new owner's name: \n";
					cin >> ov->Q->owner;
					cout << "Input new owner's ID number: \n";
					cin >> ov->Q->id;
					cout << "Input new owner's telephone number: \n";
					cin >> ov->Q->tele;
					break;
				}
				else
					ov->Q = ov->Q->next;

				if (ov->Q == NULL) {
					cout << "Vehicle not found" << endl;
					return false;
				}
			}
			break;
		case 'C':
		case 'c':
			for (int x = 0; x<ct->numVeh; x++) {
				if (ct->Q->numberP.find(vehReg) != string::npos && ct->Q->tele == prevTel && ct->Q->id == prevID) {
					cout << "Vehicle found \n";
					cout << "Input new owner's name: \n";
					cin >> ct->Q->owner;
					cout << "Input new owner's ID number: \n";
					cin >> ct->Q->id;
					cout << "Input new owner's telephone number: \n";
					cin >> ct->Q->tele;
					break;
				}
				else
					ct->Q = ct->Q->next;

				if (ct->Q == NULL) {
					cout << "Vehicle not found" << endl;
					return false;
				}
			}
			break;
		default:
			break;
		}
	}
	break;
	case 2:
	{
		char vehOpt;
		int _id, _tele;
		string _owner, _numberP;

		cout << "Specify vehicle:" << endl
			<< "[M]otorcycle, [O]rdinary vehicle, [C]ommercial truck: ";
		cin >> vehOpt;
		cout << "Input owner's name: \n";
		cin >> _owner;
		cout << "Input vehicle registration plate: \n";
		cin >> _numberP;
		cout << "Input owner's ID number: \n";
		cin >> _id;
		cout << "Input owner's telephone number: \n";
		cin >> _tele;

		switch (vehOpt) {
		case 'M':
		case 'm':
		{
			if (mc->numVeh > 0) {
				if (mc->Q->numberP.find(_numberP) != string::npos) {
					cout << "Motorcycle already registered";
					return false;
				}
				mc->Q = mc->Q->next;
			}

			int _tax = 50000;

			mc->Q = new Mcycle::Node();
			mc->Q->owner = _owner;
			mc->Q->numberP = _numberP;
			mc->Q->tele = _tele;
			mc->Q->id = _id;
			mc->Q->tax = _tax;
			(mc->numVeh == 0) ?
				mc->H = mc->Q :
				mc->P->next = mc->Q;

			mc->numVeh++;
			mc->P = mc->Q;
		}
		break;
		case 'O':
		case 'o':
		{
			if (ov->numVeh > 0) {
				if (ov->Q->numberP.find(_numberP) != string::npos) {
					cout << "Vehicle already registered";
					return false;
				}
				ov->Q = ov->Q->next;
			}

			char _vUse;
			int _engCap, _tax;

			cout << "Vehicle use: [P]rivate, [B]usiness, P[S]V: \n";
			cin >> _vUse;
			cout << "Vehicle engine capacity: \n";
			cin >> _engCap;
			_tax = long(_engCap) * 16 * 10;

			ov->Q = new Ovehicle::Node();
			ov->Q->owner = _owner;
			ov->Q->numberP = _numberP;
			ov->Q->tele = _tele;
			ov->Q->id = _id;
			ov->Q->vUse = _vUse;
			ov->Q->engCap = _engCap;
			ov->Q->tax = _tax;
			(ov->numVeh == 0) ?
				ov->H = ov->Q :
				ov->P->next = ov->Q;

			ov->numVeh++;
			ov->P = ov->Q;
		}
		break;
		case 'C':
		case 'c':
		{
			if (ct->numVeh > 0) {
				if (ct->Q->numberP.find(_numberP) != string::npos) {
					cout << "Vehicle already registered";
					return false;
				}
				ct->Q = ct->Q->next;
			}

			int _weight, _tax;
			string _trNumberP;

			cout << "Trailer registration number: \n";
			cin >> _trNumberP;
			cout << "Vehicle weight: \n";
			cin >> _weight;
			_tax = long(_weight) * 16 * 20;

			ct->Q = new Ctruck::Node();
			ct->Q->owner = _owner;
			ct->Q->numberP = _numberP;
			ct->Q->trNumberP = _trNumberP;
			ct->Q->tele = _tele;
			ct->Q->id = _id;
			ct->Q->weight = _weight;
			ct->Q->tax = _tax;
			(ct->numVeh == 0) ?
				ct->H = ct->Q :
				ct->P->next = ct->Q;

			ct->numVeh++;
			ct->P = ct->Q;
		}
		break;
		default:
			break;
		}
	}
	break;
	case 3:
		cout << "\n***************************************Listing**************************************" << endl
			<< "    Vehicle Registration | \t Owner | \t Owner ID | \t Owner Tel | \t Tax" << endl
			<< "************************************************************************************" << endl << endl;
		if (mc->numVeh > 0) {
			mc->Q = mc->H;

			for (int x = 0; x<mc->numVeh; x++) {
				cout << "[" << x + 1 << "]\t" << mc->Q->numberP << "\t\t" << mc->Q->owner << "\t" << mc->Q->id << "\t" << mc->Q->tele << "\t" << mc->Q->tax << endl;
				mc->Q = mc->Q->next;
			}
		}
		if (ov->numVeh > 0) {
			ov->Q = ov->H;

			for (int x = 0; x<ov->numVeh; x++) {
				cout << "[" << x + 1 << "]\t" << ov->Q->numberP << "\t\t" << ov->Q->owner << "\t" << ov->Q->id << "\t" << ov->Q->tele << "\t" << ov->Q->tax << endl;
				ov->Q = ov->Q->next;
			}
		}
		if (ct->numVeh > 0) {
			ct->Q = ct->H;

			for (int x = 0; x<ct->numVeh; x++) {
				cout << "[" << x + 1 << "]\t" << ct->Q->numberP << "\t\t" << ct->Q->owner << "\t" << ct->Q->id << "\t" << ct->Q->tele << "\t" << ct->Q->tax << endl;
				ct->Q = ct->Q->next;
			}
		}
		cout << "***********************************End of listing***********************************\n" << endl;
		break;
	default:
		break;
	}
	return true;
}

Mcycle::Mcycle() {
	string _owner, _numberP;
	int _tax, _tele, _id, x;

error00:
	cout << "Specify number of motorcycles to register: ";
	cin >> x;
	if (cin.fail()) { //input validation
		clr();
		goto error00;
	}

	for (int y = 0; y<x; y++) {
		cout << "Owner's name: \n";
		cin >> _owner;
		cout << "Vehicle registration number: \n";
		cin >> _numberP;
		cout << "Owner's telephone number: \n";
		cin >> _tele;
		cout << "Owner's ID number: \n";
		cin >> _id;
		_tax = 50000;

		Mcycle::Q = new Mcycle::Node();
		Mcycle::Q->owner = _owner;
		Mcycle::Q->numberP = _numberP;
		Mcycle::Q->tele = _tele;
		Mcycle::Q->id = _id;
		Mcycle::Q->tax = _tax;
		(Mcycle::numVeh == 0) ?
			Mcycle::H = Mcycle::Q :
			Mcycle::P->next = Mcycle::Q;

		Mcycle::numVeh++;
		Mcycle::P = Mcycle::Q;
	}
}

Ovehicle::Ovehicle() {
	string _owner, _numberP, _vUse; //owner, number plate, vehicle use( p=private, b=business, s=PSV)
	int _engCap, _tax, _tele, _id, x;

error00:
	cout << "Specify number of vehicles to register: ";
	cin >> x;
	if (cin.fail()) { //input validation
		clr();
		goto error00;
	}

	for (int y = 0; y<x; y++) {
		cout << "Owner's name: \n";
		cin >> _owner;
		cout << "Vehicle registration number: \n";
		cin >> _numberP;
		cout << "Owner's telephone number: \n";
		cin >> _tele;
		cout << "Owner's ID number: \n";
		cin >> _id;
		cout << "Vehicle use: [P]rivate, [B]usiness, P[S]V: \n";
		cin >> _vUse;
		cout << "Vehicle engine capacity: \n";
		cin >> _engCap;
		_tax = long(_engCap) * 16 * 10;

		Ovehicle::Q = new Ovehicle::Node();
		Ovehicle::Q->owner = _owner;
		Ovehicle::Q->numberP = _numberP;
		Ovehicle::Q->tele = _tele;
		Ovehicle::Q->id = _id;
		Ovehicle::Q->vUse = _vUse;
		Ovehicle::Q->engCap = _engCap;
		Ovehicle::Q->tax = _tax;
		(Ovehicle::numVeh == 0) ?
			Ovehicle::H = Ovehicle::Q :
			Ovehicle::P->next = Ovehicle::Q;

		Ovehicle::numVeh++;
		Ovehicle::P = Ovehicle::Q;
	}
}

Ctruck::Ctruck() {
	string _owner, _numberP, _trNumberP;
	int _weight, _tax, _tele, _id, x;

error00:
	cout << "Specify number of commercial trucks to register: ";
	cin >> x;
	if (cin.fail()) { //input validation
		clr();
		goto error00;
	}

	for (int y = 0; y<x; y++) {
		cout << "Owner's name: \n";
		cin >> _owner;
		cout << "Vehicle registration number: \n";
		cin >> _numberP;
		cout << "Trailer registration number: \n";
		cin >> _trNumberP;
		cout << "Owner's telephone number: \n";
		cin >> _tele;
		cout << "Owner's ID number: \n";
		cin >> _id;
		cout << "Vehicle weight: \n";
		cin >> _weight;
		_tax = long(_weight) * 16 * 20;

		Ctruck::Q = new Ctruck::Node();
		Ctruck::Q->owner = _owner;
		Ctruck::Q->numberP = _numberP;
		Ctruck::Q->trNumberP = _trNumberP;
		Ctruck::Q->tele = _tele;
		Ctruck::Q->id = _id;
		Ctruck::Q->weight = _weight;
		Ctruck::Q->tax = _tax;
		(Ctruck::numVeh == 0) ?
			Ctruck::H = Ctruck::Q :
			Ctruck::P->next = Ctruck::Q;

		Ctruck::numVeh++;
		Ctruck::P = Ctruck::Q;
	}
}



