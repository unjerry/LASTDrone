#include <box2d/box2d.h>
#include <stdio.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <core/gmWindow.h>
#include <resource_manager.h>
#include <learnopengl/filesystem.h>
#include <sprite_renderer.h>
#include <math.h>
#define Min(a, b) ((a < b) ? (a) : (b))
GladGLContext *gl;
SpriteRenderer *Rend;
void DRAWPOLY(b2Transform transform, const b2Vec2 *vertices, int vertexCount, float radius, b2HexColor color, void *context)
{
    printf("TRANS (%4.2f,%4.2f) (%4.2f) (%4.2f,%4.2f)\n", vertices[0].x, vertices[0].y, atan2(transform.q.s, transform.q.c), vertices[2].x, vertices[2].y);
    Rend->DrawSprite(ResourceManager::GetTexture("background"), glm::vec3((vertices[0].x + transform.p.x + (1.0 - transform.q.c + transform.q.s) ) / 30, (vertices[0].y + transform.p.y + (1.0 - transform.q.c - transform.q.s) ) / 30, 0.0f), glm::vec2(2. / 30, 2. / 30), atan2(transform.q.s, transform.q.c) * 180.0 / 2 * M_PI);
}
void DRAWSTRING(b2Vec2 p, const char *s, void *context)
{
}
void DrawPolygon(const b2Vec2 *vertices, int vertexCount, b2HexColor color, void *context)
{
    // for (size_t i = 0; i < vertexCount; i++)
    // {
    //     printf("%lf,%lf\n", vertices[i].x, vertices[i].y);
    // }
    // printf("\n");
    Rend->DrawSprite(ResourceManager::GetTexture("particle"), glm::vec3(vertices[0].x / 30, vertices[0].y / 30, 0.0f), glm::vec2((vertices[2].x - vertices[0].x) / 30, (vertices[2].y - vertices[0].y) / 30), 0.0f);
}
void DrawCircle(b2Vec2 center, float radius, b2HexColor color, void *context)
{
    Rend->DrawSprite(ResourceManager::GetTexture("background"), glm::vec3(center.x / 30, center.y / 30, 0.0f), glm::vec2(2 * radius / 30, 2 * radius / 30), 0.0f, glm::vec3(1.0, 0.0, 0.0));
}
void DrawSolidCircle(b2Transform transform, float radius, b2HexColor color, void *context)
{
    b2Vec2 center = transform.p;
    Rend->DrawSprite(ResourceManager::GetTexture("background"), glm::vec3(center.x / 30, center.y / 30, 0.0f), glm::vec2(2 * radius / 30, 2 * radius / 30), 0.0f, glm::vec3(1.0, 0.0, 0.0));
}
void DrawSolidCapsule(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color, void *context)
{
}
void DrawSegment(b2Vec2 p1, b2Vec2 p2, b2HexColor color, void *context)
{
    Rend->DrawSprite(ResourceManager::GetTexture("background"), glm::vec3(Min(p1.x, p2.x) / 30, Min(p1.y, p2.y) / 30, 0.0f), glm::vec2(abs(p1.x - p2.x) / 30, abs(p1.y - p2.y) / 30), 0.0f, glm::vec3(1.0, 0.0, 0.0));
}
void DrawTransform(b2Transform transform, void *context)
{
}
void DrawPoint(b2Vec2 p, float size, b2HexColor color, void *context)
{
}
int main()
{
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2({0.0, -10.0});
    b2WorldId worldId = b2CreateWorld(&worldDef);

    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = b2Vec2({0.0f, -10.0f});
    b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);
    b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2({0.0f, 20.0f});
    b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);
    b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.3f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

    b2Body_SetLinearVelocity(bodyId, b2Vec2(10., 0.));

    gmWindow::gmWindowSpecification spec(800, 600, "BreakOut");
    gmWindow::gmWindow WINDW(spec);
    GLFWwindow *window = WINDW.getWindow();
    gl = WINDW.getGl();

    // GLFWimage images[1];
    // images[0].pixels = stbi_load(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), &images[0].width, &images[0].height, 0, 4); // rgba channels
    // glfwSetWindowIcon(window, 1, images);
    // stbi_image_free(images[0].pixels);
    // OpenGL configuration
    // --------------------
    gl->Viewport(0, 0, 800, 600);
    // gl->Enable(GL_DEPTH_TEST);
    // gl->Enable(GL_BLEND);
    // gl->BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // deltaTime variables
    // -------------------
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float aspect_ratio = 800.0f / 600;
    glm::vec2 cameraPos(0.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(cameraPos, 1.732f), glm::vec3(cameraPos, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), aspect_ratio, 0.1f, 100.0f);
    // ResourceManager::LoadShader(FileSystem::getPath("resources/shaders/particle.vs").c_str(), FileSystem::getPath("resources/shaders/particle.fs").c_str(), nullptr, "particle");
    ResourceManager::LoadShader(FileSystem::getPath("resources/shaders/sprite.vs").c_str(), FileSystem::getPath("resources/shaders/sprite.fs").c_str(), nullptr, "sprite");
    ResourceManager::LoadTexture(FileSystem::getPath("resources/textures/background.jpg").c_str(), false, "background");
    ResourceManager::LoadTexture(FileSystem::getPath("resources/textures/particle.png").c_str(), true, "particle");

    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    ResourceManager::GetShader("sprite").Use().SetMatrix4("view", view);
    // ResourceManager::GetShader("particle").Use().SetMatrix4("view", view);
    Rend = new SpriteRenderer(ResourceManager::GetShader("sprite"));

    b2DebugDraw ddd;
    ddd.drawAABBs = true;
    ddd.drawShapes = true;
    ddd.useDrawingBounds = false;
    ddd.DrawSolidPolygon = DRAWPOLY;
    ddd.DrawString = DRAWSTRING;
    ddd.DrawPolygon = DrawPolygon;
    ddd.DrawCircle = DrawCircle;
    ddd.DrawSegment = DrawSegment;
    ddd.DrawTransform = DrawTransform;
    ddd.DrawPoint = DrawPoint;

    while (!glfwWindowShouldClose(window))
    {
        // calculate delta time
        // --------------------
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        b2World_Step(worldId, deltaTime, 256);
        b2Vec2 position = b2Body_GetPosition(bodyId);
        b2Rot rotation = b2Body_GetRotation(bodyId);
        b2Vec2 velocity = b2Body_GetLinearVelocity(bodyId);
        // printf("t=%4.2f dt=%.6f FPS=%6.0f x(%4.2f %4.2f) v(%4.2f %4.2f)\n", currentFrame, deltaTime, 1.0 / deltaTime, position.x, position.y, velocity.x, velocity.y);

        // render
        // ------
        gl->ClearColor(0.1f, 0.2f, 0.4f * sin(currentFrame), 1.0f);
        gl->Clear(GL_COLOR_BUFFER_BIT);

        // Rend->DrawSprite(ResourceManager::GetTexture("background"), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), 0.0f);
        b2World_Draw(worldId, &ddd);

        glfwSwapBuffers(window);
    }

    // delete all resources as loaded using the resource manager
    // ---------------------------------------------------------
    glfwTerminate();
    return 0;
}