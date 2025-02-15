/******************************************************************************
 * Targoman: A robust Machine Translation framework               *
 *                                                                            *
 * Copyright 2014-2018 by ITRC <http://itrc.ac.ir>                            *
 *                                                                            *
 * This file is part of Targoman.                                             *
 *                                                                            *
 * Targoman is free software: you can redistribute it and/or modify           *
 * it under the terms of the GNU Lesser General Public License as published   *
 * by the Free Software Foundation, either version 3 of the License, or       *
 * (at your option) any later version.                                        *
 *                                                                            *
 * Targoman is distributed in the hope that it will be useful,                *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU Lesser General Public License for more details.                        *
 * You should have received a copy of the GNU Lesser General Public License   *
 * along with Targoman. If not, see <http://www.gnu.org/licenses/>.           *
 *                                                                            *
 ******************************************************************************/
/**
 * @author S. Mohammad M. Ziabary <ziabary@targoman.com>
 */

#ifndef TARGOMAN_APPS_APPE4MT_H
#define TARGOMAN_APPS_APPE4MT_H

#include "libTargomanCommon/clsSafeCoreApplication.h"
#include "libTargomanCommon/CmdIO.h"
#include "libTargomanCommon/Configuration/intfRPCExporter.hpp"
#include "libTargomanCommon/JSONConversationProtocol.h"
#include "clsFormalityChecker.h"
#include "libTargomanTextProcessor/TextProcessor.h"



namespace Targoman {
namespace Apps {

class appE4MT : public Common::Configuration::intfRPCExporter
{
    Q_OBJECT
public:
    appE4MT(){
        this->exportMyRPCs();
    }


public slots:
    void slotExecute();

private slots:
    void slotValidateAgent(INOUT QString&        _user,
                          const QString&        _pass,
                          const QString&        _ip,
                          OUTPUT bool&          _canView,
                          OUTPUT bool&          _canChange);

    void slotPong(QString _ssid, Targoman::Common::stuPong& _pong);

private slots:
    Common::Configuration::stuRPCOutput rpcNormalize(const QVariantMap&_args);
    Common::Configuration::stuRPCOutput rpcText2IXML(const QVariantMap&);
    Common::Configuration::stuRPCOutput rpcIXML2Text(const QVariantMap&);
    Common::Configuration::stuRPCOutput rpcTokenize(const QVariantMap&);
    Common::Configuration::stuRPCOutput rpcPreprocessText(const QVariantMap &_args);

private:
    void processDir(const QString& _dir, const QString &_basePath);
    void processFile(const QString &_inputFile, const QString& _outFile);
    QStringList retrieveFileItems(const QString& _filePath);
    std::tuple<bool, QString> text2Ixml_Helper(const QVariantList &_temovalItems,
                            bool _useSpellCorrector, QString _language, QString _text,
                            bool _putXmlTagsInSeperateList,
                            QVariantList* _lstXmlTags,
                            bool _setTagValue,
                            bool _convertToLower,
                            bool _detectSymbols,
                            bool _setTagIndex);

private:
    QScopedPointer<clsFormalityChecker> FormalityChecker;
};

}
}
#endif // TARGOMAN_APPS_APPE4MT_H
