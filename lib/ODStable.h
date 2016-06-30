/*
** ODStable.h
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

#ifndef ODSTABLE_H
#define ODSTABLE_H

#include <QExplicitlySharedDataPointer>

#include "ODSprototypeContentRepeatable.h"

namespace ODSlib
{
class ODScell;
class ODStableData;
class ODSelementFactory;

class ODStable : public ODSprototypeContentRepeatable
{
	friend class ODSelementFactory;

private:
	ODStable(QDomElement &element);
	//ODStable(const ODStable &);
	//ODStable &operator=(const ODStable &);

public:
	virtual ~ODStable();

protected:
	virtual void parse();
	void doDetach();

public:
	const QString& name() const;
	void setName(const QString &name);

	static QString coordinatesToString(st y, st x);
	static void stringToCoordinates(QString s, st &y, st &x);

	// TODO: Implement differentiated read/write access
	ODScell *cell(QString pos);
	ODScell *cell(st y, st x);

protected:
	QExplicitlySharedDataPointer<ODStableData> m_pTableData;

private:
	static QString coordinatesToString(st x, QString s = QString());
};

} // namespace ODSlib

#endif // ODSTABLE_H
