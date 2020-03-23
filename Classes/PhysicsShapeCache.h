#ifndef __PhysicsShapeCache_h__
#define __PhysicsShapeCache_h__
#include "cocos2d.h"

USING_NS_CC;


class PhysicsShapeCache
{
public:

	/**
	* Get pointer to the PhysicsShapeCache singleton instance
	*
	* @return PhysicsShapeCache*
	*/
	static PhysicsShapeCache *getInstance();

	/**
	* Adds all physics shapes from a plist file.
	* Shapes are scaled by contentScaleFactor
	*
	* @param plist name of the shape definitions file to load
	*
	* @retval true if ok
	* @retval false on error
	*/
	bool addShapesWithFile(const std::string &plist);

	/**
	* Adds all physics shapes from a plist file.
	*
	* @param plist name of the shape definitions file to load
	* @param scaleFactor scale factor to apply for all shapes
	*
	* @retval true if ok
	* @retval false on error
	*/
	bool addShapesWithFile(const std::string &plist, float scaleFactor);

	/**
	* Removes all shapes loaded from the given file
	*
	* @param plist name of the body definitions file
	*/
	void removeShapesWithFile(const std::string &plist);

	/**
	* Removes all shapes
	*/
	void removeAllShapes();

	/**
	* Creates a PhysicsBody with the given name
	*
	* @param name name of the body to create
	*
	* @return new PhysicsBody
	* @retval nullptr if body is not found
	*/
	PhysicsBody *createBodyWithName(const std::string &name);

	/**
	* Creates a new PhysicsBody and attaches it to the given sprite
	*
	* @param name name of the body to attach
	* @param sprite sprite to attach the body to
	*
	* @retval true if body was attached to the sprite
	* @retval false if body was not found
	*/
	bool setBodyOnSprite(const std::string &name, Sprite *sprite);

private:
	typedef enum
	{
		FIXTURE_POLYGON,
		FIXTURE_CIRCLE
	} FixtureType;


	class Polygon
	{
	public:
		Point* vertices;
		int numVertices;
	};


	class FixtureData
	{
	public:
		FixtureType fixtureType;

		float density;
		float restitution;
		float friction;

		int tag;
		int group;
		int categoryMask;
		int collisionMask;
		int contactTestMask;

		// for circles
		Point center;
		float radius;


		std::vector<Polygon *> polygons;
	};


	class BodyDef
	{
	public:
		Point anchorPoint;
		std::vector<FixtureData *> fixtures;

		bool isDynamic;
		bool affectedByGravity;
		bool allowsRotation;

		float linearDamping;
		float angularDamping;
		float velocityLimit;
		float angularVelocityLimit;
	};

	PhysicsShapeCache();
	~PhysicsShapeCache();
	void safeDeleteBodyDef(BodyDef *bodyDef);
	BodyDef *getBodyDef(const std::string &name);
	void setBodyProperties(PhysicsBody *body, BodyDef *bd);
	void setShapeProperties(PhysicsShape *shape, FixtureData *fd);

	std::map<std::string, BodyDef *> bodyDefs;
	std::map<std::string, std::vector<BodyDef *>> bodiesInFile;
};


#endif // __PhysicsShapeCache_h