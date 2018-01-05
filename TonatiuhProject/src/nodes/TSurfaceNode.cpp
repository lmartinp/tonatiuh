/***************************************************************************
Copyright (C) 2008 by the Tonatiuh Software Development Team.

This file is part of Tonatiuh.

Tonatiuh program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


Acknowledgments:

The development of Tonatiuh was started on 2004 by Dr. Manuel Blanco,
at the time Chair of the Department of Engineering of the University of Texas
at Brownsville. From May 2004 to August 2008 Tonatiuh's development was
supported by the Department of Energy (DOE) and the National Renewable
Energy Laboratory (NREL) under the Minority Research Associate (MURA)
Program Subcontract ACQ-4-33623-06. During 2007, NREL also contributed to
the validation of Tonatiuh under the framework of the Memorandum of
Understanding signed with the Spanish National Renewable Energy Centre (CENER)
on February, 20, 2007 (MOU#NREL-07-117). Since June 2006, the development of
Tonatiuh is being led by CENER, under the direction of Dr. Blanco, now
Manager of the Solar Thermal Energy Department of CENER.

Developers: Manuel J. Blanco (mblanco@cener.com), Amaia Mutuberria, Victor Martin.

Contributors: Javier Garcia-Barberena, Inaki Perez, Inigo Pagola,  Gilda Jimenez,
Juana Amieva, Azael Mancillas, Cesar Cantu.
***************************************************************************/

#include "TSurfaceNode.h"

/******************************
 * TSurfaceNode
 ******************************/

TNodeType TSurfaceNode::m_nodeType = TNodeType::CreateEmptyType();

/*!
 * Creates a new instance of the class type corresponding object.
 */
void* TSurfaceNode::CreateInstance( )
{
  return ( new TSurfaceNode() );
}

/*!
 * Initializes TSurfaceNode type.
 */
void TSurfaceNode::Init()
{

	m_nodeType = TNodeType::CreateType( TNodeType::FromName( "ContainerNode" ), "SurfaceNode", &TSurfaceNode::CreateInstance );
}

/*!
 * TGroupNode : public TNode
 */
TSurfaceNode::TSurfaceNode()
:TContainerNode()
{

	//setObjectName(GetType().GetName().c_str() );
	SetName( GetType().GetName() );

	//Parts
	AppendPart( "shape", TNodeType::FromName( "Shape" ) , 0 );
	AppendPart( "material", TNodeType::FromName( "Material" ) , 0 );

}

/*!
 * Destructor.
 */
TSurfaceNode::~TSurfaceNode()
{
	SetPart( "shape", 0 );
	SetPart( "material", 0 );
}



/*!
 * Creates a copy of surface node.
 */
TSurfaceNode* TSurfaceNode::Copy() const
 {
	TSurfaceNode* surfaceNode = new TSurfaceNode;
	 if( surfaceNode == 0 )	return ( 0  );

	 for (std::map<std::string, TNodeType>::iterator it = surfaceNode->m_partsTypeList.begin(); it!=surfaceNode->m_partsTypeList.end(); ++it)
	 {
		 std::string partName = it->first;
		 TNodeType partType = it->second;
		 TNode* partNode = surfaceNode->m_partsList[partName];


		 surfaceNode->AppendPart( partName, partType, partNode->Copy() );
	 }

	 //Coping the parameters.
	 //No parameters.

	 return ( surfaceNode );
 }

/*!
 * Returns the type of node.
 */
TNodeType TSurfaceNode::GetType() const
{
	return ( TSurfaceNode::m_nodeType );
}
