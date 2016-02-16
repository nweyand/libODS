/*
** ODSrow.cpp
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

#include "ODSrow.h"

#include "ODSprototypeXMLfamiliarData.h"
#include "ODSprototypeContentRepeatableData.h"
#include "ODSprototypeRepeatableData.h"

namespace ODSlib
{
/*class ODSrowData : public QSharedData
{
public:
};*/

ODSrow::ODSrow(QDomElement &element) :
    ODSprototypeXMLfamiliar( ODS_TAG_TABLE_CELL, element ), // req due to virtual inheritance
    ODSprototypeContentRepeatable( ODS_TAG_TABLE_CELL, ODS_ATTR_TBL_CELL_REPEAT, element ), // child: cell; child repetitions for: cell
    ODSprototypeRepeatable( ODS_TAG_TABLE_CELL, ODS_ATTR_TBL_ROW_REPEAT, element ) // child: cell; expecting repetitions for: row
    //,pRowData(new ODSrowData)
{
}

/*ODSrow::ODSrow(const ODSrow &rhs) : pRowData(rhs.pRowData)
{
}

ODSrow &ODSrow::operator=(const ODSrow &rhs)
{
	if (this != &rhs)
		pRowData.operator=(rhs.pRowData);
	return *this;
}*/

ODSrow::~ODSrow()
{
}

/*ODSprototypeRepeatable *ODSrow::clone()
{
	// create a deep copy of this node
	QDomElement cloneElement = m_oAssociated.cloneNode( true ).toElement();
	m_oAssociated.parentNode().insertAfter( cloneElement, m_oAssociated );

	// and create a row out of it
	ODSrow *pRow = new ODSrow( cloneElement );
	pRow->parse();
	return pRow;
}*/

} // namespace ODSlib

