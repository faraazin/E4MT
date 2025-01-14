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

#include "Configs.h"
#include "ISO639.h"
#include "libTargomanTextProcessor/TextProcessor.h"

namespace Targoman {
namespace Apps {

using namespace NLPLibs;
using namespace Common;
using namespace Common::Configuration;

tmplConfigurable<enuAppMode::Type> gConfigs::Mode(
        gConfigs::appConfig("Mode"),
        "Application working mode",
        enuAppMode::Text2IXML,
        ReturnTrueCrossValidator(),
        "m",
        "ApplicationMode",
        "mode",
        enuConfigSource::Arg  |
        enuConfigSource::File);

tmplConfigurable<QString> gConfigs::Language(
        gConfigs::appConfig("Language"),
        "Source text language in ISO639 format",
        "",
        [](const Targoman::Common::Configuration::intfConfigurable& _item,QString& _errorMessage){
            if (ISO639isValid(_item.toVariant().toString().toUtf8().constData()))
               return true;
            _errorMessage = _item.toVariant().toString() + " is not in ISO639 format";
            return false;
        },
        "l",
        "LANGUAGE",
        "lang",
            enuConfigSource::Arg  |
            enuConfigSource::File);

tmplConfigurable<QString> gConfigs::Input(
        gConfigs::appConfig("Input"),
        "One line input which can be plain text or IXML. All other Input/Output configs will be ignored",
        "",
        ReturnTrueCrossValidator(),
        "i",
        "TEXT/IXML",
        "input",
        enuConfigSource::Arg);

tmplConfigurable<FilePath_t>     gConfigs::InputFile(
        gConfigs::appConfig("InputFile"),
        "Input file path to convert. Relative to config file path unless specified as absolute path.",
        "",
        Validators::tmplPathAccessValidator<
        TARGOMAN_PATH_ACCESS(enuPathAccess::File | enuPathAccess::Readable),
        false>,
        "f",
        "FILEPATH",
        "input-file",

            enuConfigSource::Arg  |
            enuConfigSource::File);

tmplConfigurable<double>     gConfigs::Classifier::Threshold(
        gConfigs::appConfig("FastTextThreshold"),
        "Threshold to be used by classifier",
        0.8,
        ReturnTrueCrossValidator(),
        "",
        "",
        "fasttext-threshold",
            enuConfigSource::Arg  |
            enuConfigSource::File);

tmplConfigurable<FilePath_t>     gConfigs::Classifier::ModelPath(
        gConfigs::appConfig("FastTextModelPath"),
        "Directory where FastText models are stored.",
        "",
        Validators::tmplPathAccessValidator<
        TARGOMAN_PATH_ACCESS(enuPathAccess::Dir | enuPathAccess::Readable),
        false>,
        "",
        "",
        "fasttext-models-path",
            enuConfigSource::Arg  |
            enuConfigSource::File);

tmplConfigurable<QString> gConfigs::Classifier::ModelPattern(
        gConfigs::appConfig("FastTextModelPattern"),
        "File pattern for FastText models must have <%LANG%> pattern as language placeholder",
        "fasttext-%LANG%.bin",
        ReturnTrueCrossValidator(),
        "",
        "",
        "fasttext-model-pattrn",
            enuConfigSource::Arg  |
            enuConfigSource::File);

tmplConfigurable<FilePath_t>     gConfigs::InputDir(
        gConfigs::appConfig("InputDir"),
        "Input directory to convert. Relative to config file path unless specified as absolute path.",
        "",
        Validators::tmplPathAccessValidator<
        TARGOMAN_PATH_ACCESS(enuPathAccess::Dir | enuPathAccess::Readable),
        false>,
        "d",
        "PATH",
        "input-dir",
            enuConfigSource::Arg  |
            enuConfigSource::File);

tmplConfigurable<FilePath_t>     gConfigs::OutputPath(
        gConfigs::appConfig("Output"),
        "Output file/directory path to write converted file/files. Defaults to standard output",
        "",
        [] (const intfConfigurable& _item, QString& _errorMessage){
            if (gConfigs::InputDir.value().size())
                return  Validators::tmplPathAccessValidator<
                        TARGOMAN_PATH_ACCESS(enuPathAccess::Dir | enuPathAccess::Writeatble),false>(
                            _item, _errorMessage);
            else if (gConfigs::InputFile.value().size())
                return  Validators::tmplPathAccessValidator<
                        TARGOMAN_PATH_ACCESS(enuPathAccess::File | enuPathAccess::Writeatble), false>(
                            _item, _errorMessage);
            else if (_item.toVariant().toString().isEmpty())
                return true;
            _errorMessage="Invalid output selection for simple input text";
            return false;
        },
        "o",
        "PATH",
        "output",
            enuConfigSource::Arg  |
            enuConfigSource::File);

tmplConfigurable<QWildCard>     gConfigs::IncludePattern(
        gConfigs::appConfig("IncludePattern"),
        "FilePatterns to include when converting (WildCard format)",
        "",
        ReturnTrueCrossValidator(),
        "p",
        "PTRN",
        "pattern",
            enuConfigSource::Arg  |
            enuConfigSource::File);

tmplConfigurable<bool>     gConfigs::Overwrite(
        gConfigs::appConfig("Overwrite"),
        "Overwrite existing files",
        false,
        ReturnTrueCrossValidator(),
        "w",
        "",
        "overwrite",
            enuConfigSource::Arg  |
            enuConfigSource::File);

tmplConfigurable<bool>     gConfigs::Interactive(
        gConfigs::appConfig("Interactive"),
        "Interactive normalization and spell correction",
        false,
        ReturnTrueCrossValidator(),
        "",
        "",
        "interactive",
            enuConfigSource::Arg  |
            enuConfigSource::File);

tmplConfigurable<bool>     gConfigs::NoSpellcorrector(
        gConfigs::appConfig("DontUseSpellcorrector"),
        "Do not use spell corrector",
        false,
        ReturnTrueCrossValidator(),
        "",
        "",
        "no-spellcorrect",
            enuConfigSource::Arg  |
            enuConfigSource::File);


tmplConfigurable<bool>     gConfigs::Recursive(
        gConfigs::appConfig("Recursive"),
        "Recursive directory processing",
        false,
        ReturnTrueCrossValidator(),
        "r",
        "",
        "recursive",
            enuConfigSource::Arg  |
            enuConfigSource::File);


tmplConfigurable<bool>     gConfigs::PlainText(
        gConfigs::appConfig("PlainText"),
        "Assume all files as plain text and ignore file suffix",
        false,
        ReturnTrueCrossValidator(),
        "t",
        "",
        "plaintext",
            enuConfigSource::Arg  |
            enuConfigSource::File);

tmplConfigurable<bool>     gConfigs::BreakLines(
        gConfigs::appConfig("BreakLines"),
        "Breaks to lines after converting to either IXML or tokenized text",
        false,
        ReturnTrueCrossValidator(),
        "n",
        "",
        "breaklines",
            enuConfigSource::Arg  |
            enuConfigSource::File);

tmplConfigurable<bool>     gConfigs::KeepTitles(
        gConfigs::appConfig("KeepTitles"),
        "On XML files keep titles as text",
        false,
        ReturnTrueCrossValidator(),
        "k",
        "",
        "keeptitles",
            enuConfigSource::Arg  |
            enuConfigSource::File);

tmplConfigurable<FilePath_t>     gConfigs::DTDFilePath(
        gConfigs::appConfig("DTDFilePath"),
        "DTD file used to validate XML Files",
        "",
        Validators::tmplPathAccessValidator<
        TARGOMAN_PATH_ACCESS(enuPathAccess::Dir | enuPathAccess::Writeatble),
        false>,
        "",
        "DTD_Path",
        "dtd",
            enuConfigSource::Arg  |
            enuConfigSource::File);

tmplConfigurable<bool>     gConfigs::Text2IXML::SetTagValue(
        gConfigs::appConfig("IXMLTagValue"),
        "Set tag values in Text2IXML converter or not",
        true,
        ReturnTrueCrossValidator(),
        "g",
        "",
        "ixml-tagvalue",
            enuConfigSource::Arg  |
            enuConfigSource::File);

tmplConfigurable<bool>     gConfigs::Text2IXML::SetTagIndex(
        gConfigs::appConfig("IXMLTagIndex"),
        "Set tag index in Text2IXML converter or not",
        false,
        ReturnTrueCrossValidator(),
        "ti",
        "",
        "ixml-tagindex",
            enuConfigSource::Arg  |
            enuConfigSource::File);

tmplConfigurable<bool>     gConfigs::ConvertToLowerCase(
        gConfigs::appConfig("ConvertToLowerCase"),
        "Convert all letters to lower case",
        false,
        ReturnTrueCrossValidator(),
        "lc",
        "",
        "converttolowercase",
            enuConfigSource::Arg  |
            enuConfigSource::File);

tmplConfigurable<bool>     gConfigs::DetectSymbols(
        gConfigs::appConfig("DetectSymbols"),
        "Detect symbols in text2ixml or tokenization",
        true,
        ReturnTrueCrossValidator(),
        "ds",
        "",
        "detectsymbols",
            enuConfigSource::Arg  |
            enuConfigSource::File);

tmplConfigurable<QString> gConfigs::Text2IXML::RemovingTags(
        gConfigs::appConfig("RemovingTags"),
        "Text2IXML Removing Tags (Number,SpecialNumber,Email,URL,Abbreviation,OrderedListItem,Time,Date,Ordinals,Symbol)",
        "",
        [](const Targoman::Common::Configuration::intfConfigurable& _item,QString& _errorMessage){
            
            foreach(const QString& TagVariant, _item.toVariant().toString().split(',')){
                enuTextTags::Type Tag = enuTextTags::toEnum(TagVariant);
                if (Tag == enuTextTags::Unknown)
                {
                    _errorMessage = TagVariant + " tag is not valid";         
                    return true;
                }        
            }
            return true;
        },
        "rt",
        "REMOVINGTAGS",
        "removetags",
            enuConfigSource::Arg  |
            enuConfigSource::File);

}}




/**************************************************************************************************************/
ENUM_CONFIGURABLE_IMPL(Targoman::Apps::enuAppMode)
