﻿#pragma once

static const unsigned int WORLD_WIDTH = 4032;
static const unsigned int WORLD_HEIGHT = 2268;
static const float MAP_SCALE_FACTOR = 1.96875f;

// Physical body
static const int FACE_BIT_MASK		= 0b100000000;
static const int HAMMER_BIT_MASK	= 0b010000000;
static const int GROUND_BIT_MASK	= 0b001000000;
static const int EDGE_BIT_MASK		= 0b000100000;
static const int PROPS_BIT_MASK		= 0b000010000;
static const int BEE_BIT_MASK		= 0b000001000;
static const int FIRE_BIT_MASK		= 0b000000100;
static const int WATER_BIT_MASK		= 0b000000010;
static const int CACTUS_BIT_MASK	= 0b000000001;
static const unsigned int  EDGE_BODY_TAG = 1;
static const unsigned int  HAMMER_BODY_TAG = 2;
static const unsigned int  BOTTOM_GROUND_TAG = 3;

// Map tags & types
static const unsigned int  BLACK_BEE = 1;
static const unsigned int  YELLOW_BEE = 2;
static const unsigned int  BLUE_BEE = 3;
static const unsigned int  RED_BEE = 4;

static const unsigned int  YELLOW_FLAG = 1;
static const unsigned int  GREEN_FLAG = 2;
static const unsigned int  RED_FLAG = 3;
static const unsigned int  BLUE_FLAG = 4;




//#define FACE_CATEGORY_MASK		0b100000
//#define BEE_CATEGORY_MASK		0b010000
//#define HAMMER_CATEGORY_MASK	0b001000
//#define EDGE_CATEGORY_MASK		0b000100
//#define PROPS_CATEGORY_MASK		0b000010
//#define GROUND_CATEGORY_MASK	0b000001
//
//#define FACE_COLLISION_MASK		0b011111
//#define HAMMER_COLLISION_MASK	0b101111
//#define GROUND_COLLISION_MASK	0b101111
//#define PROPS_COLLISION_MASK	0b101111
//#define BEE_COLLISION_MASK		0b110100
//#define EDGE_COLLISION_MASK		0b111111