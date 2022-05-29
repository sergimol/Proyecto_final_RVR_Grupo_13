#ifndef ECS_DEFS_H_
#define ECS_DEFS_H_

// components -- forward declaration, i.e., assume they are defined somewhere
class Transform;
class Image;
class FramedImage;
class State;
class GameCtrl;
class GameManager;


#define _CMPS_LIST_  \
	Transform,\
	Image,\
	FramedImage, \
	State, \
	GameCtrl, \
	GameManager

// groups
struct Asteroid_grp;
struct Bullet_grp;
#define _GRPS_LIST_  Asteroid_grp, \
	Bullet_grp

// handlers
struct Player_hdlr;
struct Manager_hdlr;
#define _HDLRS_LIST_ Player_hdlr, \
	Manager_hdlr

#endif