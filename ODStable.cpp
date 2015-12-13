/*
** ODStable.cpp
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

#include "ODStable.h"
#include "ODScell.h"

using namespace ODSlib;

ODStable::ODStable(QDomElement &element) :
	OSDprototypeXMLfamiliar(element)
{
	m_bValid = parse();
}

ODStable::~ODStable()
{
}

ODScell &ODStable::cell(ST y, ST x)
{
	return *((ODScell*)(*m_vContainer[y]).at(x));
}

bool ODStable::parse()
{
	bool bReturn = false;

	QDomNodeList rows = m_oAssociated.childNodes();
	const int size = rows.size();
	for ( int i = 0; i < size; ++i )
	{
		QDomElement row = rows.at(i).toElement();

		// check for table elements
		if ( !row.isNull() && !row.tagName().compare("table:table-row") )
		{
			bReturn |= parseRowEntry(row);
		}
	}

	return bReturn;
}

bool ODStable::parseRowEntry(QDomElement row)
{
	int nRepetitions = 1;

	if ( row.hasAttribute("table:number-rows-repeated") )
	{
		bool bOK;
		nRepetitions = row.attribute("table:number-rows-repeated").toInt(&bOK);

		// TODO: maybe catch some more errors
		if ( !bOK || nRepetitions < 1 )
		{
			return false;
		}
	}

	bool bReturn = false;

	bReturn |= parseSingleRowEntry(row);

	if ( nRepetitions > 1 )
	{
		row.removeAttribute("table:number-rows-repeated");

		for ( int i = 1; i < nRepetitions; ++i )
		{
			QDomElement singleRow = row.cloneNode(true).toElement();
			singleRow = row.parentNode().insertAfter(singleRow, row).toElement();
			bReturn |= parseSingleRowEntry(singleRow);
		}
	}

	return bReturn;
}

bool ODStable::parseSingleRowEntry(QDomElement row)
{
	bool bReturn = false;



	return bReturn;
}

