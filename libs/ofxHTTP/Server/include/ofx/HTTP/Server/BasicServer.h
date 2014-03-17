// =============================================================================
//
// Copyright (c) 2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#pragma once


#include "ofx/HTTP/Server/BaseServer.h"
#include "ofx/HTTP/Server/FileSystemRoute.h"
#include "ofx/HTTP/Server/FileSystemRouteSettings.h"


namespace ofx {
namespace HTTP {


class BasicServerSettings:
    public FileSystemRouteSettings,
    public BaseServerSettings
{
};

class BasicServer: public BaseServer_<BasicServerSettings>
{
public:
    typedef std::shared_ptr<BasicServer> SharedPtr;
        ///< \brief A typedef for a shared pointer.

    typedef BasicServerSettings Settings;
        ///< \brief A typedef for the BasicServerSettings.


    BasicServer(const Settings& settings = Settings());
        ///< \brief Create a BasicServer with the provided Settings.
        ///< \param settings The Settings used to configure the server.

    virtual ~BasicServer();
        ///< \brief Destroy the BasicServer.

    static SharedPtr makeShared(const Settings& settings = Settings())
        ///< \brief Construct a shared pointer to this server.
        ///< \param settings The Settings used to configure the server.
        ///< \note This will be replaced with C++11 (std::make_shared<...>).
    {
        return SharedPtr(new BasicServer(settings));
    }

private:
    FileSystemRoute::SharedPtr _fileSystemRoute;
        ///< \brief The FileSystemRoute attached to this server.

};


} } // namespace ofx::HTTP