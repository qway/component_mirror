/*
 * Ubitrack - Library for Ubiquitous Tracking
 * Copyright 2006, Technische Universitaet Muenchen, and individual
 3* contributors as indicated by the @authors tag. See the
 * copyright.txt in the distribution for a full listing of individual
 * contributors.
 *
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this software; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA, or see the FSF site: http://www.fsf.org.
 */

/**
 * @ingroup 
 * @file
 * 
 *
 * @author 
 */


#include <string>
#include <list>
#include <iostream>
#include <iomanip>
#include <strstream>
#include <log4cpp/Category.hh>


#include <utDataflow/PushSupplier.h>
#include <utDataflow/PullSupplier.h>
#include <utDataflow/PullConsumer.h>
#include <utDataflow/Component.h>
#include <utDataflow/ComponentFactory.h>
#include <utMeasurement/Measurement.h>
#include <utUtil/OS.h>

// get a logger
static log4cpp::Category& logger( log4cpp::Category::getInstance( "Ubitrack.Component.Mirror" ) );

using namespace Ubitrack;



namespace Ubitrack { namespace Drivers {


class MirrorComponent
	: public Dataflow::Component	
{
public:

	



	/** constructor */
	MirrorComponent( const std::string& sName, boost::shared_ptr< Graph::UTQLSubgraph >  subgraph)
		: Ubitrack::Dataflow::Component(sName)
		, m_mirrorPose("MirrorPose", *this)
		, m_markerPose("MarkerPose", *this, boost::bind(&MirrorComponent::pushMarkerPose, this, _1))
		, m_correctedMarkerPose("Output", *this)
	{

	}

	/** destructor, waits until thread stops */
	~MirrorComponent(){

	}


	void pushMarkerPose(const Measurement::Pose pos);

protected:	
	Dataflow::PushConsumer<Measurement::Pose> m_markerPose;
	Dataflow::PullConsumer<Measurement::Pose> m_mirrorPose;
	Dataflow::PushSupplier<Measurement::Pose> m_correctedMarkerPose;
	
};

void MirrorComponent::pushMarkerPose(const Measurement::Pose pose){
	Measurement::Timestamp ts = pose.time();
	Math::Pose mathPose = *pose;
	
	Math::Pose mirrorPose = *m_mirrorPose.get(ts);







	Math::Pose result;


	m_correctedMarkerPose.send(Measurement::Pose(ts, result));
}


} } // namespace Ubitrack::Driver

UBITRACK_REGISTER_COMPONENT( Dataflow::ComponentFactory* const cf ) {
	cf->registerComponent< Ubitrack::Drivers::MirrorComponent > ( "MirrorComponent" );
}

