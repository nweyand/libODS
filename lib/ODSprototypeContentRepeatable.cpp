/*
** ODSprototypeContentRepeatable.cpp
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

#include "ODSprototypeContentRepeatable.h"
#include "ODSprototypeRepeatable.h"

#include "ODSprototypeXMLfamiliarData.h"
#include "ODSprototypeContentRepeatableData.h"

namespace ODSlib
{

ODSprototypeContentRepeatable::
ODSprototypeContentRepeatable(const QString &sChild, const QString &sRepeat, QDomElement &element) :
	ODSprototypeXMLfamiliar( sChild, element ),
	m_pPCRData( new ODSprototypeContentRepeatableData( sRepeat ) )
{
}

/*ODSprototypeContentRepeatable::
ODSprototypeContentRepeatable(const ODSprototypeContentRepeatable &rhs) :
    pPCRData(rhs.pPCRData)
{
}

ODSprototypeContentRepeatable &ODSprototypeContentRepeatable::
operator=(const ODSprototypeContentRepeatable &rhs)
{
	if (this != &rhs)
		pPCRData.operator=(rhs.pPCRData);
	return *this;
}*/

ODSprototypeContentRepeatable::~ODSprototypeContentRepeatable()
{
}

void ODSprototypeContentRepeatable::doMagic(ODSprototypeXMLfamiliar *pNew)
{
	// Remember the current position for faster lookup. This allows to look up items by their real
	// position in order to allow fast access to their XML storage position.
	m_pPCRData->m_mPositions[m_pPCRData->m_nParseCounter] = m_pPXFData->m_vContainer.size();

	// keep track of parse counter incrementation (counts the number of „real“ items as oppesed to
	// the number of XML entries).
	const QDomElement repeatableXML = pNew->m_pPXFData->m_oAssociated;
	if ( repeatableXML.hasAttribute( m_pPCRData->m_sRepeatFilter ) )
	{
		bool bOK;
		const unsigned int nRepetitions = repeatableXML.attribute( m_pPCRData->m_sRepeatFilter ).toUInt(&bOK);

		if ( bOK )
		{
			m_pPCRData->m_nParseCounter += nRepetitions;
		}
		else // handle the xml item as not repeated in case of error
		{
			++(m_pPCRData->m_nParseCounter);
		}
	}
	else
	{
		++(m_pPCRData->m_nParseCounter);
	}

	// make sure to call parent
	ODSprototypeXMLfamiliar::doMagic(pNew);
}

ODSprototypeXMLfamiliar *ODSprototypeContentRepeatable::item(st pos)
{
	// The content of this node is repeatable (i.e. this is a table or a row node).
	// This means that in a fully constructed node of this type there is at least one child node
	// (at position 0).
	Q_ASSERT( m_pPCRData->m_mPositions.size() );

	if ( m_pPCRData->m_mPositions.count(pos) )
	{
		st nStoragePos = m_pPCRData->m_mPositions.at(pos);
		if ( nStoragePos < m_pPXFData->m_vContainer.size() )
		{
			return m_pPXFData->m_vContainer[nStoragePos];
		}
		else
		{
			// should never happen except if there is a bug in the counting code...
			qCritical() << "ERROR: something went wrong in ODSprototypeContentRepeatable::item!";
			Q_ASSERT( false ); // this is nicer for debugging
			throw(42);         // in case assertions disabled, cause crash :)
			return NULL;
		}
	}
	else
	{
		st key = (*(m_pPCRData->m_mPositions).begin()).first;
		st val = (*(m_pPCRData->m_mPositions).begin()).second;

		// First item is always (key:0;val:0)
		Q_ASSERT( !key );
		Q_ASSERT( !val );

		st nPosFirstBiggerItem = 0;

		for ( std::map<st,st>::const_iterator it = m_pPCRData->m_mPositions.begin();
		      it != m_pPCRData->m_mPositions.end(); ++it )
		{
			if ( (*it).first < pos )
			{
				key = (*it).first;
				val = (*it).second;

				// always points to the position after the last item with a smaller position
				++nPosFirstBiggerItem;
			}
			else
			{
				break;
			}
		}

		// At this point we need to make (and verify) an assumption:
		// There is no way the item with index 0 doesn't exist because of repetition.
		// This means that nPosLastSmallerItem is never 0 (because m_mPositions is supposed to
		// contain the node with index 0)
		Q_ASSERT( nPosFirstBiggerItem );

		// Now we are at the child item whose repetition is what we are looking for.
		const st nPosTarget = nPosFirstBiggerItem - 1;

		// This should be guaranteed anyway.
		Q_ASSERT( nPosTarget < m_pPXFData->m_vContainer.size() );

		// OK, we know now which element to split up...
		ODSprototypeXMLfamiliar* pRepeatedChild = m_pPXFData->m_vContainer[nPosTarget];

		// ...and we also know that all children stored in ODSprototypeContentRepeatable's are
		// ODSprototypeRepeatable...
		ODSprototypeRepeatable* pChild = dynamic_cast< ODSprototypeRepeatable* >( pRepeatedChild );

		// calculate the target position for extration abong the repeated items
		const st nRealCellPos = key;
		const st nDeltaSplit  = pos - nRealCellPos;

		Q_ASSERT( pos > nRealCellPos );

		// cut out the target child for later external editing
		ODSprototypeRepeatable* pExtract = pChild->splitUpRepetition( nDeltaSplit );

		return pExtract;
	}
}

void ODSprototypeContentRepeatable::doDetach()
{
	m_pPCRData.detach();
}

} // namespace ODSlib
