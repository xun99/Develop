
/*
 Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004 J�r�me Lecomte
 Copyright (C) 2009 2011 Narinder S Claire

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef INC_EXCEL32_API_H
#define INC_EXCEL32_API_H

/*!
\file EXCEL32_API.h
\brief Defines the EXCEL32_API macro that flags exported classes of the framework.
*/

/*! \defgroup macros Global XLW macros
    Global definitions and quite a few macros which help porting the code to
    different compilers
    @{
*/


//! version hexadecimal number
#define XLW_HEX_VERSION 0x060000f0
//! version string for output lib name
#define XLW_LIB_VERSION "6_0_0"

//! version string
#ifndef NDEBUG
    #define XLW_VERSION "6.0.0f0-debug"
    //    #define XLW_VERSION "5DEV-debug"
#else
    // #define XLW_VERSION "6.0.0f0"
     #define XLW_VERSION "6DEV"
#endif

//! global trace level (may be superseded locally by a greater value)
#define XLW_TRACE_LEVEL 0

//! Place holder for import/export declaration
#if defined (_DLL) && defined(XLW_IMPORTEXPORT)
    #ifdef EXCEL32_EXPORTS
        #define EXCEL32_API __declspec(dllexport)
    #else
        #define EXCEL32_API __declspec(dllimport)
    #endif
#else
    #define EXCEL32_API
#endif

#define EXCEL_EXPORT __declspec(dllexport)

/*! @}  */

#endif

