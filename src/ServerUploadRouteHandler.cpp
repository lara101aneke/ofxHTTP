#include "ServerUploadRouteHandler.h"

namespace ofx {
namespace HTTP {
        
        

//------------------------------------------------------------------------------
ServerUploadRouteHandler::ServerUploadRouteHandler(const Settings& _settings)
: BaseServerRouteHandler(_settings)
{

}

//------------------------------------------------------------------------------
ServerUploadRouteHandler::~ServerUploadRouteHandler()
{

}

//------------------------------------------------------------------------------
void ServerUploadRouteHandler::handleRequest(Poco::Net::HTTPServerRequest& request,
                                             Poco::Net::HTTPServerResponse& response)
{

//    if(isValidRequest(request,response,settings.route)) {
//
//        Path dataFolder(ofToDataPath("",true));
//        Path uploadFolder(ofToDataPath(settings.uploadFolder,true));
//        
//        string dataFolderString = dataFolder.toString();
//        string uploadFolderString = uploadFolder.toString();
//        
//        // upload folder validity check
//        if(settings.bRequireUploadFolderInDataFolder &&
//           (uploadFolderString.length() < dataFolderString.length() ||
//            uploadFolderString.substr(0,dataFolderString.length()) != dataFolderString)) {
//               ofLogError("ServerUploadRouteHandler::handleRequest") << "Upload folder is not a sub directory of the data folder.";
//               response.setStatusAndReason(HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
//               sendErrorResponse(response);
//               return;
//        }
//
//        HTMLForm form(request, request.stream(), *this);
//        
//        if(!settings.uploadRedirect.empty()) {
//            response.redirect(settings.uploadRedirect);
//        } else {
//            response.setStatusAndReason(HTTPResponse::HTTP_OK);
//            response.setContentLength(0);
//            response.send();
//        }
//    } else {
//        return; // isValidRequest took care of the response
//    }
}

//------------------------------------------------------------------------------
void ServerUploadRouteHandler::handlePart(const Poco::Net::MessageHeader& header,
                                          std::istream& stream)
{
    //NameValueCollection::ConstIterator iter = header.begin();
    
    //        while(iter != header.end()) {
    //            cout << (*iter).first << "=" << (*iter).second << endl;
    //            ++iter;
    //        }
    //
    
    if(header.has("Content-Type")) {
        std::string contentType = header["Content-Type"];
        if(!isContentTypeValid(contentType)) {
            ofLogError("ServerUploadRouteHandler::handlePart") << "Invalid content type: " << contentType;
            return; // reject
        }
    } else {
        ofLogError("ServerUploadRouteHandler::handlePart") << "No Content-Type header.";
        return;
    }
    
    // is this an uploaded file?
    if(header.has("Content-Disposition")) {// && header.has("form-data")) {

        std::string contentDisposition = header["Content-Disposition"];
        Poco::Net::NameValueCollection parameters;
        Poco::Net::MessageHeader::splitParameters(contentDisposition.begin(),contentDisposition.end(),parameters);
        
        if(parameters.has("filename")) {

            try {
                ofFile file(_settings.uploadFolder + "/" + parameters["filename"], ofFile::WriteOnly);

                cout << file.getAbsolutePath() << endl;
                
                std::streamsize sz = Poco::StreamCopier::copyStream(stream,file,_settings.writeBufferSize);
                
                cout << sz << endl;
                
                // The section below is from StreamCopier::copyStream,
                // and can be used for upload progress feedback
                //                int bufferSize = 8192;
                //                Buffer<char> buffer(bufferSize);
                //                streamsize len = 0;
                //                stream.read(buffer.begin(), bufferSize);
                //                streamsize n = stream.gcount();
                //                while (n > 0) {
                //                    len += n;
                //                    file.write(buffer.begin(), n);
                //                    if (stream && file) {
                //                        stream.read(buffer.begin(), bufferSize);
                //                        n = stream.gcount();
                //                        cout << n << endl;
                //                    }
                //                    else n = 0;
                //                }
                
                file.close();
                
            } catch(const Poco::Exception& exc) {
                ofLogError("ServerUploadRouteHandler::handlePart") << exc.displayText();
            } catch(const std::exception& exc) {
                ofLogError("ServerUploadRouteHandler::handlePart") << exc.what();
            } catch(...) {
                ofLogError("ServerUploadRouteHandler::handlePart") << "Uncaught thread exception: Unknown exception.";
            }
            
        } else {
            // error
        }
    }
    
}

//------------------------------------------------------------------------------
bool ServerUploadRouteHandler::isContentTypeValid(const std::string& contentType) const {
    // default true
    return true;
}


} }