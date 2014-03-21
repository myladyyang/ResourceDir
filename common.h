#ifndef _COMMON_H__
#define _COMMON_H__

#define GAME_WIDTH 700
#define GAME_HEIGHT 400
#define MOVE_RANGE GAME_WIDTH/5
#define BACKGROUND_WIDTH GAME_WIDTH*2
#define BACKGROUND_HEIGHT GAME_HEIGHT*2
#define GROUND_RATIO 0.25

#define GROUND_CATA_MASK  0x00000001
#define VALKYRIE_CATA_MASK  0x00000001<<1
#define STATIC_OBJ_CATA_MASK  0x00000001<<2
#define INTERACT_OBJ_CATA_MASK  0x00000001<<3
#define RANGE_CATA_MASK  0x00000001<<4

#define GROUND_CONTACT_MASK 0x00000000//don't raise any contact event
#define GROUND_COLLISION_MASK  VALKYRIE_CATA_MASK | STATIC_OBJ_CATA_MASK | INTERACT_OBJ_CATA_MASK

#define VALKYRIE_CONTACT_MASK 0x00000000//no contact needed by now
#define VALKYRIE_COLLISION_MASK  GROUND_CATA_MASK | STATIC_OBJ_CATA_MASK |INTERACT_OBJ_CATA_MASK

#define STATIC_OBJ_CONTACT_MASK 0x00000000
#define STATIC_OBJ_COLLISION_MASK GROUND_CATA_MASK| VALKYRIE_CATA_MASK| INTERACT_OBJ_CATA_MASK


#define INTERACT_OBJ_CONTACT_MASK RANGE_CATA_MASK
#define INTERACT_OBJ_COLLISION_MASK GROUND_CATA_MASK| VALKYRIE_CATA_MASK| INTERACT_OBJ_CATA_MASK

#define RANGE_CONTACT_MASK INTERACT_OBJ_CATA_MASK
#define RANGE_COLLISION_MASK 0x00000000







#endif
