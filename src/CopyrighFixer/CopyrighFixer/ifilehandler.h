//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef IFILEHANDLER_H
#define IFILEHANDLER_H

#include "CopyrighFixer_global.h"
#include "CopyrighFixer/sign.h"


namespace CopyrighFixer {

/**
 * @brief The Extensinon enum File extensions for signature.
 */
enum Extensinon {
    CPP,
    HPP,
    H,
    CC,
    QML,
    PRO,
    TXT,
    PY,
};

/**
 * @brief The IFileHandler class This is class that handles the source files that need to be signed.
 */
class IFileHandler {
public:

    /**
     * @brief read This is method be read a copyright singnature from a source file.
     * @param pathToFile The source file path.
     * @param objSign The object signature.
     * @return Returns true if the file was read successfully.
     */
    virtual bool read(const QString &pathToFile, Signature &objSign) = 0;

    /**
     * @brief write This is method be write a new copyright signature into file (replace an old signature).
     * @param pathToFile Path to the file in which to replace the signature.
     * @param objSign The object signature.
     * @return Returns true if the signature is valid.
     */
    virtual bool write(const QString &pathToFile, const Signature &objSign) = 0;

    /**
     * @brief supportsExtensions This method contains a list of file extensions that will be checked against the source files.
     * @return Return A set of the supported extensions.
     */
    virtual Extensinon supportsExtensions() = 0;

    virtual ~IFileHandler();
};

};
#endif // IFILEHANDLER_H
