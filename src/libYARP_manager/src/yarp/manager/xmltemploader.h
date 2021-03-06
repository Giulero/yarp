/*
 * Copyright (C) 2006-2021 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef YARP_MANAGER_XMLTEMPLOADER
#define YARP_MANAGER_XMLTEMPLOADER

#include <yarp/manager/ymm-types.h>
#include <yarp/manager/manifestloader.h>
#include <yarp/manager/impl/textparser.h>

namespace yarp {
namespace manager {


/**
 * Class XmlTempLoader
 */
class XmlTempLoader : public TempLoader {

public:
    XmlTempLoader(const char* szFileName);
    XmlTempLoader(const char* szPath, const char* szAppName);
    ~XmlTempLoader() override;
    bool init() override;
    void fini() override;
    void reset() override;
    AppTemplate* getNextAppTemplate() override;

protected:

private:
    std::string strAppName;
    std::string strPath;
    std::string strFileName;
    std::vector<std::string> fileNames;
    TextParser     parser;
    AppTemplate app;
    AppTemplate* parsXml(const char* szFile);
};

} // namespace yarp
} // namespace manager


#endif // __YARP_MANAGER_XMLTEMPLOADER__
