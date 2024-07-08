// INTEL CONFIDENTIAL
// Copyright (C) 2012-2023 Intel Corporation
//
// This software and the related documents are Intel copyrighted materials, and
// your use of them is governed by the express license under which they were
// provided to you ("License"). Unless the License provides otherwise, you may
// not use, modify, copy, publish, distribute, disclose or transmit this software or
// the related documents without Intel's prior written permission.
//
// This software and the related documents are provided as is, with no express
// or implied warranties, other than those that are expressly stated in the
// License.

#ifndef SAMPLETESTMETHOD_API_H
#define SAMPLETESTMETHOD_API_H

#ifndef CommonTestMethod_EXPORTS
#define CommonTestMethod_EXPORTS

#ifdef SAMPLETESTMETHOD_STATIC_DEFINE
#  define SAMPLETESTMETHOD_API
#  define SAMPLETESTMETHOD_NO_EXPORT
#else
#  ifndef SAMPLETESTMETHOD_API
#    ifdef CommonTestMethod_EXPORTS
/* We are building this library */
#      define SAMPLETESTMETHOD_API __declspec(dllexport)
#    else
/* We are using this library */
#      define SAMPLETESTMETHOD_API __declspec(dllimport)
#    endif
#  endif

#  ifndef SAMPLETESTMETHOD_NO_EXPORT
#    define SAMPLETESTMETHOD_NO_EXPORT
#  endif
#endif

#ifndef SAMPLETESTMETHOD_DEPRECATED
#  define SAMPLETESTMETHOD_DEPRECATED __declspec(deprecated)
#endif

#ifndef SAMPLETESTMETHOD_DEPRECATED_EXPORT
#  define SAMPLETESTMETHOD_DEPRECATED_EXPORT SAMPLETESTMETHOD_API SAMPLETESTMETHOD_DEPRECATED
#endif

#ifndef SAMPLETESTMETHOD_DEPRECATED_NO_EXPORT
#  define SAMPLETESTMETHOD_DEPRECATED_NO_EXPORT SAMPLETESTMETHOD_NO_EXPORT SAMPLETESTMETHOD_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef SAMPLETESTMETHOD_NO_DEPRECATED
#    define SAMPLETESTMETHOD_NO_DEPRECATED
#  endif
#endif

#endif /* CommonTestMethod_EXPORTS */
#endif /* SAMPLETESTMETHOD_API_H */
