#include <box2d/box2d.h>
#include <stdio.h>
int main()
{
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2({0.0, 0.0});
    b2WorldId worldId = b2CreateWorld(&worldDef);

    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = b2Vec2({0.0f, -10.0f});
    b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);
    b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2({0.0f, 4.0f});
    b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);
    b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.3f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

    float timeStep = 1.0f / 60.0f;
    int subStepCount = 16;
    b2Body_SetLinearVelocity(bodyId, b2Vec2(0., -1.));
    for (int i = 0; i < 390; ++i)
    {
        b2World_Step(worldId, timeStep, subStepCount);
        b2Vec2 position = b2Body_GetPosition(bodyId);
        b2Rot rotation = b2Body_GetRotation(bodyId);
        b2Vec2 velocity = b2Body_GetLinearVelocity(bodyId);
        printf("%d x(%4.2f %4.2f) v(%4.2f %4.2f)\n", i, position.x, position.y, velocity.x, velocity.y);
    }
    return 0;
}