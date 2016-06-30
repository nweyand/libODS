/*
** ODSrepeatable.h
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

#ifndef ODSPROTOTYPEREPEATABLE_H
#define ODSPROTOTYPEREPEATABLE_H

#include <QExplicitlySharedDataPointer>

#include "ODSprototypeXMLfamiliar.h"

namespace ODSlib
{
class ODSprototypeRepeatableData;

/**
 * @brief The ODSprototypeRepeatable class represents content that can be repeated in the ODS
 * document XML structure. Typically, repeatable contents are things like identical consecutive
 * cells and rows which are saved as a single XML entry instead of multiple ones.
 *
 * The best example of this are empty ODS files, where all cells and rows are identical and can
 * therefore be reduced to one single row XML entry containing one single cell XML entry.
 */
class ODSprototypeRepeatable : virtual public ODSprototypeXMLfamiliar
{
protected:
	/**
	 * @brief ODSprototypeContentRepeatable
	 * @param sChildElementFilter The name of child elements to watch for/expect while parsing.
	 * @param sRepeatFilter The element tag associated with the number of repetitions of THIS
	 * element.
	 * @param associatedElement The XML element associated with this node.
	 */
	ODSprototypeRepeatable( const QString &sChildElementFilter, const QString &sRepeatFilter,
	                        QDomElement &associatedElement );

	//ODSprototypeRepeatable(const ODSprototypeRepeatable &);
	//ODSprototypeRepeatable &operator=(const ODSprototypeRepeatable &);

public:
	virtual ~ODSprototypeRepeatable();

	size_t multiplicity() const;

	/**
	 * @brief splitUpRepetition allows to cut up a repeted XML entry so that parts of it can be
	 * edited without impacting the other parts.
	 * @param afterN The number of consecutive repeated items before the item to be cut out of the
	 * repetition.
	 * @return The now editable item that was cut out.
	 */
	ODSprototypeRepeatable *splitUpRepetition(size_t afterN);

protected:
	//virtual ODSprototypeRepeatable *clone() = 0;
	void doDetach();

	QExplicitlySharedDataPointer<ODSprototypeRepeatableData> m_pPRData;

private:
	/**
	 * @brief setMultiplicity Correctly sets the multiplicity both in this item and its asscoiated
	 * XML entry.
	 * @param multiplicity The number of consecutive repetitions of this item to be set.
	 */
	void setMultiplicity(const size_t &multiplicity);
};

} // namespace ODSlib

#endif // ODSPROTOTYPEREPEATABLE_H
