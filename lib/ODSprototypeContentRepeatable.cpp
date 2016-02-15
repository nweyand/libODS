/*
** ODSprototypeContentRepeatable.cpp
**
** Copyright © libODS Development Team, 2015.
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

using namespace ODSlib;

ODSprototypeContentRepeatable::ODSprototypeContentRepeatable(const QString &sChildElementFilter, const QString &sRepeatFilter, QDomElement &associatedElement) :
	ODSprototypeXMLfamiliar( sChildElementFilter, associatedElement ),
	m_sRepeatFilter( sRepeatFilter ),
	m_nParseCounter( 0 )
{
}

ODSprototypeContentRepeatable::~ODSprototypeContentRepeatable()
{
}

void ODSprototypeContentRepeatable::doMagic(ODSprototypeXMLfamiliar *pNew)
{
	// remember the current position for faster lookup
	m_mPositions[m_nParseCounter] = m_vContainer.size();

	// keep track of pos counter incrementation
	const QDomElement row = pNew->m_oAssociated;
	if ( row.hasAttribute( m_sRepeatFilter ) )
	{
		bool bOK;
		const unsigned int nRepetitions = row.attribute( m_sRepeatFilter ).toUInt(&bOK);

		if ( bOK )
		{
			m_nParseCounter += nRepetitions;
		}
		else // handle the cell as not repeated in case of error
		{
			++m_nParseCounter;
		}
	}
	else
	{
		++m_nParseCounter;
	}

	// make sure to call parent
	ODSprototypeXMLfamiliar::doMagic(pNew);
}

ODSprototypeXMLfamiliar *ODSprototypeContentRepeatable::item(ODSprototypeXMLfamiliar::TContainer::size_type pos)
{
	// The content of this node is repeatable (i.e. this is a table or a row node).
	// This means that in a fully constructed node of this type there is at least one child node (at position 0).
	Q_ASSERT( m_mPositions.size() );

	if ( m_mPositions.count(pos) )
	{
		st nStoragePos = m_mPositions.at(pos);
		if ( nStoragePos < m_vContainer.size() )
		{
			return m_vContainer[nStoragePos];
		}
		else
		{
			// should never happen except if there is a bug in the counting code...
			qCritical() << "ERROR: something really went wrong in ODSprototypeContentRepeatable::item!";
			Q_ASSERT( false ); // this is nicer for debugging
			throw(42);         // in case assertions disabled, cause crash :)
			return NULL;
		}
	}
	else
	{
		st key = (*m_mPositions.begin()).first;
		st val = (*m_mPositions.begin()).second;

		// First item is always (key:0;val:0)
		Q_ASSERT( !key );
		Q_ASSERT( !val );

		//TContainer::iterator containerIt = m_vContainer.begin();
		st nPosFirstBiggerItem = 0;

		for ( std::map<st,st>::const_iterator it = m_mPositions.begin(); it != m_mPositions.end(); ++it )
		{
			if ( (*it).first < pos )
			{
				key = (*it).first;
				val = (*it).second;

				// always points to the position after the last item with a smaller position
				//++containerIt;
				++nPosFirstBiggerItem;
			}
			else
			{
				break;
			}
		}

		// At this point we need to make (and verify) an assumption:
		// There is no way the item with index 0 doesn't exist because of repetition.
		// This means that nPosLastSmallerItem is never 0 (because m_mPositions is supposed to contain the node with index 0)
		Q_ASSERT( nPosFirstBiggerItem );

		// Now we are at the child item whose repetition is what we are looking for.
		--nPosFirstBiggerItem;

		// This should be guaranteed anyway.
		Q_ASSERT( nPosFirstBiggerItem < m_vContainer.size() );

		// OK, we know now which element to split...
		ODSprototypeXMLfamiliar* pRepeatedChild = m_vContainer[nPosFirstBiggerItem];

		// ...and we also know that all children stored in ODSprototypeContentRepeatable's are ODSprototypeRepeatable...
		ODSprototypeRepeatable* pChild = dynamic_cast< ODSprototypeRepeatable* >( pRepeatedChild );


		// TODO: fix
		return NULL;
	}
}

