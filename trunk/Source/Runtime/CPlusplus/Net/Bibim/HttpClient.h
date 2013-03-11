#pragma once
#ifndef __BIBIM_HTTPCLIENT_H__
#define __BIBIM_HTTPCLIENT_H__

#   include <Bibim/Foundation.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       include <Bibim/HttpClient.Windows.h>
#   else
#       include <Bibim/HttpClient.Curl.h>
#   endif

#endif