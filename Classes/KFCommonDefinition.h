﻿#pragma once
#define PI 3.14159265

#define WORLD_WIDTH			4032
#define WORLD_HEIGHT		2268
#define MAP_SCALE_FACTOR	1.96875f

// Physical body
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

#define FACE_BIT_MASK	0b100000
#define HAMMER_BIT_MASK	0b010000
#define GROUND_BIT_MASK	0b001000
#define EDGE_BIT_MASK	0b000100
#define PROPS_BIT_MASK	0b000010
#define BEE_BIT_MASK	0b000001

#define EDGE_BODY_TAG		1
#define HAMMER_BODY_TAG		2
#define BOTTOM_GROUND_TAG	3

// Map tags & types

#define BLACK_BEE	1
#define YELLOW_BEE	2
#define BLUE_BEE	3
#define RED_BEE		4

