/******************************************************************************

GHAAS Water Balance/Transport Model V3.0
Global Hydrologic Archive and Analysis System
Copyright 1994-2007, University of New Hampshire

MDPointSource.c

m.m.mineau@unh.edu
rob.stewart@unh.edu

*******************************************************************************/


#include <stdio.h>
#include <cm.h>
#include <MF.h>
#include <MD.h>

// Inputs

static int _MDInWWTFID = MFUnset;

// Outputs

static int _MDOutPointSourceID = MFUnset;


static void _MDPointSource (int itemID) {



	float WWTF_daily  = 0.0;	// MMM daily input of DIN from waste water treatment facility in kg / day
	float Total_daily = 0.0;	// Total daily input of DIN from all point sources in kg/day
	int day, month, year;

	WWTF_daily    	   = MFVarGetFloat (_MDInWWTFID,   itemID, 0.0);

	Total_daily = WWTF_daily;		// MMM currently total point sources = only input from WWTF but can add other point source layers here in future

	day   = MFDateGetCurrentDay ();
	month = MFDateGetCurrentMonth ();
	year  = MFDateGetCurrentYear ();

//if (itemID == 31) printf("WWTF_daily = %f\n", WWTF_daily);

	MFVarSetFloat (_MDOutPointSourceID,   itemID, Total_daily);

}


int MDPointSourceDef() {


	MFDefEntering ("Point Source");

//	 if (((_MDInWWTFID		        = MFVarGetID (MDVarWWTF,		       "kg/y",  MFInput,   MFFlux, MFBoundary)) == CMfailed) ||
//		 ((_MDOutPointSourceID	    = MFVarGetID (MDVarPointSource,        "kg/d",  MFOutput,  MFFlux, MFInitial)) == CMfailed) ||
		 (MFModelAddFunction(_MDPointSource) == CMfailed)) return (CMfailed);

	MFDefLeaving ("Point Source");
	return (_MDOutPointSourceID);

}

