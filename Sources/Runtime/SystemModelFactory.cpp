#include "StdAfx.h"
#include "SystemModelFactory.h"
#include "BISModel.h"
#include "BunkerModel.h"
#include "DamperModel.h"
#include "GateModel.h"
#include "GrainDryerModel.h"
#include "TransporterModel.h"

SystemModelFactory::SystemModelFactory(void)
{
}


SystemModelFactory::~SystemModelFactory(void)
{
}

BaseModelObject * SystemModelFactory::createModel( QString type )
{
	if(type.isEmpty())
		return NULL;
	QString temp = type.toLower();
	BaseModelObject* obj = NULL;
	if(temp == "bis")
	{
		obj = new BISModel();
	}
	else if(temp == "bunker")
	{
		obj = new BunkerModel();
	}
	else if(temp == "damper")
	{
		obj = new DamperModel();
	}
	else if(temp == "gate")
	{
		obj = new GateModel();
	}
	else if(temp == "graindryer")
	{
		obj = new GrainDryerModel();
	}
	else if(temp == "transporter")
	{
		obj = new TransporterModel();
	}
	return obj;
}
