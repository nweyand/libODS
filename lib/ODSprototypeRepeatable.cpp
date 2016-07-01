/*
** ODSprototypeRepeatable.cpp
**
** Copyright © libODS Development Team, 2015-2016.
** This file is part of libODS (https://github.com/nweyand/libODS/)
**
** libODS is free software; this file may be used under the terms of the GNU
** General Public License version 3.0 or later or later as published by the Free Software
** Foundation and appearing in the file LICENSE included in the
** packaging of this file.
**
** libODS is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
**
** Please review the following information to ensure the GNU General Public
** License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** You should have received a copy of the GNU General Public License version
** 3.0 along with libODS; if not, write to the Free Software Foundation,
** Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "ODSprototypeRepeatable.h"

#include "ODSprototypeXMLfamiliarData.h"
#include "ODSprototypeRepeatableData.h"

namespace ODSlib
{

ODSprototypeRepeatable::
ODSprototypeRepeatable( const QString &sChildElementFilter, const QString &sRepeatFilter,
                        QDomElement &associatedElement ) :
	ODSprototypeXMLfamiliar( sChildElementFilter, associatedElement ),
	m_pPRData( new ODSprototypeRepeatableData( sRepeatFilter, associatedElement ) )
{
}

/*ODSprototypeRepeatable::ODSprototypeRepeatable(const ODSprototypeRepeatable &rhs) :
    pPRData(rhs.pPRData)
{
}

ODSprototypeRepeatable &ODSprototypeRepeatable::operator=(const ODSprototypeRepeatable &rhs)
{
	if (this != &rhs)
		pPRData.operator=(rhs.pPRData);
	return *this;
}*/

ODSprototypeRepeatable::~ODSprototypeRepeatable()
{
}

size_t ODSprototypeRepeatable::multiplicity() const
{
	return m_pPRData->m_nMultiplicity;
}

void ODSprototypeRepeatable::doDetach()
{
	m_pPRData.detach();
}

ODSprototypeRepeatable *ODSprototypeRepeatable::splitUpRepetition(size_t target)
{
	if ( target > 0 && target < m_pPRData->m_nMultiplicity )
	{
		if ( target > 1 ) // create new item before this one
		{
			// TODO: continue here
		}

		if ( target + 1 != m_pPRData->m_nMultiplicity ) // create new item after this one
		{
			// TODO: continue here
		}

		detach();
		setMultiplicity( 1 );

		// TODO: Optimize. Mulitiplicity should not be part of shared data.

		return NULL; //this;
	}

	return NULL;
}

void ODSprototypeRepeatable::setMultiplicity(const size_t &multiplicity)
{
	m_pPXFData->m_oAssociated.setAttribute( m_pPRData->m_sRepeatAttribute, multiplicity );
	m_pPRData->m_nMultiplicity = multiplicity;
}

} // namespace ODSlib
