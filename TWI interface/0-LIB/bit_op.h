//header file for bit math operations for global use:
#ifndef bit_op
#define bit_op

#define SET_BIT(VAR,BIT_NO)	VAR |= ( 1<< (BIT_NO) )
//set value of bit
#define CLR_BIT(VAR,BIT_NO) VAR &= (~(1<< (BIT_NO)))
//clear value of bit
#define TOG_BIT(VAR,BIT_NO) VAR ^= ( 1<< (BIT_NO))
//toggle bit on/off
#define GET_BIT(VAR,BIT_NO) ( (VAR >> (BIT_NO)) &1 )
//get bit information from pin, usually returns u8
#endif
