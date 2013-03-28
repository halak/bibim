#pragma once
#ifndef __BIBIM_HTTPCLIENT_H__
#define __BIBIM_HTTPCLIENT_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_PLATFORM_IOS))
#       include <Bibim/HttpClient.Null.h>
#   else
#       include <Bibim/HttpClient.Curl.h>
#   endif

#endif