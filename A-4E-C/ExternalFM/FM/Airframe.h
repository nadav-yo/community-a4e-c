#ifndef AIRFRAME_H
#define AIRFRAME_H
#pragma once
#include "BaseComponent.h"
#include "AircraftState.h"
#include "Actuator.h"
#include "Input.h"
#include <stdio.h>
#include "Engine2.h"
#include "Vec3.h"

//Macro police don't hurt me
#define DMG_ELEM(v) m_integrityElement[(int)v]

namespace Skyhawk
{//begin namespace



#define c_aileronUp 0.35
#define c_aileronDown -0.35

#define c_elevatorUp 0.3
#define c_elevatorDown -0.35

#define c_rudderRight 0.35
#define c_rudderLeft -0.35

#define c_flapUp 0.0
#define c_flapDown 0.52

#define c_speedBrakeIn 0.0
#define c_speedBrakeOut 1.0

#define c_maxfuel 2137.8

#define c_catAngle 0.0
#define	c_catConstrainingForce 4500.0



class Airframe : public BaseComponent
{
public:

	enum CatapultState
	{
		ON_CAT_READY,
		ON_CAT_NOT_READY,
		ON_CAT_WAITING,
		ON_CAT_LAUNCHING,
		OFF_CAT
	};

	enum class Damage
	{
		NOSE_CENTER = 0,
		FRONT = 0,
		Line_NOSE = 0,
		NOSE_LEFT_SIDE = 1,
		NOSE_RIGHT_SIDE = 2,
		COCKPIT = 3,
		CABINA = 3,
		CABIN_LEFT_SIDE = 4,
		CABIN_RIGHT_SIDE = 5,
		CABIN_BOTTOM = 6,
		GUN = 7,
		FRONT_GEAR_BOX = 8,
		GEAR_REAR = 8,
		GEAR_C = 8,
		GEAR_F = 8,
		STOIKA_F = 8,
		FUSELAGE_LEFT_SIDE = 9,
		FUSELAGE_RIGHT_SIDE = 10,
		MAIN = 10,
		LINE_MAIN = 10,
		ENGINE = 11,
		ENGINE_L = 11,
		ENGINE_L_VNUTR = 11,
		ENGINE_L_IN = 11,
		ENGINE_R = 12,
		ENGINE_R_VNUTR = 12,
		ENGINE_R_IN = 12,
		MTG_L_BOTTOM = 13,
		MTG_R_BOTTOM = 14,
		LEFT_GEAR_BOX = 15,
		GEAR_L = 15,
		STOIKA_L = 15,
		RIGHT_GEAR_BOX = 16,
		GEAR_R = 16,
		STOIKA_R = 16,
		MTG_L = 17,
		ENGINE_L_VNESHN = 17,
		ENGINE_L_OUT = 17,
		EWU_L = 17,
		MTG_R = 18,
		ENGINE_R_VNESHN = 18,
		ENGINE_R_OUT = 18,
		EWU_R = 18,
		AIR_BRAKE_L = 19,
		AIR_BRAKE_R = 20,
		WING_L_PART_OUT = 21,
		WING_R_PART_OUT = 22,
		WING_L_OUT = 23,
		WING_R_OUT = 24,
		ELERON_L = 25,
		AILERON_L = 25,
		ELERON_R = 26,
		AILERON_R = 26,
		WING_L_PART_CENTER = 27,
		WING_R_PART_CENTER = 28,
		WING_L_CENTER = 29,
		WING_R_CENTER = 30,
		FLAP_L_OUT = 31,
		FLAP_R_OUT = 32,
		WING_L_PART_IN = 33,
		WING_R_PART_IN = 34,
		WING_L_IN = 35,
		WING_L = 35,
		Line_WING_L = 35,
		WING_R_IN = 36,
		WING_R = 36,
		Line_WING_R = 36,
		FLAP_L_IN = 37,
		FLAP_L = 37,
		FLAP_R_IN = 38,
		FLAP_R = 38,
		FIN_L_TOP = 39,
		KEEL_L_OUT = 39,
		KEEL_OUT = 39,
		FIN_R_TOP = 40,
		KEEL_R_OUT = 40,
		FIN_L_CENTER = 41,
		KEEL_L_CENTER = 41,
		KEEL_CENTER = 41,
		FIN_R_CENTER = 42,
		KEEL_R_CENTER = 42,
		FIN_L_BOTTOM = 43,
		KIL_L = 43,
		Line_KIL_L = 43,
		KEEL = 43,
		KEEL_IN = 43,
		KEEL_L = 43,
		KEEL_L_IN = 43,
		FIN_R_BOTTOM = 44,
		KIL_R = 44,
		Line_KIL_R = 44,
		KEEL_R = 44,
		KEEL_R_IN = 44,
		STABILIZER_L_OUT = 45,
		STABILIZATOR_L_OUT = 45,
		STABILIZER_R_OUT = 46,
		STABILIZATOR_R_OUT = 46,
		STABILIZER_L_IN = 47,
		STABILIZATOR_L = 47,
		STABILIZATOR_L01 = 47,
		Line_STABIL_L = 47,
		STABILIZER_R_IN = 48,
		STABILIZATOR_R = 48,
		STABILIZATOR_R01 = 48,
		Line_STABIL_R = 48,
		ELEVATOR_L_OUT = 49,
		ELEVATOR_R_OUT = 50,
		ELEVATOR_L_IN = 51,
		ELEVATOR_L = 51,
		RV_L = 51,
		ELEVATOR_R_IN = 52,
		ELEVATOR_R = 52,
		RV_R = 52,
		RUDDER_L = 53,
		RN_L = 53,
		RUDDER = 53,
		RUDDER_R = 54,
		RN_R = 54,
		TAIL = 55,
		TAIL_LEFT_SIDE = 56,
		TAIL_RIGHT_SIDE = 57,
		TAIL_BOTTOM = 58,
		NOSE_BOTTOM = 59,
		PWD = 60,
		PITOT = 60,
		FUEL_TANK_F = 61,
		FUEL_TANK_LEFT_SIDE = 61,
		FUEL_TANK_B = 62,
		FUEL_TANK_RIGHT_SIDE = 62,
		ROTOR = 63,
		BLADE_1_IN = 64,
		BLADE_1_CENTER = 65,
		BLADE_1_OUT = 66,
		BLADE_2_IN = 67,
		BLADE_2_CENTER = 68,
		BLADE_2_OUT = 69,
		BLADE_3_IN = 70,
		BLADE_3_CENTER = 71,
		BLADE_3_OUT = 72,
		BLADE_4_IN = 73,
		BLADE_4_CENTER = 74,
		BLADE_4_OUT = 75,
		BLADE_5_IN = 76,
		BLADE_5_CENTER = 77,
		BLADE_5_OUT = 78,
		BLADE_6_IN = 79,
		BLADE_6_CENTER = 80,
		BLADE_6_OUT = 81,
		FUSELAGE_BOTTOM = 82,
		WHEEL_F = 83,
		WHEEL_C = 83,
		WHEEL_REAR = 83,
		WHEEL_L = 84,
		WHEEL_R = 85,
		PYLON1 = 86,
		PYLONL = 86,
		PYLON2 = 87,
		PYLONR = 87,
		PYLON3 = 88,
		PYLON4 = 89,
		CREW_1 = 90,
		CREW_2 = 91,
		CREW_3 = 92,
		CREW_4 = 93,
		ARMOR_NOSE_PLATE_LEFT = 94,
		ARMOR_NOSE_PLATE_RIGHT = 95,
		ARMOR_PLATE_LEFT = 96,
		ARMOR_PLATE_RIGHT = 97,
		HOOK = 98,			
		FUSELAGE_TOP = 99,
		TAIL_TOP = 100,
		FLAP_L_CENTER = 101,
		FLAP_R_CENTER = 102	,
		ENGINE_1 = 103,
		ENGINE_2 = 104,
		ENGINE_3 = 105,
		ENGINE_4 = 106,
		ENGINE_5 = 107,
		ENGINE_6 = 108,
		ENGINE_7 = 109,
		ENGINE_8 = 110,
		COUNT = 111,
	};


	struct DamageDelta
	{
		Damage m_element;
		float m_delta;
	};

	//Don't touch this it's order dependent you will break the tank code.
	enum Tank
	{
		INTERNAL,
		LEFT_EXT,
		CENTRE_EXT,
		RIGHT_EXT,
		DONT_TOUCH //Seriously don't touch it.
	};


	Airframe(AircraftState& state, Input& controls, Engine2& engine);
	~Airframe();
	virtual void zeroInit();
	virtual void coldInit();
	virtual void hotInit();
	virtual void airborneInit();

	//Utility
	inline void setGearLPosition(double position); //for airstart or ground start
	inline void setGearRPosition(double position); //for airstart or ground start
	inline void setGearNPosition(double position); //for airstart or ground start
	inline void setFlapsPosition(double position);
	inline void setSpoilerPosition(double position);
	inline void setSlatLPosition(double position);
	inline void setSlatRPosition(double position);
	inline void setAirbrakePosition(double position);
	inline void setFuelState(Tank tank, Vec3 pos, double fuel);
	inline void setAngle(double angle);
	inline void setMass(double angle);

	inline void setNoseCompression( double x );

	inline void setSelectedTank( Tank selected );
	inline void setFuelPrevious( Tank tank );

	inline double getFuelPrevious( Tank tank );

	inline const Vec3& getFuelPos(Tank tank) const;
	inline double getFuelQty(Tank tank) const;
	inline double getFuelQtyExternal() const;
	inline double getFuelQtyDelta(Tank tank) const;

	inline double getGearLPosition(); //returns gear pos
	inline double getGearRPosition(); //returns gear pos
	inline double getGearNPosition(); //returns gear pos

	inline double getFlapsPosition();
	inline double getSpoilerPosition();
	inline double getSpeedBrakePosition();
	inline double getHookPosition();
	inline double getSlatLPosition();
	inline double getSlatRPosition();
	inline double getCatMoment();
	inline Tank getSelectedTank();
	inline double getMass();
	inline double setAileron(double dt);
	inline double setElevator(double dt);
	inline double setRudder(double dt);
	inline double getAileron();
	inline double getElevator();
	inline double getRudder();



	inline double aileronAngle();
	inline double elevatorAngle();
	inline double rudderAngle();

	inline const CatapultState& catapultState() const;
	inline CatapultState& catapultState();
	inline const bool& catapultStateSent() const;
	inline bool& catapultStateSent();
	inline void setCatStateFromKey();

	inline void setIntegrityElement(Damage element, float integrity);
	inline float getIntegrityElement(Damage element);
	inline void setDamageDelta( Damage element, float delta );
	inline bool processDamageStack( Damage& element, float& damage );

	void resetDamage();

	void printDamageState();

	//Update
	void airframeUpdate(double dt); //performs calculations and updates

	//Damage
	inline float getLWingDamage() const;
	inline float getRWingDamage() const;

	inline float getAileronDamage() const;

	inline float getVertStabDamage() const;
	inline float getRudderDamage() const;

	inline float getHoriStabDamage() const;
	inline float getElevatorDamage() const;

	inline float getCompressorDamage() const;
	inline float getTurbineDamage() const;
	inline float getSpoilerDamage() const;
	inline float getSpeedbrakeDamage() const;
	inline float getFlapDamage() const;

private:

	//Airframe Constants
	const double m_hookExtendTime = 1.5;

	//Airframe Variables
	double m_gearLPosition = 0.0; //0 -> 1
	double m_gearRPosition = 0.0;
	double m_gearNPosition = 0.0;

	double m_flapsPosition = 0.0;
	double m_spoilerPosition = 0.0;
	double m_speedBrakePosition = 0.0;
	double m_hookPosition = 0.0;
	double m_slatLPosition = 0.0;
	double m_slatRPosition = 0.0;

	double m_aileronLeft = 0.0;
	double m_aileronRight = 0.0;
	double m_elevator = 0.0;
	double m_rudder = 0.0;

	Actuator m_actuatorElev;
	Actuator m_actuatorAil;
	Actuator m_actuatorRud;


	Tank m_selected = Tank::INTERNAL;

	double m_fuel[4] = { 0.0, 0.0, 0.0, 0.0 };
	double m_fuelPrev[4] = { 0.0, 0.0, 0.0, 0.0 };
	Vec3 m_fuelPos[4] = { Vec3(), Vec3(), Vec3(), Vec3() };

	float* m_integrityElement;

	double m_mass = 1.0;

	CatapultState m_catapultState = OFF_CAT;
	bool m_catStateSent = false;
	double m_catMoment = 0.0;
	double m_catMomentVelocity = 0.0;
	double m_angle = 0.0;
	double m_integral = 0.0;
	double m_prevAccel = 0.0;
	double m_noseCompression = 0.0;

	Engine2& m_engine;
	Input& m_controls;
	AircraftState& m_state;
	std::vector<DamageDelta> m_damageStack;
};

void Airframe::setSelectedTank(Tank selected)
{
	m_selected = selected;
}

void Airframe::setFuelPrevious( Tank tank )
{

	m_fuelPrev[tank] = m_fuel[tank];
}

void Airframe::setFuelState(Tank tank, Vec3 pos, double fuel)
{
	m_fuel[tank] = fuel;
	m_fuelPos[tank] = pos;
}

double Airframe::setAileron(double dt)
{
	double input = m_controls.roll() + m_controls.rollTrim();
	return m_actuatorAil.inputUpdate(input, dt);
}

double Airframe::setElevator(double dt)
{
	double input = m_controls.pitch() + m_controls.pitchTrim();
	return m_actuatorElev.inputUpdate(input, dt);
}

double Airframe::setRudder(double dt)
{
	double input = m_controls.yaw() + m_controls.yawDamper() + m_controls.yawTrim();
	return m_actuatorRud.inputUpdate(input, dt);
}

void Airframe::setFlapsPosition(double position)
{
	m_flapsPosition = position;
}

void Airframe::setGearLPosition(double position)
{
	m_gearLPosition = position;
}

void Airframe::setGearRPosition( double position )
{
	m_gearRPosition = position;
}

void Airframe::setGearNPosition( double position )
{
	m_gearNPosition = position;
}

void Airframe::setAirbrakePosition(double position)
{
	m_speedBrakePosition = position;
}

void Airframe::setAngle(double angle)
{
	m_angle = angle;
}

void Airframe::setMass(double mass)
{
	m_mass = mass;
}

void Airframe::setNoseCompression( double x )
{
	m_noseCompression = x;
}

double Airframe::getFuelPrevious( Tank tank )
{
	return m_fuelPrev[tank];
}

double Airframe::getGearLPosition()
{
	return m_gearLPosition;
}

double Airframe::getGearRPosition()
{
	return m_gearRPosition;
}

double Airframe::getGearNPosition()
{
	return m_gearNPosition;
}

double Airframe::getFlapsPosition()
{
	return m_flapsPosition;
}

double Airframe::getSpoilerPosition()
{
	return m_spoilerPosition;
}

double Airframe::getSpeedBrakePosition()
{
	return m_speedBrakePosition;
}

double Airframe::getHookPosition()
{
	return m_hookPosition;
}

double Airframe::getSlatLPosition()
{
	return m_slatLPosition;
}

double Airframe::getSlatRPosition()
{
	return m_slatRPosition;
}

double Airframe::getAileron()
{
	return m_aileronLeft;
}

double Airframe::getElevator()
{
	return m_elevator;
}

double Airframe::getRudder()
{
	return m_rudder;
}

double Airframe::aileronAngle()
{
	return 	m_aileronLeft > 0.0 ? c_aileronUp * m_aileronLeft : -c_aileronDown * m_aileronLeft;
}

double Airframe::elevatorAngle()
{
	return m_elevator > 0.0 ? -c_elevatorUp * m_elevator : c_elevatorDown * m_elevator;
}

double Airframe::rudderAngle()
{
	return m_rudder > 0.0 ? c_rudderRight * m_rudder : -c_rudderLeft * m_rudder;
}

void Airframe::setSlatLPosition(double position)
{
	m_slatLPosition = position;
}

void Airframe::setSlatRPosition(double position)
{
	m_slatRPosition = position;
}

void Airframe::setSpoilerPosition(double position)
{
	m_spoilerPosition = position;
}

const Airframe::CatapultState& Airframe::catapultState() const
{
	return m_catapultState;
}

Airframe::CatapultState& Airframe::catapultState()
{
	return m_catapultState;
}

const bool& Airframe::catapultStateSent() const
{
	return m_catStateSent;
}

bool& Airframe::catapultStateSent()
{
	return m_catStateSent;
}

void Airframe::setCatStateFromKey()
{
	switch (m_catapultState)
	{
	case ON_CAT_NOT_READY:
	case ON_CAT_READY:
	case ON_CAT_WAITING:
		printf("OFF_CAT\n");
		m_catapultState = OFF_CAT;
		break;
	case OFF_CAT:
		printf("ON_CAT_NOT_READY\n");
		m_catapultState = ON_CAT_NOT_READY;
		break;
	}
}

const Vec3& Airframe::getFuelPos(Tank tank) const
{
	return m_fuelPos[tank];
}

double Airframe::getFuelQty(Tank tank) const
{
	return m_fuel[tank];
}

double Airframe::getFuelQtyExternal() const
{
	return m_fuel[Tank::LEFT_EXT] + m_fuel[Tank::CENTRE_EXT] + m_fuel[Tank::RIGHT_EXT];
}

double Airframe::getFuelQtyDelta(Tank tank) const
{
	return m_fuel[tank] - m_fuelPrev[tank];
}

double Airframe::getCatMoment()
{
	return m_catMoment;
}

double Airframe::getMass()
{
	return m_mass;
}

inline Airframe::Tank Airframe::getSelectedTank()
{
	return m_selected;
}

inline void Airframe::setIntegrityElement(Damage element, float integrity)
{
	m_integrityElement[(int)element] = integrity;
}

inline float Airframe::getIntegrityElement(Damage element)
{
	return m_integrityElement[(int)element];
}

void Airframe::setDamageDelta( Damage element, float delta )
{
	DamageDelta d;
	d.m_delta = delta;
	d.m_element = element;
	m_damageStack.push_back( d );
}

bool Airframe::processDamageStack( Damage& element, float& damage )
{
	if ( m_damageStack.empty() )
		return false;

	DamageDelta delta = m_damageStack.back();
	m_damageStack.pop_back();


	m_integrityElement[(int)delta.m_element] -= delta.m_delta;
	
	element = delta.m_element;
	damage = m_integrityElement[(int)delta.m_element];

	return true;
}

inline float Airframe::getLWingDamage() const
{
	return (DMG_ELEM( Damage::WING_L_IN) + DMG_ELEM( Damage::WING_L_CENTER) + DMG_ELEM( Damage::WING_L_OUT)) / 3.0;
}

inline float Airframe::getRWingDamage() const
{
	return (DMG_ELEM( Damage::WING_R_IN) + DMG_ELEM( Damage::WING_R_CENTER) + DMG_ELEM( Damage::WING_R_OUT)) / 3.0;
}

inline float Airframe::getAileronDamage() const
{
	return (DMG_ELEM(Damage::AILERON_L) + DMG_ELEM(Damage::AILERON_R)) / 2.0;
}

inline float Airframe::getVertStabDamage() const
{
	return (DMG_ELEM( Damage::FIN_L_TOP ) + DMG_ELEM( Damage::FIN_L_BOTTOM )) / 2.0;
}

inline float Airframe::getRudderDamage() const
{
	return DMG_ELEM( Damage::RUDDER );
}

inline float Airframe::getHoriStabDamage() const
{
	return (DMG_ELEM(Damage::STABILIZATOR_L) + DMG_ELEM(Damage::STABILIZATOR_R)) / 2.0;
}

inline float Airframe::getElevatorDamage() const
{
	return (DMG_ELEM( Damage::ELEVATOR_L ) + DMG_ELEM( Damage::ELEVATOR_R )) / 2.0;
}

inline float Airframe::getCompressorDamage() const
{
	return 1.0; //stub for now
}
inline float Airframe::getTurbineDamage() const
{
	return 1.0; //stub for now
}

inline float Airframe::getSpoilerDamage() const
{
	return (DMG_ELEM( Damage::WING_L_PART_CENTER ) + DMG_ELEM( Damage::WING_R_PART_CENTER )) / 2.0;
}
inline float Airframe::getSpeedbrakeDamage() const
{
	return (DMG_ELEM( Damage::AIR_BRAKE_L ) + DMG_ELEM( Damage::AIR_BRAKE_R )) / 2.0;
}
inline float Airframe::getFlapDamage() const
{
	return (DMG_ELEM( Damage::FLAP_L ) + DMG_ELEM( Damage::FLAP_R )) / 2.0;
}

} // end namespace

#endif
