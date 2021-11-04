/*++

Copyright (c) 2013 Minoca Corp.

This project is dual licensed. You are receiving it under the terms of the
GNU General Public License version 3 (GPLv3). Alternative licensing terms are
available. Contact info@minocacorp.com for details. See the LICENSE file at the
root of this project for complete licensing information.

Module Name:

    stubs.c

Abstract:

    This module implements basic runtime library stubs for system-level
    functions in the build environment.

Author:

    Evan Green 23-Oct-2013

Environment:

    Build

--*/

//
// ------------------------------------------------------------------- Includes
//

#include "rtlp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// ---------------------------------------------------------------- Definitions
//

//
// ------------------------------------------------------ Data Type Definitions
//

//
// ----------------------------------------------- Internal Function Prototypes
//

//
// -------------------------------------------------------------------- Globals
//

//
// ------------------------------------------------------------------ Functions
//

RTL_API
VOID
RtlRaiseAssertion (
    PCSTR Expression,
    PCSTR SourceFile,
    ULONG SourceLine
    )

/*++

Routine Description:

    This routine is a stub for the callouts to the rtl library from the mm
    library. Actually it effectively implements RtlRaiseAssertion.

Arguments:

    Expression - Supplies the string containing the expression that failed.

    SourceFile - Supplies the string describing the source file of the failure.

    SourceLine - Supplies the source line number of the failure.

Return Value:

    None.

--*/

{

    fprintf(stderr,
            "\n *** Assertion Failure: %s\n *** File: %s, Line %d\n",
            Expression,
            SourceFile,
            SourceLine);

    abort();
    return;
}

RTL_API
VOID
RtlDebugPrint (
    PCSTR Format,
    ...
    )

/*++

Routine Description:

    This routine is a stub for the debugger print routines.

Arguments:

    Format - Supplies the printf-style format string to print. The contents of
        this string determine the rest of the arguments passed.

    ... - Supplies any arguments needed to convert the Format string.

Return Value:

    None.

--*/

{

    va_list Arguments;

    va_start(Arguments, Format);
    vprintf(Format, Arguments);
    va_end(Arguments);
    return;
}

VOID
RtlpGetDoubleArgument (
    BOOL LongDouble,
    va_list *ArgumentList,
    PDOUBLE_PARTS DoubleParts
    )

/*++

Routine Description:

    This routine gets a double from the argument list. It is used by printf,
    and is a separate function so that floating point support can be shaved out
    of the library.

Arguments:

    LongDouble - Supplies a boolean indicating if the argument is a long double
        or just a regular double.

    ArgumentList - Supplies a pointer to the VA argument list. It's a pointer
        so that the effect of the va_arg can be felt by the calling function.

    DoubleParts - Supplies a pointer where the double is returned, disguised in
        a structure so as not to force floating point arguments.

Return Value:

    None.

--*/

{

    DoubleParts->Ulonglong = (ULONGLONG)DOUBLE_NAN_EXPONENT <<
                             DOUBLE_EXPONENT_SHIFT;

    return;
}

BOOL
RtlpPrintDouble (
    PPRINT_FORMAT_CONTEXT Context,
    double Value,
    PPRINT_FORMAT_PROPERTIES Properties
    )

/*++

Routine Description:

    This routine prints a double to the destination given the style
    properties.

Arguments:

    Context - Supplies a pointer to the initialized context structure.

    DestinationSize - Supplies the size of the destination buffer. If NULL was
        passed as the Destination argument, then this argument is ignored.

    Value - Supplies a pointer to the value to convert to a string.

    Properties - Supplies the style characteristics to use when printing this
        integer.

Return Value:

    TRUE on success.

    FALSE on failure.

--*/

{

    ASSERT(FALSE);

    return FALSE;
}

RTL_API
ULONG
RtlAtomicExchange32 (
    volatile ULONG *Address,
    ULONG ExchangeValue
    )
{
    volatile ULONG ret = *Address;
    *Address = ExchangeValue;
    return ret;
}

RTL_API
PVOID
RtlCopyMemory (
    PVOID Destination,
    PCVOID Source,
    UINTN ByteCount
    )
{
    return memcpy (Destination, Source, ByteCount);
}

RTL_API
VOID
RtlZeroMemory (
    PVOID Buffer,
    UINTN ByteCount
    )
{
    memset (Buffer, 0, ByteCount);
}

//
// --------------------------------------------------------- Internal Functions
//

