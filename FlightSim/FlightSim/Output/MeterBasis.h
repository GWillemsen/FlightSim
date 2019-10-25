/*
 * MeterBasis.h
 *
 * Created: 18/10/2019 16:03:53
 *  Author: Gielw
 */ 


#ifndef METERBASIS_H_
#define METERBASIS_H_

class MeterBasis
{
public:
	virtual bool NextUpdateIsLongOfDuration() { return false; }
	virtual int UpdateMeter() {};	
};



#endif /* METERBASIS_H_ */