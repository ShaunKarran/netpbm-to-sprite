// Information ----------------------------------------------------------------

/*	Library:		libTeensy20
 *	Purpose:		Bitwise macros
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
*/

#ifndef _BITWISE_H_
#define _BITWISE_H_

// Macros ----------------------------------------------------------------

#define SET_BIT(byte, bit) 		(byte |= (1 << bit))
#define CLR_BIT(byte, bit) 		(byte &= ~(1 << bit))
#define TOG_BIT(byte, bit)		(byte ^= (1 << bit))
#define GET_BIT(byte, bit) 		(byte & (1 << bit))

#endif // _BITWISE_H_
