#ifndef GLOBAL_TYPES_H
#define GLOBAL_TYPES_H


typedef unsigned char  		UCHAR8;                  /** defined for unsigned 8-bits integer variable 	    ???8?????       */
typedef signed   char  		SCHAR8;                  /** defined for signed 8-bits integer variable		    ???8?????       */
typedef unsigned short 		USHORT16;                /** defined for unsigned 16-bits integer variable 	    ???16?????      */
typedef signed   short 		SSHORT16;                /** defined for signed 16-bits integer variable 	    ???16?????      */
typedef unsigned int   		UINT32;                  /** defined for unsigned 32-bits integer variable 	    ???32?????      */
typedef int   						SINT32;                  /** defined for signed 32-bits integer variable         ???32?????      */
typedef float          		FP32;                    /** single precision floating point variable (32bits)   ??????(32???) */
typedef double         		DB64;                    /** double precision floating point variable (64bits)   ??????(64???) */

typedef UCHAR8            u8;                      /** defined for unsigned 8-bits integer variable 	        ???8?????  */
typedef USHORT16          u16;                     /** defined for unsigned 16-bits integer variable 	    ???16????? */
typedef UINT32            u32;                     /** defined for unsigned 32-bits integer variable 	    ???32????? */
typedef SCHAR8            s8;                      /** defined for unsigned 8-bits integer variable 	        ???8?????  */
typedef SSHORT16          s16;                     /** defined for unsigned 16-bits integer variable 	    ???16????? */
typedef SINT32            s32;                     /** defined for unsigned 32-bits integer variable 	    ???32????? */

typedef enum {FALSE = 0, TRUE = !FALSE} bool;

typedef struct
{
	float TestFValue1;
	float TestFValue2;
	float TestFValue3;
	float TestFValue4;
	
	int TestIValue1;
	int TestIValue2;
	int TestIValue3;
	int TestIValue4;

	u32 TestUValue1;
	u32 TestUValue2;
	u32 TestUValue3;
	u32 TestUValue4;
	
	bool TestBValue1;
	bool TestBValue2;
	bool TestBValue3;
	bool TestBValue4;
}TESTBOX;



#endif
