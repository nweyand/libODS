/*
** ODSprototypeFactory.cpp
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

#include "ODSprototypeFactory.h"
#include "ODSelementFactory.h"

#include "ODScell.h"
#include "ODSrow.h"
#include "ODStable.h"
#include "ODSspreadsheet.h"

using namespace ODSlib;

ODSprototypeFactory::ODSprototypeFactory()
{
}

ODSprototypeFactory::~ODSprototypeFactory()
{
}

ODSprototypeXMLfamiliar *ODSprototypeFactory::generate(QDomElement &element, const QString &sSelect)
{
	ODSprototypeXMLfamiliar *pReturn = NULL;

	// clauses sorted by number of occurrences
	if ( !sSelect.compare(ODS_TAG_TABLE_CELL) )
	{
		pReturn = ODSelementFactory::generateCell(element);
	}
	else if ( !sSelect.compare(ODS_TAG_TABLE_ROW) )
	{
		pReturn = ODSelementFactory::generateRow(element);
	}
	else if ( !sSelect.compare(ODS_TAG_TABLE) )
	{
		pReturn = ODSelementFactory::generateTable(element);
	}
	else if ( !sSelect.compare(ODS_TAG_OFFICE_SPREADSHEET) )
	{
		pReturn = ODSelementFactory::generateSpreadsheet(element);
	}

	return pReturn;
}

