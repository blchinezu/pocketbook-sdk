/*
 * libjingle
 * Copyright 2004--2005, Google Inc.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice, 
 *     this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products 
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _SASLPLAINMECHANISM_H_
#define _SASLPLAINMECHANISM_H_

#include "talk/base/cryptstring.h"
#include "talk/xmpp/saslmechanism.h"

namespace buzz {

class SaslPlainMechanism : public SaslMechanism {

public:
  SaslPlainMechanism(const buzz::Jid user_jid, const talk_base::CryptString & password) :
    user_jid_(user_jid), password_(password) {}

  virtual std::string GetMechanismName() { return "PLAIN"; }
    
  virtual XmlElement * StartSaslAuth() {
    // send initial request
    XmlElement * el = new XmlElement(QN_SASL_AUTH, true);
    el->AddAttr(QN_MECHANISM, "PLAIN");

    talk_base::FormatCryptString credential;
    credential.Append("\0", 1);
    credential.Append(user_jid_.node());
    credential.Append("\0", 1);
    credential.Append(&password_);
    el->AddText(Base64EncodeFromArray(credential.GetData(), credential.GetLength()));
    return el;
  }
  
private:
  Jid user_jid_;
  talk_base::CryptString password_;
};

}

#endif
