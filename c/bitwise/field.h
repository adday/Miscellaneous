#ifndef __FIELD_H__
#define __FIELD_H__

#include <stdbool.h>

/** Get the specified bit from a value.
 *  @param value the source value or bit pattern
 *  @param position the bit position to get (0..31)
 *  @return 1 when the bit is set, and 0 otherwise.
 */
int getBit (int value, int position);

/** Set the specified bit in a value to 1.
 *  @param value the source value or bit pattern
 *  @param position the bit position to be set (0..31)
 *  @return An integer value that is the original value with the bit set to 1.
 */
int setBit (int value, int position);

/** Set the specified bit in a value to 0.
 *  @param value the source value or bit pattern
 *  @param position the bit position to be set (0..31)
 *  @return An integer value that is the original value with the bit set to 0.
 */
int clearBit (int value, int position);

/** Extract the field (possibly signed) between bits hi and lo (inclusive).
 *  @param value  the source value or bit pattern
 *  @param hi the bit position of one end of the field
 *  @param lo the bit position of the other end of the field
 *  @param isSigned false means the field is unsigned, true means the field is signed
 *  @return The value of the field.  Sanity check example: 
 *   if the field is three bits wide and unsigned, the result
 *   will be a value between 0 and 7, regardless of the actual position of the
 *   bits in value. If the value is signed, the result will be between -4 and 3.
 *   Furthermore, if the value is signed, it will be negative <b>only</b> if
 *   the left most bit of the field is 1. In this case, the field must be
 *   sign extended (i.e. make all bits to the left 1).
 */
int getField (int value, int hi, int lo, bool isSigned);

/** Change the bits of oldValue between hi and lo to the newValue,
 * leaving the other bits unchanged.
 * @param oldValue the original value
 * @param hi the bit position of one end of the field
 * @param lo the bit position of the other end of the field
 * @param newValue the new value to put in the field (use lower bits)
 * @return the value after replacing <b>only</b> the hi to low bits 
 *         inclusive by newValue
 */
int setField (int oldValue, int hi, int lo, int newValue);

/** Determine if a value will fit in a specified field
 *  @param value  the source value
 *  @param width the number of bits holding the value
 *  @param isSigned false means the field is unsigned, true means the field is signed
 *  @return zero if the field does NOT fit. Return 1 if the value fits.
 */
int fieldFits (int value, int width, bool isSigned);

#endif
