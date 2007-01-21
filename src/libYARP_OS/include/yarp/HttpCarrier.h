// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2006 Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the GNU GPL v2.0.
 *
 */

#ifndef _YARP2_HTTPCARRIER_
#define _YARP2_HTTPCARRIER_

#include <yarp/TcpCarrier.h>
#include <yarp/NameClient.h>
#include <yarp/NetType.h>

namespace yarp {
    class HttpCarrier;
    class HttpTwoWayStream;
}

/**
 * Minimal http connection support.
 * Most useful for connections to YARP ports from browsers.
 * No support for connections in the opposite direction.
 * This carrier is recruited when a port sees a TCP stream that
 * begins with "GET /".  
 *
 * For "GET /", the URL following the "/" is
 * currently translated to text as follows:
 *   "," becomes newline
 *   "+" becomes " "
 * This text is then passed on to the port, just as for a normal
 * text connection.
 * For example
 *   "GET /d,list"
 * is the same as telnetting into a port and typing:
 *   CONNECT anon
 *   d
 *   list
 * or typing "list" to "yarp rpc /portname".
 * The response of the port, if any, is output in ugly html.
 *
 * For "POST /" ... not done yet.
 */
class yarp::HttpTwoWayStream : public TwoWayStream, public OutputStream {
private:
    String proc;
    String part;
    bool data;
    bool filterData;
    TwoWayStream *delegate;
    StringInputStream sis;
    StringOutputStream sos;
public:
    HttpTwoWayStream(TwoWayStream *delegate, const char *txt);

    virtual ~HttpTwoWayStream() {
        if (delegate!=NULL) {
            delete delegate;
            delegate = NULL;
        }
    }

    virtual InputStream& getInputStream() { return sis; }
    virtual OutputStream& getOutputStream() { return *this; }


    virtual const Address& getLocalAddress() {
        return delegate->getLocalAddress();
    }

    virtual const Address& getRemoteAddress() {
        return delegate->getRemoteAddress();
    }

    virtual bool isOk() {
        return delegate->isOk();
    }

    virtual void reset() {
        delegate->reset();
    }

    virtual void write(const Bytes& b) { // throws
        for (int i=0; i<b.length(); i++) {
            apply(b.get()[i]);
        }
    }

    virtual void apply(char ch) {
        if (ch=='\r') { return; }
        if (ch == '\n') {
            proc = "";
            Address addr = NameClient::extractAddress(part);
            if (addr.isValid()) {
                if (addr.getCarrierName()=="tcp") {
                    proc += "<a href=\"http://";
                    proc += addr.getName();
                    proc += ":";
                    proc += NetType::toString(addr.getPort());
                    proc += "\">";
                    proc += part;
                    proc += "</A>\n";
                } else {
                    proc += part;
                    proc += "\n";
                }
            } else {
                proc += part;
                proc += "\n";
            }
            if (data||!filterData) {
                Bytes tmp((char*)proc.c_str(),proc.length());
                delegate->getOutputStream().write(tmp);
                delegate->getOutputStream().flush();
            }
            data = false;
            if (proc[0] == 'd') {
                data = true;
            }
            part = "";
        } else {
            part += ch;
        }
    }

    virtual void close() {
        apply('\n');
        apply('\n');
        delegate->close();
    }

    virtual void beginPacket() {
        delegate->beginPacket();
    }

    virtual void endPacket() {
        delegate->endPacket();
    }
};



/**
 * Communicating via http.
 */
class yarp::HttpCarrier : public TcpCarrier {
private:
    String url, input;
    bool urlDone;
    bool expectPost;
    int contentLength;
public:
    HttpCarrier() {
        url = "";
        input = "";
        urlDone = false;
        expectPost = false;
        contentLength = 0;
    }

    virtual String getName() {
        return "http";
    }

    bool checkHeader(const Bytes& header, const char *prefix) {
        if (header.length()==8) {
            String target = prefix;
            for (unsigned int i=0; i<target.length(); i++) {
                if (!(target[i]==header.get()[i])) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    virtual bool checkHeader(const Bytes& header) {
        bool ok = checkHeader(header,"GET /");
        if (!ok) {
            ok = checkHeader(header,"POST /");
        }
        return ok;
    }

    virtual void setParameters(const Bytes& header) {
        if (header.length()==8) {
            bool adding = false;
            for (unsigned int j=0; j<8; j++) {
                char ch = header.get()[j];
                if (adding) {
                    if (ch!=' ') {
                        url += ch;
                    } else {
                        urlDone = true;
                        break;
                    }
                }
                if (ch=='/') {
                    adding = true;
                }
            }
        }
    }

    virtual void getHeader(const Bytes& header) {
        if (header.length()==8) {
            String target = "GET / HT";
            for (int i=0; i<8; i++) {
                header.get()[i] = target[i];
            }
        }   
    }

    virtual Carrier *create() {
        return new HttpCarrier();
    }

    virtual bool requireAck() {
        return false;
    }

    virtual bool isTextMode() {
        return true;
    }


    virtual bool supportReply() {
        return false;
    }

    virtual void sendHeader(Protocol& proto) {
        printf("not yet meant to work\n");
        String target = "GET / HTTP/1.1";
        Bytes b((char*)target.c_str(),8);
        proto.os().write(b);
        /*
        String target = getSpecifierName();
        Bytes b((char*)target.c_str(),8);
        proto.os().write(b);
        String from = proto.getRoute().getFromName();
        Bytes b2((char*)from.c_str(),from.length());
        proto.os().write(b2);
        proto.os().write('\r');
        proto.os().write('\n');
        proto.os().flush();
        */

    }

    void expectSenderSpecifier(Protocol& proto);

    void expectReplyToHeader(Protocol& proto) {
        // expect and ignore CONTENT lines
        String result = NetType::readLine(proto.is());
    }


    void sendIndex(Protocol& proto) {
        // no index
    }

    void expectIndex(Protocol& proto) {
        // no index
    }

    void sendAck(Protocol& proto) {
        // no acknowledgement
    }

    virtual void expectAck(Protocol& proto) {
        // no acknowledgement
    }

    void respondToHeader(Protocol& proto) {
        HttpTwoWayStream *stream = 
            new HttpTwoWayStream(proto.giveStreams(),input.c_str());
        proto.takeStreams(stream);
    }
};

#endif
