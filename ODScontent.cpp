/*
** ODScontent.cpp
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

#include "ODScontent.h"
#include "ODSspreadsheet.h"

using namespace ODSlib;

ODScontent::ODScontent(ODSfile &ioFile) :
	OSDprototypeXMLfamiliar()
{
	QIODevice* pDevice = ioFile.accessContainerElement(m_sContentFileName);

	m_oContentFile = QDomDocument();
	int errorLine, errorCol;
	QString sError;

	if ( m_oContentFile.setContent(pDevice, &sError, &errorLine, &errorCol) )
	{
		m_oAssociated = m_oContentFile.documentElement();
		m_bValid = parse();
	}
	else
	{
		// TODO: improve warning with error string from above
		qWarning("ODScontent::parse - Failed to parse file.");
	}

	ioFile.closeContainerElement(pDevice);
}

ODScontent::~ODScontent()
{
}

QString ODScontent::toString()
{
	return m_oContentFile.toString(-1);
}

bool ODScontent::parse()
{
	bool bReturn = false;

	QDomNodeList officeSpreadsheets = m_oAssociated.elementsByTagName("office:spreadsheet");

	// there should be only one, but in case there are several...
	for ( int i = 0; i < officeSpreadsheets.size(); ++i )
	{
		QDomElement sheet = officeSpreadsheets.at(i).toElement();
		if ( !sheet.isNull() )
		{
			ODSspreadsheet *pNewSheet = new ODSspreadsheet(sheet);
			if ( pNewSheet->valid() )
			{
				m_vContainer.push_back(pNewSheet);
				bReturn = true;
			}
			else
			{
				delete pNewSheet;
			}
		}
	}

	return bReturn;
}

