/*
*****************************************************************************************
* Copyright (C) 2010-2013, International Business Machines
* Corporation and others. All Rights Reserved.
*****************************************************************************************
*/

#ifndef UGENDER_H
#define UGENDER_H

#include "unicode/utypes.h"

#if !UCONFIG_NO_FORMATTING
#ifndef U_HIDE_DRAFT_API

#include "unicode/localpointer.h"

/**
 * \file
 * \brief C API: The purpose of this API is to compute the gender of a list as a
 * whole given the gender of each element.
 *
 */

/**
 * Genders
 * @draft ICU 50
 */
enum UGender {
    /**
     * Male gender.
     * @draft ICU 50
     */
    UGENDER_MALE,
    /**
     * Female gender.
     * @draft ICU 50
     */
    UGENDER_FEMALE,
    /**
     * Neutral gender.
     * @draft ICU 50
     */
    UGENDER_OTHER
};
/**
 * @draft ICU 50
 */
typedef enum UGender UGender;

/**
 * Opaque UGenderInfo object for use in C programs.
 * @draft ICU 50
 */
struct UGenderInfo;
typedef struct UGenderInfo UGenderInfo;

/**
 * Opens a new UGenderInfo object given locale.
 * @param locale The locale for which the rules are desired.
 * @return A UGenderInfo for the specified locale, or NULL if an error occurred.
 * @draft ICU 50
 */
U_DRAFT const UGenderInfo* U_EXPORT2
ugender_getInstance(const char *locale, UErrorCode *status);


/**
 * Given a list, returns the gender of the list as a whole.
 * @param genderInfo pointer that ugender_getInstance returns.
 * @param genders the gender of each element in the list.
 * @param size the size of the list.
 * @param status A pointer to a UErrorCode to receive any errors.
 * @return The gender of the list.
 * @draft ICU 50
 */
U_DRAFT UGender U_EXPORT2
ugender_getListGender(const UGenderInfo* genderinfo, const UGender *genders, int32_t size, UErrorCode *status);

#endif /* U_HIDE_DRAFT_API */
#endif /* #if !UCONFIG_NO_FORMATTING */

#endif
