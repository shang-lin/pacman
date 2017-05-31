/******************************************************************************/
/* RCS file: /www/cvs/pacman/network/NetworkException.h,v                     */
/* Working file: NetworkException.h                                           */
/* head: 1.5                                                                  */
/* branch:                                                                    */
/* locks: strict                                                              */
/* access list:                                                               */
/* symbolic names:                                                            */
/* keyword substitution: kv                                                   */
/* total revisions: 5                                                         */
/* selected revisions: 5                                                      */
/* description:                                                               */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.5                                                               */
/*                                                                            */
/* DATE: 2002/03/15 18:49:25                                                  */
/* CHANGES MADE BY: Philip Nowell                                             */
/*                                                                            */
/* Added comments                                                             */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.4                                                               */
/*                                                                            */
/* DATE: 2002/02/19 18:26:49                                                  */
/* CHANGES MADE BY: Philip Nowell                                             */
/*                                                                            */
/* A few more things (fixed some indentation)                                 */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.3                                                               */
/*                                                                            */
/* DATE: 2002/02/19 18:17:09                                                  */
/* CHANGES MADE BY: Philip Nowell                                             */
/*                                                                            */
/* Finally got Exceptions working.  Now you can toss an NetworkException,     */
/* catch it as an Exception (call it Exception e) and then just call          */
/* cerr << e  to print it out.                                                */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.2                                                               */
/*                                                                            */
/* DATE: 2002/02/19 15:43:15                                                  */
/* CHANGES MADE BY: Philip Nowell                                             */
/*                                                                            */
/* Fixed bugs I should have fixed before I committed last time.               */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.1                                                               */
/*                                                                            */
/* DATE: 2002/02/19 15:21:20                                                  */
/* CHANGES MADE BY: Philip Nowell                                             */
/*                                                                            */
/* Updated TCP to throw Exceptions, and put exceptions in NetworkException.h  */
/*                                                                            */
/******************************************************************************/


#ifndef _NETWORKEXCEPTION_H_
#define _NETWORKEXCEPTION_H_

#include "Exception.h"

/**
 * This is the parent class for all exceptions dealing with
 * network problems.
 **/
class NetworkException : public Exception{
  public:
  NetworkException();
  NetworkException(const char* desc);
  NetworkException(string desc);
};

/**
 * This is the exception thrown when bind() returns an error
 **/
class BindException : public NetworkException{
  public:
  BindException();
  BindException(const char* desc);
  BindException(string desc);
};

/**
 * This is the exception thrown when connect() returns an error
 **/
class ConnectException : public NetworkException{
  public:
  ConnectException();
  ConnectException(const char* desc);
  ConnectException(string desc);
};

/**
 * This is the exception thrown when socket() returns an error
 **/
class SocketException : public NetworkException{
  public:
  SocketException();
  SocketException(const char* desc);
  SocketException(string desc);
};

/**
 * This is thrown when writing to a socket returns an error
 **/
class SocketIOException : public NetworkException{
  public:
  SocketIOException();
  SocketIOException(const char* desc);
  SocketIOException(string desc);
};

/**
 * This is thrown when a hostname fails to be resolved
 **/
class UnknownHostException : public NetworkException{
  public:
  UnknownHostException();
  UnknownHostException(const char* desc);
  UnknownHostException(string desc);
};

/**
 * This is thrown when an RUDP header is malformed
 **/
class ProtocolException : public NetworkException{
  public:
  ProtocolException();
  ProtocolException(const char* desc);
  ProtocolException(string desc);
};

#endif
