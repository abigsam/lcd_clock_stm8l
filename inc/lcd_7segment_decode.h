




/* Defines */
#define SEG_MASK_A              ((uint8_t) 1 << 0)
#define SEG_MASK_B              ((uint8_t) 1 << 1)
#define SEG_MASK_C              ((uint8_t) 1 << 2)
#define SEG_MASK_D              ((uint8_t) 1 << 3)
#define SEG_MASK_E              ((uint8_t) 1 << 4)
#define SEG_MASK_F              ((uint8_t) 1 << 5)
#define SEG_MASK_G              ((uint8_t) 1 << 6)

#define SPACE_SIGN              (0U)
#define DEGREES_SIGN            ((uint8_t) ( SEG_MASK_A | SEG_MASK_B | SEG_MASK_F | SEG_MASK_G ) )
#define MINUS_SIGN              ((uint8_t) ( SEG_MASK_G ) )
#define LETTER_SMALL_C          ((uint8_t) ( SEG_MASK_D | SEG_MASK_E | SEG_MASK_G ) )
#define LETTER_SMALL_H          ((uint8_t) ( SEG_MASK_C | SEG_MASK_E | SEG_MASK_F | SEG_MASK_G ) )
#define LETTER_SMALL_U          ((uint8_t) ( SEG_MASK_C | SEG_MASK_D | SEG_MASK_E ) )

//#define CASE_CAPITAL:           case 'A': case 'B'

/* Constants */
const uint8_t NUMBER_MAP[10] = {
    //0
    ( SEG_MASK_A | SEG_MASK_B | SEG_MASK_C | SEG_MASK_D | SEG_MASK_E | SEG_MASK_F ),
    //1
    ( SEG_MASK_B | SEG_MASK_C ),
    //2
    ( SEG_MASK_A | SEG_MASK_B | SEG_MASK_D | SEG_MASK_E | SEG_MASK_G ),
    //3
    ( SEG_MASK_A | SEG_MASK_B | SEG_MASK_C | SEG_MASK_D | SEG_MASK_G ),
    //4
    ( SEG_MASK_B | SEG_MASK_C | SEG_MASK_F | SEG_MASK_G ),
    //5
    ( SEG_MASK_A | SEG_MASK_C | SEG_MASK_D | SEG_MASK_F | SEG_MASK_G ),
    //6
    ( SEG_MASK_A | SEG_MASK_C | SEG_MASK_D | SEG_MASK_E | SEG_MASK_F | SEG_MASK_G ),
    //7
    ( SEG_MASK_A | SEG_MASK_B | SEG_MASK_C ),
    //8
    ( SEG_MASK_A | SEG_MASK_B | SEG_MASK_C | SEG_MASK_D | SEG_MASK_E | SEG_MASK_F | SEG_MASK_G ),
    //9
    ( SEG_MASK_A | SEG_MASK_B | SEG_MASK_C | SEG_MASK_D | SEG_MASK_F | SEG_MASK_G )
};

const uint8_t LETTER_MAP[26] = {
    //A
    ( SEG_MASK_A | SEG_MASK_B | SEG_MASK_C | SEG_MASK_E | SEG_MASK_F | SEG_MASK_G ),
    //B
    ( SEG_MASK_C | SEG_MASK_D | SEG_MASK_E | SEG_MASK_F | SEG_MASK_G ),
    //C
    ( SEG_MASK_A | SEG_MASK_D | SEG_MASK_E | SEG_MASK_F ),
    //D
    ( SEG_MASK_B | SEG_MASK_C | SEG_MASK_D | SEG_MASK_E | SEG_MASK_G ),
    //E
    ( SEG_MASK_A | SEG_MASK_D | SEG_MASK_E | SEG_MASK_F | SEG_MASK_G ),
    //F
    ( SEG_MASK_A | SEG_MASK_E | SEG_MASK_F | SEG_MASK_G ),
    //G
    ( SEG_MASK_D ),
    //H
    ( SEG_MASK_B | SEG_MASK_C | SEG_MASK_E | SEG_MASK_F | SEG_MASK_G ),
    //I
    ( SEG_MASK_E | SEG_MASK_F ),
    //J
    ( SEG_MASK_B | SEG_MASK_C | SEG_MASK_D | SEG_MASK_E ),
    //K
    ( SEG_MASK_D ),
    //L
    ( SEG_MASK_D | SEG_MASK_E | SEG_MASK_F ),
    //M
    ( SEG_MASK_D ),
    //N
    ( SEG_MASK_C | SEG_MASK_E | SEG_MASK_G ),
    //O
    ( SEG_MASK_C | SEG_MASK_D | SEG_MASK_E | SEG_MASK_G ),
    //P
    ( SEG_MASK_A | SEG_MASK_B | SEG_MASK_E | SEG_MASK_F | SEG_MASK_G ),
    //Q
    ( SEG_MASK_D ),
    //R
    ( SEG_MASK_E | SEG_MASK_G ),
    //S
    ( SEG_MASK_A | SEG_MASK_C | SEG_MASK_D | SEG_MASK_F | SEG_MASK_G ),
    //T
    ( SEG_MASK_D | SEG_MASK_E | SEG_MASK_F | SEG_MASK_G ),
    //U
    ( SEG_MASK_B | SEG_MASK_C | SEG_MASK_D | SEG_MASK_E | SEG_MASK_F ),
    //V
    ( SEG_MASK_D ),
    //W
    ( SEG_MASK_D ),
    //X
    ( SEG_MASK_D ),
    //Y
    ( SEG_MASK_B | SEG_MASK_C | SEG_MASK_D | SEG_MASK_F | SEG_MASK_G ),
    //Z
    ( SEG_MASK_D )
};

//EOF