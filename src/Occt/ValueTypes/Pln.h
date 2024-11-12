// Copyright [2024] SunCAD

#ifndef OCCT_VALUETYPES_PLN_H_
#define OCCT_VALUETYPES_PLN_H_

#include <gp_Pln.hxx>

class Pln : public gp_Pln {
public:
	using gp_Pln::gp_Pln;

	static Pln XOY() { return Pln(); }
};

#endif // OCCT_VALUETYPES_PLN_H_
