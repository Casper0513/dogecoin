// Copyright (c) 2011-2013 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_BITCOINUNITS_H
#define BITCOIN_QT_BITCOINUNITS_H

#include "amount.h"

#include <QAbstractListModel>
#include <QString>
#include <QLocale>
<<<<<<< HEAD
=======

// U+2009 THIN SPACE = UTF-8 E2 80 89
#define REAL_THIN_SP_CP 0x2009
#define REAL_THIN_SP_UTF8 "\xE2\x80\x89"
#define REAL_THIN_SP_HTML "&thinsp;"

// U+200A HAIR SPACE = UTF-8 E2 80 8A
#define HAIR_SP_CP 0x200A
#define HAIR_SP_UTF8 "\xE2\x80\x8A"
#define HAIR_SP_HTML "&#8202;"

// U+2006 SIX-PER-EM SPACE = UTF-8 E2 80 86
#define SIXPEREM_SP_CP 0x2006
#define SIXPEREM_SP_UTF8 "\xE2\x80\x86"
#define SIXPEREM_SP_HTML "&#8198;"

// U+2007 FIGURE SPACE = UTF-8 E2 80 87
#define FIGURE_SP_CP 0x2007
#define FIGURE_SP_UTF8 "\xE2\x80\x87"
#define FIGURE_SP_HTML "&#8199;"

// QMessageBox seems to have a bug whereby it doesn't display thin/hair spaces
// correctly.  Workaround is to display a space in a small font.  If you
// change this, please test that it doesn't cause the parent span to start
// wrapping.
#define HTML_HACK_SP "<span style='white-space: nowrap; font-size: 6pt'> </span>"

// Define THIN_SP_* variables to be our preferred type of thin space
#define THIN_SP_CP   REAL_THIN_SP_CP
#define THIN_SP_UTF8 REAL_THIN_SP_UTF8
#define THIN_SP_HTML HTML_HACK_SP
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707

/** Bitcoin unit definitions. Encapsulates parsing and formatting
   and serves as list model for drop-down selection boxes.
*/
class BitcoinUnits: public QAbstractListModel
{
    Q_OBJECT

public:
    explicit BitcoinUnits(QObject *parent);

    /** Bitcoin units.
      @note Source: https://en.bitcoin.it/wiki/Units . Please add only sensible ones
     */
    enum Unit   //Note: preserve positions in order to preserve existing settings
    {
<<<<<<< HEAD
        DOGE,
        //formerly mDOGE
        //formerly uDOGE
        MDOGE = 3,
        kDOGE = 4,
        Koinu = 5
=======
        MBTC,
        kBTC,
        BTC,
        mBTC,
        uBTC
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707
    };

    enum SeparatorStyle
    {
        separatorNever,
        separatorStandard,
        separatorAlways
    };

    //! @name Static API
    //! Unit conversion and formatting
    ///@{

    //! Get list of units, for drop-down box
    static QList<Unit> availableUnits();
    //! Is unit ID valid?
    static bool valid(int unit);
    //! Short name
    static QString name(int unit);
    //! Longer description
    static QString description(int unit);
    //! Number of Satoshis (1e-8) per unit
    static qint64 factor(int unit);
    //! Max amount per unit
    static qint64 maxAmount(int unit);
    //! Number of decimals left
    static int decimals(int unit);
    //! Format as string
<<<<<<< HEAD
    static QString format(int unit, qint64 amount, bool plussign=false, bool trim=true, const QLocale &locale=QLocale());
    //! Format as string (with unit)
    static QString formatWithUnit(int unit, qint64 amount, bool plussign=false, bool trim=true, const QLocale &locale=QLocale());
    //! Parse string to coin amount
    static bool parse(int unit, const QString &value, qint64 *val_out, const QLocale &locale=QLocale());
=======
    static QString format(int unit, const CAmount& amount, bool plussign=false, bool trim=true, const QLocale &locale=QLocale());
    //! Format as string (with unit)
    static QString formatWithUnit(int unit, const CAmount& amount, bool plussign=false, bool trim=true, const QLocale &locale=QLocale());
    static QString formatHtmlWithUnit(int unit, const CAmount& amount, bool plussign=false, bool trim=true, const QLocale &locale=QLocale());
    //! Parse string to coin amount
    static bool parse(int unit, const QString &value, CAmount *val_out, const QLocale &locale=QLocale());
    //! Gets title for amount column including current display unit if optionsModel reference available */
    static QString getAmountColumnTitle(int unit);
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707
    ///@}

    //! @name AbstractListModel implementation
    //! List model for unit drop-down selection box.
    ///@{
    enum RoleIndex {
        /** Unit identifier */
        UnitRole = Qt::UserRole
    };
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    ///@}

    static QString removeSpaces(QString text)
    {
        text.remove(' ');
        text.remove(QChar(THIN_SP_CP));
#if (THIN_SP_CP != REAL_THIN_SP_CP)
        text.remove(QChar(REAL_THIN_SP_CP));
#endif
        return text;
    }

    //! Return maximum number of base units (Satoshis)
    static CAmount maxMoney();

private:
    QList<BitcoinUnits::Unit> unitlist;
};
typedef BitcoinUnits::Unit BitcoinUnit;

#endif // BITCOIN_QT_BITCOINUNITS_H
