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

#ifndef _multiuserchatmodule_h_
#define _multiuserchatmodule_h_

#include "talk/xmpp/module.h"
#include "talk/xmpp/rostermodule.h"

namespace buzz {

// forward declarations
class XmppChatroomModule;
class XmppChatroomHandler;
class XmppChatroomMember;
class XmppChatroomMemberEnumerator;

enum XmppChatroomState {
  XMPP_CHATROOM_STATE_NOT_IN_ROOM      = 0,
  XMPP_CHATROOM_STATE_REQUESTED_ENTER  = 1,
  XMPP_CHATROOM_STATE_IN_ROOM          = 2,
  XMPP_CHATROOM_STATE_REQUESTED_EXIT   = 3,
};

//! Module that encapsulates a chatroom. 
class XmppChatroomModule : public XmppModule {
public:

  //! Creates a new XmppChatroomModule
  static XmppChatroomModule* Create();
  virtual ~XmppChatroomModule() {}

  //! Sets the chatroom handler (callbacks) for the chatroom
  virtual XmppReturnStatus set_chatroom_handler(XmppChatroomHandler* handler) = 0;

  //! Gets the chatroom handler for the module
  virtual XmppChatroomHandler* chatroom_handler() = 0;

  //! Sets the jid of the chatroom.
  //! Has to be set before entering the chatroom and can't be changed
  //! while in the chatroom
  virtual XmppReturnStatus set_chatroom_jid(const Jid& chatroom_jid) = 0;

  //! The jid for the chatroom
  virtual const Jid& chatroom_jid() const = 0;

  //! Sets the nickname of the member
  //! Has to be set before entering the chatroom and can't be changed
  //! while in the chatroom
  virtual XmppReturnStatus set_nickname(const std::string& nickname) = 0;

  //! The nickname of the member in the chatroom
  virtual const std::string& nickname() const = 0;

  //! Returns the jid of the member (this is the chatroom_jid plus the
  //! nickname as the resource name)
  virtual const Jid member_jid() const = 0;

  //! Requests that the user enter a chatroom
  //! The EnterChatroom callback will be called when the request is complete.
  //! Password should be empty for a room that doesn't require a password
  //! If the room doesn't exist, the server will create an "Instant Room" if the 
  //! server policy supports this action.
  //! There will be different methods for creating/configuring a "Reserved Room"
  //! Async callback for this method is ChatroomEnteredStatus
  virtual XmppReturnStatus RequestEnterChatroom(const std::string& password) = 0;

  //! Requests that the user exit a chatroom
  //! Async callback for this method is ChatroomExitedStatus
  virtual XmppReturnStatus RequestExitChatroom() = 0;

  //! Requests a status change
  //! status is the standard XMPP status code
  //! extended_status is the extended status when status is XMPP_PRESENCE_XA
  virtual XmppReturnStatus RequestStatusChange(XmppPresenceShow status, 
                                               const std::string& extended_status) = 0;

  //! Returns the number of members in the room
  virtual size_t GetChatroomMemberCount() = 0;

  //! Gets an enumerator for the members in the chatroom
  //! The caller must delete the enumerator when the caller is finished with it. 
  //! The caller must also ensure that the lifetime of the enumerator is 
  //! scoped by the XmppChatRoomModule that created it.
  virtual XmppReturnStatus CreateMemberEnumerator(XmppChatroomMemberEnumerator** enumerator) = 0;

  //! Gets the subject of the chatroom
  virtual const std::string& subject() = 0;

  //! Returns the current state of the user with respect to the chatroom
  virtual XmppChatroomState state() = 0;

  virtual XmppReturnStatus SendMessage(const XmlElement& message) = 0;
};

//! Class for enumerating participatns
class XmppChatroomMemberEnumerator {
public:
  virtual ~XmppChatroomMemberEnumerator() { }
  //! Returns the member at the current position
  //! Returns null if the enumerator is before the beginning
  //! or after the end of the collection
  virtual XmppChatroomMember* current() = 0;

  //! Returns whether the enumerator is valid
  //! This returns true if the collection has changed
  //! since the enumerator was created
  virtual bool IsValid() = 0;

  //! Returns whether the enumerator is before the beginning
  //! This is the initial state of the enumerator
  virtual bool IsBeforeBeginning() = 0;

  //! Returns whether the enumerator is after the end
  virtual bool IsAfterEnd() = 0;

  //! Advances the enumerator to the next position
  //! Returns false is the enumerator is advanced
  //! off the end of the collection
  virtual bool Next() = 0;

  //! Advances the enumerator to the previous position
  //! Returns false is the enumerator is advanced
  //! off the end of the collection
  virtual bool Prev() = 0;
};


//! Represents a single member in a chatroom
class XmppChatroomMember {
public:
  virtual ~XmppChatroomMember() { }
    
  //! The jid for the member in the chatroom
  virtual const Jid member_jid() const = 0;

  //! The full jid for the member 
  //! This is only available in non-anonymous rooms.
  //! If the room is anonymous, this returns JID_EMPTY
  virtual const Jid full_jid() const = 0;

   //! Returns the backing presence for this member
  virtual const XmppPresence* presence() const = 0;

  //! The nickname for this member
  virtual const std::string name() const = 0;
};

//! Status codes for ChatroomEnteredStatus callback
enum XmppChatroomEnteredStatus
{
  //! User successfully entered the room
  XMPP_CHATROOM_ENTERED_SUCCESS                    = 0,
  //! The nickname confliced with somebody already in the room
  XMPP_CHATROOM_ENTERED_FAILURE_NICKNAME_CONFLICT  = 1,
  //! A password is required to enter the room
  XMPP_CHATROOM_ENTERED_FAILURE_PASSWORD_REQUIRED  = 2,
  //! The specified password was incorrect
  XMPP_CHATROOM_ENTERED_FAILURE_PASSWORD_INCORRECT = 3,
  //! The user is not a member of a member-only room
  XMPP_CHATROOM_ENTERED_FAILURE_NOT_A_MEMBER       = 4,
  //! The user cannot enter because the user has been banned
  XMPP_CHATROOM_ENTERED_FAILURE_MEMBER_BANNED      = 5,
  //! The room has the maximum number of users already
  XMPP_CHATROOM_ENTERED_FAILURE_MAX_USERS          = 6,
  //! The room has been locked by an administrator
  XMPP_CHATROOM_ENTERED_FAILURE_ROOM_LOCKED        = 7,
  //! Some other reason
  XMPP_CHATROOM_ENTERED_FAILURE_UNSPECIFIED        = 2000,
};

//! Status codes for ChatroomExitedStatus callback
enum XmppChatroomExitedStatus
{
  //! The user requested to exit and did so
  XMPP_CHATROOM_EXITED_REQUESTED                   = 0,
  //! The user was banned from the room
  XMPP_CHATROOM_EXITED_BANNED                      = 1,
  //! The user has been kicked out of the room
  XMPP_CHATROOM_EXITED_KICKED                      = 2,
  //! The user has been removed from the room because the
  //! user is no longer a member of a member-only room
  //! or the room has changed to membership-only
  XMPP_CHATROOM_EXITED_NOT_A_MEMBER                = 3,
  //! The system is shutting down
  XMPP_CHATROOM_EXITED_SYSTEM_SHUTDOWN             = 4,
  //! For some other reason
  XMPP_CHATROOM_EXITED_UNSPECIFIED                 = 5,             
};

//! The XmppChatroomHandler is the interface for callbacks from the
//! the chatroom
class XmppChatroomHandler {
public:
  //! Indicates the response to RequestEnterChatroom method
  //! XMPP_CHATROOM_SUCCESS represents success.
  //! Other status codes are for errors
  virtual void ChatroomEnteredStatus(XmppChatroomModule* room,
                                     XmppChatroomEnteredStatus status) = 0;


  //! Indicates that the user has exited the chatroom, either due to 
  //! a call to RequestExitChatroom or for some other reason.
  //! status indicates the reason the user exited
  virtual void ChatroomExitedStatus(XmppChatroomModule* room,
                                    XmppChatroomExitedStatus status) = 0;

  //! Indicates a member entered the room.
  virtual void MemberEntered(XmppChatroomModule* room,
                                  const XmppChatroomMember* entered_member) = 0;

  //! Indicates that a member exited the room.
  virtual void MemberExited(XmppChatroomModule* room,
                              const XmppChatroomMember* exited_member) = 0;

  //! Indicates that the data for the member has changed
  //! (such as the nickname or presence)
  virtual void MemberChanged(XmppChatroomModule* room,
                              size_t index) = 0;

  //! Indicates a new message has been received
  //! message is the message - 
  // $TODO - message should be changed
  //! to a strongly-typed message class that contains info
  //! such as the sender, message bodies, etc.,
  virtual void MessageReceived(XmppChatroomModule* room,
                               const XmlElement& message) = 0;
};


}

#endif

