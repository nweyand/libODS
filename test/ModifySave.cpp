/*
** ModifySave.cpp
**
** Copyright © libODS Development Team, 2016.
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

#include "ModifySave.h"

ModifySave::ModifySave() :
	SingleDocumentTestCase( "testData/ModifySave.ods" ),
	m_pTable( NULL )
{
}

void ModifySave::checkDocumentValid()
{
	QVERIFY2( m_pDoc->valid(), "The specified document could not be verified as valid." );
	qDebug() << "\n   File: " << m_pDoc->fileName()
			 << "\n   Path: " << m_pDoc->path();
}

void ModifySave::readTable()
{
	m_pTable = m_pDoc->getFirstTable();
	QVERIFY2( m_pTable, "No table could be obtained from the ODS document." );
	QVERIFY2( m_pTable->valid(), "Got an invalid table from within the ODS document." );
}

void ModifySave::readOverwriteCelly0x0()
{
	ODSlib::ODScell* pCell = m_pTable->cell(0,0);
	QVERIFY2( pCell, "Expected a cell, got NULL." );
	QVERIFY2( pCell->valid(), "Cell invalid." );
	if ( pCell->value() != 0.0f )
	{
		qDebug() << "\n   Cell: (float value) " << QString::number(pCell->value()).toLatin1().constData();
	}
	QVERIFY2( pCell->value() == 0.0f, "Found an unexpected value in the target cell." );

	pCell->setValue(42.0f);
	QVERIFY2( pCell->value() == 42.0f, "Could not verify a successful write to the cell." );

	ODSlib::ODScell* pCell2 = m_pTable->cell(0,0);
	QVERIFY2( pCell2->value() == 42.0f, "Data not stored permanently in target cell!" );
}

void ModifySave::saveDocument()
{
	QVERIFY2( m_pDoc->save(), "Document counld not be saved!" );
}

void ModifySave::openVerifyDocument()
{
	ODSlib::ODSdocument* pTestDoc = new ODSlib::ODSdocument( m_sPath );
	QVERIFY2( pTestDoc->valid(), "The saved document is not valid anymore afterwards." );

	ODSlib::ODStable* pTable = pTestDoc->getFirstTable();
	QVERIFY2( pTable, "No table could be obtained from the saved ODS document." );
	QVERIFY2( pTable->valid(), "Got an invalid table from within the saved ODS document." );

	ODSlib::ODScell* pCell = pTable->cell(0,0);
	QVERIFY2( pCell, "Expected a cell from saved doc, got NULL." );
	QVERIFY2( pCell->valid(), "Saved cell invalid." );
	QVERIFY2( pCell->value() == 42.0f, "Could not verify the content of the saved cell." );
}
