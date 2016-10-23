#include "fmtg.h"
//
// MIDI note number define
// unusually, "C0" stants for lowest MIDI note (0)
// "C5" for "middle C"
//
#define M_REST (-1)
//
#define M_C4  (48)
#define M_Db4 (49)
#define M_D4  (50)
#define M_Eb4 (51)
#define M_E4  (52)
#define M_F4  (53)
#define M_Gb4 (54)
#define M_G4  (55)
#define M_Ab4 (56)
#define M_A4  (57)
#define M_Bb4 (58)
#define M_B4  (59)
//
#define M_C5  (60)
#define M_Db5 (61)
#define M_D5  (62)
#define M_Eb5 (63)
#define M_E5  (64)
#define M_F5  (65)
#define M_Gb5 (66)
#define M_G5  (67)
#define M_Ab5 (68)
#define M_A5  (69)
#define M_Bb5 (70)
#define M_B5  (71)
//
#define M_C6  (72)
#define M_Db6 (73)
#define M_D6  (74)
#define M_Eb6 (75)
#define M_E6  (76)
#define M_F6  (77)
#define M_Gb6 (78)
#define M_G6  (79)
#define M_Ab6 (80)
#define M_A6  (81)
#define M_Bb6 (82)
#define M_B6  (83)
//
// length code define
// suffix "t" means "triplet"
//
#define L_1   (96)
#define L_2   (48)
#define L_2t  (32)
#define L_3   (32)
#define L_4   (24)
#define L_4t  (16)
#define L_6   (16)
#define L_8   (12)
#define L_8t  (8)
#define L_12  (8)
#define L_16  (6)
#define L_16t (4)
#define L_24  (4)
#define L_32  (3)
#define L_32t (2)
#define L_48  (2)
#define L_64t (1)
#define L_96  (1)
//
